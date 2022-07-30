/********************************** (C) COPYRIGHT *******************************
* File Name          : Main.c
* Author             : bvernoux
* Version            : V1.0
* Date               : 2022/07/30
* Description 		 : Basic example to test SerDes communication between 2x HydraUSB3 boards
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include "CH56x_common.h"
#include "CH56x_hydrausb3.h"
#include "CH56x_debug_log.h"

#undef FREQ_SYS
/* System clock / MCU frequency in Hz */
#define FREQ_SYS (120000000)

#if(defined DEBUG) // DEBUG=1 to be defined in C Compiler Prepocessor defined symbols
//#define UART1_BAUD (115200)
//#define UART1_BAUD (921600)
//#define UART1_BAUD (3000000) // Real baud rate 3Mbauds(For Fsys 96MHz or 120MHz) => Requires USB2HS Serial like FTDI C232HM-DDHSL-0
#define UART1_BAUD (5000000) // Real baud rate is round to 5Mbauds (For Fsys 120MHz) => Requires USB2HS Serial like FTDI C232HM-DDHSL-0
#endif

// Use 64bits SysTick counter (by default use 32bits SysTick counter if not defined)
//#define CNT_64BITS (1)

//#define SERDES_TX_RX_SPEED (SDS_PLL_FREQ_180M)
//#define SERDES_TX_RX_SPEED (SDS_PLL_FREQ_600M)
//#define SERDES_TX_RX_SPEED (SDS_PLL_FREQ_1_08G)
#define SERDES_TX_RX_SPEED (SDS_PLL_FREQ_1_20G )

//#define SERDES_CUSTOM_NUMBER (0x05555555) // Max 28bits
#define SERDES_CUSTOM_NUMBER (0x0FFFFFFF) // Max 28bits

__attribute__((aligned(16))) uint8_t RX_DMA0buff[4096] __attribute__((section(".DMADATA")));
__attribute__((aligned(16))) uint8_t RX_DMA1buff[4096] __attribute__((section(".DMADATA")));
__attribute__((aligned(16))) uint8_t TX_DMAbuff[4096] __attribute__((section(".DMADATA")));

uint32_t RX_DMA0_addr = (uint32_t)RX_DMA0buff;
uint32_t RX_DMA1_addr = (uint32_t)RX_DMA1buff;
uint32_t TX_DMA_addr = (uint32_t)TX_DMAbuff;

volatile uint32_t RX_LEN0=0, RX_LEN1=0;
volatile uint32_t SDS_RX_LEN0=0, SDS_RX_LEN1=0, SDS_RTX_CTRL=0;

volatile uint32_t SDS_RX_ERR=0;
volatile uint32_t SDS_FIFO_OV=0;
volatile uint32_t SDS_STATUS[2];

volatile uint32_t i=0;
volatile uint32_t k=0;

int is_HostBoard; /* Return TRUE or FALSE */

#ifdef CNT_64BITS
uint64_t CNT_S;
uint64_t CNT_E;
#else
uint32_t CNT_S;
uint32_t CNT_E;
#endif
uint32_t CNT_nb_cycles;

int is_HostBoard; /* Return TRUE or FALSE */

/* Required for CH56x_debug_log.h */
char debug_log_buf[DEBUG_LOG_BUF_SIZE+1];
volatile int debug_log_buf_idx = 0;

void SERDES_IRQHandler (void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
int main()
{
	uint32_t *p32_txdma = (uint32_t *)TX_DMA_addr;

	/* Configure GPIO In/Out default/safe state for HydraUSB3 */
	hydrausb3_gpio_init();
	/* Init BSP (MCU Frequency & SysTick) */
	bsp_init(FREQ_SYS);
	log_init();
	/* Configure serial debugging for printf()/log_printf()... */
	UART1_init(UART1_BAUD, FREQ_SYS);
	printf("\n");

	/******************************************/
	/* Start Synchronization between 2 Boards */
	/* J3 MOSI(PA14) & J3 SCS(PA12) signals   */
	/******************************************/
	if(hydrausb3_pb24() == 0)
	{
		is_HostBoard = TRUE;
		i = hydrausb3_sync2boards(PA14, PA12, HYDRAUSB3_HOST);
	}
	else
	{
		is_HostBoard = FALSE;
		i = hydrausb3_sync2boards(PA14, PA12, HYDRAUSB3_DEVICE);
	}
	log_printf("SYNC %08d\n", i);
	log_time_reinit(); // Reinit log time after synchro
	/* Test Synchronization to be checked with Oscilloscope/LA */
	ULED_ON();
	ULED_OFF();
	/****************************************/
	/* End Synchronization between 2 Boards */
	/****************************************/

	log_printf("Start\n");
	if(hydrausb3_pb24() == 0)
	{
		is_HostBoard = TRUE;
		log_printf("SerDes_Rx 2022/07/30 start @ChipID=%02X (CPU Freq=%d MHz)\n", R8_CHIP_ID, (FREQ_SYS/1000000));
	}
	else
	{
		is_HostBoard = FALSE;
		log_printf("SerDes_Tx 2022/07/30 start @ChipID=%02X (CPU Freq=%d MHz)\n", R8_CHIP_ID, (FREQ_SYS/1000000));
	}

	if(is_HostBoard == FALSE) // SerDes TX
	{
		uint32_t data=0;
		int n;
		log_printf("TX_DMA_addr=0x%08X\n", TX_DMA_addr);
		log_printf("SerDes_Tx_Init(SERDES_TX_RX_SPEED=0x%04X) Before\n", SERDES_TX_RX_SPEED);
		SerDes_Tx_Init(SERDES_TX_RX_SPEED);
		log_printf("SerDes_Tx_Init() After\n");
		n=0;
		do
		{
			*p32_txdma++ = data;
			data += 0x01010101;
			n++;
		}while(n!=(2048/4));

		log_printf("Wait 100us\n"); /* Wait 100us RX is ready before to TX */
		bsp_wait_us_delay(100);

		int state=0;
		while(1)
		{
			p32_txdma = (uint32_t *)TX_DMA_addr;
			n=0;
			switch(state)
			{
				case 0:
				{
					data = 0x5A5A5A5A;
					*p32_txdma = data;
					SerDes_DMA_Tx_CFG(TX_DMA_addr,4,SERDES_CUSTOM_NUMBER);
					state = 1;
				}
				break;
				case 1:
				{
					data = 0xAAAA5555;
					do
					{
						*p32_txdma++ = data;
						n++;
					}while(n!=(8/4));
					SerDes_DMA_Tx_CFG(TX_DMA_addr,8,SERDES_CUSTOM_NUMBER);
					state = 2;
				}
				break;
				case 2:
				{
					data = 0x11111111;
					do
					{
						*p32_txdma++ = data;
						n++;
					}while(n!=(16/4));
					SerDes_DMA_Tx_CFG(TX_DMA_addr,16,SERDES_CUSTOM_NUMBER);
					state = 3;
				}
				break;
				case 3:
				{
					data = 0x22222222;
					do
					{
						*p32_txdma++ = data;
						n++;
					}while(n!=(64/4));
					SerDes_DMA_Tx_CFG(TX_DMA_addr,64,SERDES_CUSTOM_NUMBER);
					state = 4;
				}
				break;
				case 4:
				{
					data = 0x33333333;
					do
					{
						*p32_txdma++ = data;
						n++;
					}while(n!=(128/4));
					SerDes_DMA_Tx_CFG(TX_DMA_addr,128,SERDES_CUSTOM_NUMBER);
					state = 5;
				}
				break;
				case 5:
				{
					data = 0x44444444;
					do
					{
						*p32_txdma++ = data;
						n++;
					}while(n!=(512/4));
					SerDes_DMA_Tx_CFG(TX_DMA_addr,512,SERDES_CUSTOM_NUMBER);
					state = 6;
				}
				break;
				case 6:
				{
					data = 0x55555555;
					do
					{
						*p32_txdma++ = data;
						n++;
					}while(n!=(576/4));
					SerDes_DMA_Tx_CFG(TX_DMA_addr,576,SERDES_CUSTOM_NUMBER);
					state = 7;
				}
				break;
				case 7:
				{
					data = 0x66666666;
					do
					{
						*p32_txdma++ = data;
						n++;
					}while(n!=(1024/4));
					SerDes_DMA_Tx_CFG(TX_DMA_addr,1024,SERDES_CUSTOM_NUMBER);
					state = 8;
				}
				break;
				case 8:
				{
					data = 0x77777777;
					do
					{
						*p32_txdma++ = data;
						n++;
					}while(n!=(2048/4));
					SerDes_DMA_Tx_CFG(TX_DMA_addr,2048,SERDES_CUSTOM_NUMBER);
					state = 9;
				}
				break;
				case 9:
				{
					data = 0;
					do
					{
						*p32_txdma++ = data;
						data += 0x01010101;
						n++;
					}while(n!=(2048/4));
					SerDes_DMA_Tx_CFG(TX_DMA_addr,2048,SERDES_CUSTOM_NUMBER);
					state = 10;
				}
				break;
				case 10:
				{
					do
					{
						*p32_txdma++ = data;
						data += 0x10101010;
						n++;
					}while(n!=(2048/4));
					SerDes_DMA_Tx_CFG(TX_DMA_addr,2048,SERDES_CUSTOM_NUMBER);
					state = 11;
				}
				break;
				case 11:
				{
					do
					{
						*p32_txdma++ = data;
						data += 0x10101010;
						n++;
					}while(n!=(4096/4));
					SerDes_DMA_Tx_CFG(TX_DMA_addr,4096,SERDES_CUSTOM_NUMBER);
					state = 12;
				}
				break;
				case 12:
				{
					do
					{
						*p32_txdma++ = data;
						data += 0x10101010;
						n++;
					}while(n!=(4096/4));
					SerDes_DMA_Tx_CFG(TX_DMA_addr,4096,SERDES_CUSTOM_NUMBER);
					state = 0;
				}
				break;

				default:
					state = 0;
					break;
			}
			/* Send same data 2 times to test the Double DMA RX mechanism */
			ULED_ON();
			SerDes_DMA_Tx();
			SerDes_Wait_Txdone();
			ULED_OFF();

			ULED_ON();
			SerDes_DMA_Tx();
			SerDes_Wait_Txdone();
			ULED_OFF();

			if(hydrausb3_ubtn()) // Send data in burst continuously
			{
				p32_txdma = (uint32_t *)TX_DMA_addr;
				n=0;
				data = 0;
				do
				{
					*p32_txdma++ = data;
					data += 0x10101010;
					n++;
				}while(n!=(4096/4));
				SerDes_DMA_Tx_CFG(TX_DMA_addr,4096,SERDES_CUSTOM_NUMBER);

				while(hydrausb3_ubtn())
				{
					ULED_ON();
					SerDes_DMA_Tx();
					SerDes_Wait_Txdone();
					ULED_OFF();

					ULED_ON();
					SerDes_DMA_Tx();
					SerDes_Wait_Txdone();
					ULED_OFF();

					bsp_wait_us_delay(100); /* Wait 100us (about 80us to transmit 2x*4096bytes @1.2Gbps) */
				}
			}
			bsp_wait_ms_delay(2000);
		} // loop while(1)
	}else  // SerDes RX
	{
		PFIC_EnableIRQ(INT_ID_SERDES);

		log_printf("SerDes_DoubleDMA_Rx_CFG() Before\n");
		log_printf("RX_DMA0_addr=0x%08X RX_DMA1_addr=0x%08X\n", RX_DMA0_addr, RX_DMA1_addr);
		SerDes_DoubleDMA_Rx_CFG(RX_DMA0_addr ,RX_DMA1_addr);
		log_printf("SerDes_DoubleDMA_Rx_CFG() After\n");

		log_printf("SerDes_Rx_Init(SERDES_TX_RX_SPEED=0x%04X) Before\n", SERDES_TX_RX_SPEED);
		SerDes_Rx_Init(SERDES_TX_RX_SPEED);
		log_printf("SerDes_Rx_Init() After\n");

		log_printf("SerDes_EnableIT(SDS_RX_INT_EN|SDS_RX_ERR_EN|SDS_FIFO_OV_EN) Before\n");
		SerDes_EnableIT(SDS_RX_INT_EN|SDS_RX_ERR_EN|SDS_FIFO_OV_EN);
		log_printf("SerDes_EnableIT(SDS_RX_INT_EN|SDS_RX_ERR_EN|SDS_FIFO_OV_EN) After\n");

		SerDes_ClearIT(ALL_INT_TYPE);

		while(1)
		{
			if(k==2)
			{
				int RX_CRC_OK = 0;
				k=0;
				CNT_nb_cycles = (CNT_S - CNT_E);
				SDS_RX_LEN0 = SDS->SDS_RX_LEN0;
				SDS_RX_LEN1 = SDS->SDS_RX_LEN1;
				if( (SDS_STATUS[0] & SDS_RX_CRC_OK) &&
					(SDS_STATUS[1] & SDS_RX_CRC_OK))
				{
					RX_CRC_OK = 1;
				}
				log_printf("SDS_RX_LEN0=%d SDS_RX_LEN1=%d CNT_nb_cycles=%d(%dus)\n", SDS_RX_LEN0, SDS_RX_LEN1, CNT_nb_cycles, (CNT_nb_cycles/bsp_get_nbtick_1us()) );
				log_printf("SDS_STATUS[0]=0x%08X SDS_STATUS[1]=0x%08X SDS_DATA0=0x%08X SDS_DATA1=0x%08X\n", SDS_STATUS[0], SDS_STATUS[1], SDS->SDS_DATA0, SDS->SDS_DATA1);
				log_printf("SDS_RX_ERR=%d SDS_FIFO_OV=%d RX_CRC_OK=%d\n", SDS_RX_ERR, SDS_FIFO_OV, RX_CRC_OK);

				uint32_t *d;
				if (SDS_RX_LEN0 <= 4)
				{
					d = (uint32_t *)(RX_DMA0_addr);
					log_printf("%08X\n",
							d[0], d[1]);
					d = (uint32_t *)(RX_DMA1_addr);
					log_printf("%08X\n",
							d[0], d[1]);
				}else if (SDS_RX_LEN0 <= 8)
				{
					d = (uint32_t *)(RX_DMA0_addr);
					log_printf("%08X %08X\n",
							d[0], d[1]);
					d = (uint32_t *)(RX_DMA1_addr);
					log_printf("%08X %08X\n",
							d[0], d[1]);
				}else if (SDS_RX_LEN0 <= 16)
				{
					d = (uint32_t *)(RX_DMA0_addr);
					log_printf("%08X %08X %08X %08X\n",
							d[0], d[1], d[2], d[3]);
					d = (uint32_t *)(RX_DMA1_addr);
					log_printf("%08X %08X %08X %08X\n",
							d[0], d[1], d[2], d[3]);
				}
				else
				{
					for(i=0; i<(SDS_RX_LEN0/4); i+=16)
					{
						d = (uint32_t *)(RX_DMA0_addr+4*i);
						log_printf("%08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X\n",
								d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7],
								d[8], d[9], d[10], d[11], d[12], d[13], d[14], d[15]);
						d = (uint32_t *)(RX_DMA1_addr+4*i);
						log_printf("%08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X %08X\n",
								d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7],
								d[8], d[9], d[10], d[11], d[12], d[13], d[14], d[15]);
					}
				}
			}
		}
	}

}
/*******************************************************************************
* Function Name  : SERDES_IRQHandler
* Description    : Interruption function
* Input          : None
* Return         : None
*******************************************************************************/
void SERDES_IRQHandler (void)
{
	uint32_t sds_it_status;
	sds_it_status = SerDes_StatusIT();
	if(sds_it_status & SDS_RX_INT_FLG)
	{
		if(k == 0)
		{
#ifdef CNT_64BITS
			CNT_S = bsp_get_SysTickCNT();
#else
			CNT_S = bsp_get_SysTickCNT_LSB();
#endif
			SDS_STATUS[0] = sds_it_status;
		}else if(k == 1)
		{
#ifdef CNT_64BITS
			CNT_E = bsp_get_SysTickCNT();
#else
			CNT_E = bsp_get_SysTickCNT_LSB();
#endif
			SDS_STATUS[1] = sds_it_status;
		}
		ULED_ON();
		k++;
		SerDes_ClearIT(SDS_RX_INT_FLG|SDS_COMMA_INT_FLG);
		ULED_OFF();
	}
	if(sds_it_status & SDS_RX_ERR_FLG)
	{
		ULED_ON();
		SDS_RX_ERR++;
		SerDes_ClearIT(SDS_RX_ERR_FLG);
		ULED_OFF();
	}
	if(sds_it_status & SDS_FIFO_OV_FLG)
	{
		ULED_ON();
		SDS_FIFO_OV++;
		SerDes_ClearIT(SDS_FIFO_OV_FLG);
		ULED_OFF();
	}
}
