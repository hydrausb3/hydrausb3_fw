/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_debug_log.h
* Author             : bvernoux
* Version            : V1.0.1
* Date               : 2022/08/07
* Description
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#ifndef CH56X_DEBUG_LOG_H_
#define CH56X_DEBUG_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_LOG_BUF_SIZE (4096-1) /* Maximum string size */
/* 4096 bytes is the size of USB3 SS Bulk with Burst buffer to output log over USB3 SS or USB2 HS */
typedef struct
{
	char buf[DEBUG_LOG_BUF_SIZE+1];
	volatile uint16_t idx; /* Position in the buffer */
} debug_log_buf_t;

void log_init(debug_log_buf_t *buf);
void log_time_reinit(void);

/*
 * cprintf() write formatted text data on stdout and debug_log_buf buffer
 * Note: debug_log_buf buffer use debug_log_buf_idx with max size DEBUG_LOG_BUF_SIZE
 * Warning: cprintf() can output at maximum LOG_PRINTF_BUFF_SIZE
 * Can be used in main code & interrupts (use bsp_disable_interrupts() / bsp_enable_interrupts())
 */
void cprintf(const char *fmt, ...);

/*
 * log_printf() write formatted text data with "timestamp" prefix format "%02us %03ums %03uus "
 * log_printf() output text data on both stdout and debug_log_buf buffer
 * Note: debug_log_buf buffer use debug_log_buf_idx with max size DEBUG_LOG_BUF_SIZE
 * Warning: log_printf() can output at maximum LOG_PRINTF_BUFF_SIZE
 * Can be used in main code & interrupts (use bsp_disable_interrupts() / bsp_enable_interrupts())
 */
void log_printf(const char *fmt, ...);

/* Print ASCII Hex of data/size using cprintf() */
void cprint_hex(uint8_t* data, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif /* CH56X_DEBUG_LOG_H_ */
