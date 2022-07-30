/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_uart.h
* Author             : WCH, bvernoux
* Version            : V1.1
* Date               : 2022/07/30
* Description
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#ifndef __CH56x_UART_H__
#define __CH56x_UART_H__

#ifdef __cplusplus
 extern "C" {
#endif

/** 
  * @brief	Line Error Status Definition
  */     
#define  STA_ERR_BREAK   RB_LSR_BREAK_ERR   // Data interval error
#define  STA_ERR_FRAME   RB_LSR_FRAME_ERR   // Data frame error
#define  STA_ERR_PAR     RB_LSR_PAR_ERR     // Parity bit error
#define  STA_ERR_FIFOOV  RB_LSR_OVER_ERR    // Receive data overflow
     
#define  STA_TXFIFO_EMP  RB_LSR_TX_FIFO_EMP // The current transmit FIFO is empty and can continue to fill the transmit data
#define  STA_TXALL_EMP   RB_LSR_TX_ALL_EMP  // All data have been sent
#define  STA_RECV_DATA   RB_LSR_DATA_RDY    // Currently receiving data

/**
  * @brief  Serial port byte trigger configuration
  */     
typedef enum
{
	UART_1BYTE_TRIG = 0, // 1 Byte trigger
	UART_2BYTE_TRIG = 1, // 2 Byte trigger
	UART_4BYTE_TRIG = 2, // 4 Byte trigger
	UART_7BYTE_TRIG = 3, // 7 Byte trigger
	
}UARTByteTRIGTypeDef;     
 
/****************** UART0 */ 
void UART0_init(uint32_t baudrate, uint32_t systemclck);
void UART0_DefInit(void); /* Serial Default initialization configuration */
void UART0_BaudRateCfg(UINT32 baudrate); /* Serial Baud rate configuration */
void UART0_ByteTrigCfg(UARTByteTRIGTypeDef b); /*Serial Byte-triggered interrupt configuration */
void UART0_INTCfg(UINT8 s,  UINT8 i); /* Serial Interrupt configuration */
void UART0_Reset(void); /* Serial Software reset */

#define UART0_CLR_RXFIFO() (R8_UART0_FCR |= RB_FCR_RX_FIFO_CLR) /* Clear current RX FIFO */
#define UART0_CLR_TXFIFO() (R8_UART0_FCR |= RB_FCR_TX_FIFO_CLR) /* Clear the current TX FIFO */

#define UART0_GetITFlag() (R8_UART0_IIR & RB_IIR_INT_MASK) /* Get current interrupt flag */
// please refer to LINE error and status define
#define UART0_GetLinSTA() (R8_UART0_LSR) /* Get current communication status */
#define UART0_GetMSRSTA() (R8_UART0_MSR) /* Get the current flow control state, only applicable UART0 */

#define	UART0_SendByte(b) (R8_UART0_THR = b) /* Serial Single byte send */
void UART0_SendString(PUINT8 buf, UINT16 l); /* Serial Multibyte send */
#define UART0_tx UART0_SendString

#define	UART0_RecvByte() (R8_UART0_RBR) /* Serial Read single byte */
UINT16 UART0_RecvString(PUINT8 buf); /*Serial Read multiple bytes */
uint16_t UART0_rx(uint8_t* buf, int buf_len_max);

/****************** UART1 */ 	 
void UART1_init(uint32_t baudrate, uint32_t systemclck);
void UART1_DefInit(void); /*Serial Default initialization configuration */
void UART1_BaudRateCfg(UINT32 baudrate); /*Serial Baud rate configuration */
void UART1_ByteTrigCfg(UARTByteTRIGTypeDef b); /*Serial Byte-triggered interrupt configuration */
void UART1_INTCfg(UINT8 s,  UINT8 i); /*Serial Interrupt configuration */
void UART1_Reset(void); /*Serial Software reset */

#define UART1_CLR_RXFIFO() (R8_UART1_FCR |= RB_FCR_RX_FIFO_CLR) /* Clear current receive FIFO */
#define UART1_CLR_TXFIFO() (R8_UART1_FCR |= RB_FCR_TX_FIFO_CLR) /* Clear the current TX FIFO */

#define UART1_GetITFlag() (R8_UART1_IIR&RB_IIR_INT_MASK) /* Get current interrupt flag */
// please refer to LINE error and status define
#define UART1_GetLinSTA() (R8_UART1_LSR) /* Get current communication status */

#define	UART1_SendByte(b) (R8_UART1_THR = b) /*Serial Single byte send */
void UART1_SendString(PUINT8 buf, UINT16 l); /*Serial Multibyte send */
#define UART1_tx UART1_SendString

#define	UART1_RecvByte() (R8_UART1_RBR) /* Serial Read single byte */
UINT16 UART1_RecvString(PUINT8 buf); /* Serial Read multiple bytes */
uint16_t UART1_rx(uint8_t* buf, int buf_len_max);

/****************** UART2 */ 
void UART2_init(uint32_t baudrate, uint32_t systemclck);
void UART2_DefInit(void); /*Serial Default initialization configuration */
void UART2_BaudRateCfg(UINT32 baudrate); /*Serial Baud rate configuration */
void UART2_ByteTrigCfg(UARTByteTRIGTypeDef b); /*Serial Byte-triggered interrupt configuration */
void UART2_INTCfg(UINT8 s,  UINT8 i); /*Serial Interrupt configuration */
void UART2_Reset(void); /*Serial Software reset */

#define UART2_CLR_RXFIFO() (R8_UART2_FCR |= RB_FCR_RX_FIFO_CLR) /* Clear current receive FIFO */
#define UART2_CLR_TXFIFO() (R8_UART2_FCR |= RB_FCR_TX_FIFO_CLR) /* Clear the current TX FIFO */

#define UART2_GetITFlag() (R8_UART2_IIR&RB_IIR_INT_MASK) /* Get current interrupt flag */
// please refer to LINE error and status define
#define UART2_GetLinSTA() (R8_UART2_LSR) /* Get current communication status */

#define	UART2_SendByte(b) (R8_UART2_THR = b) /* Serial Single byte send */
void UART2_SendString(PUINT8 buf, UINT16 l); /* Serial Multibyte send */
#define UART2_tx UART2_SendString

#define	UART2_RecvByte() (R8_UART2_RBR) /* Serial Read single byte */
UINT16 UART2_RecvString(PUINT8 buf); /* Serial Read multiple bytes */
uint16_t UART2_rx(uint8_t* buf, int buf_len_max);

/****************** UART3 */ 
void UART3_init(uint32_t baudrate, uint32_t systemclck);
void UART3_DefInit(void); /* Serial Default initialization configuration */
void UART3_BaudRateCfg(UINT32 baudrate); /* Serial Baud rate configuration */
void UART3_ByteTrigCfg(UARTByteTRIGTypeDef b); /* Serial Byte-triggered interrupt configuration */
void UART3_INTCfg(UINT8 s,  UINT8 i); /* Serial Interrupt configuration */
void UART3_Reset(void); /* Serial Software reset */

#define UART3_CLR_RXFIFO() (R8_UART3_FCR |= RB_FCR_RX_FIFO_CLR) /* Clear current RX FIFO */
#define UART3_CLR_TXFIFO() (R8_UART3_FCR |= RB_FCR_TX_FIFO_CLR) /* Clear the current TX FIFO */

#define UART3_GetITFlag() (R8_UART3_IIR&RB_IIR_INT_MASK) /* Get current interrupt flag */
// please refer to LINE error and status define
#define UART3_GetLinSTA() (R8_UART3_LSR) /* Get current communication status */

#define	UART3_SendByte(b) (R8_UART3_THR = b) /*Serial Single byte send */
void UART3_SendString(PUINT8 buf, UINT16 l); /*Serial Multibyte send */
#define UART3_tx UART3_SendString

#define	UART3_RecvByte() (R8_UART3_RBR) /*Serial Read single byte */
UINT16 UART3_RecvString(PUINT8 buf); /*Serial Read multiple bytes */
uint16_t UART3_rx(uint8_t* buf, int buf_len_max);

#ifdef __cplusplus
}
#endif

#endif  // __CH56x_UART_H__	
