## HydraUSB3_Blink_ULED
HydraUSB3_Blink_ULED repository contains open source (see [LICENSE](../LICENSE)) test firmware for HydraUSB3 v1 board using WCH CH569W MCU.
* Contributor shall check [CODING_STYLE.md](../CODING_STYLE.md)

For more details on HydraUSB3 v1 see https://hydrabus.com/hydrausb3-v1-0-specifications

The aim of this example is to discover minimalist example with following features/API
* Log over serial port (9600 bauds 8N1 in that example) with timestamp(second, millisecond, microsecond).
  * For more details on HydraUSB3 v1 WCH CH569 UART see https://github.com/hydrausb3/hydrausb3_hw/blob/main/HydraUSB3_V1_CH569_UART.ods
* Use a delay (with API `bsp_wait_ms_delay()`).
* Read a button status **UBTN** (with API `hydrausb3_ubtn()`).
* Drive a led **ULED** (with macro `ULED_ON()` & `ULED_OFF()`) with minimal MCU speed frequency set to 15MHz (see `#define FREQ_SYS` in [User/main.c](User/main.c)).

Note:
* The current/power consumption can be checked with a multimeter in milliamps mode connected on P4 SHUNT (requires to remove the Jumper on **P4 SHUNT**).
* To check the power consumption at max speed 120MHz just change the #define FREQ_SYS in [User/Main.c](User/Main.c) to `#define FREQ_SYS (120000000)`.

This example is a very basic example to blink a LED called **ULED** (each 500ms)
* When pressing continuously **UBTN** the **ULED** blink quickly (each 100ms).
* After each blink the string "Blink" is sent on UART1 (see HydraUSB3 v1 **J5** connector => **TXD1** pin).

Example output on Serial Port:
```
00s 000ms 010us Start
00s 514ms 073us Blink
01s 028ms 040us Blink
01s 542ms 008us Blink
02s 055ms 976us Blink
02s 569ms 944us Blink
03s 083ms 912us Blink
03s 597ms 880us Blink
04s 111ms 848us Blink
04s 625ms 816us Blink
05s 139ms 784us Blink
05s 653ms 752us Blink
06s 167ms 720us Blink
06s 681ms 688us Blink
07s 195ms 656us Blink
07s 709ms 624us Blink
08s 223ms 592us Blink
08s 737ms 560us Blink
09s 251ms 528us Blink
09s 765ms 496us Blink
10s 279ms 464us Blink
10s 793ms 432us Blink
```

For more details on how to build and flash this example on HydraUSB3 v1 board see the Wiki:
* For GNU/Linux:
  * https://github.com/hydrausb3/hydrausb3_fw/wiki/how-to-build-flash-and-use-examples-on-linux
* For Windows:
  * https://github.com/hydrausb3/hydrausb3_fw/wiki/how-to-build-flash-and-use-examples-on-windows
