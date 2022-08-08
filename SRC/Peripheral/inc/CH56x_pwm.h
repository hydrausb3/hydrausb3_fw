/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_pwm.h
* Author             : WCH, bvernoux
* Version            : V1.0.1
* Date               : 2022/07/30
* Description
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#ifndef __CH56x_PWM_H__
#define __CH56x_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  channel of PWM define
  */
#define	CH_PWM0 0x01 // PWM0 channel
#define	CH_PWM1 0x02 // PWM1 channel
#define	CH_PWM2 0x04 // PWM2 channel
#define	CH_PWM3 0x08 // PWM3 channel

/**
  * @brief  channel of PWM define
  */
typedef enum
{
	High_Level = 0, // Default low level, active high level
	Low_Level, // Default high level, active low level
} PWMX_PolarTypeDef;

/**
  * @brief  Configuration PWM0_3 Cycle size
  */
typedef enum
{
	PWMX_Cycle_256 = 0, // 256 PWMX cycles
	PWMX_Cycle_255, // 255 PWMX cycles
} PWMX_CycleTypeDef;

#define  PWMX_CLKCfg(d) (R8_PWM_CLOCK_DIV=d) // PWM Reference Clock Configuration
void PWMX_CycleCfg(PWMX_CycleTypeDef cyc); // PWM output waveform period configuration

#define PWM0_ActDataWidth(d) (R8_PWM0_DATA = d) //PWM0 Effective data pulse width
#define PWM1_ActDataWidth(d) (R8_PWM1_DATA = d) //PWM1 Effective data pulse width
#define PWM2_ActDataWidth(d) (R8_PWM2_DATA = d) //PWM2 Effective data pulse width
#define PWM3_ActDataWidth(d) (R8_PWM3_DATA = d) //PWM3 Effective data pulse width

// Duty Cycle = Data Valid Width / Waveform Period
void PWMX_ACTOUT(UINT8 ch, UINT8 da, PWMX_PolarTypeDef pr, UINT8 s); // PWM0-3 output waveform configuration

#ifdef __cplusplus
}
#endif

#endif  // __CH56x_PWM_H__	
