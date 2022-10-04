## HydraUSB3_DualBoard_HSPI
HydraUSB3_DualBoard_HSPI repository contains open source (see [LICENSE](../LICENSE)) test firmware for HydraUSB3 v1 board using WCH CH569W MCU.
* Contributor shall check [CODING_STYLE.md](../CODING_STYLE.md)
* For more details on HydraUSB3 v1 see https://hydrabus.com/hydrausb3-v1-0-specifications

This example(DualBoard) requires 2x HydraUSB3 v1 boards to be plugged together.
* First HydraUSB3 board(on bottom) shall have PB24 not populated (called RX mode)
* Seconds HydraUSB3 board(on top of First board) shall have PB24 populated with a 2.54mm Jumper (called TX mode)

The aim of this example is to use HSPI(High Speed Parallel Interface running at 120MHz with 32bits) with Dual HydraUSB3 v1 boards connected together with following features/API
* Main code available in [User/Main.c](User/Main.c)
* Log over serial port (5000000 bauds 8N1 in that example which requires USB2HS Serial like FTDI C232HM-DDHSL-0) with timestamp(second, millisecond, microsecond).
    | FTDI C232HM-DDHSL-0 Pin | HydraUSB3 Pin   |
    |-------------------------|-----------------|
    | Orange ADBUS0 TX(Pin2)  | J5 RXD1         |
    | Yellow ADBUS1 RX(Pin3)  | J5 TXD1         |
    | Black GND (Pin10)       | GND (near RXD1) |
  * For more details on HydraUSB3 v1 WCH CH569 UART see https://github.com/hydrausb3/hydrausb3_hw/blob/main/HydraUSB3_V1_CH569_UART.ods
* Usage of PB24 GPIO to detect TX mode/RX mode board (with API `bsp_switch()`)
* Synchronize 2 HydraUSB3 v1 boards at startup using 2 GPIOs (with API `bsp_sync2boards()`).
* Usage of HSPI in TX mode (with API `HSPI_DoubleDMA_Init()` and `HSPI_DMA_Tx()`)
* Usage of HSPI in RX mode (with API `HSPI_DoubleDMA_Init()`)
* Usage of HSPI Interrupt see (`HSPI_IRQHandler()` see Transmit/Receive code)

This example is a very basic example to sent 32K data over HSPI from one board to an other board
* When pressing continuously **UBTN** 32K are sent in loop on HSPI with **ULED** blink quickly (each 100ms).

Example output on Serial Port on RXD1:
```
00s 006ms 034us SYNC 00103087
00s 000ms 000us Start
00s 000ms 076us HSPI_Rx 2022/07/30 @ChipID=69
00s 000ms 215us FSYS=120000000
00s 000ms 322us HSPI RX Data_Size=2
00s 000ms 441us Clear RAMX 32K
00s 000ms 726us DMA_RX_Addr0[0]=0x00000000 [8191]=0x00000000
00s 000ms 924us Wait Rx
00s 001ms 380us Rx_End
00s 001ms 935us Verify suc
00s 002ms 022us DMA_RX_Addr0[0]=0x55555555 [8191]=0x55557554
00s 002ms 210us Clear RAMX 32K
00s 002ms 495us DMA_RX_Addr0[0]=0x00000000 [8191]=0x00000000
00s 002ms 688us Wait Rx
```

Example output on Serial Port on TXD1:
```
00s 000ms 020us SYNC 00000001
00s 000ms 000us Start
00s 000ms 076us HSPI_Tx 2022/07/30 @ChipID=69
00s 000ms 215us FSYS=120000000
00s 000ms 322us HSPI TX Data_Size=2
00s 000ms 446us Write RAMX 0x20020000 32K
00s 000ms 979us Wait 100us
00s 001ms 166us Start Tx 32K data
00s 001ms 378us Tx 32K data suc
00s 001ms 480us Wait 20ms before blink loop
```

For more details on how to build and flash this example on HydraUSB3 v1 board see the Wiki:
* For GNU/Linux:
  * https://github.com/hydrausb3/hydrausb3_fw/wiki/how-to-build-flash-and-use-examples-on-linux
* For Windows:
  * https://github.com/hydrausb3/hydrausb3_fw/wiki/how-to-build-flash-and-use-examples-on-windows
