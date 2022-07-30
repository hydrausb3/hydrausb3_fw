/********************************** (C) COPYRIGHT *******************************
* File Name          : Main.c
* Author             : bvernoux
* Version            : V1.0
* Date               : 2022/07/30
* Description 		 : Basic example with minimal MCU speed(15MHz) and ULED blinking
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include <stdarg.h>
#include "CH56x_common.h"
#include "CH56x_hydrausb3.h"

#undef FREQ_SYS
/* System clock / MCU frequency in Hz (lowest possible speed 15MHz) */
#define FREQ_SYS (15000000)

/* Blink time in ms */
#define BLINK_FAST (50)
#define BLINK_SLOW (250)
int blink_ms = BLINK_SLOW;

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main()
{
	/* Configure GPIO In/Out default/safe state for HydraUSB3 */
	hydrausb3_gpio_init();
	/* Init BSP (MCU Frequency & SysTick) */
	bsp_init(FREQ_SYS);

	while(1)
	{
		if(hydrausb3_ubtn())
		{
			blink_ms = BLINK_FAST;
		}
		else
		{
			blink_ms = BLINK_SLOW;
		}
		ULED_ON();
		bsp_wait_ms_delay(blink_ms);
		ULED_OFF();
		bsp_wait_ms_delay(blink_ms);
	}
}
