/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_dvp.c
* Author             : WCH, bvernoux
* Version            : V1.1
* Date               : 2022/08/07
* Description
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#ifndef __CH56x_DVP_H__
#define __CH56x_DVP_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  DVP Data Mode
  */
typedef enum
{
	Video_Mode = 0,
	JPEG_Mode,
} DVP_Data_ModeTypeDef;

/**
  * @brief  DVP DMA
  */
typedef enum
{
	DVP_DMA_Disable = 0,
	DVP_DMA_Enable,
} DVP_DMATypeDef;

/**
  * @brief  DVP FLAG and FIFO Reset
  */
typedef enum
{
	DVP_FLAG_FIFO_RESET_Disable = 0,
	DVP_FLAG_FIFO_RESET_Enable,
} DVP_FLAG_FIFO_RESETTypeDef;

/**
  * @brief  DVP RX Reset
  */
typedef enum
{
	DVP_RX_RESET_Disable = 0,
	DVP_RX_RESET_Enable,
} DVP_RX_RESETTypeDef;

void DVP_INTCfg( uint8_t s,  uint8_t i );
void DVP_Mode( uint8_t s,  DVP_Data_ModeTypeDef i);
void DVP_Cfg( DVP_DMATypeDef s,  DVP_FLAG_FIFO_RESETTypeDef i, DVP_RX_RESETTypeDef j);

#ifdef __cplusplus
}
#endif

#endif  // __CH56x_DVP_H__	
