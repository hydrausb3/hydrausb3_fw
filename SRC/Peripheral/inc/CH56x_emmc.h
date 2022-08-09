/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_emmc.h
* Author             : WCH, bvernoux
* Version            : V1.1
* Date               : 2022/08/07
* Description
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

#ifndef __CH56x_EMMC_H__
#define __CH56x_EMMC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* CMD code */
#define EMMC_CMD0  0  /* rsp:none */
#define EMMC_CMD1  1  /* rsp:R3 SEND_OP_COND */
#define EMMC_CMD2  2  /* rsp:R2 ALL_SEND_CID */
#define EMMC_CMD3  3  /* rsp:R6 SEND_RELATIVE_ADDR */
#define EMMC_CMD6  6  /* rsp: */
#define EMMC_CMD7  7  /* rsp:Rb1 */
#define EMMC_CMD8  8  /* rsp:R7 */
#define EMMC_CMD9  9  /* rsp: */
#define EMMC_CMD11 11 /* rsp: */
#define EMMC_CMD12 12 /* rsp: */
#define EMMC_CMD13 13
#define EMMC_CMD17 17 /* rsp: READ_SINGLE_BLOCK */
#define EMMC_CMD18 18 /* rsp: READ_MULTIPLE_BLOCK */
#define EMMC_CMD24 24 /* rsp: WRITE_BLOCK */
#define EMMC_CMD25 25 /* rsp: WRITE_MILTIPLE_BLOCK */
#define EMMC_CMD41 41 /* rsp: */
#define EMMC_CMD55 55 /* rsp: */

/* operation status */
#define CMD_NULL        0x00
#define CMD_SUCCESS     0x01
#define CMD_FAILED      0x02
#define OP_SUCCESS		CMD_SUCCESS
#define OP_FAILED		CMD_FAILED
#define OP_INVALID_ADD	0x21 // invalid address

/* connection status*/
#define EMMCDisconnect 0
#define EMMCConnect    1

/* operation on EMMC */
#define EMMCCardSatus_Idle               0  /* EMMC on free */
#define EMMCCardSatus_SendSingleReadCmd  1  /* send command:read single  */
#define EMMCCardSatus_SendMultReadCmd    2  /* send command:read multiple  */
#define EMMCCardSatus_SendSingleWriteCmd 3  /* send command:write single  */
#define EMMCCardSatus_SendMultWriteCmd   4  /* send command:write multiple  */
#define EMMCCardSatus_SingleReadData     5  /* on reading single  */
#define EMMCCardSatus_MultReadData       6  /* on reading multiple  */
#define EMMCCardSatus_SingleWriteData    7  /* on writing single  */
#define EMMCCardSatus_MultWriteData      8  /* on writing multiple  */
#define EMMCCardSatus_SingleReadComp     9  /* read single done  */
#define EMMCCardSatus_MultReadComp       10 /* read multiple done  */
#define EMMCCardSatus_SingleWriteComp    11 /* write single done */
#define EMMCCardSatus_MultWriteComp      12 /* write multiple done  */

/* EMMC type  */
#define EMMCIO_CAPACITY_SD_CARD_V1_1 0
#define EMMCIO_CAPACITY_SD_CARD_V2_0 1
#define EMMCIO_HIGH_CAPACITY_SD_CARD 2
/* EMMC useful voltage type  */
#define EMMCCardVolt_3_3 (1<<0)
#define EMMCCardVolt_1_8 (1<<1)

#define EMMCPLUGIN (1<<12)

/* EMMC information */
typedef struct _EMMC_PARAMETER
{
	uint8_t  EMMCLinkSatus;   // connecting type
	uint8_t  EMMCCardSatus;   // EMMC operation status
	uint8_t  EMMCType;        // EMMC type
	uint8_t  EMMCVoltageMode; // EMMC useful voltage type  bit0:3.3v bit1:1.8v
	uint32_t EMMC_CID[4];
	uint32_t EMMC_CSD[4];
	uint16_t EMMC_RCA;        // relative address
	uint16_t EMMCSecSize;		// single section capacity
	uint32_t EMMCSecNum;		// capacity of section

	uint8_t  EMMCOpErr;		// latest error status

} EMMC_PARAMETER, *PSD_PARAMETER;

//#define RESP_TYPE_48  (0<<8)
#define RESP_TYPE_136 (1<<8)
#define RESP_TYPE_48 (2<<8)
#define RESP_TYPE_R1b (3<<8)

/* EMMC CLK SET */
#define EMMCCLK_48   10
#define EMMCCLK_60   8
#define EMMCCLK_80   6
#define EMMCCLK_96   5
#define LOWEMMCCLK	 0x1F
#define DEFAULTSDCLK EMMCCLK_48
#define HIGHEMMCCLK	 EMMCCLK_96

/* EMMCIO power */
#define EMMCIOSetPower_3_3 (R32_PA_CLR |= (1<<3)) /* PA3=0 SDIO power = 3.3v */
#define EMMCIOSetPower_1_8 (R32_PA_OUT |= (1<<3)) /* PA3=1 SDIO EMMC*/

#define EMMCSendCmd(a, b) {R32_EMMC_ARGUMENT = a; R16_EMMC_CMD_SET = b;}
#define EMMCDat0Sta (R32_EMMC_STATUS&(1<<17)) /* EMMC data0 status */

extern uint8_t EMMCIO0Init(void);
extern uint8_t CheckCMDComp(PSD_PARAMETER pEMMCPara);
extern void EMMCResetIdle(PSD_PARAMETER pEMMCPara);
extern uint8_t EMMCReadOCR(PSD_PARAMETER pEMMCPara);
extern uint8_t EMMCReadCID(PSD_PARAMETER pEMMCPara);
extern uint8_t EMMCSetRCA(PSD_PARAMETER pEMMCPara);
extern uint8_t EMMCReadCSD(PSD_PARAMETER pEMMCPara);
extern uint8_t SelectEMMCCard(PSD_PARAMETER pEMMCPara);
extern uint8_t ReadEMMCStatus(PSD_PARAMETER pEMMCPara);
extern uint8_t EMMCSetBusWidth(PSD_PARAMETER pEMMCPara, uint8_t bus_mode);
extern uint8_t EMMCSetHighSpeed(PSD_PARAMETER pEMMCPara);
extern uint8_t EMMCCardConfig(PSD_PARAMETER pEMMCPara);
extern uint8_t EMMCIOTransErrorDeal(PSD_PARAMETER pEMMCPara);
extern uint8_t EMMCCardReadEXCSD(PSD_PARAMETER pEMMCPara, puint8_t pRdatbuf);
extern uint8_t AES_EMMCWriteMulSec(PSD_PARAMETER pEMMCPara, puint32_t pReqnum, puint32_t pWdatbuf, uint32_t Lbaaddr, uint8_t excutemode, uint8_t endianmode, puint32_t pcount);
extern uint8_t AES_EMMCReadMulSec(PSD_PARAMETER pEMMCPara, puint32_t pReqnum, puint32_t pRdatbuf, uint32_t Lbaaddr, uint8_t excutemode, uint8_t endianmode, puint32_t pcount);
uint8_t EMMCCardReadOneSec(PSD_PARAMETER pEMMCPara, puint8_t pRdatbuf, uint32_t Lbaaddr);
uint8_t EMMCCardReadMulSec(PSD_PARAMETER pEMMCPara, puint16_t pReqnum, puint8_t pRdatbuf, uint32_t Lbaaddr);
uint8_t EMMCCardWriteMulSec(PSD_PARAMETER pEMMCPara, puint16_t pReqnum, puint8_t pWdatbuf, uint32_t Lbaaddr);

#ifdef __cplusplus
}
#endif

#endif		//__CH56X_EMMC_H__
