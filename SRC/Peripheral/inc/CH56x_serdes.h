/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_serdes.h
* Author             : WCH, bvernoux
* Version            : V1.1
* Date               : 2022/07/30
* Description
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#ifndef __SERDES_H__
#define __SERDES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "CH56xSFR.h"
#include "core_riscv.h"

/*
 * SDS->SDS_CTRL
 */
#define SDS_ALIGN_EN	(1<<18) // 0x40000 SDS SATA ALIGN Primitive
#define SDS_CONT_EN		(1<<17) // 0x20000 SDS SATA CONT Primitive
#define SDS_POWR_UP		(1<<16) // 0x10000
#define SDS_TX_PU		(1<<15) // 0x8000
#define SDS_RX_PU		(1<<14) // 0x4000
#define SDS_PLL_PU		(1<<13) // 0x2000

//#define SDS_PLL_DIV   (16<<8) // 60*(DIV+2)MHz
typedef enum _sds_pll_freq
{
	//SDS_PLL_FREQ_1_98G = (31<<8), // 60*(31+2)MHz = 0x1F00 => RX ERR / Data corrupted (Not supported)
	//SDS_PLL_FREQ_1_62G = (25<<8), // 60*(25+2)MHz = 0x1900 => RX ERR (Not supported)
	//SDS_PLL_FREQ_1_56G = (24<<8), // 60*(24+2)MHz = 0x1800 => RX ERR (Not supported)
	//SDS_PLL_FREQ_1_50G = (23<<8), // 60*(23+2)MHz = 0x1700 => RX ERR (Not supported)
	//SDS_PLL_FREQ_1_44G = (22<<8), // 60*(22+2)MHz = 0x1600 => RX ERR (Not supported)
	SDS_PLL_FREQ_1_38G = (21<<8), // 60*(21+2)MHz = 0x1500 (Experimental not officially supported)
	SDS_PLL_FREQ_1_32G = (20<<8), // 60*(20+2)MHz = 0x1400 (Experimental not officially supported)
	SDS_PLL_FREQ_1_26G = (19<<8), // 60*(19+2)MHz = 0x1300 (Experimental not officially supported)
	SDS_PLL_FREQ_1_20G = (18<<8), // 60*(18+2)MHz = 0x1200 => Official SerDes Speed 1.2Gbps
	SDS_PLL_FREQ_1_14G = (17<<8), // 60*(17+2)MHz = 0x1100
	SDS_PLL_FREQ_1_08G = (16<<8), // 60*(16+2)MHz = 0x1000
	SDS_PLL_FREQ_1_02G = (15<<8), // 60*(15+2)MHz = 0xF000
	SDS_PLL_FREQ_960M  = (14<<8), // 60*(14+2)MHz = 0xE000
	SDS_PLL_FREQ_900M  = (13<<8), // 60*(13+2)MHz = 0x0D00
	SDS_PLL_FREQ_600M  = ( 8<<8), // 60*( 8+2)MHz = 0x0800
	SDS_PLL_FREQ_540M  = ( 7<<8), // 60*( 7+2)MHz = 0x0700
	SDS_PLL_FREQ_480M  = ( 6<<8), // 60*( 6+2)MHz = 0x0600
	SDS_PLL_FREQ_420M  = ( 5<<8), // 60*( 5+2)MHz = 0x0500
	SDS_PLL_FREQ_360M  = ( 4<<8), // 60*( 4+2)MHz = 0x0400
	SDS_PLL_FREQ_300M  = ( 3<<8), // 60*( 3+2)MHz = 0x0300
	SDS_PLL_FREQ_240M  = ( 2<<8), // 60*( 2+2)MHz = 0x0200 (Experimental not officially supported)
	SDS_PLL_FREQ_180M  = ( 1<<8)  // 60*( 1+2)MHz = 0x0100 (Experimental not officially supported)
} e_sds_pll_freq;

#define SDS_DMA_EN      (1<<7) // 0x80
#define SDS_TX_EN		(1<<6) // 0x40
#define SDS_RX_EN		(1<<5) // 0x20
#define SDS_RX_POLAR 	(1<<4) // 0x10
#define SDS_INT_BUSY_EN (1<<3) // 0x08
#define PHY_RESET 		(1<<2) // 0x04
#define LINK_RESET 		(1<<1) // 0x02
#define SDS_ALL_CLR 	(1<<0) // 0x01

/*
 * SDS_RTX_CTRL
 */
#define SDS_LINK_INIT	(1<<16) // 0x10000
#define SDS_TX_START	(1<<17) // 0x20000
#define SDS_BUF_MODE	(1<<18) // 0x40000 (Double DMA Buffer Mode)

/*
 * SDS->SDS_INT_EN => SerDes_EnableIT()
 */
#define SDS_PHY_RDY_EN    (1<<0) // 0x01
#define SDS_TX_INT_EN     (1<<1) // 0x02
#define SDS_RX_ERR_EN     (1<<1) // 0x02
#define SDS_RX_INT_EN     (1<<2) // 0x04
#define SDS_FIFO_OV_EN    (1<<3) // 0x08
#define SDS_COMMA_INT_EN  (1<<5) // 0x20 => Seems to do not work Triggered 500us before data ...
#define ALL_INT_TYPE      47   // 0x2F

/*
 * SDS->SDS_STATUS => SerDes_Status() / SerDes_ClearIT()
 */
#define SDS_PHY_RDY_FLG 	(1<<0) // 0x01
#define SDS_TX_INT_FLG		(1<<1) // 0x02
#define SDS_RX_ERR_FLG      (1<<1) // 0x02
#define	SDS_RX_INT_FLG		(1<<2) // 0x04
#define	SDS_FIFO_OV_FLG		(1<<3) // 0x08
#define	SDS_COMMA_INT_FLG	(1<<5) // 0x20
#define ALL_INT_FLG         47   // 0x2F

#define SDS_SEQ_MATCH	(1<<17)
#define SDS_RX_CRC_OK	(1<<18)
#define SDS_PLL_READY	(1<<19)
#define SDS_TX_READY	(1<<20)

#define SDS_RX_BUF		(1<<24) // Not documented/not used
#define SDS_TX_BUF		(1<<28) // Not documented/not used

#define SDS_TX_NUMP_1	(1<<20) // Not documented/not used
#define SDS_TX_NUMP_2	(2<<20) // Not documented/not used
#define SDS_TX_NUMP_3	(3<<20) // Not documented/not used
#define SDS_TX_NUMP_4	(4<<20) // Not documented/not used

/*******************************************************************************
* Function Name  : SerDes_Tx_Init
* Description    : SerDes configuration of hardware in Tx mode
* Input          : SDS_PLL_FREQ see e_sds_pll_freq
* Return         : None
*******************************************************************************/
void SerDes_Tx_Init(e_sds_pll_freq SDS_PLL_FREQ);

/*******************************************************************************
* Function Name  : SerDes_DoubleDMA_Rx_CFG
* Description    : Configure double DMA receiving mode
* Input          : DMA0_addr: DMA0 starting address
                   DMA1_addr: DMA1 starting address
* Return         : None
*******************************************************************************/
void SerDes_DoubleDMA_Rx_CFG(uint32_t DMA0_addr, uint32_t DMA1_addr);

/*******************************************************************************
* Function Name  : SerDes_DMA_Rx_CFG
* Description    : Configure single DMA receiving mode
* Input          : DMA0_addr: DMA0 starting address
* Return         : None
*******************************************************************************/
void SerDes_DMA_Rx_CFG(uint32_t DMA0_addr);

/*******************************************************************************
* Function Name  : SerDes_Rx_Init
* Description    : SerDes configuration of hardware in Rx mode
* Input          : SDS_PLL_FREQ see e_sds_pll_freq
* Return         : None
*******************************************************************************/
void SerDes_Rx_Init(e_sds_pll_freq SDS_PLL_FREQ);

/*******************************************************************************
* Function Name  : SerDes_DMA_Tx_CFG
* Description    : Configure DMA transmitting mode
* Input          : DMAaddr: DMA starting address
*                  Tx_len : length of transmitting data once
*                  custom_number: customized data using for data checking(28bits)
* Return         : None
*******************************************************************************/
void SerDes_DMA_Tx_CFG(uint32_t DMAaddr, uint32_t Tx_len, uint32_t custom_number);

/*******************************************************************************
* Function Name  : SerDes_DMA_Tx
* Description    : DMA start sending data
* Input          : None
* Return         : None
*******************************************************************************/
void SerDes_DMA_Tx(void);

/*******************************************************************************
* Function Name  : SerDes_Wait_Txdone
* Description    : waiting for Tx done
* Input          : None
* Return         : None
*******************************************************************************/
void SerDes_Wait_Txdone(void);

/*******************************************************************************
* Function Name  : SerDes_Wait_commadone
* Description    : waiting for Rx COMMA done
* Input          : None
* Return         : None
*******************************************************************************/
void SerDes_Wait_commadone(void);

/*******************************************************************************
* Function Name  : SerDes_StatusIT
* Description    : SerDes IRQ status
* Input          : None
* Return         : return SerDes IRQ status register value
*******************************************************************************/
/*
For different IT flag see
#define SDS_PHY_RDY_FLG     1<<0 // 1
#define SDS_TX_INT_FLG      1<<1 // 2
#define SDS_RX_INT_FLG      1<<2 // 4
#define SDS_FIFO_OV_FLG     1<<3 // 8
// 1<<4 // 16 TBD
#define SDS_COMMA_INT_FLG   1<<5 // 32 / 0x20
*/
#define SerDes_StatusIT() (SDS->SDS_STATUS)

/*******************************************************************************
* Function Name  : SerDes_EnableIT
* Description    : Enable Interrupt
* Input          : ITType:
                      1.SDS_PHY_RDY_EN
                      2(1).SDS_TX_INT_EN (Tx mode)
                      2(2).SDS_RX_ERR_EN (Rx mode)
                      3.SDS_RX_INT_EN
                      4.SDS_FIFO_OV_EN
                      5.SDS_COMMA_INT_EN
                      6.ALL_INT_TYPE
* Return         : None
*******************************************************************************/
#define SerDes_EnableIT(x) (SDS->SDS_INT_EN = x)

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
#define SerDes_ClearIT(x) (SDS->SDS_STATUS = x)

#ifdef __cplusplus
}
#endif

#endif
