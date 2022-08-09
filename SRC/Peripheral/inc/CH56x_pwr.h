/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_pwr.h
* Author             : WCH, bvernoux
* Version            : V1.1
* Date               : 2022/08/07
* Description
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#ifndef __CH56x_PWR_H__
#define __CH56x_PWR_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief	Peripher CLK control bit define
  */
#define BIT_SLP_CLK_TMR0  RB_SLP_CLK_TMR0   /*!< TMR0 peripher clk bit */
#define BIT_SLP_CLK_TMR1  RB_SLP_CLK_TMR1   /*!< TMR1 peripher clk bit */
#define BIT_SLP_CLK_TMR2  RB_SLP_CLK_TMR2   /*!< TMR2 peripher clk bit */
#define BIT_SLP_CLK_PWMX  RB_SLP_CLK_PWMX   /*!< PWMX peripher clk bit */
#define BIT_SLP_CLK_UART0 RB_SLP_CLK_UART0  /*!< UART0 peripher clk bit */
#define BIT_SLP_CLK_UART1 RB_SLP_CLK_UART1  /*!< UART1 peripher clk bit */
#define BIT_SLP_CLK_UART2 RB_SLP_CLK_UART2  /*!< UART2 peripher clk bit */
#define BIT_SLP_CLK_UART3 RB_SLP_CLK_UART3  /*!< UART3 peripher clk bit */
#define BIT_SLP_CLK_SPI0  RB_SLP_CLK_SPI0   /*!< SPI0 peripher clk bit */
#define BIT_SLP_CLK_SPI1  RB_SLP_CLK_SPI1   /*!< SPI1 peripher clk bit */
#define BIT_SLP_CLK_EMMC  RB_SLP_CLK_EMMC   /*!< EMMC peripher clk bit */
#define BIT_SLP_CLK_HSPI  RB_SLP_CLK_HSPI   /*!< HSPI peripher clk bit */
#define BIT_SLP_CLK_USBHS RB_SLP_CLK_USBHS  /*!< USBHS peripher clk bit */
#define BIT_SLP_CLK_USBSS RB_SLP_CLK_USBSS  /*!< USBSS peripher clk bit */
#define BIT_SLP_CLK_SERD  RB_SLP_CLK_SERD   /*!< SERD peripher clk bit */
#define BIT_SLP_CLK_DVP   RB_SLP_CLK_DVP    /*!< DVP peripher clk bit */
#define BIT_SLP_CLK_ETH   RB_SLP_CLK_ETH    /*!< ETH peripher clk bit */
#define BIT_SLP_CLK_ECDC  RB_SLP_CLK_ECDC   /*!< ECDC peripher clk bit */

void PWR_PeriphClkCfg( uint8_t s, uint16_t perph );    /* Peripheral Clock Control Bits */
void PWR_PeriphWakeUpCfg( uint8_t s, uint16_t perph ); /* Sleep wake source configuration */
void LowPower_Idle( void );                        /* Low Power - IDLE Mode */
void LowPower_Halt( void );                        /* Low Power - Halt Mode */
void LowPower_Sleep( void );                       /* Low Power - Sleep Mode */

#ifdef __cplusplus
}
#endif

#endif  // __CH56x_PWR_H__	
