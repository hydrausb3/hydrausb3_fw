/********************************** (C) COPYRIGHT *******************************
* File Name          : Main.c
* Author             : bvernoux
* Version            : V1.0
* Date               : 2022/07/30
* Description 		 : Basic example to test HSPI communication between 2x HydraUSB3 boards
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include <stdarg.h>
#include "CH56x_common.h"
#include "CH56x_debug_log.h"
#include "CH56x_hydrausb3.h"

#undef FREQ_SYS
/* System clock / MCU frequency(HSPI Frequency) in Hz */
#define FREQ_SYS (120000000)

#if(defined DEBUG) // DEBUG=1 to be defined in pre-processor compiler option
//#define UART1_BAUD (115200)
//#define UART1_BAUD (921600)
//#define UART1_BAUD (3000000) // Real baud rate 3Mbauds(For Fsys 96MHz or 120MHz) => Requires USB2HS Serial like FTDI C232HM-DDHSL-0
#define UART1_BAUD (5000000) // Real baud rate is round to 5Mbauds (For Fsys 120MHz) => Requires USB2HS Serial like FTDI C232HM-DDHSL-0
#endif

//Data size
#define DataSize_8bit  0
#define DataSize_16bit 1
#define DataSize_32bit 2
/* HSPI Data Size Selection 8, 16 or 32bits bus */
//#define Data_Size DataSize_8bit
//#define Data_Size DataSize_16bit
#define Data_Size DataSize_32bit

//DMA_Len
#define DMA_Tx_Len   (512)
#define DMA_Tx_Len0   DMA_Tx_Len
#define DMA_Tx_Len1   DMA_Tx_Len

//DMA_Addr0
#define TX_DMA_Addr0   0x20020000
#define RX_DMA_Addr0   0x20020000

//DMA_Addr1
#define TX_DMA_Addr1   0x20020000 + DMA_Tx_Len0
#define RX_DMA_Addr1   0x20020000 + DMA_Tx_Len1

/* Shared variables */
volatile int Tx_End_Flag; // Send completion flag
volatile int Rx_End_Flag; // Receive completion flag
volatile int Rx_End_Err; // 0=No Error else >0 Error code

/* HSPI_IRQHandler variables */
uint32_t Tx_Cnt = 0;
uint32_t Rx_Cnt = 0;
uint32_t addr_cnt = 0;

/* Blink time in ms */
#define BLINK_ULTRA_FAST  2 // Determine the speed of Packets Sent (It shall be not too fast for the Slave)
/* BLINK_ULTRA_FAST < 2ms do error on HSPI Slave
 * It heavily depends on Master/Slave UART "debug" speed too (if it is too fast => Serial Port have a big impact on speed)
 * */
#define BLINK_SLOW   250
int blink_ms = BLINK_SLOW;

int is_HostBoard; /* Return TRUE or FALSE */

/* Required for CH56x_debug_log.h */
char debug_log_buf[DEBUG_LOG_BUF_SIZE+1];
volatile int debug_log_buf_idx = 0;

void HSPI_IRQHandler (void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main()
{
	uint32_t i;

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
	}else
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
	if(is_HostBoard == FALSE)
	{
		log_printf("HSPI_Tx 2022/07/30 @ChipID=%02X\n", R8_CHIP_ID );
	}else
	{
		log_printf("HSPI_Rx 2022/07/30 @ChipID=%02X\n", R8_CHIP_ID );
	}
	log_printf("FSYS=%d\n", FREQ_SYS);

	if (is_HostBoard ==  FALSE) // HOST TX Mode
	{
		log_printf("HSPI Host Data_Size=%d\n", Data_Size);
		HSPI_DoubleDMA_Init(HSPI_HOST, RB_HSPI_DAT32_MOD, TX_DMA_Addr0, TX_DMA_Addr1, DMA_Tx_Len);

		log_printf("Write RAMX 0x20020000 32K\n");
		// Write RAMX
		for(i = 0; i < 8192; i++) // 8192*4 = 32K
		{
		  *(UINT32*)(0x20020000+i*4) = (i + 0x55555555);
		}

		log_printf("Wait 100us\n"); /* Wait 100us RX is ready before to TX */
		bsp_wait_us_delay(100);

		log_printf("Start Tx 32K data\n");

		ULED_ON();
		HSPI_DMA_Tx();
		ULED_OFF();

		while(Tx_End_Flag == 0);

		log_printf("Tx 32K data suc\r\n");
		log_printf("Wait 20ms before blink loop\n");
		bsp_wait_ms_delay(20);
		while(1)
		{
			if( hydrausb3_ubtn() )
			{
				ULED_ON();

				// Write RAMX
				for(i=0; i<8192; i++) // 8192*4 = 32K
				{
				  *(UINT32*)(0x20020000+i*4) = i + 0x55555555;
				}
				log_printf("Start Tx 32K\n");
				HSPI_DMA_Tx();

				while(Tx_End_Flag == 0);
				log_printf("Tx 32K OK\n");

				blink_ms = BLINK_ULTRA_FAST;
			}
			else
			{
				blink_ms = BLINK_SLOW;
			}
			ULED_ON();
			bsp_wait_ms_delay(blink_ms);
			ULED_OFF();
			bsp_wait_ms_delay(blink_ms);
		}
	} else // DEVICE RX mode
	{
		log_printf("HSPI Dev Data_Size=%d\n", Data_Size);

		log_printf("Clear RAMX 32K\n");
		for(i = 0; i < 8192; i++) // 8192*4 = 32K
		{
		  *(uint32_t*)(0x20020000+i*4) = 0;
		}
		log_printf("DMA_RX_Addr0[0]=0x%08X [8191]=0x%08X\n",
				((uint32_t*)RX_DMA_Addr0)[0], ((uint32_t*)RX_DMA_Addr0)[8191]);

		Rx_End_Flag = 0;  // Receive completion flag
		Rx_End_Err = 0; // 0=No Error else >0 Error code
		HSPI_DoubleDMA_Init(HSPI_DEVICE, RB_HSPI_DAT32_MOD, RX_DMA_Addr0, RX_DMA_Addr1, 0);

		int Rx_Verify_Flag = 0;
		while(1)
		{
			log_printf("Wait Rx\n");
			while(Rx_End_Flag == 0)
			{

			}
			log_printf("Rx_End\n");

			if(Rx_End_Err == 0)
			{
				//verify
				for(i = 0; i < 8192; i++) // 8192*4 = 32K
				{
				  uint32_t val_u32;
				  val_u32 = *(UINT32*)(0x20020000+i*4);
				  if(val_u32 != (i + 0x55555555))
				  {
					Rx_Verify_Flag = 1;
					log_printf("Verify err Rx_End_Err=%d\n", Rx_End_Err);
					log_printf("Err addr=0x%08X val=0x%08X expected val=0x%08X\n",
							(0x20020000+i*4),
							val_u32,
							(i + 0x55555555));
					break;
				  }
				}
			}
			else
			{
				Rx_Verify_Flag = Rx_End_Err;
			}

			if(Rx_Verify_Flag == 0)
			{
				log_printf("Verify suc\n");
				log_printf("DMA_RX_Addr0[0]=0x%08X [8191]=0x%08X\n",
						((uint32_t*)RX_DMA_Addr0)[0], ((uint32_t*)RX_DMA_Addr0)[8191]);
			}
			else
			{ // Error reset Rx_Verify_Flag
				Rx_Verify_Flag = 0;
				log_printf("HSPI_Init\n");
				HSPI_DoubleDMA_Init(HSPI_DEVICE, RB_HSPI_DAT32_MOD, RX_DMA_Addr0, RX_DMA_Addr1, 0);
			}

			log_printf("Clear RAMX 32K\n");
			for(i=0; i<8192; i++) // 8192*4 = 32K
			{
			  *(UINT32*)(0x20020000+i*4) = 0;
			}
			log_printf("DMA_RX_Addr0[0]=0x%08X [8191]=0x%08X\n",
					((uint32_t*)RX_DMA_Addr0)[0], ((uint32_t*)RX_DMA_Addr0)[8191]);

			Rx_End_Err = 0;
			Rx_End_Flag = 0;
		}
	}
}

void HSPI_IRQHandler_ReInitRX(void)
{
	R32_HSPI_RX_ADDR0 = RX_DMA_Addr0;
	R32_HSPI_RX_ADDR1 = RX_DMA_Addr1;
	addr_cnt = 0;
	Rx_Cnt = 0;
}

/*********************************************************************
 * @fn      HSPI_IRQHandler
 *
 * @brief   This function handles HSPI exception.
 *
 * @return  none
 */
void HSPI_IRQHandler(void)
{
	/**************/
	/** Transmit **/
	/**************/
	if(R8_HSPI_INT_FLAG & RB_HSPI_IF_T_DONE) // Single packet sending completed
	{
		ULED_ON();
		R8_HSPI_INT_FLAG = RB_HSPI_IF_T_DONE;  // Clear Interrupt
		if (is_HostBoard ==  FALSE) // HOST TX Mode
		{
			Tx_Cnt++;
			addr_cnt++;

			// log_printf("Tx_Cnt=%d addr_cnt=%d\r\n", Tx_Cnt, addr_cnt);
			if(Tx_Cnt<64) // Send 32K (64*512 bytes)
			{
				if(addr_cnt%2){
					R32_HSPI_TX_ADDR0 += DMA_Tx_Len0*2;
				} else {
					R32_HSPI_TX_ADDR1 += DMA_Tx_Len0*2;
				}
				// bsp_wait_us_delay(1); // Send Data each 1us (to let time to the Device/Receiver to retrieve the packet)
				R8_HSPI_CTRL |= RB_HSPI_SW_ACT;  // Software, trigger to send
			}
			else // Send completed
			{
				R32_HSPI_TX_ADDR0 = TX_DMA_Addr0;
				R32_HSPI_TX_ADDR1 = TX_DMA_Addr1;
				addr_cnt = 0;
				Tx_Cnt = 0;
				Tx_End_Flag = 1;
			}
		}
	}
	/*************/
	/** Receive **/
	/*************/
	if(R8_HSPI_INT_FLAG & RB_HSPI_IF_R_DONE) // Single packet reception completed
	{
		ULED_ON();
	    //log_printf("R8_HSPI_INT_FLAG=0x%02X\n", R8_HSPI_INT_FLAG);
		R8_HSPI_INT_FLAG = RB_HSPI_IF_R_DONE;  // Clear Interrupt

		// The CRC is correct, the received serial number matches (data is received correctly)
		if((R8_HSPI_RTX_STATUS & (RB_HSPI_CRC_ERR|RB_HSPI_NUM_MIS)) == 0)
		{
			Rx_Cnt++;
			addr_cnt++;
			if(Rx_Cnt<64) // Receive 32K (64*512 bytes)
			{
				if(addr_cnt%2)
				{
					R32_HSPI_RX_ADDR0 += 512*2;
				}
				else
				{
					R32_HSPI_RX_ADDR1 += 512*2;
				}
			} else
			{ // Receive completed
				HSPI_IRQHandler_ReInitRX();
				Rx_End_Flag = 1;
			}
		}
		// Determine whether the CRC is correct
		if(R8_HSPI_RTX_STATUS & RB_HSPI_CRC_ERR)
		{  // CRC check err
			// R8_HSPI_CTRL &= ~RB_HSPI_ENABLE;
			log_printf("CRC err\n");
			HSPI_IRQHandler_ReInitRX();
			Rx_End_Err |= 1;
			Rx_End_Flag = 1;
		}
		// Whether the received serial number matches, (does not match, modify the packet serial number)
		if(R8_HSPI_RTX_STATUS & RB_HSPI_NUM_MIS)
		{  // Mismatch
			log_printf("NUM_MIS err\n");
			HSPI_IRQHandler_ReInitRX();
			Rx_End_Err |= 2;
			Rx_End_Flag = 1;
		}
	}
	/*
	if(R8_HSPI_INT_FLAG & RB_HSPI_IF_FIFO_OV)
	{ // FIFO OV
		R8_HSPI_INT_FLAG = RB_HSPI_IF_FIFO_OV; // Clear Interrupt
		log_printf("FIFO OV\n");
		HSPI_IRQHandler_ReInitRX();
		Rx_End_Err |= 4;
		Rx_End_Flag = 1;
	}
	*/
	ULED_OFF();
}
