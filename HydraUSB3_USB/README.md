## HydraUSB3_USB

### HydraUSB3_USB firmware
HydraUSB3_USB repository contains open source (see [LICENSE](../LICENSE)) test firmware for HydraUSB3 v1 board using WCH CH569W MCU.
* Contributor shall check [CODING_STYLE.md](../CODING_STYLE.md)
* For more details on HydraUSB3 v1 see https://hydrabus.com/hydrausb3-v1-0-specifications

The aim of this example is to use USB2 High Speed and USB3 Super Speed (Device Bulk) with following features/API:
* Main code available in [User/Main.c](User/Main.c)
* Detection of USB2 or USB3 connection using global g_DeviceConnectstatus
  * ULED blink if USB2 or USB3 is connected
* The USB2/USB3 Device stack support following USB commands (see [User/usb_cmd.c](User/usb_cmd.c))
  * `USB_CMD_LOGR` : Returns internal logs data over USB2/USB3 (log_printf()/cprintf())
  * `USB_CMD_USBS` : Return USB status of actual used USB (USB2 or USB3)
  * `USB_CMD_USB2` : Switch to USB2 even if USB3 is available
  * `USB_CMD_USB3` : Switch to USB3 or do a fall-back to USB2 if not available
  * `USB_CMD_BOOT` : Reboot the board
* USB Bulk Endpoints configuration (see [wch-ch56x-bsp/usb/usb_devbulk](wch-ch56x-bsp/usb/usb_devbulk))
  * Endpoint1 is used for command/answer with 4KiB buffer(IN) and  4KiB buffer(OUT)
      * This Endpoint use 4 burst over USB3 (4KiB)
  * Endpoint2 is used for fast USB streaming with 8KiB buffers(IN/OUT)
    * This Endpoint use 8 burst over USB3 (8KiB)
* The USB2/USB3 Device stack is fully compatible with Linux
* The USB2/USB3 Device stack support automatic plug&play driver installation(WinUSB) for Windows8 or more 
   * Windows Compatible ID see https://github.com/pbatard/libwdi/wiki/WCID-Devices#What_is_WCID
   * For the USB descriptors (see [wch-ch56x-bsp/usb/usb_devbulk/CH56x_usb_devbulk_desc_cmd.c](https://github.com/hydrausb3/wch-ch56x-bsp/blob/main/usb/usb_devbulk/CH56x_usb_devbulk_desc_cmd.c))
   * USB String Serial Number include unique 64bits identifier for each board
     * Example format "HydraUSB3_SN:0123456789ABCDEF"
   * USB2.0 / 3.0 Binary Device Object Store (BOS) descriptor
   * USB2.0 / 3.0 Microsoft OS 2.0 descriptor for Windows 8 or more
   * USB2.0 / 3.0 Compatible Id (WINUSB) for Windows 8 or more
   * USB2.0 / 3.0 Property Header (Device GUID) for Windows 8 or more

This firmware shall be used with the PC tool [hydrausb3_host/HydraUSB3_USB_benchmark](https://github.com/hydrausb3/hydrausb3_host/tree/main/HydraUSB3_USB_benchmark) to check different commands and do a benchmark with different speed USB2.0 High Speed and USB3.0 Super Speed
* The USB2 High Speed benchmark reach more than 48MBytes/s average or more (depending on the PC)
* The USB3 Super Speed benchmark reach more than 330MBytes/s average or more (depending on the PC)

### Flash tool `wch-isp` (To flash this firmware on the WCH CH569 MCU)
- Pre-built binaries (Windows/Ubuntu): https://github.com/hydrausb3/wch-isp/releases
- Documentation: https://github.com/hydrausb3/wch-isp

### PC host tool `HydraUSB3_USB_benchmark` (PC host tool to communicate with this firmware)
- Pre-built binaries (Windows/Ubuntu): https://github.com/hydrausb3/hydrausb3_host/releases
- Documentation: https://github.com/hydrausb3/hydrausb3_host/tree/main/HydraUSB3_USB_benchmark

For more details on how to build and flash this example on HydraUSB3 v1 board see the Wiki:
* For GNU/Linux:
  * https://github.com/hydrausb3/hydrausb3_fw/wiki/how-to-build-flash-and-use-examples-on-linux
* For Windows:
  * https://github.com/hydrausb3/hydrausb3_fw/wiki/how-to-build-flash-and-use-examples-on-windows
