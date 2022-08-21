/********************************** (C) COPYRIGHT *******************************
* File Name          : usb_cmd.h
* Author             : bvernoux
* Version            : V1.0
* Date               : 2022/08/20
* Description        :
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#ifndef USB_CMD_H_
#define USB_CMD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "CH56x_usb_devbulk_desc_cmd.h"

/* USB2 or USB3 commands from Host to Device */
#define USB_CMD_LOGR (0x4C4F4752) // CMD LOGR (Return LOG)
#define USB_CMD_USBS (0x55534253) // CMD USBS (USB Status)
#define USB_CMD_USB2 (0x55534232) // CMD USB2 (Switch to USB2 even if USB3 is available)
#define USB_CMD_USB3 (0x55534233) // CMD USB3 (Switch to USB3 or do a fall-back to USB2 if not available)
#define USB_CMD_BOOT (0x424F4F54) // CMD BOOT (Reboot the board)

#define CMD_USB_INFO_BUF_SIZE (4096-1) /* Maximum string size */
extern char cmd_usb_info_buf[CMD_USB_INFO_BUF_SIZE+1];

#ifdef __cplusplus
}
#endif

#endif /* USB_CMD_H_ */
