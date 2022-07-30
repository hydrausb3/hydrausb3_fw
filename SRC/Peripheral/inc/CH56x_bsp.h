/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_bsp.h
* Author             : bvernoux
* Version            : V1.0
* Date               : 2022/07/30
* Description        : This file contains all the functions prototypes for 
*                      Board Support Package(BSP) related to Init/Delays/Timebase
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#ifndef __CH56x_BSP_H__
#define __CH56x_BSP_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH56xSFR.h"

/* Memory mapped structure for lowleve SysTick access */
typedef struct __attribute__((packed))
{
 __IO uint32_t CTLR;
 __IO uint32_t CNT_LSB;
 __IO uint32_t CNT_MSB;
 __IO uint32_t CMP_LSB;
 __IO uint32_t CMP_MSB;
 __IO uint32_t CNTFG;
}SysTickU32_Type;
#define SysTickU32 ((SysTickU32_Type *)0xE000F000)

extern uint64_t bsp_us_nbcycles;
extern uint64_t bsp_ms_nbcycles;
extern uint32_t bsp_tick_frequency;

/*
Set MCU frequency and SysTick
*/
void bsp_init(uint32_t systemclck);

/*
Returns the number of system ticks since the system boot
This function is thread-safe 
Shall be called only after a call to bsp_init
*/
uint64_t bsp_get_tick(void);

/*
Delay, wait for N microseconds
This function is thread-safe
Shall be called only after a call to bsp_init
*/
void bsp_wait_us_delay(uint32_t us);

/*
Delay, wait for N milliseconds
This function is thread-safe
Precondition: call to bsp_init
*/
void bsp_wait_ms_delay(uint32_t ms);

/*
Delay, wait for N MCU cycles
This function is thread-safe
Precondition: call to bsp_init
*/
void bsp_wait_nb_cycles(uint32_t nb_cycles);

/* 
Returns the Number of tick for 1 microsecond
This function is thread-safe
Precondition: call to bsp_init
*/
#define  bsp_get_nbtick_1us() (bsp_us_nbcycles)

/* 
Returns the Number of tick for 1 millisecond
This function is thread-safe
Precondition: call to bsp_init
*/
#define bsp_get_nbtick_1ms() (bsp_ms_nbcycles)

/* 
Returns the tick frequency in Hz
This function is thread-safe
Precondition: call to bsp_init
*/
#define bsp_get_tick_frequency() (bsp_tick_frequency)

/*
Returns SysTick CNT 64bits
Potential rollover is managed
This function will always return correct 64bits CNT
This function is thread-safe
Precondition: call to bsp_init
Note:
CNT value is decremented at each MCU cycle
CNT value is one's complement of bsp_get_tick()
 */
uint64_t bsp_get_SysTickCNT(void);

/*
Returns SysTick CNT 32bits
Shall be used only safely after startup during <36s
This function is thread-safe
Precondition: call to bsp_init
Note:
CNT value is decremented at each MCU cycle
CNT value is one's complement of bsp_get_tick() 32bits only
 */
#define bsp_get_SysTickCNT_LSB() (SysTickU32->CNT_LSB)

#ifdef __cplusplus
}
#endif

#endif  // __CH56x_BSP_H__	
