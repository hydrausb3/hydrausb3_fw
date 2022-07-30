/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_hspi.h
* Author             : WCH, bvernoux
* Version            : V1.1
* Date               : 2022/07/30
* Description
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#ifndef __CH56x_HSPI_H__
#define __CH56x_HSPI_H__

#ifdef __cplusplus
 extern "C" {
#endif

/**
  * @brief  HSPI Mode Type
  */
typedef enum
{
    HSPI_HOST = 0, /* HSPI_HOST Send Data */
    HSPI_DEVICE = 1, /* HSPI_DEVICE Receive Data */
}HSPI_ModeTypeDef;

/*******************************************************************************
 * @fn     HSPI_DoubleDMA_Init
 *
 * @brief  HSPI_DoubleDMA_Init mode
 *
 * @param  mode_type -  Operating mode
 *                  HSPI_HOST - Host send data to Device
 *                  HSPI_DEVICE - Device receive data from Host
 *         data_mode -  Data bit width
 *                  RB_HSPI_DAT8_MOD  - 8bits data
 *                  RB_HSPI_DAT16_MOD - 16bits data
 *                  RB_HSPI_DAT32_MOD - 32bits data
 *          DMA0_addr - Depending on mode HOST/TX or DEVICE/RX)
 *                  DMA0 starting address (shall contains up to 4096bytes)
 *          DMA1_addr - Depending on mode TX or RX
 *                  DMA1 starting address (shall contains up to 4096bytes)
 *          DMA_addr_len
 *                  Len in bytes of data to TX(max 4096) can be set to 0 for RX
 *
 * @return   None
 */
void HSPI_DoubleDMA_Init(HSPI_ModeTypeDef mode_type, uint8_t mode_data,
        uint32_t DMA0_addr , uint32_t DMA1_addr,
        uint16_t DMA_addr_len);

/*******************************************************************************
 * @fn     HSPI_INTCfg
 *
 * @brief  HSPI Interrupt configuration
 *
 * @param  s -  Interrupt control state
 *                  ENABLE  - Enable the corresponding interrupt
 *                  DISABLE - Disable the corresponding interrupt
 *         i -  Interrupt type
 *                  RB_HSPI_IE_T_DONE  - Burst Sequence Transmit Complete Interrupt
 *                  RB_HSPI_IE_R_DONE  - Single packet reception completion interrupt
 *                  RB_HSPI_IE_FIFO_OV - Receive FIFO overflow interrupt
 *                  RB_HSPI_IE_B_DONE  - Send completion interrupt
 *
 * @return   None
 */
void HSPI_INTCfg(uint8_t s,  uint8_t i);

/*******************************************************************************
* Function Name  : HSPI_DMA_Tx_CFG
* Description    : Configure DMA transmitting mode
* Input          : DMAaddr: DMA starting address
*                  Tx_len : length of transmitting data once
* Return         : None
*******************************************************************************/
void HSPI_DMA_Tx_CFG(uint32_t DMAaddr, uint32_t Tx_len);

/*******************************************************************************
 * @fn     HSPI_DMA_Tx
 *
 * @brief  HSPI_DMA_Tx Transmit HSPI data (previously configured)
 *
 * @return   None
 */
void HSPI_DMA_Tx(void);

/*******************************************************************************
 * @fn     HSPI_Wait_Txdone
 *
 * @brief  HSPI_Wait_Txdone wait until HSPI data are transmitted
 *
 * @return   None
 */
void HSPI_Wait_Txdone(void);

#ifdef __cplusplus
}
#endif

#endif  // __CH56x_HSPI_H__	
