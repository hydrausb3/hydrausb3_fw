/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_clk.h
* Author             : WCH, bvernoux
* Version            : V1.1
* Date               : 2022/07/30
* Description
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#ifndef __CH56x_CLK_H__
#define __CH56x_CLK_H__

#ifdef __cplusplus
extern "C" {
#endif

enum
{
	CLK_SOURCE_PLL_15MHz = 15, // Power-on default
	CLK_SOURCE_PLL_30MHz = 30,
	CLK_SOURCE_PLL_60MHz = 60,
	CLK_SOURCE_PLL_80MHz = 80,
	CLK_SOURCE_PLL_96MHz = 96,
	CLK_SOURCE_PLL_120MHz = 120,
	CLK_SOURCE_PLL_160MHz = 160 // Experimental overclocking 160MHz does not work with USB3
};

void SystemInit(uint32_t systemclck); /* System clock initialization */
UINT32 GetSysClock( void ); /* Get the current system clock */

#ifdef __cplusplus
}
#endif

#endif  // __CH56x_CLK_H__	
