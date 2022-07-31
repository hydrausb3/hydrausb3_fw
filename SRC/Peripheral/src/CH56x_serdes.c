/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_serdes.c
* Author             : bvernoux
* Version            : V1.1
* Date               : 2022/07/30
* Description        : This file contains all the functions prototypes for SerDes
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include "CH56x_common.h"
#include "CH56x_debug_log.h"

/*******************************************************************************
* Function Name  : SerDes_Tx_Init
* Description    : SerDes configuration of hardware in Tx mode
* Input          : SDS_PLL_FREQ see e_sds_pll_freq
* Return         : None
*******************************************************************************/
void SerDes_Tx_Init(e_sds_pll_freq SDS_PLL_FREQ)
{
	uint32_t sds_status;

	R8_SAFE_ACCESS_SIG = 0x57; // enable safe access mode
	R8_SAFE_ACCESS_SIG = 0xa8;
	R16_SERD_ANA_CFG1 = 0x5a;
	R32_SERD_ANA_CFG2 = 0x00423015; // This value is not documented
	/* R32_SERD_ANA_CFG2
	 * [24:0] RB_SERD_TRX_CFG (Undocumented)
	 * Receive/transmit parameter configuration of SerDes PHY.
	 */

	SDS->SDS_CTRL = (PHY_RESET | LINK_RESET | SDS_ALL_CLR); // Init all required to change in live from TX/RX...
	SDS->SDS_CTRL = (SDS_POWR_UP |
					 SDS_TX_PU | SDS_RX_PU |
					 SDS_PLL_PU | SDS_PLL_FREQ |
					 LINK_RESET | SDS_ALL_CLR);
	do
	{
		sds_status = SDS->SDS_STATUS;
	}
	while ( !(sds_status & SDS_PLL_READY) );

	bsp_wait_us_delay(1);

	SDS->SDS_CTRL = (SDS_POWR_UP |
					 SDS_TX_PU | SDS_RX_PU |
					 SDS_PLL_PU | SDS_PLL_FREQ |
					 SDS_INT_BUSY_EN |
					 SDS_DMA_EN |
					 SDS_TX_EN |
					 SDS_ALIGN_EN |
					 SDS_CONT_EN);

	SDS->SDS_RTX_CTRL = SDS_LINK_INIT;
	bsp_wait_us_delay(1);

	SDS->SDS_RTX_CTRL = 0;
	do
	{
		sds_status = SDS->SDS_STATUS;
	}
	while(!(sds_status & SDS_TX_READY));
}

/*******************************************************************************
* Function Name  : SerDes_Rx_Init
* Description    : SerDes configuration of hardware in Rx mode
* Input          : SDS_PLL_FREQ see e_sds_pll_freq
* Return         : None
*******************************************************************************/
void SerDes_Rx_Init(e_sds_pll_freq SDS_PLL_FREQ)
{
	uint32_t sds_status;

	R8_SAFE_ACCESS_SIG = 0x57; // enable safe access mode
	R8_SAFE_ACCESS_SIG = 0xa8;
	R16_SERD_ANA_CFG1 = 0x5a;
	R32_SERD_ANA_CFG2 = 0x00423015;

	SDS->SDS_CTRL = (PHY_RESET | LINK_RESET | SDS_ALL_CLR);
	bsp_wait_us_delay(1);

	/* R32_SERD_ANA_CFG2
	 * [24:0] RB_SERD_TRX_CFG
	 * Receive/transmit parameter configuration of SerDes PHY.
	 */
	SDS->SDS_CTRL = (SDS_POWR_UP |
					 SDS_TX_PU | SDS_RX_PU |
					 SDS_PLL_PU | SDS_PLL_FREQ |
					 LINK_RESET | SDS_ALL_CLR);

	/* Wait until SDS PLL is ready */
	do
	{
		sds_status = SDS->SDS_STATUS;
	}
	while(!(sds_status & SDS_PLL_READY));

	bsp_wait_us_delay(1);

	SDS->SDS_CTRL = (SDS_POWR_UP |
					 SDS_TX_PU | SDS_RX_PU |
					 SDS_PLL_PU | SDS_PLL_FREQ |
					 SDS_DMA_EN | SDS_RX_EN);
}

/*******************************************************************************
* Function Name  : SerDes_DMA_Tx_CFG
* Description    : Wait TX Ready and Configure DMA transmitting mode
* Input          : DMAaddr: DMA starting address
*                  Tx_len : length of transmitting data once
*                  custom_number: customized data using for data checking(28bits)
* Return         : None
*******************************************************************************/
void SerDes_DMA_Tx_CFG(uint32_t DMAaddr, uint32_t Tx_len, uint32_t custom_number)
{
	uint32_t sds_status;
	do
	{
		sds_status = SDS->SDS_STATUS;
	}
	while(!(sds_status & SDS_TX_READY));

	SDS->SDS_DMA0 = DMAaddr;
	SDS->SDS_RTX_CTRL = Tx_len;
	SDS->SDS_DATA0 = custom_number;
}

/*******************************************************************************
* Function Name  : SerDes_DMA_Tx
* Description    : Wait TX Ready and DMA start sending data
* Input          : None
* Return         : None
*******************************************************************************/
void SerDes_DMA_Tx(void)
{
	uint32_t sds_status;
	do
	{
		sds_status = SDS->SDS_STATUS;
	}
	while(!(sds_status & SDS_TX_READY));

	SDS->SDS_RTX_CTRL |= SDS_TX_START;
}

/*******************************************************************************
* Function Name  : SerDes_Wait_Txdone
* Description    : Waiting for Tx done
* Input          : None
* Return         : None
*******************************************************************************/
void SerDes_Wait_Txdone(void)
{
	uint32_t sds_status;
	uint32_t sds_rtx_ctrl;

	do
	{
		sds_status = SDS->SDS_STATUS;
	}
	while((sds_status & SDS_TX_INT_FLG) == 0);

	SDS->SDS_RTX_CTRL &= ~SDS_TX_START;
	do
	{
		sds_rtx_ctrl = SDS->SDS_RTX_CTRL;
	}
	while(sds_rtx_ctrl & SDS_TX_START);

	/* Clear TX Interrupt Flag */
	SDS->SDS_STATUS = SDS_TX_INT_FLG;
}

/*******************************************************************************
* Function Name  : SerDes_Wait_commadone
* Description    : waiting for Rx COMMA done
* Input          : None
* Return         : None
*******************************************************************************/
void SerDes_Wait_commadone(void)
{
	uint32_t sds_status;

	do
	{
		sds_status = SDS->SDS_STATUS;
	}
	while((sds_status & SDS_COMMA_INT_FLG) == 0);
	SDS->SDS_STATUS = SDS_COMMA_INT_FLG;
}

/*******************************************************************************
* Function Name  : SerDes_DoubleDMA_Rx_CFG
* Description    : Configure double DMA receiving mode
* Input          : DMA0_addr: DMA0 starting address
				   DMA1_addr: DMA1 starting address
* Return         : None
*******************************************************************************/
void SerDes_DoubleDMA_Rx_CFG(uint32_t DMA0_addr,uint32_t DMA1_addr)
{
	SDS->SDS_DMA0 = DMA0_addr;
	SDS->SDS_DMA1 = DMA1_addr;
	SDS->SDS_RTX_CTRL = SDS_BUF_MODE;
}

/*******************************************************************************
* Function Name  : SerDes_DMA_Rx_CFG
* Description    : Configure single DMA receiving mode
* Input          : DMA0_addr: DMA0 starting address
* Return         : None
*******************************************************************************/
void SerDes_DMA_Rx_CFG(uint32_t DMA0_addr)
{
	SDS->SDS_DMA0 = DMA0_addr;
	SDS->SDS_RTX_CTRL = 0;
}

/*******************************************************************************
* Function Name  : SerDes_StatusIT
* Description    : SerDes IRQ status
* Input          : None
* Return         : return SerDes IRQ status register value
*******************************************************************************/
// See definition/macro in CH56x_serdes.h
/*
inline uint32_t SerDes_StatusIT(void)
{
	return (SDS->SDS_STATUS);
}
*/

/*******************************************************************************
* Function Name  : SerDes_ClearIT
* Description    : Clear interruption flag
* Input          : ITFlag:
					  1.SDS_PHY_RDY_FLG
					  2.SDS_TX_INT_FLG
					  3.SDS_RX_INT_FLG
					  4.SDS_FIFO_OV_FLG
					  5.SDS_COMMA_INT_FLG
					  6.ALL_INT_FLG
* Return         : None
*******************************************************************************/
// See definition/macro in CH56x_serdes.h
/*
void SerDes_ClearIT(uint16_t serdes_IT_flag)
{
	SDS->SDS_STATUS = serdes_IT_flag;
}
*/
/*******************************************************************************
* Function Name  : SerDes_EnableIT
* Description    : Enable Interrupt
* Input          : ITType:
					  1.SDS_PHY_RDY_EN
					  2(1).SDS_TX_INT_EN      (Tx mode)
					  2(2).SDS_RX_ERR_EN      (Rx mode)
					  3.SDS_RX_INT_EN
					  4.SDS_FIFO_OV_EN
					  5.SDS_COMMA_INT_EN
					  6.ALL_INT_TYPE
* Return         : None
*******************************************************************************/
// See definition/macro in CH56x_serdes.h
/*
void SerDes_EnableIT(uint16_t ITType)
{
	SDS->SDS_INT_EN = ITType;
}
*/
