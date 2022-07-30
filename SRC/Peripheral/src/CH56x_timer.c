/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_timer.c
* Author             : WCH
* Version            : V1.0
* Date               : 2020/07/31
* Description 
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#include "CH56x_common.h"


/*******************************************************************************
 * @fn     TMR0_TimerInit
 *
 * @brief  Counting Function on TIM PeriPheral
 *
 * @param  t - the Most End Value counting to
 *
 * @return   None
 */
void TMR0_TimerInit( UINT32 t )
{
    R32_TMR0_CNT_END = t;
    R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR0_CTRL_MOD = RB_TMR_COUNT_EN | RB_TMR_CAP_COUNT;
}

/*******************************************************************************
 * @fn     TMR1_TimerInit
 *
 * @brief  Counting Function on TIM PeriPheral
 *
 * @param  t - the Most End Value counting to
 *
 * @return   None
 */
void TMR1_TimerInit( UINT32 t )
{
    R32_TMR1_CNT_END = t;
    R8_TMR1_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR1_CTRL_MOD = RB_TMR_COUNT_EN | RB_TMR_CAP_COUNT;
}

/*******************************************************************************
 * @fn     TMR2_TimerInit
 *
 * @brief  Counting Function on TIM PeriPheral
 *
 * @param  t - the Most End Value counting to
 *
 * @return   None
 */
void TMR2_TimerInit( UINT32 t )
{
    R32_TMR2_CNT_END = t;
    R8_TMR2_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR2_CTRL_MOD = RB_TMR_COUNT_EN | RB_TMR_CAP_COUNT;
}

/*******************************************************************************
 * @fn     TMR0_EXTSignalCounterInit
 *
 * @brief  external signal count
 *
 * @param  c
 *
 * @return  None
 */
void TMR0_EXTSignalCounterInit( UINT32 c )
{
    R32_TMR0_CNT_END = c;
    R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR0_CTRL_MOD = RB_TMR_CAP_COUNT|RB_TMR_MODE_IN|RB_TMR_COUNT_EN;
}

/*******************************************************************************
 * @fn     TMR1_EXTSignalCounterInit
 *
 * @brief  external signal count
 *
 * @param  c
 *
 * @return  None
 */
void TMR1_EXTSignalCounterInit( UINT32 c )
{
    R32_TMR1_CNT_END = c;
    R8_TMR1_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR1_CTRL_MOD = RB_TMR_CAP_COUNT|RB_TMR_MODE_IN|RB_TMR_COUNT_EN;
}

/*******************************************************************************
 * @fn     TMR2_EXTSignalCounterInit
 *
 * @brief  external signal count
 *
 * @param  c
 *
 * @return  None
 */
void TMR2_EXTSignalCounterInit( UINT32 c )
{
    R32_TMR2_CNT_END = c;
    R8_TMR2_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR2_CTRL_MOD = RB_TMR_CAP_COUNT|RB_TMR_MODE_IN|RB_TMR_COUNT_EN;
}

/*******************************************************************************
 * @fn     TMR0_PWMInit
 *
 * @brief  PWM Output Init
 *
 * @param  pr-
 *         ts-
 *
 * @return   None
 */
void TMR0_PWMInit( PWM_PolarTypeDef pr, PWM_RepeatTsTypeDef ts )
{
    R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR0_CTRL_MOD = RB_TMR_COUNT_EN
                        |RB_TMR_OUT_EN
                        |(pr<<4)
                        |(ts<<6);
}

/*******************************************************************************
 * @fn     TMR1_PWMInit
 *
 * @brief  PWM Output Init
 *
 * @param  pr-
 *         ts-
 *
 * @return   None
 */
void TMR1_PWMInit( PWM_PolarTypeDef pr, PWM_RepeatTsTypeDef ts )
{
    R8_TMR1_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR1_CTRL_MOD = RB_TMR_COUNT_EN
                        |RB_TMR_OUT_EN
                        |(pr<<4)
                        |(ts<<6);
}

/*******************************************************************************
 * @fn     TMR2_PWMInit
 *
 * @brief  PWM Output Init
 *
 * @param  pr-
 *         ts-
 *
 * @return   None
 */
void TMR2_PWMInit( PWM_PolarTypeDef pr, PWM_RepeatTsTypeDef ts )
{
    R8_TMR2_CTRL_MOD = RB_TMR_ALL_CLEAR;
    R8_TMR2_CTRL_MOD = RB_TMR_COUNT_EN
                        |RB_TMR_OUT_EN
                        |(pr<<4)
                        |(ts<<6);
}

/*******************************************************************************
 * @fn     TMR0_CapInit
 *
 * @brief  cap
 *
 * @param  CapModeTypeDef
 *
 * @return   None
 */
void TMR0_CapInit( CapModeTypeDef cap )
{
        R8_TMR0_CTRL_MOD = RB_TMR_ALL_CLEAR;
        R8_TMR0_CTRL_MOD = RB_TMR_COUNT_EN      \
                            |RB_TMR_MODE_IN     \
                            |(cap<<6);
}

/*******************************************************************************
 * @fn     TMR1_CapInit
 *
 * @brief  cap
 *
 * @param  CapModeTypeDef
 *
 * @return   None
 */
void TMR1_CapInit( CapModeTypeDef cap )
{
        R8_TMR1_CTRL_MOD = RB_TMR_ALL_CLEAR;
        R8_TMR1_CTRL_MOD = RB_TMR_COUNT_EN      \
                            |RB_TMR_MODE_IN     \
                            |(cap<<6);
}

/*******************************************************************************
 * @fn     TMR2_CapInit
 *
 * @brief  cap
 *
 * @param  CapModeTypeDef
 *
 * @return   None
 */
void TMR2_CapInit( CapModeTypeDef cap )
{
     R8_TMR2_CTRL_MOD = RB_TMR_ALL_CLEAR;
     R8_TMR2_CTRL_MOD = RB_TMR_COUNT_EN      \
                         |RB_TMR_MODE_IN     \
                         |(cap<<6);
}

/*******************************************************************************
 * @fn     TMR1_DMACfd
 *
 * @brief  TMR DMA Configuration
 *
 * @param  ENABLE/DISABLE
 *                 startAddr
 *                 endAddr
 *                 DMAModeTypeDef
 * @return   None
 **/
void TMR1_DMACfg( UINT8 s, UINT16 startAddr, UINT16 endAddr, DMAModeTypeDef m )
{
        if(s == DISABLE){
            R8_TMR1_CTRL_DMA = 0;
        }
        else{
            if(m)   R8_TMR1_CTRL_DMA = RB_TMR_DMA_LOOP|RB_TMR_DMA_ENABLE;
            else    R8_TMR1_CTRL_DMA = RB_TMR_DMA_ENABLE;
            R32_TMR1_DMA_BEG = startAddr;
            R32_TMR1_DMA_END = endAddr;
        }
}

/*******************************************************************************
 * @fn     TMR2_DMACfd
 *
 * @brief  TMR DMA Configuration
 *
 * @param  ENABLE/DISABLE
 *                 startAddr
 *                 endAddr
 *                 DMAModeTypeDef
 * @return   None
 **/

void TMR2_DMACfg( UINT8 s, UINT16 startAddr, UINT16 endAddr, DMAModeTypeDef m )
{
        if(s == DISABLE){
            R8_TMR2_CTRL_DMA = 0;
        }
        else{
            if(m)   R8_TMR2_CTRL_DMA = RB_TMR_DMA_LOOP|RB_TMR_DMA_ENABLE;
            else    R8_TMR2_CTRL_DMA = RB_TMR_DMA_ENABLE;
            R32_TMR2_DMA_BEG = startAddr;
            R32_TMR2_DMA_END = endAddr;
        }
}


