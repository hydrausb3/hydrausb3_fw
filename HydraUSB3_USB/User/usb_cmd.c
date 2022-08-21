/********************************** (C) COPYRIGHT *******************************
* File Name          : usb_cmd.c
* Author             : bvernoux
* Version            : V1.0
* Date               : 2022/08/20
* Description 		 :
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#include "CH56x_common.h"
#include "CH56x_usb20_devbulk.h"
#include "CH56x_usb30_devbulk.h"
#include "CH56x_usb30_devbulk_LIB.h"

#include "CH56x_debug_log.h"
#include "usb_cmd.h"

static int usb_cmd_val_last = 0;

extern debug_log_buf_t log_buf;
char cmd_usb_info_buf[CMD_USB_INFO_BUF_SIZE+1];

/*******************************************************************************
 * @fn     usb_cmd_rx
 *
 * @brief  Callback called by USB2 & USB3 endpoint 1
 *         - For USB3 this usb_cmd_rx() is called from IRQ(USBHS_IRQHandler)
 *           with rx_usb_dma_buff containing 4096 bytes (DEF_ENDP1_MAX_SIZE)
 *         - For USB2 this usb_cmd_rx() is called from IRQ USB30_IRQHandler->EP1_OUT_Callback)
 *           with rx_usb_dma_buff containing 4096 bytes (DEF_ENDP1_MAX_SIZE)
 *
 * @param  usb_type: USB Type (USB2 HS or USB3 SS)
 * @param  rx_usb_dma_buff: USB RX DMA buffer containing 4096 bytes of data
 *                          Data received from USB
 * @param  tx_usb_dma_buff: USB TX DMA buffer containing 4096 bytes of data
 *                          Data to be transmitted over USB
 *
 * @return None
 */
void usb_cmd_rx(e_usb_type usb_type, uint8_t* rx_usb_dma_buff, uint8_t* tx_usb_dma_buff)
{
	uint32_t* cmd = (uint32_t*)(rx_usb_dma_buff);

	uint32_t cmd_val = cmd[0];
	switch(cmd_val)
	{
		case USB_CMD_LOGR:
		{
			usb_cmd_val_last = USB_CMD_LOGR;
			log_printf("cmd LOGR\n");
			memcpy(tx_usb_dma_buff, log_buf.buf, log_buf.idx); // Copy log_buff to endp1Tbuff for next receive EP1_IN_Callback
			tx_usb_dma_buff[log_buf.idx] = 0; // Add end of string
			/* Reset Log buffer index to 0 */
			log_buf.idx = 0;
		}
		break;

		case USB_CMD_USBS:
		{
			usb_cmd_val_last = USB_CMD_USBS;
			if(usb_type == USB_TYPE_USB3)
			{
				log_printf("cmd USBS USB3\n");
				snprintf(cmd_usb_info_buf, CMD_USB_INFO_BUF_SIZE, "USBS USB3:\n"
						 "LINK_STATUS=0x%08X\n"
						 "LINK_ERR_STATUS=0x%08X\n"
						 "LINK_ERR_CNT=0x%08X",
						 USBSS->LINK_STATUS,
						 USBSS->LINK_ERR_STATUS,
						 USBSS->LINK_ERR_CNT);
			}
			else
			{
				log_printf("cmd USBS USB2\n");
				if((R8_USB_SPD_TYPE & RB_USBSPEED_MASK) == 1)
				{
					snprintf(cmd_usb_info_buf, CMD_USB_INFO_BUF_SIZE, "USBS USB2:\n"
							 "USB2 SPEED=%d (0=FS,1=HS,2=LS)\nTest end with success\n",
							 (R8_USB_SPD_TYPE & RB_USBSPEED_MASK));
				}
				else
				{
					snprintf(cmd_usb_info_buf, CMD_USB_INFO_BUF_SIZE, "USBS USB2:\n"
							 "USB2 SPEED=%d (0=FS,1=HS,2=LS)\nTest failure end with error\n",
							 (R8_USB_SPD_TYPE & RB_USBSPEED_MASK));
				}
			}
			memcpy(tx_usb_dma_buff, cmd_usb_info_buf, DEF_ENDP1_MAX_SIZE); // Copy cmd_usb_info_buf to endp1Tbuff for next receive EP1_IN_Callback
		}
		break;

		case USB_CMD_USB2:
		{
			usb_cmd_val_last = USB_CMD_USB2;
			log_printf("cmd USB2\n");
			if(usb_type == USB_TYPE_USB3)
			{
				log_printf("Force USB2\n");
				USB2_force();
			}
		}
		break;

		case USB_CMD_USB3:
		{
			usb_cmd_val_last = USB_CMD_USB3;
			log_printf("cmd USB3\n");
			if(usb_type == USB_TYPE_USB2)
			{
				log_printf("Force USB3\n");
				USB3_force();
			}
		}
		break;

		case USB_CMD_BOOT: /* Reboot (execute reset) */
		{
			SYS_ResetExecute();
		}
		break;

		default:
			log_printf("CMD UNKN\n");
	}
}
