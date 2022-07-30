/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_sys.c
* Author             : WCH, bvernoux
* Version            : V1.1
* Date               : 2022/07/30
* Description        : This file contains all the functions prototypes for
*                      SystemCoreClock, UART Printf , Delay functions .
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include "CH56x_common.h"

/*******************************************************************************
 * @fn     Delay_Init
 *
 * @brief  Initializes Delay Funcation.
 *
 * @param  systemclck - System clock in Hz
 *
 * @return   None
 **/
void Delay_Init(uint32_t systemclck)
{
	bsp_init(systemclck);
}

/*******************************************************************************
 * @fn     mDelayuS
 *
 * @brief  Microsecond Delay Time.
 *
 * @param  n - Microsecond number.
 *
 * @return   None
 **/
void mDelayuS(uint32_t n)
{
	bsp_wait_us_delay(n);
}

/*******************************************************************************
 * @fn     mDelaymS
 *
 * @brief  Millisecond Delay Time.
 *
 * @param  n - Millisecond number.
 *
 * @return   None
 **/
void mDelaymS(uint32_t n)
{
	bsp_wait_ms_delay(n);
}

/*******************************************************************************
 * @fn     SYS_GetInfoSta
 *
 * @brief  Get current system information status
 *
 * @param  i -
 * @return  stat
 **/
UINT8 SYS_GetInfoSta( SYS_InfoStaTypeDef i )
{
	return (R8_RST_BOOT_STAT&(1<<i));
}

/*******************************************************************************
 * @fn     SYS_ResetExecute
 *
 * @brief  Perform a system software reset
 *
 * @return   None
 **/
void SYS_ResetExecute( void )
{
	R8_SAFE_ACCESS_SIG = 0x57; // enable safe access mode
	R8_SAFE_ACCESS_SIG = 0xa8;
	R8_RST_WDOG_CTRL |= RB_SOFTWARE_RESET | 0x40;
	R8_SAFE_ACCESS_SIG = 0;
}

/*******************************************************************************
 * @fn     WWDG_ITCfg
 *
 * @brief  Watchdog Timer Overflow Interrupt Enable
 *
 * @param  s -
 *           DISABLE - Overflow no interrupted
 *           ENABLE - Overflow interrupt
 *
 * @return   None
 **/
void  WWDG_ITCfg( UINT8 s )
{
	R8_SAFE_ACCESS_SIG = 0x57; // enable safe access mode
	R8_SAFE_ACCESS_SIG = 0xa8;
	if(s == DISABLE)
		R8_RST_WDOG_CTRL=(R8_RST_WDOG_CTRL & (~RB_WDOG_INT_EN)) | 0x40;
	else
		R8_RST_WDOG_CTRL|=RB_WDOG_INT_EN | 0x40;
	R8_SAFE_ACCESS_SIG = 0;
}

/*******************************************************************************
 * @fn     WWDG_ResetCfg
 *
 * @brief  Watchdog Timer Reset Function
 *
 * @param  s -
 *           DISABLE - Overflow does not reset
 *           ENABLE - Overflow system reset
 *
 * @return   None
 **/
void WWDG_ResetCfg( UINT8 s )
{
	R8_SAFE_ACCESS_SIG = 0x57; // enable safe access mode
	R8_SAFE_ACCESS_SIG = 0xa8;
	if(s == DISABLE)
		R8_RST_WDOG_CTRL=(R8_RST_WDOG_CTRL & (~RB_WDOG_RST_EN)) | 0x40;
	else
		R8_RST_WDOG_CTRL|=RB_WDOG_RST_EN | 0x40;
	R8_SAFE_ACCESS_SIG = 0;
}

/*******************************************************************************
 * @fn     WWDG_ClearFlag
 * @brief  Clear watchdog interrupt flag, reload count value can also be cleared
 * @param  None
 * @return   None
 **/
void WWDG_ClearFlag( void )
{
	R8_SAFE_ACCESS_SIG = 0x57; // enable safe access mode
	R8_SAFE_ACCESS_SIG = 0xa8;
	R8_RST_WDOG_CTRL |= RB_WDOG_INT_FLAG | 0x40;
	R8_SAFE_ACCESS_SIG = 0;
}


#if( defined  DEBUG)
/*******************************************************************************
 * @fn     _write
 *
 * @brief  Support Printf Function
 *
 * @param  *buf: UART send Data.
 *           size - Data length
 *
 * @return   size - Data length
 **/
 __attribute__((used))
int _write(int fd, char *buf, int size)
{
	int i;

	for(i=0; i<size; i++){
#if  DEBUG == Debug_UART0
		while( R8_UART0_TFC == UART_FIFO_SIZE );
		R8_UART0_THR = *buf++;
#elif DEBUG == Debug_UART1
		while( R8_UART1_TFC == UART_FIFO_SIZE );
		R8_UART1_THR = *buf++;
#elif DEBUG == Debug_UART2
		while( R8_UART2_TFC == UART_FIFO_SIZE );
		R8_UART2_THR = *buf++;
#elif DEBUG == Debug_UART3
		while( R8_UART3_TFC == UART_FIFO_SIZE );
		R8_UART3_THR = *buf++;
#endif
	}
	return size;
}
#endif
