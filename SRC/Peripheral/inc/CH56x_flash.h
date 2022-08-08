/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_flash.h
* Author             : Hans Baier
* Version            : V1.1.1
* Date               : 2022/08/07
* Description        : Contains functions for reading and writing flash
* Copyright (c) 2022 Hans Baier
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#ifndef __CH56x_FLASH_H__
#define __CH56x_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "CH56xSFR.h"

UINT8  FLASH_ROMA_ReadByte(UINT32 addr);
UINT32 FLASH_ROMA_ReadWord(UINT32 addr);
UINT8  FLASH_ROMA_READ(UINT32 StartAddr, PUINT32 Buffer, UINT32 Length);

UINT8  FLASH_ROMA_WRITE(UINT32 StartAddr, PVOID Buffer, UINT32 Length);
UINT8  FLASH_ROMA_ERASE_4K(UINT32 Addr);
UINT8  FLASH_ROMA_ERASE_64K(UINT32 Addr);

#ifdef __cplusplus
}
#endif

#endif  // __CH56x_SYS_H__
