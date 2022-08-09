/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_ecdc.h
* Author             : WCH, bvernoux
* Version            : V1.1
* Date               : 2022/08/07
* Description
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#ifndef __CH56x_ECDC_H__
#define __CH56x_ECDC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Encryption and decryption mode */
#define   MODE_SM4_ECB        0
#define   MODE_AES_ECB        1
#define   MODE_SM4_CTR        2
#define   MODE_AES_CTR        3

/* Endian mode */
#define   MODE_BIG_ENDIAN     1
#define   MODE_LITTLE_ENDIAN  0

/* Key length */
#define   KEYLENGTH_128BIT    0
#define   KEYLENGTH_192BIT    1
#define   KEYLENGTH_256BIT    2

/* Encryption and decryption speed */
#define   ECDCCLK_DISABLE     1
#define   ECDCCLK_240MHZ      2
#define   ECDCCLK_160MHZ      3

/* Orientation and Mode */
#define   SELFDMA_ENCRY				0x84
#define   SELFDMA_DECRY				0x8c
#define   SINGLEREGISTER_ENCRY		PERIPHERAL_TO_RAM_ENCRY
#define   SINGLEREGISTER_DECRY		PERIPHERAL_TO_RAM_DECRY
#define   PERIPHERAL_TO_RAM_ENCRY   0x02
#define   PERIPHERAL_TO_RAM_DECRY   0x0a
#define   RAM_TO_PERIPHERAL_ENCRY   0x04
#define   RAM_TO_PERIPHERAL_DECRY   0x0c

void ECDC_Init(uint8_t ecdcmode, uint8_t clkmode, uint8_t keylen, puint32_t pkey, puint32_t pcount);
void ECDC_SetKey(puint32_t pkey, uint8_t keylen);
void ECDC_SetCount(puint32_t pcount);
void ECDC_Excute(uint8_t excutemode, uint8_t endianmode);
void ECDC_SingleRegister(puint32_t pWdatbuff, puint32_t pRdatbuff);
void ECDC_SelfDMA(uint32_t ram_addr, uint32_t ram_len);
void ECDC_RloadCount(uint8_t excutemode, uint8_t endianmode, puint32_t pcount);

#ifdef __cplusplus
}
#endif

#endif  // __CH56x_ECDC_H__	
