/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_sys.c
* Author             : Hans Baier
* Version            : V1.1
* Date               : 2022/08/02
* Description        : code for reading/writing the internal flash memory
* Copyright (c) 2022 Hans Baier
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include "CH56x_flash.h"

#define ROM_ADDR_OFFSET 0x8000
#define ROM_END 0x80000

#define ROM_BEGIN_READ  0b1011
#define ROM_BEGIN_WRITE 0b0110
#define ROM_END_WRITE   0b0101

static void FLASH_ROMA_WaitControlRegister()
{
	INT8 status;
	do
	{
		status = (INT8)R8_SPI_ROM_CR;
	}
	while (status < 0);
}

static void FLASH_ROMA_Access(UINT8 access_code)
{
	FLASH_ROMA_WaitControlRegister();
	R8_SPI_ROM_CR = access_code;
}

static void FLASH_ROMA_AccessEnd()
{
	FLASH_ROMA_Access(0);
}

static void FLASH_ROMA_DataWrite(UINT8 data)
{
	FLASH_ROMA_WaitControlRegister();
	R8_SPI_ROM_DATA = data;
}

static UINT8 FLASH_ROMA_DataRead()
{
	FLASH_ROMA_WaitControlRegister();
	return R8_SPI_ROM_DATA;
}

static void FLASH_ROMA_Begin(UINT8 begin_code)
{
	R8_SPI_ROM_CR    = 0;
	R8_SPI_ROM_CR    = 0b111;
	R8_SPI_ROM_CTRL  = begin_code;
}

static void FLASH_ROMA_WriteAddr(UINT32 rom_addr)
{
	FLASH_ROMA_DataWrite((rom_addr >> 16) & 0xff);
	FLASH_ROMA_DataWrite((rom_addr >> 8)  & 0xff);
	FLASH_ROMA_DataWrite( rom_addr        & 0xff);
}

static UINT8 FLASH_ROMA_ReadByteInternal()
{
	FLASH_ROMA_DataRead();
	FLASH_ROMA_DataRead();
	FLASH_ROMA_DataRead();
	return R8_SPI_ROM_DATA;
}

/*******************************************************************************
 * @fn     FLASH_ROMA_ReadByte
 *
 * @brief  read a single byte from internal flash memory
 *
 * @param  addr - memory location to read from
 *
 * @return data - the data which has been read
 **/
UINT8 FLASH_ROMA_ReadByte(UINT32 addr)
{
	UINT32 rom_addr = addr + ROM_ADDR_OFFSET;
	FLASH_ROMA_Begin(ROM_BEGIN_READ);
	FLASH_ROMA_WriteAddr(rom_addr);
	UINT8 result = FLASH_ROMA_ReadByteInternal();
	FLASH_ROMA_AccessEnd();
	return result;
}

/*******************************************************************************
 * @fn     FLASH_ROMA_ReadWord
 *
 * @brief  read a single 32 bit word from internal flash memory
 *
 * @param  addr - memory location to read from
 *
 * @return data - the data which has been read
 **/
UINT32 FLASH_ROMA_ReadWord(UINT32 addr)
{
	UINT32 rom_addr = (addr & ~0b11) + ROM_ADDR_OFFSET;

	FLASH_ROMA_Begin(ROM_BEGIN_READ);
	FLASH_ROMA_WriteAddr(rom_addr);
	FLASH_ROMA_DataRead();
	FLASH_ROMA_DataRead();

	UINT32 result = FLASH_ROMA_ReadByteInternal();
	result       |= FLASH_ROMA_ReadByteInternal() << 8;
	result       |= FLASH_ROMA_ReadByteInternal() << 16;
	result       |= FLASH_ROMA_ReadByteInternal() << 24;

	FLASH_ROMA_AccessEnd();
	return result;
}

static void FLASH_ROMA_WriteStart()
{
	FLASH_ROMA_Begin(ROM_BEGIN_WRITE);
	FLASH_ROMA_AccessEnd();
	FLASH_ROMA_Begin(0b10);
}

static void FLASH_ROMA_ERASE_4K_Start()
{
	FLASH_ROMA_Begin(ROM_BEGIN_WRITE);
	FLASH_ROMA_AccessEnd();
	FLASH_ROMA_Begin(0x20);
}

static void FLASH_ROMA_ERASE_64K_Start()
{
	FLASH_ROMA_Begin(ROM_BEGIN_WRITE);
	FLASH_ROMA_AccessEnd();
	FLASH_ROMA_Begin(0xd8);
}

static UINT8 FLASH_ROMA_WriteEnd()
{
	FLASH_ROMA_AccessEnd();
	for (int i = 0; i < 0x280000; i++)
	{
		FLASH_ROMA_Begin(ROM_END_WRITE);
		FLASH_ROMA_DataRead();
		UINT8 status = FLASH_ROMA_DataRead();
		FLASH_ROMA_AccessEnd();
		if (status & 1) return 0;
	}

	return 0xff;
}

static void FLASH_ROMA_WriteEnable()
{
	// enable safe access mode
	R8_SAFE_ACCESS_SIG = 0x57;
	R8_SAFE_ACCESS_SIG = 0xa8;
	R8_GLOB_ROM_CFG |= RB_ROM_DATA_WE | RB_ROM_CODE_WE | (1 << 7);
}

static void FLASH_ROMA_WriteDisable()
{
	// enable safe access mode
	R8_SAFE_ACCESS_SIG = 0x57;
	R8_SAFE_ACCESS_SIG = 0xa8;
	R8_GLOB_ROM_CFG &= ~(RB_ROM_DATA_WE | RB_ROM_CODE_WE);
	R8_GLOB_ROM_CFG |= 1 << 7;
}

/*******************************************************************************
 * @fn     FLASH_ROMA_WRITE
 *
 * @brief  Write to flash ROM
 *
 * @param  StartAddr - memory location to write to
 * @param  Buffer    - data to write
 * @param  Length    - how many bytes to write, minimum length is 4 bytes
 *
 * @return success   - 0: failure, 1: success
 **/
UINT8 FLASH_ROMA_WRITE( UINT32 StartAddr, PVOID Buffer, UINT32 Length )
{
	// rom writes need to be word aligned
	UINT32 rom_addr = ~0b11 & StartAddr + ROM_ADDR_OFFSET;

	if (  rom_addr          >= ROM_END
			|| rom_addr + Length >= ROM_END
			|| Length            < 4)
		return 0;

	FLASH_ROMA_WriteEnable();

	UINT8 write_success;
	do
	{
		FLASH_ROMA_WriteStart();
		FLASH_ROMA_WriteAddr(rom_addr);

		// write word per word
		for (int i = 0; i < (Length >> 2); i ++)
		{
			R32_SPI_ROM_DATA = ((PUINT32)Buffer)[i];
			UINT8 cr_value = R8_SPI_ROM_CR | 0x10;
			FLASH_ROMA_Access(cr_value);
			FLASH_ROMA_Access(cr_value);
			FLASH_ROMA_Access(cr_value);
			FLASH_ROMA_Access(cr_value);
		}

		write_success = FLASH_ROMA_WriteEnd();
	}
	while (!write_success);

	FLASH_ROMA_WriteDisable();
	return 1;
}

/*******************************************************************************
 * @fn     FLASH_ROMA_ERASE_4K
 *
 * @brief  erase a 1kB ROM page
 *
 * @param  Addr - memory location to erase
 *
 * @return success   - 0: failure, 1: success
 **/
UINT8 FLASH_ROMA_ERASE_4K( UINT32 Addr )
{
	// rom writes need to be word aligned
	UINT32 rom_addr = ~0xfff & Addr + ROM_ADDR_OFFSET;

	if (rom_addr >= ROM_END) return 0;

	FLASH_ROMA_WriteEnable();
	FLASH_ROMA_ERASE_4K_Start();
	FLASH_ROMA_WriteAddr(rom_addr);
	UINT8 write_success = FLASH_ROMA_WriteEnd();
	FLASH_ROMA_WriteDisable();

	return write_success;
}

/*******************************************************************************
 * @fn     FLASH_ROMA_ERASE_64K
 *
 * @brief  erase a 64kB ROM page
 *
 * @param  Addr - memory location to erase
 *
 * @return success   - 0: failure, 1: success
 **/
UINT8 FLASH_ROMA_ERASE_64K( UINT32 Addr )
{
	// rom writes need to be word aligned
	UINT32 rom_addr = ~0xffff & Addr + ROM_ADDR_OFFSET;

	if (rom_addr >= ROM_END) return 0;

	FLASH_ROMA_WriteEnable();
	FLASH_ROMA_ERASE_64K_Start();
	FLASH_ROMA_WriteAddr(rom_addr);
	UINT8 write_success = FLASH_ROMA_WriteEnd();
	FLASH_ROMA_WriteDisable();

	return write_success;
}
