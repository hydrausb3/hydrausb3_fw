/********************************** (C) COPYRIGHT *******************************
* File Name   : Main.c
* Author      : bvernoux
* Version     : V1.0
* Date        : 2022/07/30
* Description : Basic example with minimal MCU speed(15MHz) and ULED blinking
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include <stdarg.h>
#include "CH56x_common.h"
#include "CH56x_debug_log.h"
#include "CH56x_hydrausb3.h"

#undef FREQ_SYS
/* System clock / MCU frequency in Hz (lowest possible speed 15MHz) */
#define FREQ_SYS (15000000)

#if(defined DEBUG) // DEBUG=1 to be defined in pre-processor compiler option
#define UART1_BAUD (9600)
#endif

/* Blink time in ms */
#define BLINK_FAST (50) // Blink LED each 100ms (50*2)
#define BLINK_SLOW (250) // Blink LED each 500ms (250*2)
int blink_ms = BLINK_SLOW;

/* Required for log_init() => log_printf()/cprintf() */
debug_log_buf_t log_buf;

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
	/* Configure serial debugging for printf()/log_printf()... */
	log_init(&log_buf);
	/* Configure serial debugging for printf()/log_printf()... */
	UART1_init(UART1_BAUD, FREQ_SYS);
	
	log_printf("Start\n");
	
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
		log_printf("Blink\n");
	}
}
