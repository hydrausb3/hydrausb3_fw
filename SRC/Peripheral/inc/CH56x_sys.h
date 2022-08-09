/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_sys.h
* Author             : WCH, bvernoux
* Version            : V1.1
* Date               : 2022/08/07
* Description        : This file contains all the functions prototypes for
*                      SystemCoreClock, UART Printf , Delay functions .
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#ifndef __CH56x_SYS_H__
#define __CH56x_SYS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "CH56xSFR.h"

/**
  * @brief  SYSTEM Information State
  */
typedef enum
{
	INFO_RESET_EN = 2,// RST# Whether the external manual reset input function is enabled
	INFO_BOOT_EN,	  // Whether the system boot program BootLoader is enabled
	INFO_DEBUG_EN,	  // Whether the system emulation debugging interface is enabled
	INFO_LOADER,	  // Whether the current system is in the Bootloader area
} SYS_InfoStaTypeDef;

#define SYS_GetChipID() R8_CHIP_ID /* Get the chip ID class, generally a fixed value */
#define SYS_GetAccessID() R8_SAFE_ACCESS_ID /* Get the security access ID, usually a fixed value */
uint8_t SYS_GetInfoSta(SYS_InfoStaTypeDef i); /* Get current system information status */

void Delay_Init(uint32_t systemclck);
void mDelayuS(uint32_t n);
void mDelaymS(uint32_t n);

//refer to SYS_ResetStaTypeDef
#define SYS_GetLastResetSta() (R8_RST_BOOT_STAT&RB_RESET_FLAG) /* Get system last reset status */
void SYS_ResetExecute(void); /* Perform a system software reset */
#define SYS_ResetKeepBuf(d) (R8_GLOB_RESET_KEEP = d) /* Not affected by manual reset, software reset, watchdog reset, or normal wake-up reset */

//WWDG
#define  WWDG_SetCounter(c) (R8_WDOG_COUNT = c) /* Load the initial value of watchdog count, increment type */
void  WWDG_ITCfg(uint8_t s); /* Watchdog overflow interrupt enable */
void  WWDG_ResetCfg(uint8_t s); /* Watchdog overflow reset enable */
#define  WWDG_GetFlowFlag() (R8_RST_WDOG_CTRL&RB_WDOG_INT_FLAG) /* Get the current watchdog timer overflow flag */
void WWDG_ClearFlag(void); /* Clear watchdog interrupt flag, reload count value can also be cleared */

#ifdef __cplusplus
}
#endif

#endif  // __CH56x_SYS_H__	
