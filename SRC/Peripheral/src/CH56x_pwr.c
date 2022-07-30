/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_pwr.c
* Author             : WCH
* Version            : V1.0
* Date               : 2020/07/31
* Description 
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#include "CH56x_common.h"


/*******************************************************************************
 * @fn     PWR_PeriphClkCfg
 *
 * @brief  外设时钟控制位
 * @param  s -
 *                  ENABLE  - 打开外设时钟
 *                  DISABLE - 关闭外设时钟
 *                  perph -
 *                     please refer to Peripher CLK control bit define
 
 * @return   None
 */
void PWR_PeriphClkCfg( UINT8 s, UINT16 perph )
{
    if( s == DISABLE )
    {
        R8_SAFE_ACCESS_SIG = 0x57;
        R8_SAFE_ACCESS_SIG = 0xA8;
        R32_SLEEP_CONTROL |= perph;
    }
    else
    {
        R8_SAFE_ACCESS_SIG = 0x57;
        R8_SAFE_ACCESS_SIG = 0xA8;
        R32_SLEEP_CONTROL &= ~perph;
    }
    R8_SAFE_ACCESS_SIG = 0;
}

/*******************************************************************************
 * @fn     PWR_PeriphWakeUpCfg
 *
 * @brief  睡眠唤醒源配置
 *
 * @param  s -
 *                  ENABLE  - 打开此外设睡眠唤醒功能
 *                  DISABLE - 关闭此外设睡眠唤醒功能
 *         perph -
 *                 RB_SLP_USBHS_WAKE -  USB2.0为唤醒源
 *                 RB_SLP_USBSS_WAKE -  USB3.0为唤醒源
 *                 RB_SLP_GPIO_WAKE  -  GPIO为唤醒源
 *                 RB_SLP_ETH_WAKE   -  ETH为唤醒源
 *                 ALL              -  以上所有
 * @return   None
 */
void PWR_PeriphWakeUpCfg( UINT8 s, UINT16 perph )
{
    if( s == DISABLE )
    {
        R8_SAFE_ACCESS_SIG = 0x57;
        R8_SAFE_ACCESS_SIG = 0xA8;
        R8_SLP_WAKE_CTRL &= ~perph;
    }
    else
    {
        R8_SAFE_ACCESS_SIG = 0x57;
        R8_SAFE_ACCESS_SIG = 0xA8;
        R8_SLP_WAKE_CTRL |= perph;
    }
    R8_SAFE_ACCESS_SIG = 0;
}

/*******************************************************************************
 * @fn     LowPower_Idle
 *
 * @brief  低功耗-Idle模式
 *
 * @return   None
 */
void LowPower_Idle( void )
{

	PFIC->SCTLR &= ~1<<2;				// 设置内核PFIC_SCTLR寄存器的SleepDeep字段为0
    __WFI();                            // 设置唤醒条件后执行__WFI()

}

/*******************************************************************************
 * @fn     LowPower_Halt
 *
 * @brief  低功耗-Halt模式
 * 
 * @return   None
 */
void LowPower_Halt( void )
{

	PFIC->SCTLR |= 1<<2;                      // 设置内核PFIC_SCTLR寄存器的SleepDeep字段为1
	R8_SLP_POWER_CTRL |= RB_SLP_USBHS_PWRDN;  // RB_SLP_USBHS_PWRDN置1
	__WFI();                                  // 设置唤醒条件后执行__WFI()
}

/*******************************************************************************
 * @fn     LowPower_Sleep
 *
 * @brief  低功耗-Sleep模式
 *
 * @return   None
 */
void LowPower_Sleep( void )
{

	PFIC->SCTLR |= 1<<2;                      // 设置内核PFIC_SCTLR寄存器的SleepDeep字段为1
	R8_SLP_POWER_CTRL |= RB_SLP_USBHS_PWRDN;  // RB_SLP_USBHS_PWRDN置1
	R8_SLP_WAKE_CTRL &= ~RB_SLP_USBSS_WAKE;   // RB_SLP_USBSS_WAKE置0
	__WFI();                                  // 设置唤醒条件后执行__WFI()

}




