/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_debug_log.c
* Author             : bvernoux
* Version            : V1.0.1
* Date               : 2022/08/07
* Description
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include <stdarg.h>
#include "CH56x_common.h"
#include "CH56x_debug_log.h"

// Add option in pre-processor compiler option
// CH56x_DEBUG_LOG_BASIC_TIMESTAMP=1
// or
// CH56x_DEBUG_LOG_LIBDIVIDE_SYSLCLK=120000000

#ifdef CH56x_DEBUG_LOG_BASIC_TIMESTAMP
#ifdef CH56x_DEBUG_LOG_LIBDIVIDE_SYSLCLK
#error "CH56x_DEBUG_LOG_BASIC_TIMESTAMP and CH56x_DEBUG_LOG_LIBDIVIDE_SYSLCLK shall not be set together"
#endif
#endif

#ifdef CH56x_DEBUG_LOG_BASIC_TIMESTAMP
#undef CH56x_DEBUG_LOG_LIBDIVIDE_SYSLCLK
#endif

#ifdef CH56x_DEBUG_LOG_LIBDIVIDE_SYSLCLK
#include "libdivide.h"
#endif

#define LOG_PRINTF_BUFF_SIZE (511)

static uint64_t startCNT64;

static debug_log_buf_t* debug_log_buf;

#ifdef CH56x_DEBUG_LOG_LIBDIVIDE_SYSLCLK
static struct libdivide_u64_t fast_u64_divSysClock;
static struct libdivide_u64_t fast_u64_divSysClock_nbtick_1ms;
static struct libdivide_u64_t fast_u64_divSysClock_nbtick_1us;
#endif

/* Function declaration */

void log_init(debug_log_buf_t *buf)
{
	debug_log_buf = buf;
	debug_log_buf->idx = 0;
	startCNT64 = bsp_get_SysTickCNT();
#ifdef CH56x_DEBUG_LOG_LIBDIVIDE_SYSLCLK
	fast_u64_divSysClock = libdivide_u64_gen(CH56x_DEBUG_LOG_LIBDIVIDE_SYSLCLK);
	fast_u64_divSysClock_nbtick_1ms = libdivide_u64_gen( (CH56x_DEBUG_LOG_LIBDIVIDE_SYSLCLK/1000ULL) );
	fast_u64_divSysClock_nbtick_1us = libdivide_u64_gen( (CH56x_DEBUG_LOG_LIBDIVIDE_SYSLCLK/1000000ULL) );
#endif
}

void log_time_reinit(void)
{
	startCNT64 = bsp_get_SysTickCNT();
}

void cprintf(const char *fmt, ...)
{
	va_list va_args;
	int print_size;
	char log_printf_buff[LOG_PRINTF_BUFF_SIZE+1];

	bsp_disable_interrupt(); // Enter Critical Section

	va_start(va_args, fmt);
	print_size = vsnprintf(log_printf_buff, LOG_PRINTF_BUFF_SIZE, fmt, va_args);
	va_end(va_args);
	if(print_size > 0)
	{
		/* Save all log_printf data in a big buffer */
		int idx = debug_log_buf->idx;
		if((idx + print_size) < DEBUG_LOG_BUF_SIZE)
		{
			memcpy(&debug_log_buf->buf[idx], log_printf_buff, print_size);
			debug_log_buf->idx += print_size;
		}
	}
#if(defined DEBUG)
	if(print_size > 0)
		fwrite(log_printf_buff, sizeof(char), print_size, stdout);
#endif
	bsp_enable_interrupt(); // Exit Critical Section
}

void cprint_hex(uint8_t* data, uint16_t size)
{
	uint16_t i, j;
	for(i = 0; i < size; ++i)
	{
		cprintf("%02X ", data[i]);
		if( ((i+1) % 8 == 0) || (i + 1 == size))
		{
			cprintf(" ");
			if((i+1) % 16 == 0)
			{
				cprintf("\n");
			}
			else if(i+1 == size)
			{
				if((i+1) % 16 <= 8)
				{
					cprintf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j)
				{
					cprintf("   ");
				}
				cprintf("\n");
			}
		}
	}
}

void log_printf(const char *fmt, ...)
{
	va_list va_args;
	int print_size1;
	int print_size2;
	uint64_t delta;
	uint64_t deltaCNT64;
	uint32_t sec;
	uint32_t msec;
	uint32_t usec;
	uint32_t tick_freq;
	char log_printf_buff[LOG_PRINTF_BUFF_SIZE+1];

	delta = startCNT64 - bsp_get_SysTickCNT(); // CNT is decremented so comparison is inverted
	deltaCNT64 = delta;

	tick_freq = bsp_get_tick_frequency();
#ifndef CH56x_DEBUG_LOG_BASIC_TIMESTAMP
#ifdef CH56x_DEBUG_LOG_LIBDIVIDE_SYSLCLK
	{
		uint32_t start, stop;
		start = bsp_get_SysTickCNT_LSB();

		// Fast, computes division using libdivide
		sec = (uint32_t)libdivide_u64_do(deltaCNT64, &fast_u64_divSysClock);
		deltaCNT64 -= ((uint64_t)(sec) * (uint64_t)(tick_freq) );

		msec = (uint32_t)libdivide_u64_do(deltaCNT64, &fast_u64_divSysClock_nbtick_1ms);
		deltaCNT64 -= ( (uint64_t)(msec) * (uint64_t)( (CH56x_DEBUG_LOG_LIBDIVIDE_SYSLCLK/1000ULL) ) );

		usec = (uint32_t)libdivide_u64_do(deltaCNT64, &fast_u64_divSysClock_nbtick_1us);

		stop = bsp_get_SysTickCNT_LSB(); // CNT is decremented so comparison is inverted
	}
#else
	{
		uint32_t start, stop;
		start = bsp_get_SysTickCNT_LSB();
		uint32_t nbtick_1ms = bsp_get_nbtick_1ms();

		sec = (uint32_t)( deltaCNT64 / (uint64_t)(tick_freq) );
		deltaCNT64 -= ((uint64_t)(sec) * (uint64_t)(tick_freq) );

		msec = (uint32_t)( deltaCNT64 / (uint64_t)(nbtick_1ms) );
		deltaCNT64 -= ( (uint64_t)(msec) * (uint64_t)(nbtick_1ms) );

		usec = (uint32_t)( deltaCNT64 / (uint64_t)(bsp_get_nbtick_1us()) );

		stop = bsp_get_SysTickCNT_LSB(); // CNT is decremented so comparison is inverted
	}
#endif
#endif // ifndef CH56x_DEBUG_LOG_BASIC_TIMESTAMP

	bsp_disable_interrupt(); // Enter Critical Section
#ifdef CH56x_DEBUG_LOG_BASIC_TIMESTAMP
	print_size = sprintf(log_printf_buff, "0x%08X ", (uint32_t)(delta));
#else
	//print_size = sprintf(log_printf_buff, "%02us %03ums %03uus(0x%08X)(%d) ", sec, msec, usec, (uint32_t)(delta), (start - stop));
	print_size1 = sprintf(log_printf_buff, "%02us %03ums %03uus ", sec, msec, usec);
#endif

	va_start(va_args, fmt);
	print_size2 = vsnprintf(&log_printf_buff[print_size1], LOG_PRINTF_BUFF_SIZE, fmt, va_args);
	va_end(va_args);
	print_size2 += print_size1;
	if(print_size2 > 0)
	{
		/* Save all log_printf data in a big buffer */
		int idx = debug_log_buf->idx;
		if( (idx + print_size2) < DEBUG_LOG_BUF_SIZE)
		{
			memcpy(&debug_log_buf->buf[idx], log_printf_buff, print_size2);
			debug_log_buf->idx += print_size2;
		}
#if(defined DEBUG)
		fwrite(log_printf_buff, sizeof(char), print_size2, stdout);
#endif
	}
	bsp_enable_interrupt(); // Exit Critical Section
}
