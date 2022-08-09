/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_flash.h
* Author             : Hans Baier
* Version            : V1.2
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

uint8_t  FLASH_ROMA_ReadByte(uint32_t addr);
uint32_t FLASH_ROMA_ReadWord(uint32_t addr);
uint8_t  FLASH_ROMA_READ(uint32_t StartAddr, puint32_t Buffer, uint32_t Length);

uint8_t  FLASH_ROMA_WRITE(uint32_t StartAddr, void* Buffer, uint32_t Length);
uint8_t  FLASH_ROMA_ERASE_4K(uint32_t Addr);
uint8_t  FLASH_ROMA_ERASE_64K(uint32_t Addr);

#ifdef __cplusplus
}
#endif

#endif  // __CH56x_SYS_H__
