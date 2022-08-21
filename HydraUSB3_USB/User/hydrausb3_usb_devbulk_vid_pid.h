/********************************** (C) COPYRIGHT *******************************
* File Name          : hydrausb3_usb_devbulk_vid_pid.h
* Author             : bvernoux
* Version            : V1.0
* Date               : 2022/08/20
* Description        :
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
/*
Use default USB PID/VID if not configured with usb_descriptor_set_usb_vid_pid()
https://github.com/obdev/v-usb/blob/master/usbdrv/USB-IDs-for-free.txt
PID dec (hex) | VID dec (hex) | Description of use
==============+===============+============================================
1500 (0x05dc) | 5824 (0x16c0) | For Vendor Class devices with libusb
*/
// Default USB Vendor ID
// Default VID 0x16C0 "Van Ooijen Technische Informatica"
#define USB_VID_BYTE_MSB (0x16)
#define USB_VID_BYTE_LSB (0xC0)
#define USB_VID ((USB_VID_BYTE_MSB << 8) | USB_VID_BYTE_LSB)
// Default USB Product ID
// Default PID 0x05DC
#define USB_PID_BYTE_MSB (0x05)
#define USB_PID_BYTE_LSB (0xDC)
#define USB_PID ((USB_PID_BYTE_MSB << 8) | USB_PID_BYTE_LSB)
