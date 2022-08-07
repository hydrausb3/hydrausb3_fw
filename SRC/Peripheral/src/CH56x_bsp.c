/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_bsp.c
* Author             : bvernoux
* Version            : V1.0.1
* Date               : 2022/08/06
* Description        : This file contains all the functions prototypes for
*                      Board Support Package(BSP) related to Init/Delays/Timebase
*                      DisableInterrupts/EnableInterrupts(see .h macros)
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include "CH56x_common.h"

uint64_t bsp_us_nbcycles = 0;
uint64_t bsp_ms_nbcycles = 0;
uint32_t bsp_tick_frequency = 0;

/*******************************************************************************
 * @fn     bsp_systick_init
 *
 * @brief  Initializes Systick
 *         Note: SysTick IRQ is disabled
 *         Note: SysTick CNT decrement after each MCU cycle
 *         Precondition: call to SystemInit
 *
 * @return   None
 **/
static void bsp_systick_init(void)
{
	// See CH569DS1_EN_v1_2.PDF 4.4.2 SysTick register description
	SysTick->CNTFG = 0;
	SysTick->CMP = SysTick_LOAD_RELOAD_Msk; /* set CMP register max value */
	SysTick->CNT = SysTick_LOAD_RELOAD_Msk; /* set CNT register max value */
	SysTick->CTLR = SysTick_CTRL_RELOAD_Msk    |
					SysTick_CTRL_CLKSOURCE_Msk |
					SysTick_CTRL_ENABLE_Msk; /* Enable SysTick Timer */
}
/*******************************************************************************
 * @fn     bsp_init
 *
 * @brief  Set MCU frequency and SysTick
 *
 * @param  systemclck: MCU frequency in Hz
 *
 * @return  None
 */
void bsp_init(uint32_t systemclck)
{
	SystemInit(systemclck);
	bsp_systick_init();
	bsp_tick_frequency = GetSysClock();
	bsp_us_nbcycles = (uint64_t)(bsp_tick_frequency / 1000000ULL);
	bsp_ms_nbcycles = (uint64_t)(bsp_tick_frequency / 1000ULL);
}

/*******************************************************************************
 * @fn     bsp_get_tick_frequency
 *
 * @brief  Tick Frequency in Hz
 *         This function is thread-safe
 *         Precondition: call to bsp_init
 *
 * @return Number of Tick Frequency in Hz
 **/
/* See #define bsp_get_tick_frequency() */

/*******************************************************************************
 * @fn     bsp_get_nbtick_1us
 *
 * @brief  Number of tick for 1 microsecond
 *         This function is thread-safe
 *         Precondition: call to bsp_init
 *
 * @return  Return number of tick for 1 microsecond
 **/
/* See #define bsp_get_nbtick_1us() */

/*******************************************************************************
 * @fn     bsp_get_nbtick_1ms
 *
 * @brief  Number of tick for 1 millisecond
 *         This function is thread-safe
 *         Precondition: call to bsp_init
 *
 * @return  Return number of tick for 1 millisecond
 **/
/* See #define bsp_get_nbtick_1ms() */

/*******************************************************************************
 * @fn     bsp_get_SysTickCNT
 *
 * @brief  Get SysTick CNT and take care of potential rollover
 *         This function is thread-safe
 *         Precondition: call to bsp_init
 *
 * @return  Return SysTick CNT since the boot
 **/
inline uint64_t bsp_get_SysTickCNT(void)
{
	/*
	It is required to manage potential 32bits/64bits rollover,
	especially in case SysTick is configured to decrement on each MCU cycle.
	Note:
	The rollover on LSB appears about each 36s at 120MHz, each "lw" take 2 cycles on CH569W
	return SysTick->CNT;
	RISC-V ASM output:
	b7 f7 00 e0     lui      a5,0xe000f
	c8 43           lw       a0,4(a5) // 0xe000f004
	8c 47           lw       a1,8(a5) // 0xe000f008
	82 80           ret
	*/
	while (1)
	{
		uint32_t hi = SysTickU32->CNT_MSB;
		uint32_t lo = SysTickU32->CNT_LSB;
		if (hi == SysTickU32->CNT_MSB)
		{
			return ( ((uint64_t)(hi) << 32) | (uint64_t)(lo) );
		}
	}
	/*
	RISC-V ASM output:
	00000f44 b7 f7 00 e0     lui      a5,0xe000f
		LAB_00000f48
	00000f48 98 47           lw       a4,0x8(a5) // 0xe000f008
	00000f4a c8 43           lw       a0,0x4(a5) // 0xe000f004
	00000f4c 8c 47           lw       a1,0x8(a5) // 0xe000f008
	00000f4e e3 9d e5 fe     bne      a1,a4,LAB_00000f48
	00000f52 82 80           ret
	*/
}

/*******************************************************************************
 * @fn     bsp_get_tick
 *
 * @brief  Get the number of ticks from SysTick since the boot
 *         This function is thread-safe
 *         Precondition: call to bsp_init
 *
 * @return  Return number of tick from SysTick since the boot
 **/
inline uint64_t bsp_get_tick(void)
{
	while (1)
	{
		uint32_t hi = SysTickU32->CNT_MSB;
		uint32_t lo = SysTickU32->CNT_LSB;
		if (hi == SysTickU32->CNT_MSB)
		{
			return ( ~(((uint64_t)(hi) << 32) | (uint64_t)(lo)) ); // Invert the value at end
		}
	}
}

/*******************************************************************************
 * @fn     bsp_wait_nb_cycles
 *
 * @brief  Delay, wait for N MCU cycles
 *         This function is thread-safe
 *         Precondition: call to bsp_init
 *
 * @param  nb_cycles
 *
 * @return  None
 **/
// Delay in cycles using SysTick->CNT (64bits)
// nb_cycles shall be < 4 294 967 295 => (2^32)-1
// Accuracy about 9 cycles
// Accuracy 75ns (with systemclck 120 MHz)
// Accuracy 600ns (with systemclck 15 MHz) => For >32cycles
// => 1us = 2.33us (with systemclck 15 MHz)
void bsp_wait_nb_cycles(uint32_t nb_cycles)
{
	uint64_t start = bsp_get_SysTickCNT();
	uint64_t curr;
	uint32_t delta;

	if(nb_cycles > 20)
	{
		nb_cycles -= 20; // Remove function overhead with -O3 optim
	}
	else
	{
		nb_cycles = 0;
	}

	while(1)
	{
		curr = bsp_get_SysTickCNT();
		delta = start - curr; // CNT is decremented so comparison is inverted
		if( delta > nb_cycles )
			break;
	}
}

// Software delay accurate only if there is no any IRQ
/*
void bsp_wait_nb_cycles_sw(uint32_t nb_cycles)
{
	int32_t cycles = (nb_cycles / 4); // The loop take 4 cycles worst case
	cycles -= 6; // Remove function overhead with -O3 optim
	if(cycles < 1)
		return;
	do
	{
		__NOP();
	}while(--cycles>0);
}
*/

/*******************************************************************************
 * @fn     bsp_wait_us_delay
 *
 * @brief  Delay, wait for N microseconds
 *         This function is thread-safe
 *         Precondition: call to bsp_init
 *
 * @param  us
 *
 * @return  None
 **/
// Delay in microsecond using SysTick->CNT (64bits)
// Accuracy about 19 cycles
// Accuracy 158ns (with systemclck 120 MHz)
// Accuracy 1267ns (with systemclck 15 MHz) => For >=3us
// => 1us = 2.33us (with systemclck 15 MHz)
void bsp_wait_us_delay(uint32_t us)
{
	uint64_t start = bsp_get_SysTickCNT();
	uint64_t nb_cycles = bsp_us_nbcycles * (uint64_t)us;
	uint64_t curr;
	uint64_t delta;

	if(nb_cycles > 34)
	{
		nb_cycles -= 34; // Remove function overhead with -O3 optim
	}
	else
	{
		nb_cycles = 0;
	}

	while(1)
	{
		curr = bsp_get_SysTickCNT();
		delta = start - curr; // SysTickCNT is decremented so comparison is inverted
		if( delta > nb_cycles )
			break;
	}
}

/*******************************************************************************
 * @fn     bsp_wait_ms_delay
 *
 * @brief  Delay, wait for N milliseconds
 *         This function is thread-safe
 *         Precondition: call to bsp_init
 * @param  ms
 *
 * @return  None
 **/
// Delay in millisecond using SysTick->CNT (64bits)
// Accuracy about 19 cycles
// Accuracy 158ns (with systemclck 120 MHz)
// Accuracy 1267ns (with systemclck 15 MHz)
void bsp_wait_ms_delay(uint32_t ms)
{
	uint64_t start = bsp_get_SysTickCNT();
	uint64_t nb_cycles = bsp_ms_nbcycles * (uint64_t)ms;
	uint64_t curr;
	uint64_t delta;

	if(nb_cycles > 34)
	{
		nb_cycles -= 34; // Remove function overhead with -O3 optim
	}
	else
	{
		nb_cycles = 0;
	}

	while(1)
	{
		curr = bsp_get_SysTickCNT();
		delta = start - curr; // SysTickCNT is decremented so comparison is inverted
		if( delta > nb_cycles )
			break;
	}
}
