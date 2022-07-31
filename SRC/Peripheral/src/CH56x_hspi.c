/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_hspi.c
* Author             : WCH, bvernoux
* Version            : V1.1
* Date               : 2022/07/30
* Description
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include "CH56x_common.h"

/*******************************************************************************
 * @fn     HSPI_DoubleDMA_Init
 *
 * @brief  HSPI_DoubleDMA_Init mode (Double DMA for RX & TX with toggle Addr0/1)
 *
 * @param  mode_type -  Operating mode
 *                  HSPI_HOST - Host(Up) send data to Device
 *                  HSPI_DEVICE - Device(Down) receive data from Host
 *         data_mode -  Data bit width
 *                  RB_HSPI_DAT8_MOD  - 8bits data
 *                  RB_HSPI_DAT16_MOD - 16bits data
 *                  RB_HSPI_DAT32_MOD - 32bits data
 *          DMA0_addr - Depending on mode HOST/TX or DEVICE/RX)
 *                  DMA0 starting address (shall be sized to contains up to 4096 bytes)
 *          DMA1_addr - Depending on mode TX or RX
 *                  DMA1 starting address (shall be sized to contains up to 4096 bytes)
 *          DMA_addr_len
 *                  Len in bytes of data to TX(max 4096) can be set to 0 for RX
 *
 * @return   None
 */
void HSPI_DoubleDMA_Init(HSPI_ModeTypeDef mode_type, uint8_t mode_data,
						 uint32_t DMA0_addr, uint32_t DMA1_addr,
						 uint16_t DMA_addr_len)
{
	/* HSPI GPIO configuration */
	// TX GPIO PA9/PA11/PA21 Push-pull output
	R32_PA_DIR |= (1<<9) | (1<<11) | (1<<21);
	// clk 16mA
	R32_PA_DRV |= (1<<11);
	// RX GPIO PA10 Push-pull output
	R32_PA_DIR |= (1<<10);
	bsp_wait_us_delay(1); /* Wait "GPIO stabilization" mandatory before HSPI configuration to avoid potential CRC error */

	R8_HSPI_CFG &= ~(RB_HSPI_MODE | RB_HSPI_MSK_SIZE); // Clear HSPI Configuration
	if (mode_type == HSPI_HOST)
	{
		R8_HSPI_CFG |= RB_HSPI_MODE; // Host
	}
	else
	{
		R8_HSPI_CFG &= ~(RB_HSPI_MODE); // Device
	}
	// Data size (8/16 or 32bits)
	R8_HSPI_CFG |= mode_data;

	// ACk mode 0 (Hardware auto-answer mode is used in burst mode, not in normal mode)
	R8_HSPI_CFG &= ~RB_HSPI_HW_ACK;

	if (mode_type == HSPI_HOST)
	{
		R8_HSPI_CFG |= RB_HSPI_TX_TOG_EN;
	}
	else
	{
		// HSPI_DEVICE
		R8_HSPI_CFG |= RB_HSPI_RX_TOG_EN;
	}

	// DUDMA 1 Enable dual DMA function Default enabled
	R8_HSPI_CFG |= RB_HSPI_DUALDMA;

	// Enable fast DMA request
	R8_HSPI_AUX |= RB_HSPI_REQ_FT;

	// TX sampling edge
	R8_HSPI_AUX |= RB_HSPI_TCK_MOD; // falling edge sampling

	// Hardware Auto ack time disabled
	R8_HSPI_AUX &= ~RB_HSPI_ACK_TX_MOD;

	// Delay time
	R8_HSPI_AUX &= ~RB_HSPI_ACK_CNT_SEL; //  Delay 2T

	//clear ALL_CLR  TRX_RST  (reset)
	R8_HSPI_CTRL &= ~(RB_HSPI_ALL_CLR|RB_HSPI_TRX_RST);

	//Enable Interrupt
	if (mode_type == HSPI_HOST)
	{
		R8_HSPI_INT_EN |= RB_HSPI_IE_T_DONE;  // Single packet sending completed
		R8_HSPI_INT_EN |= RB_HSPI_IE_FIFO_OV;
	}
	else
	{
		// HSPI_DEVICE
		R8_HSPI_INT_EN |= RB_HSPI_IE_R_DONE;  // Single packet reception completed
		R8_HSPI_INT_EN |= RB_HSPI_IE_FIFO_OV;
	}
	// Config TX customized Header
	R32_HSPI_UDF0 = 0x3ABCDEF; // UDF0
	R32_HSPI_UDF1 = 0x3456789; // UDF1

	// addr0 DMA TX RX addr
	R32_HSPI_TX_ADDR0 = DMA0_addr;
	R32_HSPI_RX_ADDR0 = DMA0_addr;
	// addr1 DMA TX RX addr
	R32_HSPI_TX_ADDR1 = DMA1_addr;
	R32_HSPI_RX_ADDR1 = DMA1_addr;

	// addr0 TX DMA len
	R16_HSPI_DMA_LEN0 = DMA_addr_len - 1;
	// addr1 TX DMA len
	R16_HSPI_DMA_LEN1 = DMA_addr_len - 1;

	// addr0 RX DMA len
	R16_HSPI_RX_LEN0 = 0; // 0 means max size 4096 bytes
	// addr1 RX DMA len
	R16_HSPI_RX_LEN1 = 0; // 0 means max size 4096 bytes

	// Burst Disabled
	R16_HSPI_BURST_CFG = 0x0000;

	//Enable HSPI DMA
	R8_HSPI_CTRL |= RB_HSPI_ENABLE | RB_HSPI_DMA_EN;

	PFIC_EnableIRQ(HSPI_IRQn);
}

/*******************************************************************************
 * @fn     HSPI_INTCfg
 *
 * @brief  HSPI Interrupt configuration
 *
 * @param  s -  Interrupt control state
 *					ENABLE  - Enable the corresponding interrupt
 *					DISABLE - Disable the corresponding interrupt
 *		   i -  Interrupt type
 *					RB_HSPI_IE_T_DONE  - Burst Sequence Transmit Complete Interrupt
 *					RB_HSPI_IE_R_DONE  - Single packet reception completion interrupt
 *					RB_HSPI_IE_FIFO_OV - Receive FIFO overflow interrupt
 *				    RB_HSPI_IE_B_DONE  - Send completion interrupt
 *
 * @return   None
 */
void HSPI_INTCfg(uint8_t s,  uint8_t i )
{
	if(s)
	{
		R8_HSPI_INT_EN |= i;
	}
	else
	{
		R8_HSPI_INT_EN &= ~i;
	}
}

/*******************************************************************************
* Function Name  : HSPI_DMA_Tx_CFG
* Description    : Configure DMA transmitting mode
* Input          : DMAaddr: DMA starting address
*                  Tx_len : length of transmitting data once
* Return         : None
*******************************************************************************/
void HSPI_DMA_Tx_CFG(uint32_t DMAaddr, uint32_t Tx_len)
{
	uint8_t hspi_int_status;
	do
	{
		hspi_int_status = R8_HSPI_INT_FLAG;
	}
	while ( !(hspi_int_status & RB_HSPI_IF_T_DONE) );
	R8_HSPI_INT_FLAG = RB_HSPI_IF_T_DONE; // Clear Interrupt

	// addr0 DMA TX RX addr
	R32_HSPI_TX_ADDR0 = DMAaddr;
	// addr0 DMA len TX
	R16_HSPI_DMA_LEN0 = Tx_len - 1;
}

/*******************************************************************************
 * @fn     HSPI_DMA_Tx
 *
 * @brief  HSPI_DMA_Tx Transmit HSPI data (previously configured)
 *
 * @return   None
 */
void HSPI_DMA_Tx(void)
{
	R8_HSPI_INT_FLAG = 0xF; // Clear all HSPI flags to 0 before sending
	R8_HSPI_CTRL |= RB_HSPI_SW_ACT; // Software, trigger to send
}

/*******************************************************************************
 * @fn     HSPI_Wait_Txdone
 *
 * @brief  HSPI_Wait_Txdone wait until HSPI data are transmitted
 *
 * @return   None
 */
void HSPI_Wait_Txdone(void)
{
	uint8_t hspi_int_status;
	do
	{
		hspi_int_status = R8_HSPI_INT_FLAG;
	}
	while(!(hspi_int_status & RB_HSPI_IF_T_DONE));
	R8_HSPI_INT_FLAG = RB_HSPI_IF_T_DONE; // Clear Interrupt
}
