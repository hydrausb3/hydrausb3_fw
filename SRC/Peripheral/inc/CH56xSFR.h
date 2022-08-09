/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56xSFR.h
* Author             : WCH, bvernoux(ADDR USBSS/SERDES)
* Version            : V1.1
* Date               : 2022/08/07
* Description
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#ifndef __BASE_TYPE__
#define __BASE_TYPE__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ********************************************************************************************************************* */
/* Base types & constants */

#ifndef NULL
#define NULL    0
#endif

#ifndef bool_t
typedef _Bool bool_t;
#endif

#ifndef vuint8_t
typedef unsigned char volatile vuint8_t;
#endif
#ifndef vuint16_t
typedef unsigned short volatile vuint16_t;
#endif
#ifndef vuint32_t
typedef unsigned long volatile vuint32_t;
#endif
#ifndef vuint64_t
typedef unsigned long long volatile vuint64_t;
#endif

#ifndef pint8_t
typedef char *pint8_t;
#endif
#ifndef pint16_t
typedef short *pint16_t;
#endif
#ifndef pint32_t
typedef long *pint32_t;
#endif
#ifndef puint8_t
typedef unsigned char *puint8_t;
#endif
#ifndef puint16_t
typedef unsigned short *puint16_t;
#endif
#ifndef puint32_t
typedef unsigned long *puint32_t;
#endif
#ifndef vpuint8_t
typedef volatile unsigned char *vpuint8_t;
#endif
#ifndef vpuint16_t
typedef volatile unsigned short *vpuint16_t;
#endif
#ifndef vpuint32_t
typedef volatile unsigned long *vpuint32_t;
#endif

/* ********************************************************************************************************************* */
/* Base macros */

#ifndef min
#define min(a, b)    (((a) < (b)) ? (a) : (b))
#endif
#ifndef max
#define max(a, b)    (((a) > (b)) ? (a) : (b))
#endif

#ifdef DEBUG
#define PRINT(X...)    printf(X)
#else
#define PRINT(X...)
#endif

/* Calculate the byte offset of a field in a structure of type */
#define FIELD_OFFSET(Type, Field)       ((uint16_t) & (((Type *)0)->Field))

/* Calculate the size of a field in a structure of type */
#define FIELD_SIZE(Type, Field)         (sizeof(((Type *)0)->Field))

/* An expression that yields the type of a field in a struct */
#define FIELD_TYPE(Type, Field)         (((Type *)0)->Field)

/* Return the number of elements in a statically sized array */
#define NUMBER_OF(Array)                (sizeof(Array) / sizeof((Array)[0]))
#define NUMBER_OF_FIELD(Type, Field)    (NUMBER_OF(FIELD_TYPE(Type, Field)))

#ifdef __cplusplus
}
#endif

#endif // __BASE_TYPE__

#ifndef __CH56xGPSFR_H__
#define __CH56xGPSFR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* ********************************************************************************************************************* */

// Address Space
//    CODE:   00000000H - 0007FFFFH   512KB
//    DATA:   20000000H - 20003FFFH   16KB
//    DATAX:  20020000H - 20037FFFH   96KB (Min:32KB, Max:96KB)
//    SFR:    40000000H - 4000FFFFH   64KB
//    BUS:    80000000H - 80007FFFH   32KB
//
//    SFR:    40000000H - 4000FFFFH, 64KB
//      SYS:     +1000H - 13FFH, include base configuration, interrupt, GPIO, etc...
//      TMR0:    +2000H - 23FFH
//      TMR1:    +2400H - 27FFH
//      TMR2:    +2800H - 2BFFH
//      UART0:   +3000H - 33FFH
//      UART1:   +3400H - 37FFH
//      UART2:   +3800H - 3BFFH
//      UART3:   +3C00H - 3FFFH
//      SPI0:    +4000H - 43FFH
//      SPI1:    +4400H - 47FFH
//      PWMX:    +5000H - 53FFH
//      HSPI:     +6000H - 63FFH
//      ECDC:     +7000H - 73FFH
//      USBSS:   +8000H - 83FFH
//      USBHS:   +9000H - 93FFH
//      EMMC:    +A000H - A3FFH
//      SERDES:  +B000H - B3FFH
//      ETH:     +C000H - D3FFH
//      DVP:     +E000H - E3FFH

// Register Bit Attribute / Bit Access Type
//   RF:    Read only for Fixed value
//   RO:    Read Only (internal change)
//   RZ:    Read only with auto clear Zero
//   WO:    Write Only (read zero or different)
//   WA:    Write only under safe Accessing mode (read zero or different)
//   WZ:    Write only with auto clear Zero
//   RW:    Read / Write
//   RWA:   Read / Write under safe Accessing mode
//   RW1:   Read / Write 1 to Clear

/* Register name rule:
   R32_* for 32 bits register (uint32_t,ULONG)
   R16_* for 16 bits register (uint16_t,USHORT)
   R8_*  for  8 bits register (uint8_t,UCHAR)
   RB_*  for bit or bit mask of 8 bit register
   BA_*  for base address point
   b*    for GPIO bit mask
   Others for register address offset */

/* ********************************************************************************************************************* */

/* System: safe accessing register */
#define R32_SAFE_ACCESS         (*((vpuint32_t)0x40001000)) // RW, safe accessing
#define R8_SAFE_ACCESS_SIG      (*((vpuint8_t)0x40001000))  // WO, safe accessing sign register, must write 0x57 then 0xA8 to enter safe accessing mode
#define RB_SAFE_ACC_MODE        0x03                      // RO, current safe accessing mode: 11=safe/unlocked (SAM), other=locked (00..01..10..11)
#define RB_SAFE_ACC_TIMER       0x70                      // RO, safe accessing timer bit mask (16*clock number)
#define R8_CHIP_ID              (*((vpuint8_t)0x40001001))  // RF, chip ID register, always is ID_CH569W
#define R8_SAFE_ACCESS_ID       (*((vpuint8_t)0x40001002))  // RF, safe accessing ID register, always 0x02
#define R8_WDOG_COUNT           (*((vpuint8_t)0x40001003))  // RW, watch-dog count, count by clock frequency Fsys/524288

/* System: global configuration register */
#define R32_GLOBAL_CONFIG       (*((vpuint32_t)0x40001004)) // RW, global configuration
#define R8_GLOB_ROM_CFG         (*((vpuint8_t)0x40001004))  // RWA, flash ROM configuration, SAM and bit7:6 must write 1:0
#define RB_ROM_EXT_RE           0x01                      // RWA, enable flash ROM being read by external programmer: 0=reading protect, 1=enable read
#define RB_CODE_RAM_WE          0x02                      // RWA, enable code RAM being write: 0=writing protect, 1=enable write
#define RB_ROM_DATA_WE          0x04                      // RWA, enable flash ROM data area being erase/write: 0=writing protect, 1=enable program and erase
#define RB_ROM_CODE_WE          0x08                      // RWA, enable flash ROM code & data area being erase/write: 0=writing protect, 1=enable program and erase
#define RB_ROM_CODE_OFS         0x10                      // RWA,
//#define  RB_GLOB_BOOT_APP   0x10                      // RO, boot loader action status
#define R8_RST_BOOT_STAT        (*((vpuint8_t)0x40001005)) // RO, reset status and boot/debug status, bit7:6 always are 1:1
#define RB_RESET_FLAG           0x03                     // RO: recent reset flag
#define RST_FLAG_SW             0x00
#define RST_FLAG_POR            0x01
#define RST_FLAG_WDOG           0x02
#define RST_FLAG_PIN            0x03
// RB_RESET_FLAG: recent reset flag
//    00 - software reset, by RB_SOFTWARE_RESET=1 @(RB_BOOT_LOADER=0 or RB_WDOG_RST_EN=1), or set reset request from PFIC
//    01 - power on reset
//    10 - watch-dog timer overflow reset, or CORE LOCKUP reset
//    11 - external manual reset by RST# pin input low
#define RB_CFG_RESET_EN         0x04                     // RO, manual reset input enable status
#define RB_CFG_BOOT_EN          0x08                     // RO, boot-loader enable status
#define RB_CFG_DEBUG_EN         0x10                     // RO, debug enable status
#define RB_BOOT_LOADER          0x20                     // RO, indicate boot loader status: 0=application status (by software reset), 1=boot loader status
#define R8_RST_WDOG_CTRL        (*((vpuint8_t)0x40001006)) // RWA, reset and watch-dog control, SAM and bit7:6 must write 0:1
#define RB_SOFTWARE_RESET       0x01                     // WA/WZ, global software reset, high action, auto clear
#define RB_WDOG_RST_EN          0x02                     // RWA, enable watch-dog reset if watch-dog timer overflow: 0=as timer only, 1=enable reset if timer overflow
#define RB_WDOG_INT_EN          0x04                     // RWA, watch-dog interrupt enable or INT_ID_WDOG interrupt source selection: 0=software interrupt, 1=from watch-dog timer overflow
#define RB_WDOG_INT_FLAG        0x10                     // RW1, watch-dog timer overflow interrupt flag, cleared by RW1 or reload watch-dog count
#define R8_GLOB_RESET_KEEP      (*((vpuint8_t)0x40001007)) // RW, value keeper during global reset

/* System: clock configuration register */
#define R32_CLOCK_CONFIG        (*((vpuint32_t)0x40001008)) // RWA, clock configuration, SAM
#define R8_CLK_PLL_DIV          (*((vpuint8_t)0x40001008))  // RWA, output clock divider from PLL, only low 4 bit, SAM and bit7:6 must write 0:1
#define R8_CLK_CFG_CTRL         (*((vpuint8_t)0x4000100A))  // RWA, clock control, SAM and bit7:6 must write 1:0
#define RB_CLK_PLL_SLEEP        0x01                      // RWA, PLL sleep control: 0=PLL run, 1=PLL sleep
#define RB_CLK_SEL_PLL          0x02                      // RWA, clock source selection: 0=oscillator 30MHz, 1=PLL 300MHz/480MHz
// OSC_FREQ = 30MHz
// PLL_FREQ = 300MHz/480MHz
// SRC_FREQ = RB_CLK_SEL_PLL ? PLL_FREQ : OSC_FREQ
// SYS_FREQ = SRC_FREQ / R8_CLK_PLL_DIV, 2MHz ~ 120MHz
// default: SRC_FREQ = 30MHz/2 = 15MHz
#define R8_CLK_MOD_AUX          (*((vpuint8_t)0x4000100B)) // RWA, clock mode aux register
#define RB_SRC_125M_MSK         0x03                     // RWA, ETH 125MHz clock enable, high enable,[1]: clock from pin_pa[16], [0]: clock from USB_PHY PCLK(125MHz)
#define RB_EXT_125M_EN          0x02
#define RB_INT_125M_EN          0x01
#define RB_MCO_SEL_MSK          0x0C        // RWA, MCO output selection: 00=125M, 01=25M, 1x=2.5M
#define RB_SEL_125M             0x00
#define RB_SEL_25M              0x04
#define RB_SEL_2P5M             0x08
#define RB_MCO_EN               0x10        // RWA, MCO output enable, high action

/* System: sleep control register */
#define R32_SLEEP_CONTROL       (*((vpuint32_t)0x4000100C)) // RWA, sleep control, SAM
#define R8_SLP_CLK_OFF0         (*((vpuint8_t)0x4000100C))  // RWA, sleep clock off control byte 0, SAM
#define RB_SLP_CLK_TMR0         0x01                      // RWA, sleep TMR0 clock
#define RB_SLP_CLK_TMR1         0x02                      // RWA, sleep TMR1 clock
#define RB_SLP_CLK_TMR2         0x04                      // RWA, sleep TMR2 clock
#define RB_SLP_CLK_PWMX         0x08                      // RWA, sleep PWMX clock
#define RB_SLP_CLK_UART0        0x10                      // RWA, sleep UART0 clock
#define RB_SLP_CLK_UART1        0x20                      // RWA, sleep UART1 clock
#define RB_SLP_CLK_UART2        0x40                      // RWA, sleep UART2 clock
#define RB_SLP_CLK_UART3        0x80                      // RWA, sleep UART3 clock
#define R8_SLP_CLK_OFF1         (*((vpuint8_t)0x4000100D))  // RWA, sleep clock off control byte 1, SAM
#define RB_SLP_CLK_SPI0         0x01                      // RWA, sleep SPI0 clock
#define RB_SLP_CLK_SPI1         0x02                      // RWA, sleep SPI1 clock
#define RB_SLP_CLK_EMMC         0x04                      // RWA, sleep EMMC clock
#define RB_SLP_CLK_HSPI         0x08                      // RWA, sleep HSPI clock
#define RB_SLP_CLK_USBHS        0x10                      // RWA, sleep USBHS clock
#define RB_SLP_CLK_USBSS        0x20                      // RWA, sleep USBSS clock
#define RB_SLP_CLK_SERD         0x40                      // RWA, sleep SERDES clock
#define RB_SLP_CLK_DVP          0x80                      // RWA, sleep DVP clock
#define R8_SLP_WAKE_CTRL        (*((vpuint8_t)0x4000100E))  // RWA, wake control, SAM
#define RB_SLP_USBHS_WAKE       0x01                      // RWA, enable USBHS waking
#define RB_SLP_USBSS_WAKE       0x02                      // RWA, enable USBSS waking
#define RB_SLP_CLK_ETH          0x04                      // RWA, sleep ETH clock
#define RB_SLP_CLK_ECDC         0x08                      // RWA, sleep ECDC CLOCK
#define RB_SLP_GPIO_WAKE        0x10                      // RWA, enable GPIO waking
#define RB_SLP_ETH_WAKE         0x20                      // RWA, enable Eth waking
#define R8_SLP_POWER_CTRL       (*((vpuint8_t)0x4000100F))  // RWA, power control, SAM
#define RB_SLP_USBHS_PWRDN      0x01                      // RWA, enable USBHS power down

/* System: port and bus configuration register */
#define R32_PORT_CONFIG         (*((vpuint32_t)0x40001010)) // RW, port and bus configuration
#define R8_XBUS_CONFIG          (*((vpuint8_t)0x40001010))  // RW, external bus configuration
#define RB_XBUS_ENABLE          0x01                      // RW, external bus enable: 0=disable, 1=enable bRD and bWR, enable PA[7:0] as parallel DATA port
#define RB_XBUS_ADDR_OE         0x0C                      // RW, external bus address output enable: 00=none, 01=PB[5:0], 10=PB[9:0], 11=PB[14:0]
#define RB_XBUS_WIDTH           0x30                      // RW, external bus access pulse width: 00=3 clocks, 01=5 clocks, 10= 9 clocks, 11=16 clocks
#define RB_XBUS_HOLD            0x40                      // RW, external bus hold time: 0=2 clocks, 1=3 clocks
#define RB_XBUS_SETUP           0x80                      // RW, external bus setup time: 0=2 clocks, 1=3 clocks
#define R8_PIN_ALTERNATE        (*((vpuint8_t)0x40001012))  // RW, alternate pin control
#define RB_PIN_MII              0x01                      // RW, ETH mii interface selection: 0=MII interface, 1=RGMII interface
#define RB_PIN_TMR1             0x02                      // RW, TMR1 alternate pin enable: 0=TMR1/PWM5/CAP1 on PA[4], 1=TMR1X/PWM5X/CAP1X on PB[0]
#define RB_PIN_TMR2             0x04                      // RW, TMR2 alternate pin enable: 0=TMR2/PWM6/CAP2 on PA[6], 1=TMR2X/PWM6X/CAP2X on PB[3]
#define RB_PIN_UART0            0x10                      // RW, RXD0/TXD0 alternate pin enable: 0=RXD1/TXD1 on PB[5]/PB[6], 1=RXD1X/TXD1X on PA[5]/PA[6]

/* System: Serdes Analog parameter control register */
#define R16_SERD_ANA_CFG1       (*((vpuint16_t)0x40001020)) //RWA, Serdes Analog parameter configuration1
#define R32_SERD_ANA_CFG2       (*((vpuint32_t)0x40001024)) //RWA, Serdes Analog parameter configuration2

/* System: GPIO interrupt control register */
#define R32_GPIO_INT_CTRL       (*((vpuint32_t)0x4000101C)) // RW, GPIO interrupt control
#define R8_GPIO_INT_FLAG        (*((vpuint8_t)0x4000101C))  // RW1, GPIO interrupt flag
#define R8_GPIO_INT_ENABLE      (*((vpuint8_t)0x4000101D))  // RW, GPIO interrupt enable
#define R8_GPIO_INT_MODE        (*((vpuint8_t)0x4000101E))  // RW, GPIO interrupt mode: 0=level action, 1=edge action
#define R8_GPIO_INT_POLAR       (*((vpuint8_t)0x4000101F))  // RW, GPIO interrupt polarity: 0=normal(low_level/fall_edge), 1=invert(high_level/rise_edge)

/* GPIO interrupt control register address offset and bit define */
#define BA_GPIO_INT_CTRL        ((vpuint8_t)0x4000101C) // point GPIO interrupt base address
#define GPIO_INT_FLAG           0x00
#define GPIO_INT_ENABLE         0x01
#define GPIO_INT_MODE           0x02
#define GPIO_INT_POLAR          0x03
#define RB_GPIO_PA2             0x01
#define RB_GPIO_PA3             0x02
#define RB_GPIO_PA4             0x04
#define RB_GPIO_PB3             0x08
#define RB_GPIO_PB4             0x10
#define RB_GPIO_PB11            0x20
#define RB_GPIO_PB12            0x40
#define RB_GPIO_PB15            0x80

/* GPIO PA register */
#define R32_PA_DIR              (*((vpuint32_t)0x40001040)) // RW, GPIO PA I/O direction: 0=in, 1=out
#define R8_PA_DIR_0             (*((vpuint8_t)0x40001040))  // RW, GPIO PA I/O direction byte 0
#define R8_PA_DIR_1             (*((vpuint8_t)0x40001041))  // RW, GPIO PA I/O direction byte 1
#define R8_PA_DIR_2             (*((vpuint8_t)0x40001042))  // RW, GPIO PA I/O direction byte 2
#define R32_PA_PIN              (*((vpuint32_t)0x40001044)) // RO, GPIO PA input
#define R8_PA_PIN_0             (*((vpuint8_t)0x40001044))  // RO, GPIO PA input byte 0
#define R8_PA_PIN_1             (*((vpuint8_t)0x40001045))  // RO, GPIO PA input byte 1
#define R8_PA_PIN_2             (*((vpuint8_t)0x40001046))  // RO, GPIO PA input byte 2
#define R32_PA_OUT              (*((vpuint32_t)0x40001048)) // RW, GPIO PA output
#define R8_PA_OUT_0             (*((vpuint8_t)0x40001048))  // RW, GPIO PA output byte 0
#define R8_PA_OUT_1             (*((vpuint8_t)0x40001049))  // RW, GPIO PA output byte 1
#define R8_PA_OUT_2             (*((vpuint8_t)0x4000104A))  // RW, GPIO PA output byte 2
#define R32_PA_CLR              (*((vpuint32_t)0x4000104C)) // WZ, GPIO PA clear output: 0=keep, 1=clear
#define R8_PA_CLR_0             (*((vpuint8_t)0x4000104C))  // WZ, GPIO PA clear output byte 0
#define R8_PA_CLR_1             (*((vpuint8_t)0x4000104D))  // WZ, GPIO PA clear output byte 1
#define R8_PA_CLR_2             (*((vpuint8_t)0x4000104E))  // WZ, GPIO PA clear output byte 2
#define R32_PA_PU               (*((vpuint32_t)0x40001050)) // RW, GPIO PA pullup resistance enable
#define R8_PA_PU_0              (*((vpuint8_t)0x40001050))  // RW, GPIO PA pullup resistance enable byte 0
#define R8_PA_PU_1              (*((vpuint8_t)0x40001051))  // RW, GPIO PA pullup resistance enable byte 1
#define R8_PA_PU_2              (*((vpuint8_t)0x40001052))  // RW, GPIO PA pullup resistance enable byte 2
#define R32_PA_PD               (*((vpuint32_t)0x40001054)) // RW, GPIO PA output open-drain & input pulldown resistance enable
#define R8_PA_PD_0              (*((vpuint8_t)0x40001054))  // RW, GPIO PA output open-drain & input pulldown resistance enable byte 0
#define R8_PA_PD_1              (*((vpuint8_t)0x40001055))  // RW, GPIO PA output open-drain & input pulldown resistance enable byte 1
#define R8_PA_PD_2              (*((vpuint8_t)0x40001056))  // RW, GPIO PA output open-drain & input pulldown resistance enable byte 2
#define R32_PA_DRV              (*((vpuint32_t)0x40001058)) // RW, GPIO PA driving capability: 0=8mA, 1=16mA
#define R8_PA_DRV_0             (*((vpuint8_t)0x40001058))  // RW, GPIO PA driving capability byte 0
#define R8_PA_DRV_1             (*((vpuint8_t)0x40001059))  // RW, GPIO PA driving capability byte 1
#define R8_PA_DRV_2             (*((vpuint8_t)0x4000105A))  // RW, GPIO PA driving capability byte 2
#define R32_PA_SMT              (*((vpuint32_t)0x4000105C)) // RW, GPIO PA output slew rate & input schmitt trigger: 0=fast,normal, 1=slow,schmitt
#define R8_PA_SMT_0             (*((vpuint8_t)0x4000105C))  // RW, GPIO PA output slew rate & input schmitt trigger byte 0
#define R8_PA_SMT_1             (*((vpuint8_t)0x4000105D))  // RW, GPIO PA output slew rate & input schmitt trigger byte 1
#define R8_PA_SMT_2             (*((vpuint8_t)0x4000105E))  // RW, GPIO PA output slew rate & input schmitt trigger byte 2

/* GPIO PB register */
#define R32_PB_DIR              (*((vpuint32_t)0x40001060)) // RW, GPIO PB I/O direction: 0=in, 1=out
#define R8_PB_DIR_0             (*((vpuint8_t)0x40001060))  // RW, GPIO PB I/O direction byte 0
#define R8_PB_DIR_1             (*((vpuint8_t)0x40001061))  // RW, GPIO PB I/O direction byte 1
#define R8_PB_DIR_2             (*((vpuint8_t)0x40001062))  // RW, GPIO PB I/O direction byte 2
#define R8_PB_DIR_3             (*((vpuint8_t)0x40001063))  // RW, GPIO PB I/O direction byte 3
#define R32_PB_PIN              (*((vpuint32_t)0x40001064)) // RO, GPIO PB input
#define R8_PB_PIN_0             (*((vpuint8_t)0x40001064))  // RO, GPIO PB input byte 0
#define R8_PB_PIN_1             (*((vpuint8_t)0x40001065))  // RO, GPIO PB input byte 1
#define R8_PB_PIN_2             (*((vpuint8_t)0x40001066))  // RO, GPIO PB input byte 2
#define R8_PB_PIN_3             (*((vpuint8_t)0x40001067))  // RO, GPIO PB input byte 3
#define R32_PB_OUT              (*((vpuint32_t)0x40001068)) // RW, GPIO PB output
#define R8_PB_OUT_0             (*((vpuint8_t)0x40001068))  // RW, GPIO PB output byte 0
#define R8_PB_OUT_1             (*((vpuint8_t)0x40001069))  // RW, GPIO PB output byte 1
#define R8_PB_OUT_2             (*((vpuint8_t)0x4000106A))  // RW, GPIO PB output byte 2
#define R8_PB_OUT_3             (*((vpuint8_t)0x4000106B))  // RW, GPIO PB output byte 3
#define R32_PB_CLR              (*((vpuint32_t)0x4000106C)) // WZ, GPIO PB clear output: 0=keep, 1=clear
#define R8_PB_CLR_0             (*((vpuint8_t)0x4000106C))  // WZ, GPIO PB clear output byte 0
#define R8_PB_CLR_1             (*((vpuint8_t)0x4000106D))  // WZ, GPIO PB clear output byte 1
#define R8_PB_CLR_2             (*((vpuint8_t)0x4000106E))  // WZ, GPIO PB clear output byte 2
#define R8_PB_CLR_3             (*((vpuint8_t)0x4000106F))  // WZ, GPIO PB clear output byte 3
#define R32_PB_PU               (*((vpuint32_t)0x40001070)) // RW, GPIO PB pullup resistance enable
#define R8_PB_PU_0              (*((vpuint8_t)0x40001070))  // RW, GPIO PB pullup resistance enable byte 0
#define R8_PB_PU_1              (*((vpuint8_t)0x40001071))  // RW, GPIO PB pullup resistance enable byte 1
#define R8_PB_PU_2              (*((vpuint8_t)0x40001072))  // RW, GPIO PB pullup resistance enable byte 2
#define R8_PB_PU_3              (*((vpuint8_t)0x40001073))  // RW, GPIO PB pullup resistance enable byte 3
#define R32_PB_PD               (*((vpuint32_t)0x40001074)) // RW, GPIO PB output open-drain & input pulldown resistance enable
#define R8_PB_PD_0              (*((vpuint8_t)0x40001074))  // RW, GPIO PB output open-drain & input pulldown resistance enable byte 0
#define R8_PB_PD_1              (*((vpuint8_t)0x40001075))  // RW, GPIO PB output open-drain & input pulldown resistance enable byte 1
#define R8_PB_PD_2              (*((vpuint8_t)0x40001076))  // RW, GPIO PB output open-drain & input pulldown resistance enable byte 2
#define R8_PB_PD_3              (*((vpuint8_t)0x40001077))  // RW, GPIO PB output open-drain & input pulldown resistance enable byte 3
#define R32_PB_DRV              (*((vpuint32_t)0x40001078)) // RW, GPIO PB driving capability: 0=8mA, 1=16mA
#define R8_PB_DRV_0             (*((vpuint8_t)0x40001078))  // RW, GPIO PB driving capability byte 0
#define R8_PB_DRV_1             (*((vpuint8_t)0x40001079))  // RW, GPIO PB driving capability byte 1
#define R8_PB_DRV_2             (*((vpuint8_t)0x4000107A))  // RW, GPIO PB driving capability byte 2
#define R8_PB_DRV_3             (*((vpuint8_t)0x4000107B))  // RW, GPIO PB driving capability byte 3
#define R32_PB_SMT              (*((vpuint32_t)0x4000107C)) // RW, GPIO PB output slew rate & input schmitt trigger: 0=fast,normal, 1=slow,schmitt
#define R8_PB_SMT_0             (*((vpuint8_t)0x4000107C))  // RW, GPIO PB output slew rate & input schmitt trigger byte 0
#define R8_PB_SMT_1             (*((vpuint8_t)0x4000107D))  // RW, GPIO PB output slew rate & input schmitt trigger byte 1
#define R8_PB_SMT_2             (*((vpuint8_t)0x4000107E))  // RW, GPIO PB output slew rate & input schmitt trigger byte 2
#define R8_PB_SMT_3             (*((vpuint8_t)0x4000107F))  // RW, GPIO PB output slew rate & input schmitt trigger byte 3

/* GPIO register address offset and bit define */
#define BA_PA                   ((vpuint8_t)0x40001040) // point GPIO PA base address
#define BA_PB                   ((vpuint8_t)0x40001060) // point GPIO PB base address
#define GPIO_DIR                0x00
#define GPIO_DIR_0              0x00
#define GPIO_DIR_1              0x01
#define GPIO_DIR_2              0x02
#define GPIO_DIR_3              0x03
#define GPIO_PIN                0x04
#define GPIO_PIN_0              0x04
#define GPIO_PIN_1              0x05
#define GPIO_PIN_2              0x06
#define GPIO_PIN_3              0x07
#define GPIO_OUT                0x08
#define GPIO_OUT_0              0x08
#define GPIO_OUT_1              0x09
#define GPIO_OUT_2              0x0A
#define GPIO_OUT_3              0x0B
#define GPIO_CLR                0x0C
#define GPIO_CLR_0              0x0C
#define GPIO_CLR_1              0x0D
#define GPIO_CLR_2              0x0E
#define GPIO_CLR_3              0x0F
#define GPIO_PU                 0x10
#define GPIO_PU_0               0x10
#define GPIO_PU_1               0x11
#define GPIO_PU_2               0x12
#define GPIO_PU_3               0x13
#define GPIO_PD                 0x14
#define GPIO_PD_0               0x14
#define GPIO_PD_1               0x15
#define GPIO_PD_2               0x16
#define GPIO_PD_3               0x17
#define GPIO_DRV                0x18
#define GPIO_DRV_0              0x18
#define GPIO_DRV_1              0x19
#define GPIO_DRV_2              0x1A
#define GPIO_DRV_3              0x1B
#define GPIO_SMT                0x1C
#define GPIO_SMT_0              0x1C
#define GPIO_SMT_1              0x1D
#define GPIO_SMT_2              0x1E
#define GPIO_SMT_3              0x1F

/* GPIO alias name */
/* GPIOA */
#define bHSPI6                  (1 << 0) // PA0
#define bSDD5                   (1 << 0) // PA0
#define bDVP3                   (1 << 0) // PA0
#define bHSPI5                  (1 << 1) // PA1
#define bSDD6                   (1 << 1) // PA1
#define bDVP2                   (1 << 1) // PA1
#define bHSPI4                  (1 << 2) // PA2
#define bRXD2                   (1 << 2) // PA2
#define bSDD7                   (1 << 2) // PA2
#define bDVP1                   (1 << 2) // PA2
#define bHSPI3                  (1 << 3) // PA3
#define bTXD2                   (1 << 3) // PA3
#define bDVP0                   (1 << 3) // PA3
#define bHSPI1                  (1 << 4) // PA4
#define bPWM1                   (1 << 4) // PA4
#define bTMR2                   (1 << 4) // PA4
#define bCAP2                   bTMR2
#define bPWM6                   bTMR2
#define bVSYNC                  (1 << 4) // PA4
#define bHSPI0                  (1 << 5) // PA5
#define bRXD0X                  (1 << 5) // PA5
#define bHSYNC                  (1 << 5) // PA5
#define bHSPIRV                 (1 << 6) // PA6
#define bTXD0X                  (1 << 6) // PA6
#define bPCLK                   (1 << 6) // PA6
#define bRXD1                   (1 << 7) // PA7
#define bTXD1                   (1 << 8) // PA8
#define bBUSRD                  (1 << 8) // PA8
#define bHSPITRQ                (1 << 9) // PA9
#define bTMR0                   (1 << 9) // PA9
#define bCAP0                   bTMR0
#define bPWM4                   bTMR0
#define bBUSWR                  (1 << 9)  // PA9
#define bHSPITAK                (1 << 10) // PA10
#define bDBGCK                  (1 << 10) // PA10
#define bHSPITCK                (1 << 11) // PA11
#define bDBGIO                  (1 << 11) // PA11
#define bSCS0                   (1 << 12) // PA12
#define bSCK0                   (1 << 13) // PA13
#define bMOSI0                  (1 << 14) // PA14
#define bMISO0                  (1 << 15) // PA15
#define bHSPI24                 (1 << 16) // PA16
#define bEMCI                   (1 << 16) // PA16
#define bHSPI12                 (1 << 17) // PA17
#define bHSPIRAT                (1 << 18) // PA18
#define bHSPIRCK                (1 << 19) // PA19
#define bHSPI19                 (1 << 20) // PA20
#define bEMCO                   (1 << 20) // PA20
#define bHSPITV                 (1 << 21) // PA21
#define bHSPI2                  (1 << 22) // PA22
#define bHSPITRY                (1 << 23) // PA23

/* GPIOB */
#define bHSPI16                 (1 << 0) // PB0
#define bTMR1X                  (1 << 0) // PB0
#define bCAP1X                  bTMR1X
#define bPWM5X                  bTMR1X
#define bMDIO                   (1 << 0) // PB0
#define bHSPI17                 (1 << 1) // PB1
#define bPWM2                   (1 << 1) // PB1
#define bMDCK                   (1 << 1) // PB1
#define bHSPI18                 (1 << 2) // PB2
#define bPWM3                   (1 << 2) // PB2
#define bETHT3                  (1 << 2) // PB2
#define bHSPI20                 (1 << 3) // PB3
#define bTMR2X                  (1 << 3) // PB3
#define bCAP2X                  bTMR2X
#define bPWM6X                  bTMR2X
#define bRXD3                   (1 << 3)  // PB3
#define bETHT2                  (1 << 3)  // PB3
#define bHSPI21                 (1 << 4)  // PB4
#define bTXD3                   (1 << 4)  // PB4
#define bETHT1                  (1 << 4)  // PB4
#define bHSPI22                 (1 << 5)  // PB5
#define bRXD0                   (1 << 5)  // PB5
#define bETHT0                  (1 << 5)  // PB5
#define bHSPI23                 (1 << 6)  // PB6
#define bTXD0                   (1 << 6)  // PB6
#define bETHTEN                 (1 << 6)  // PB6
#define bHSPI25                 (1 << 7)  // PB7
#define bDSR                    (1 << 7)  // PB7
#define bETHTC                  (1 << 7)  // PB7
#define bHSPI26                 (1 << 8)  // PB8
#define bRI                     (1 << 8)  // PB8
#define bETHRC                  (1 << 8)  // PB8
#define bHSPI27                 (1 << 9)  // PB9
#define bDCD                    (1 << 9)  // PB9
#define bETHR3                  (1 << 9)  // PB9
#define bHSPI28                 (1 << 10) // PB10
#define bDTR                    (1 << 10) // PB10
#define bETHR2                  (1 << 10) // PB10
#define bHSPI29                 (1 << 11) // PB11
#define bSCS1                   (1 << 11) // PB11
#define bCTS                    (1 << 11) // PB11
#define bETHR1                  (1 << 11) // PB11
#define bHSPI30                 (1 << 12) // PB12
#define bSCK1                   (1 << 12) // PB12
#define bRTS                    (1 << 12) // PB12
#define bETHR0                  (1 << 12) // PB12
#define bHSPI31                 (1 << 13) // PB13
#define bMOSI1                  (1 << 13) // PB13
#define bETHRDV                 (1 << 13) // PB13
#define bHSPI15                 (1 << 14) // PB14
#define bMISO1                  (1 << 14) // PB14
#define bSDCK                   (1 << 14) // PB14
#define bDVP11                  (1 << 14) // PB14
#define bHSPI14                 (1 << 15) // PB15
#define bTMR1                   (1 << 15) // PB15
#define bCAP1                   bTMR1
#define bPWM5                   bTMR1
#define bPWM0                   (1 << 15) // PB15
#define bDVP10                  (1 << 15) // PB15
#define bHSPI13                 (1 << 16) // PB16
#define bSDCMD                  (1 << 16) // PB16
#define bDVP9                   (1 << 16) // PB16
#define bHSPI11                 (1 << 17) // PB17
#define bSDD0                   (1 << 17) // PB17
#define bDVP8                   (1 << 17) // PB17
#define bHSPI10                 (1 << 18) // PB18
#define bSDD1                   (1 << 18) // PB18
#define bDVP7                   (1 << 18) // PB18
#define bHSPI9                  (1 << 19) // PB19
#define bSDD2                   (1 << 19) // PB19
#define bDVP6                   (1 << 19) // PB19
#define bHSPI8                  (1 << 20) // PB20
#define bSDD3                   (1 << 20) // PB20
#define bDVP5                   (1 << 20) // PB20
#define bHSPI7                  (1 << 21) // PB21
#define bSDD4                   (1 << 21) // PB21
#define bDVP4                   (1 << 21) // PB21

/* Timer0 register */
#define R32_TMR0_CONTROL        (*((vpuint32_t)0x40002000)) // RW, TMR0 control
#define R8_TMR0_CTRL_MOD        (*((vpuint8_t)0x40002000))  // RW, TMR0 mode control
#define R8_TMR0_INTER_EN        (*((vpuint8_t)0x40002002))  // RW, TMR0 interrupt enable
#define R32_TMR0_STATUS         (*((vpuint32_t)0x40002004)) // RW, TMR0 status
#define R8_TMR0_INT_FLAG        (*((vpuint8_t)0x40002006))  // RW1, TMR0 interrupt flag
#define R8_TMR0_FIFO_COUNT      (*((vpuint8_t)0x40002007))  // RO, TMR0 FIFO count status
#define R32_TMR0_COUNT          (*((vpuint32_t)0x40002008)) // RO, TMR0 current count
#define R16_TMR0_COUNT          (*((vpuint16_t)0x40002008)) // RO, TMR0 current count
#define R8_TMR0_COUNT           (*((vpuint8_t)0x40002008))  // RO, TMR0 current count
#define R32_TMR0_CNT_END        (*((vpuint32_t)0x4000200C)) // RW, TMR0 end count value, only low 26 bit
#define R32_TMR0_FIFO           (*((vpuint32_t)0x40002010)) // RO/WO, TMR0 FIFO register, only low 26 bit
#define R16_TMR0_FIFO           (*((vpuint16_t)0x40002010)) // RO/WO, TMR0 FIFO register
#define R8_TMR0_FIFO            (*((vpuint8_t)0x40002010))  // RO/WO, TMR0 FIFO register

/* Timer1 register */
#define R32_TMR1_CONTROL        (*((vpuint32_t)0x40002400)) // RW, TMR1 control
#define R8_TMR1_CTRL_MOD        (*((vpuint8_t)0x40002400))  // RW, TMR1 mode control
#define R8_TMR1_CTRL_DMA        (*((vpuint8_t)0x40002401))  // RW, TMR1 DMA control
#define R8_TMR1_INTER_EN        (*((vpuint8_t)0x40002402))  // RW, TMR1 interrupt enable
#define R32_TMR1_STATUS         (*((vpuint32_t)0x40002404)) // RW, TMR1 status
#define R8_TMR1_INT_FLAG        (*((vpuint8_t)0x40002406))  // RW1, TMR1 interrupt flag
#define R8_TMR1_FIFO_COUNT      (*((vpuint8_t)0x40002407))  // RO, TMR1 FIFO count status
#define R32_TMR1_COUNT          (*((vpuint32_t)0x40002408)) // RO, TMR1 current count
#define R16_TMR1_COUNT          (*((vpuint16_t)0x40002408)) // RO, TMR1 current count
#define R8_TMR1_COUNT           (*((vpuint8_t)0x40002408))  // RO, TMR1 current count
#define R32_TMR1_CNT_END        (*((vpuint32_t)0x4000240C)) // RW, TMR1 end count value, only low 26 bit
#define R32_TMR1_FIFO           (*((vpuint32_t)0x40002410)) // RO/WO, TMR1 FIFO register, only low 26 bit
#define R16_TMR1_FIFO           (*((vpuint16_t)0x40002410)) // RO/WO, TMR1 FIFO register
#define R8_TMR1_FIFO            (*((vpuint8_t)0x40002410))  // RO/WO, TMR1 FIFO register
#define R32_TMR1_DMA_NOW        (*((vpuint32_t)0x40002414)) // RW, TMR1 DMA current address
//#define R16_TMR1_DMA_NOW    (*((vpuint16_t)0x40002414)) // RW, TMR1 DMA current address
#define R32_TMR1_DMA_BEG        (*((vpuint32_t)0x40002418)) // RW, TMR1 DMA begin address
//#define R16_TMR1_DMA_BEG    (*((vpuint16_t)0x40002418)) // RW, TMR1 DMA begin address
#define R32_TMR1_DMA_END        (*((vpuint32_t)0x4000241C)) // RW, TMR1 DMA end address
//#define R16_TMR1_DMA_END    (*((vpuint16_t)0x4000241C)) // RW, TMR1 DMA end address

/* Timer2 register */
#define R32_TMR2_CONTROL        (*((vpuint32_t)0x40002800)) // RW, TMR2 control
#define R8_TMR2_CTRL_MOD        (*((vpuint8_t)0x40002800))  // RW, TMR2 mode control
#define R8_TMR2_CTRL_DMA        (*((vpuint8_t)0x40002801))  // RW, TMR2 DMA control
#define R8_TMR2_INTER_EN        (*((vpuint8_t)0x40002802))  // RW, TMR2 interrupt enable
#define R32_TMR2_STATUS         (*((vpuint32_t)0x40002804)) // RW, TMR2 status
#define R8_TMR2_INT_FLAG        (*((vpuint8_t)0x40002806))  // RW1, TMR2 interrupt flag
#define R8_TMR2_FIFO_COUNT      (*((vpuint8_t)0x40002807))  // RO, TMR2 FIFO count status
#define R32_TMR2_COUNT          (*((vpuint32_t)0x40002808)) // RO, TMR2 current count
#define R16_TMR2_COUNT          (*((vpuint16_t)0x40002808)) // RO, TMR2 current count
#define R8_TMR2_COUNT           (*((vpuint8_t)0x40002808))  // RO, TMR2 current count
#define R32_TMR2_CNT_END        (*((vpuint32_t)0x4000280C)) // RW, TMR2 end count value, only low 26 bit
#define R32_TMR2_FIFO           (*((vpuint32_t)0x40002810)) // RO/WO, TMR2 FIFO register, only low 26 bit
#define R16_TMR2_FIFO           (*((vpuint16_t)0x40002810)) // RO/WO, TMR2 FIFO register
#define R8_TMR2_FIFO            (*((vpuint8_t)0x40002810))  // RO/WO, TMR2 FIFO register
#define R32_TMR2_DMA_NOW        (*((vpuint32_t)0x40002814)) // RW, TMR2 DMA current address
//#define R16_TMR2_DMA_NOW    (*((vpuint16_t)0x40002814)) // RW, TMR2 DMA current address
#define R32_TMR2_DMA_BEG        (*((vpuint32_t)0x40002818)) // RW, TMR2 DMA begin address
//#define R16_TMR2_DMA_BEG    (*((vpuint16_t)0x40002818)) // RW, TMR2 DMA begin address
#define R32_TMR2_DMA_END        (*((vpuint32_t)0x4000281C)) // RW, TMR2 DMA end address
//#define R16_TMR2_DMA_END    (*((vpuint16_t)0x4000281C)) // RW, TMR2 DMA end address

/* Timer register address offset and bit define */
#define TMR_FIFO_SIZE           8                     // timer FIFO size (depth)
#define BA_TMR0                 ((vpuint8_t)0x40002000) // point TMR0 base address
#define BA_TMR1                 ((vpuint8_t)0x40002400) // point TMR1 base address
#define BA_TMR2                 ((vpuint8_t)0x40002800) // point TMR2 base address
#define TMR_CTRL_MOD            0
#define RB_TMR_MODE_IN          0x01        // RW, timer in mode: 0=timer/PWM, 1=capture/count
#define RB_TMR_ALL_CLEAR        0x02        // RW, force clear timer FIFO and count
#define RB_TMR_COUNT_EN         0x04        // RW, timer count enable
#define RB_TMR_OUT_EN           0x08        // RW, timer output enable
#define RB_TMR_OUT_POLAR        0x10        // RW, timer PWM output polarity: 0=default low and high action, 1=default high and low action
#define RB_TMR_CAP_COUNT        0x10        // RW, count sub-mode if RB_TMR_MODE_IN=1: 0=capture, 1=count
#define RB_TMR_PWM_REPEAT       0xC0        // RW, timer PWM repeat mode: 00=1, 01=4, 10=8, 11-16
#define RB_TMR_CAP_EDGE         0xC0        // RW, timer capture edge mode: 00=disable, 01=edge change, 10=fall to fall, 11-rise to rise
#define TMR_CTRL_DMA            1
#define RB_TMR_DMA_ENABLE       0x01        // RW, timer1/2 DMA enable
#define RB_TMR_DMA_LOOP         0x04        // RW, timer1/2 DMA address loop enable
#define TMR_INTER_EN            2
#define RB_TMR_IE_CYC_END       0x01        // RW, enable interrupt for timer capture count timeout or PWM cycle end
#define RB_TMR_IE_DATA_ACT      0x02        // RW, enable interrupt for timer capture input action or PWM trigger
#define RB_TMR_IE_FIFO_HF       0x04        // RW, enable interrupt for timer FIFO half (capture fifo >=4 or PWM fifo <=3)
#define RB_TMR_IE_DMA_END       0x08        // RW, enable interrupt for timer1/2 DMA completion
#define RB_TMR_IE_FIFO_OV       0x10        // RW, enable interrupt for timer FIFO overflow
#define TMR_INT_FLAG            6
#define RB_TMR_IF_CYC_END       0x01        // RW1, interrupt flag for timer capture count timeout or PWM cycle end
#define RB_TMR_IF_DATA_ACT      0x02        // RW1, interrupt flag for timer capture input action or PWM trigger
#define RB_TMR_IF_FIFO_HF       0x04        // RW1, interrupt flag for timer FIFO half (capture fifo >=4 or PWM fifo <=3)
#define RB_TMR_IF_DMA_END       0x08        // RW1, interrupt flag for timer1/2 DMA completion
#define RB_TMR_IF_FIFO_OV       0x10        // RW1, interrupt flag for timer FIFO overflow
#define TMR_FIFO_COUNT          7
#define TMR_COUNT               0x08
#define TMR_CNT_END             0x0C
#define TMR_FIFO                0x10
#define TMR_DMA_NOW             0x14
#define TMR_DMA_BEG             0x18
#define TMR_DMA_END             0x1C

/* UART0 register */
#define R32_UART0_CTRL          (*((vpuint32_t)0x40003000)) // RW, UART0 control
#define R8_UART0_MCR            (*((vpuint8_t)0x40003000))  // RW, UART0 modem control
#define R8_UART0_IER            (*((vpuint8_t)0x40003001))  // RW, UART0 interrupt enable
#define R8_UART0_FCR            (*((vpuint8_t)0x40003002))  // RW, UART0 FIFO control
#define R8_UART0_LCR            (*((vpuint8_t)0x40003003))  // RW, UART0 line control
#define R32_UART0_STAT          (*((vpuint32_t)0x40003004)) // RO, UART0 status
#define R8_UART0_IIR            (*((vpuint8_t)0x40003004))  // RO, UART0 interrupt identification
#define R8_UART0_LSR            (*((vpuint8_t)0x40003005))  // RO, UART0 line status
#define R8_UART0_MSR            (*((vpuint8_t)0x40003006))  // RO, UART0 modem status
#define R32_UART0_FIFO          (*((vpuint32_t)0x40003008)) // RW, UART0 data or FIFO port
#define R8_UART0_RBR            (*((vpuint8_t)0x40003008))  // RO, UART0 receiver buffer, receiving byte
#define R8_UART0_THR            (*((vpuint8_t)0x40003008))  // WO, UART0 transmitter holding, transmittal byte
#define R8_UART0_RFC            (*((vpuint8_t)0x4000300A))  // RO, UART0 receiver FIFO count
#define R8_UART0_TFC            (*((vpuint8_t)0x4000300B))  // RO, UART0 transmitter FIFO count
#define R32_UART0_SETUP         (*((vpuint32_t)0x4000300C)) // RW, UART0 setup
#define R16_UART0_DL            (*((vpuint16_t)0x4000300C)) // RW, UART0 divisor latch
#define R8_UART0_DLL            (*((vpuint8_t)0x4000300C))  // RW, UART0 divisor latch LSB byte
#define R8_UART0_DLM            (*((vpuint8_t)0x4000300D))  // RW, UART0 divisor latch MSB byte
#define R8_UART0_DIV            (*((vpuint8_t)0x4000300E))  // RW, UART0 pre-divisor latch byte, only low 7 bit, from 1 to 0/128
#define R8_UART0_ADR            (*((vpuint8_t)0x4000300F))  // RW, UART0 slave address: 0xFF=disable, other=enable

/* UART1 register */
#define R32_UART1_CTRL          (*((vpuint32_t)0x40003400)) // RW, UART1 control
#define R8_UART1_MCR            (*((vpuint8_t)0x40003400))  // RW, UART1 modem control
#define R8_UART1_IER            (*((vpuint8_t)0x40003401))  // RW, UART1 interrupt enable
#define R8_UART1_FCR            (*((vpuint8_t)0x40003402))  // RW, UART1 FIFO control
#define R8_UART1_LCR            (*((vpuint8_t)0x40003403))  // RW, UART1 line control
#define R32_UART1_STAT          (*((vpuint32_t)0x40003404)) // RO, UART1 status
#define R8_UART1_IIR            (*((vpuint8_t)0x40003404))  // RO, UART1 interrupt identification
#define R8_UART1_LSR            (*((vpuint8_t)0x40003405))  // RO, UART1 line status
#define R32_UART1_FIFO          (*((vpuint32_t)0x40003408)) // RW, UART1 data or FIFO port
#define R8_UART1_RBR            (*((vpuint8_t)0x40003408))  // RO, UART1 receiver buffer, receiving byte
#define R8_UART1_THR            (*((vpuint8_t)0x40003408))  // WO, UART1 transmitter holding, transmittal byte
#define R8_UART1_RFC            (*((vpuint8_t)0x4000340A))  // RO, UART1 receiver FIFO count
#define R8_UART1_TFC            (*((vpuint8_t)0x4000340B))  // RO, UART1 transmitter FIFO count
#define R32_UART1_SETUP         (*((vpuint32_t)0x4000340C)) // RW, UART1 setup
#define R16_UART1_DL            (*((vpuint16_t)0x4000340C)) // RW, UART1 divisor latch
#define R8_UART1_DLL            (*((vpuint8_t)0x4000340C))  // RW, UART1 divisor latch LSB byte
#define R8_UART1_DLM            (*((vpuint8_t)0x4000340D))  // RW, UART1 divisor latch MSB byte
#define R8_UART1_DIV            (*((vpuint8_t)0x4000340E))  // RW, UART1 pre-divisor latch byte, only low 7 bit, from 1 to 0/128

/* UART2 register */
#define R32_UART2_CTRL          (*((vpuint32_t)0x40003800)) // RW, UART2 control
#define R8_UART2_MCR            (*((vpuint8_t)0x40003800))  // RW, UART2 modem control
#define R8_UART2_IER            (*((vpuint8_t)0x40003801))  // RW, UART2 interrupt enable
#define R8_UART2_FCR            (*((vpuint8_t)0x40003802))  // RW, UART2 FIFO control
#define R8_UART2_LCR            (*((vpuint8_t)0x40003803))  // RW, UART2 line control
#define R32_UART2_STAT          (*((vpuint32_t)0x40003804)) // RO, UART2 status
#define R8_UART2_IIR            (*((vpuint8_t)0x40003804))  // RO, UART2 interrupt identification
#define R8_UART2_LSR            (*((vpuint8_t)0x40003805))  // RO, UART2 line status
#define R32_UART2_FIFO          (*((vpuint32_t)0x40003808)) // RW, UART2 data or FIFO port
#define R8_UART2_RBR            (*((vpuint8_t)0x40003808))  // RO, UART2 receiver buffer, receiving byte
#define R8_UART2_THR            (*((vpuint8_t)0x40003808))  // WO, UART2 transmitter holding, transmittal byte
#define R8_UART2_RFC            (*((vpuint8_t)0x4000380A))  // RO, UART2 receiver FIFO count
#define R8_UART2_TFC            (*((vpuint8_t)0x4000380B))  // RO, UART2 transmitter FIFO count
#define R32_UART2_SETUP         (*((vpuint32_t)0x4000380C)) // RW, UART2 setup
#define R16_UART2_DL            (*((vpuint16_t)0x4000380C)) // RW, UART2 divisor latch
#define R8_UART2_DLL            (*((vpuint8_t)0x4000380C))  // RW, UART2 divisor latch LSB byte
#define R8_UART2_DLM            (*((vpuint8_t)0x4000380D))  // RW, UART2 divisor latch MSB byte
#define R8_UART2_DIV            (*((vpuint8_t)0x4000380E))  // RW, UART2 pre-divisor latch byte, only low 7 bit, from 1 to 0/128

/* UART3 register */
#define R32_UART3_CTRL          (*((vpuint32_t)0x40003C00)) // RW, UART3 control
#define R8_UART3_MCR            (*((vpuint8_t)0x40003C00))  // RW, UART3 modem control
#define R8_UART3_IER            (*((vpuint8_t)0x40003C01))  // RW, UART3 interrupt enable
#define R8_UART3_FCR            (*((vpuint8_t)0x40003C02))  // RW, UART3 FIFO control
#define R8_UART3_LCR            (*((vpuint8_t)0x40003C03))  // RW, UART3 line control
#define R32_UART3_STAT          (*((vpuint32_t)0x40003C04)) // RO, UART3 status
#define R8_UART3_IIR            (*((vpuint8_t)0x40003C04))  // RO, UART3 interrupt identification
#define R8_UART3_LSR            (*((vpuint8_t)0x40003C05))  // RO, UART3 line status
#define R32_UART3_FIFO          (*((vpuint32_t)0x40003C08)) // RW, UART3 data or FIFO port
#define R8_UART3_RBR            (*((vpuint8_t)0x40003C08))  // RO, UART3 receiver buffer, receiving byte
#define R8_UART3_THR            (*((vpuint8_t)0x40003C08))  // WO, UART3 transmitter holding, transmittal byte
#define R8_UART3_RFC            (*((vpuint8_t)0x40003C0A))  // RO, UART3 receiver FIFO count
#define R8_UART3_TFC            (*((vpuint8_t)0x40003C0B))  // RO, UART3 transmitter FIFO count
#define R32_UART3_SETUP         (*((vpuint32_t)0x40003C0C)) // RW, UART3 setup
#define R16_UART3_DL            (*((vpuint16_t)0x40003C0C)) // RW, UART3 divisor latch
#define R8_UART3_DLL            (*((vpuint8_t)0x40003C0C))  // RW, UART3 divisor latch LSB byte
#define R8_UART3_DLM            (*((vpuint8_t)0x40003C0D))  // RW, UART3 divisor latch MSB byte
#define R8_UART3_DIV            (*((vpuint8_t)0x40003C0E))  // RW, UART3 pre-divisor latch byte, only low 7 bit, from 1 to 0/128

/* UART register address offset and bit define */
#define UART_FIFO_SIZE          8                     // UART FIFO size (depth)
#define UART_RECV_RDY_SZ        7                     // the max FIFO trigger level for UART receiver data available
#define BA_UART0                ((vpuint8_t)0x40003000) // point UART0 base address
#define BA_UART1                ((vpuint8_t)0x40003400) // point UART1 base address
#define BA_UART2                ((vpuint8_t)0x40003800) // point UART2 base address
#define BA_UART3                ((vpuint8_t)0x40003C00) // point UART3 base address
#define UART_MCR                0
#define RB_MCR_DTR              0x01        // RW, UART0 control DTR
#define RB_MCR_RTS              0x02        // RW, UART0 control RTS
#define RB_MCR_OUT1             0x04        // RW, UART0 control OUT1
#define RB_MCR_OUT2             0x08        // RW, UART control OUT2
#define RB_MCR_INT_OE           0x08        // RW, UART interrupt output enable
#define RB_MCR_LOOP             0x10        // RW, UART0 enable local loop back
#define RB_MCR_AU_FLOW_EN       0x20        // RW, UART0 enable autoflow control
#define RB_MCR_TNOW             0x40        // RW, UART0 enable TNOW output on DTR pin
#define RB_MCR_HALF             0x80        // RW, UART0 enable half-duplex
#define UART_IER                1
#define RB_IER_RECV_RDY         0x01        // RW, UART interrupt enable for receiver data ready
#define RB_IER_THR_EMPTY        0x02        // RW, UART interrupt enable for THR empty
#define RB_IER_LINE_STAT        0x04        // RW, UART interrupt enable for receiver line status
#define RB_IER_MODEM_CHG        0x08        // RW, UART0 interrupt enable for modem status change
#define RB_IER_DTR_EN           0x10        // RW, UART0 DTR/TNOW output pin enable
#define RB_IER_RTS_EN           0x20        // RW, UART0 RTS output pin enable
#define RB_IER_TXD_EN           0x40        // RW, UART TXD pin enable
#define RB_IER_RESET            0x80        // WZ, UART software reset control, high action, auto clear
#define UART_FCR                2
#define RB_FCR_FIFO_EN          0x01        // RW, UART FIFO enable
#define RB_FCR_RX_FIFO_CLR      0x02        // WZ, clear UART receiver FIFO, high action, auto clear
#define RB_FCR_TX_FIFO_CLR      0x04        // WZ, clear UART transmitter FIFO, high action, auto clear
#define RB_FCR_FIFO_TRIG        0xC0        // RW, UART receiver FIFO trigger level: 00-1byte, 01-2bytes, 10-4bytes, 11-7bytes
#define UART_LCR                3
#define RB_LCR_WORD_SZ          0x03        // RW, UART word bit length: 00-5bit, 01-6bit, 10-7bit, 11-8bit
#define RB_LCR_STOP_BIT         0x04        // RW, UART stop bit length: 0-1bit, 1-2bit
#define RB_LCR_PAR_EN           0x08        // RW, UART parity enable
#define RB_LCR_PAR_MOD          0x30        // RW, UART parity mode: 00-odd, 01-even, 10-mark, 11-space
#define RB_LCR_BREAK_EN         0x40        // RW, UART break control enable
#define RB_LCR_DLAB             0x80        // RW, UART reserved bit
#define RB_LCR_GP_BIT           0x80        // RW, UART general purpose bit
#define UART_IIR                4
#define RB_IIR_NO_INT           0x01        // RO, UART no interrupt flag: 0=interrupt action, 1=no interrupt
#define RB_IIR_INT_MASK         0x0F        // RO, UART interrupt flag bit mask
#define RB_IIR_FIFO_ID          0xC0        // RO, UART FIFO enabled flag
#define UART_LSR                5
#define RB_LSR_DATA_RDY         0x01        // RO, UART receiver fifo data ready status
#define RB_LSR_OVER_ERR         0x02        // RZ, UART receiver overrun error
#define RB_LSR_PAR_ERR          0x04        // RZ, UART receiver parity error
#define RB_LSR_FRAME_ERR        0x08        // RZ, UART receiver frame error
#define RB_LSR_BREAK_ERR        0x10        // RZ, UART receiver break error
#define RB_LSR_TX_FIFO_EMP      0x20        // RO, UART transmitter fifo empty status
#define RB_LSR_TX_ALL_EMP       0x40        // RO, UART transmitter all empty status
#define RB_LSR_ERR_RX_FIFO      0x80        // RO, indicate error in UART receiver fifo
#define UART_MSR                6
#define RB_MSR_CTS_CHG          0x01        // RZ, UART0 CTS changed status, high action
#define RB_MSR_DSR_CHG          0x02        // RZ, UART0 DSR changed status, high action
#define RB_MSR_RI_CHG           0x04        // RZ, UART0 RI changed status, high action
#define RB_MSR_DCD_CHG          0x08        // RZ, UART0 DCD changed status, high action
#define RB_MSR_CTS              0x10        // RO, UART0 CTS action status
#define RB_MSR_DSR              0x20        // RO, UART0 DSR action status
#define RB_MSR_RI               0x40        // RO, UART0 RI action status
#define RB_MSR_DCD              0x80        // RO, UART0 DCD action status
#define UART_RBR                8
#define UART_THR                8
#define UART_RFC                0x0A
#define UART_TFC                0x0B
#define UART_DLL                0x0C
#define UART_DLM                0x0D
#define UART_DIV                0x0E
#define UART_ADR                0x0F

/* UART interrupt identification values for IIR bits 3:0 */
#define UART_II_SLV_ADDR        0x0E        // RO, UART0 slave address match
#define UART_II_LINE_STAT       0x06        // RO, UART interrupt by receiver line status
#define UART_II_RECV_RDY        0x04        // RO, UART interrupt by receiver data available
#define UART_II_RECV_TOUT       0x0C        // RO, UART interrupt by receiver fifo timeout
#define UART_II_THR_EMPTY       0x02        // RO, UART interrupt by THR empty
#define UART_II_MODEM_CHG       0x00        // RO, UART0 interrupt by modem status change
#define UART_II_NO_INTER        0x01        // RO, no UART interrupt is pending

/* SPI0 register */
#define R32_SPI0_CONTROL        (*((vpuint32_t)0x40004000)) // RW, SPI0 control
#define R8_SPI0_CTRL_MOD        (*((vpuint8_t)0x40004000))  // RW, SPI0 mode control
#define R8_SPI0_CTRL_CFG        (*((vpuint8_t)0x40004001))  // RW, SPI0 configuration control
#define R8_SPI0_INTER_EN        (*((vpuint8_t)0x40004002))  // RW, SPI0 interrupt enable
#define R8_SPI0_CLOCK_DIV       (*((vpuint8_t)0x40004003))  // RW, SPI0 master clock divisor
#define R8_SPI0_SLAVE_PRE       (*((vpuint8_t)0x40004003))  // RW, SPI0 slave preset value
#define R32_SPI0_STATUS         (*((vpuint32_t)0x40004004)) // RW, SPI0 status
#define R8_SPI0_BUFFER          (*((vpuint8_t)0x40004004))  // RO, SPI0 data buffer
#define R8_SPI0_RUN_FLAG        (*((vpuint8_t)0x40004005))  // RO, SPI0 work flag
#define R8_SPI0_INT_FLAG        (*((vpuint8_t)0x40004006))  // RW1, SPI0 interrupt flag
#define R8_SPI0_FIFO_COUNT      (*((vpuint8_t)0x40004007))  // RO, SPI0 FIFO count status
#define R32_SPI0_TOTAL_CNT      (*((vpuint32_t)0x4000400C)) // RW, SPI0 total byte count, only low 12 bit
#define R16_SPI0_TOTAL_CNT      (*((vpuint16_t)0x4000400C)) // RW, SPI0 total byte count, only low 12 bit
#define R32_SPI0_FIFO           (*((vpuint32_t)0x40004010)) // RW, SPI0 FIFO register
#define R8_SPI0_FIFO            (*((vpuint8_t)0x40004010))  // RO/WO, SPI0 FIFO register
#define R8_SPI0_FIFO_COUNT1     (*((vpuint8_t)0x40004013))  // RO, SPI0 FIFO count status
#define R32_SPI0_DMA_NOW        (*((vpuint32_t)0x40004014)) // RW, SPI0 DMA current address
//#define R16_SPI0_DMA_NOW    (*((vpuint16_t)0x40004014)) // RW, SPI0 DMA current address
#define R32_SPI0_DMA_BEG        (*((vpuint32_t)0x40004018)) // RW, SPI0 DMA begin address
//#define R16_SPI0_DMA_BEG    (*((vpuint16_t)0x40004018)) // RW, SPI0 DMA begin address
#define R32_SPI0_DMA_END        (*((vpuint32_t)0x4000401C)) // RW, SPI0 DMA end address
//#define R16_SPI0_DMA_END    (*((vpuint16_t)0x4000401C)) // RW, SPI0 DMA end address

/* SPI1 register */
#define R32_SPI1_CONTROL        (*((vpuint32_t)0x40004400)) // RW, SPI1 control
#define R8_SPI1_CTRL_MOD        (*((vpuint8_t)0x40004400))  // RW, SPI1 mode control
#define R8_SPI1_CTRL_CFG        (*((vpuint8_t)0x40004401))  // RW, SPI1 configuration c
#define R8_SPI1_INTER_EN        (*((vpuint8_t)0x40004402))  // RW, SPI1 interrupt enabl
#define R8_SPI1_CLOCK_DIV       (*((vpuint8_t)0x40004403))  // RW, SPI1 master clock di
#define R8_SPI1_SLAVE_PRE       (*((vpuint8_t)0x40004403))  // RW, SPI1 slave preset va
#define R32_SPI1_STATUS         (*((vpuint32_t)0x40004404)) // RW, SPI1 status
#define R8_SPI1_BUFFER          (*((vpuint8_t)0x40004404))  // RO, SPI1 data buffer
#define R8_SPI1_RUN_FLAG        (*((vpuint8_t)0x40004405))  // RO, SPI1 work flag
#define R8_SPI1_INT_FLAG        (*((vpuint8_t)0x40004406))  // RW1, SPI1 interrupt flag
#define R8_SPI1_FIFO_COUNT      (*((vpuint8_t)0x40004407))  // RO, SPI1 FIFO count stat
#define R32_SPI1_TOTAL_CNT      (*((vpuint32_t)0x4000440C)) // RW, SPI1 total byte coun
#define R16_SPI1_TOTAL_CNT      (*((vpuint16_t)0x4000440C)) // RW, SPI1 total byte coun
#define R32_SPI1_FIFO           (*((vpuint32_t)0x40004410)) // RW, SPI1 FIFO register
#define R8_SPI1_FIFO            (*((vpuint8_t)0x40004410))  // RO/WO, SPI1 FIFO registe
#define R8_SPI1_FIFO_COUNT1     (*((vpuint8_t)0x40004413))  // RO, SPI1 FIFO count stat
#define R32_SPI1_DMA_NOW        (*((vpuint32_t)0x40004414)) // RW, SPI1 DMA current add
//#define R16_SPI1_DMA_NOW    (*((vpuint16_t)0x40004414)) // RW, SPI1 DMA current add
#define R32_SPI1_DMA_BEG        (*((vpuint32_t)0x40004418)) // RW, SPI1 DMA begin addre
//#define R16_SPI1_DMA_BEG    (*((vpuint16_t)0x40004418)) // RW, SPI1 DMA begin addre
#define R32_SPI1_DMA_END        (*((vpuint32_t)0x4000441C)) // RW, SPI1 DMA end address
//#define R16_SPI1_DMA_END    (*((vpuint16_t)0x4000441C)) // RW, SPI1 DMA end address

/* SPI register address offset and bit define */
#define SPI_FIFO_SIZE           8                     // SPI FIFO size (depth)
#define BA_SPI0                 ((vpuint8_t)0x40004000) // point SPI0 base address
#define BA_SPI1                 ((vpuint8_t)0x40004400) // point SPI1 base address
#define SPI_CTRL_MOD            0
#define RB_SPI_MODE_SLAVE       0x01        // RW, SPI slave mode: 0=master/host, 1=slave/device
#define RB_SPI_ALL_CLEAR        0x02        // RW, force clear SPI FIFO and count
#define RB_SPI_2WIRE_MOD        0x04        // RW, SPI enable 2 wire mode: 0=3wire(SCK,MOSI,MISO), 1=2wire(SCK,MISO=MXSX)
#define RB_SPI_MST_SCK_MOD      0x08        // RW, SPI master clock mode: 0=mode 0, 1=mode 3
#define RB_SPI_SLV_CMD_MOD      0x08        // RW, SPI slave command mode: 0=byte stream, 1=first byte command
#define RB_SPI_FIFO_DIR         0x10        // RW, SPI FIFO direction: 0=out(write @master mode), 1=in(read @master mode)
#define RB_SPI_SCK_OE           0x20        // RW, SPI SCK output enable
#define RB_SPI_MOSI_OE          0x40        // RW, SPI MOSI output enable
#define RB_SPI1_SDO_OE          0x40        // RW, SPI1 SDO output enable
#define RB_SPI_MISO_OE          0x80        // RW, SPI MISO output enable
#define RB_SPI1_SDI_OE          0x80        // RW, SPI1 SDI output enable, SPI1 enable 2 wire mode: 0=3wire(SCK1,SDO,SDI), 1=2wire(SCK1,SDI=SDX)
#define SPI_CTRL_CFG            1
#define RB_SPI_DMA_ENABLE       0x01        // RW, SPI DMA enable
#define RB_SPI_DMA_LOOP         0x04        // RW, SPI DMA address loop enable
#define RB_SPI_AUTO_IF          0x10        // RW, enable buffer/FIFO accessing to auto clear RB_SPI_IF_BYTE_END interrupt flag
#define RB_SPI_BIT_ORDER        0x20        // RW, SPI bit data order: 0=MSB first, 1=LSB first
#define SPI_INTER_EN            2
#define RB_SPI_IE_CNT_END       0x01        // RW, enable interrupt for SPI total byte count end
#define RB_SPI_IE_BYTE_END      0x02        // RW, enable interrupt for SPI byte exchanged
#define RB_SPI_IE_FIFO_HF       0x04        // RW, enable interrupt for SPI FIFO half
#define RB_SPI_IE_DMA_END       0x08        // RW, enable interrupt for SPI DMA completion
#define RB_SPI_IE_FIFO_OV       0x10        // RW, enable interrupt for SPI FIFO overflow
#define RB_SPI_IE_FST_BYTE      0x80        // RW, enable interrupt for SPI slave mode first byte received
#define SPI_CLOCK_DIV           3
#define SPI_SLAVE_PRESET        3
#define SPI_BUFFER              4
#define SPI_RUN_FLAG            5
#define RB_SPI_SLV_CMD_ACT      0x10        // RO, SPI slave command flag
#define RB_SPI_FIFO_READY       0x20        // RO, SPI FIFO ready status
#define RB_SPI_SLV_CS_LOAD      0x40        // RO, SPI slave chip-select loading status
#define RB_SPI_SLV_SELECT       0x80        // RO, SPI slave selection status
#define SPI_INT_FLAG            6
#define RB_SPI_IF_CNT_END       0x01        // RW1, interrupt flag for SPI total byte count end
#define RB_SPI_IF_BYTE_END      0x02        // RW1, interrupt flag for SPI byte exchanged
#define RB_SPI_IF_FIFO_HF       0x04        // RW1, interrupt flag for SPI FIFO half (RB_SPI_FIFO_DIR ? >=4bytes : <4bytes)
#define RB_SPI_IF_DMA_END       0x08        // RW1, interrupt flag for SPI DMA completion
#define RB_SPI_IF_FIFO_OV       0x10        // RW1, interrupt flag for SPI FIFO overflow
#define RB_SPI_FREE             0x40        // RO, current SPI free status
#define RB_SPI_IF_FST_BYTE      0x80        // RW1, interrupt flag for SPI slave mode first byte received
#define SPI_FIFO_COUNT          7
#define SPI_TOTAL_CNT           0x0C
#define SPI_FIFO                0x10
#define SPI_DMA_NOW             0x14
#define SPI_DMA_BEG             0x18
#define SPI_DMA_END             0x1C

/* PWM0/1/2/3 register */
#define R32_PWM_CONTROL         (*((vpuint32_t)0x40005000)) // RW, PWM control
#define R8_PWM_CTRL_MOD         (*((vpuint8_t)0x40005000))  // RW, PWM mode control
#define R8_PWM_CTRL_CFG         (*((vpuint8_t)0x40005001))  // RW, PWM configuration control
#define R8_PWM_CLOCK_DIV        (*((vpuint8_t)0x40005002))  // RW, PWM clock divisor
#define R32_PWM_DATA            (*((vpuint32_t)0x40005004)) // RW, PWM data holding
#define R8_PWM0_DATA            (*((vpuint8_t)0x40005004))  // RW, PWM0 data holding
#define R8_PWM1_DATA            (*((vpuint8_t)0x40005005))  // RW, PWM1 data holding
#define R8_PWM2_DATA            (*((vpuint8_t)0x40005006))  // RW, PWM2 data holding
#define R8_PWM3_DATA            (*((vpuint8_t)0x40005007))  // RW, PWM3 data holding

/* PWM0/1/2/3 register address offset and bit define */
#define BA_PWMX                 ((vpuint8_t)0x40005000) // point PWM0/1/2/3 base address
#define PWM_CTRL_MOD            0
#define RB_PWM0_OUT_EN          0x01        // RW, PWM0 output enable
#define RB_PWM1_OUT_EN          0x02        // RW, PWM1 output enable
#define RB_PWM2_OUT_EN          0x04        // RW, PWM2 output enable
#define RB_PWM3_OUT_EN          0x08        // RW, PWM3 output enable
#define RB_PWM0_POLAR           0x10        // RW, PWM0 output polarity: 0=default low and high action, 1=default high and low action
#define RB_PWM1_POLAR           0x20        // RW, PWM1 output polarity: 0=default low and high action, 1=default high and low action
#define RB_PWM2_POLAR           0x40        // RW, PWM2 output polarity: 0=default low and high action, 1=default high and low action
#define RB_PWM3_POLAR           0x80        // RW, PWM3 output polarity: 0=default low and high action, 1=default high and low action
#define PWM_CTRL_CFG            1
#define RB_PWM_CYCLE_SEL        0x01        // RW, PWM cycle selection: 0=256 clocks, 1=255 clocks
#define PWM_CLOCK_DIV           2
#define PWM0_DATA_HOLD          4
#define PWM1_DATA_HOLD          5
#define PWM2_DATA_HOLD          6
#define PWM3_DATA_HOLD          7

/* HSPI register */
#define R32_HSPI_CR             (*((vpuint32_t)0x40006000)) // RW, parallel if control
#define R8_HSPI_CFG             (*((vpuint8_t)0x40006000))  // RW, parallel if tx/rx cfg
#define R8_HSPI_CTRL            (*((vpuint8_t)0x40006001))  // RW, parallel if tx/rx control
#define R8_HSPI_INT_EN          (*((vpuint8_t)0x40006002))  // RW, parallel if interrupt enable register
#define R8_HSPI_AUX             (*((vpuint8_t)0x40006003))  // RW, parallel if aux
#define R32_HSPI_TX_ADDR0       (*((vpuint32_t)0x40006004)) // RW, parallel if dma tx addr0
#define R32_HSPI_TX_ADDR1       (*((vpuint32_t)0x40006008)) // RW, parallel if dma tx addr1
#define R32_HSPI_RX_ADDR0       (*((vpuint32_t)0x4000600C)) // RW, parallel if dma rx addr0
#define R32_HSPI_RX_ADDR1       (*((vpuint32_t)0x40006010)) // RW, parallel if dma rx addr1
#define R16_HSPI_DMA_LEN0       (*((vpuint16_t)0x40006014)) // RW, parallel if dma length0
#define R16_HSPI_RX_LEN0        (*((vpuint16_t)0x40006016)) // RO, parallel if receive length0
#define R16_HSPI_DMA_LEN1       (*((vpuint16_t)0x40006018)) // RW, parallel if dma length1
#define R16_HSPI_RX_LEN1        (*((vpuint16_t)0x4000601A)) // RO, parallel if receive length1
#define R16_HSPI_BURST_CFG      (*((vpuint16_t)0x4000601C)) // RW, parallel if tx burst config register
#define R8_HSPI_BURST_CNT       (*((vpuint8_t)0x4000601E))  // RO, parallel if tx burst count
#define R32_HSPI_UDF0           (*((vpuint32_t)0x40006020)) // RW, parallel if
#define R32_HSPI_UDF1           (*((vpuint32_t)0x40006024)) // RW, parallel if
#define R32_HSPI_STATUS         (*((vpuint32_t)0x40006028)) // RW, parallel if status
#define R8_HSPI_INT_FLAG        (*((vpuint8_t)0x40006028))  // RW1, parallel if interrupt flag
#define R8_HSPI_RTX_STATUS      (*((vpuint8_t)0x40006029))  // RO, parallel rtx status
#define R8_HSPI_TX_SC           (*((vpuint8_t)0x4000602A))  // RW, parallel TX sequence ctrl
#define R8_HSPI_RX_SC           (*((vpuint8_t)0x4000602B))  // RW, parallel RX sequence ctrl

/* HSPI register address offset and bit define */
#define HSPI_RTX_CFG            0
#define RB_HSPI_MODE            0x01        // RW, parallel if mode: 1=UP, 0=DOWN
#define RB_HSPI_DUALDMA         0x02        // RW, parallel if dualdma mode enable
#define RB_HSPI_MSK_SIZE        0x0C        // RW, parallel if data mode
#define RB_HSPI_DAT8_MOD        0x00        // RW, 00=8bits mode
#define RB_HSPI_DAT16_MOD       0x04        // RW, 01=16bits mode
#define RB_HSPI_DAT32_MOD       0x08        // RW, 10=32bits mode
#define RB_HSPI_TX_TOG_EN       0x20        // RW, parallel if tx addr toggle enable
#define RB_HSPI_RX_TOG_EN       0x40        // RW, parallel if rx addr toggle enable
#define RB_HSPI_HW_ACK          0x80        // RW, parallel if tx ack by hardware
#define HSPI_RTX_CTRL           1
#define RB_HSPI_ENABLE          0x01        // RW, parallel if enable
#define RB_HSPI_DMA_EN          0x02        // RW, parallel if dma enable
#define RB_HSPI_SW_ACT          0x04        // RW, parallel if transmit software trigger
#define RB_HSPI_ALL_CLR         0x08        // RW, parallel if all clear
#define RB_HSPI_TRX_RST         0x10        // RW, parallel if tx and rx logic clear, high action
#define HSPI_INT_EN             2
#define RB_HSPI_IE_T_DONE       0x01        // RW, parallel if transmit done interrupt enable
#define RB_HSPI_IE_R_DONE       0x02        // RW, parallel if receive done interrupt enable
#define RB_HSPI_IE_FIFO_OV      0x04        // RW, parallel if fifo overflow interrupt enable
#define RB_HSPI_IE_B_DONE       0x08        // RW, RW, parallel if tx burst done interrupt enable
#define HSPI_RTX_AUX            3
#define RB_HSPI_TCK_MOD         0x01        // RW, parallel if tx clk polar control, 0=not invert, 1=invert
#define RB_HSPI_RCK_MOD         0x02        // RW, parallel if rx clk polar control, 0=not invert, 1=invert
#define RB_HSPI_ACK_TX_MOD      0x04        // RW, parallel if tx ack mode cfg, 0=ram write done to send, 1=delay done to send
#define RB_HSPI_ACK_CNT_SEL     0x18        // RW, delay time of parallel if send ack when receive done
#define RB_ACK_CNT_2            0x00        // RW, delay 2 clock to send ack
#define RB_ACK_CNT_4            0x08        // RW, delay 4 clock to send ack
#define RB_ACK_CNT_6            0x10        // RW, delay 6 clock to send ack
#define RB_ACK_CNT_8            0x18        // RW, delay 8 clock to send ack
#define RB_HSPI_REQ_FT          0x20        // RW, enable fast DMA request
#define HSPI_TX_ADDR0           4
#define HSPI_TX_ADDR1           5
#define HSPI_RX_ADDR0           6
#define HSPI_RX_ADDR1           7
#define HSPI_BURST_CFG          8
#define RB_HSPI_BURST_EN        0x0001      // RW, burst transmit enable
#define RB_HSPI_BURST_LEN       0xFF00      // RW, burst transmit length
#define HSPI_UDF0               9
#define HSPI_UDF1               10
#define HSPI_INT_FLAG           11
#define RB_HSPI_IF_T_DONE       0x01        // RW1, interrupt flag for parallel if transmit done
#define RB_HSPI_IF_R_DONE       0x02        // RW1, interrupt flag for parallel if receive done
#define RB_HSPI_IF_FIFO_OV      0x04        // RW1, interrupt flag for parallel if FIFO overflow
#define RB_HSPI_IF_B_DONE       0x08        // RW1, interrupt flag for parallel if tx burst done
#define HSPI_RTX_STATUS         12
//#define  RB_HSPI_TX_OK          0x01						// RO, data transmit OK (received ack)
#define RB_HSPI_CRC_ERR         0x02        // RO, CRC error occur
#define RB_HSPI_NUM_MIS         0x04        // RO, rx and tx sequence number mismatch
#define HSPI_TX_SC              13
#define RB_HSPI_TX_NUM          0x0F        // RW, parallel if tx sequence num
#define RB_HSPI_TX_TOG          0x10        // RW, parallel if tx addr toggle flag
#define HSPI_RX_SC              14
#define RB_HSPI_RX_NUM          0x0F        // RW, parallel if rx sequence num
#define RB_HSPI_RX_TOG          0x10        // RW, parallel if rx addr toggle flag

/* DVP register */
#define R32_DVP_CR              (*((vpuint32_t)0x4000E000)) // RW, DVP control register
#define R8_DVP_CR0              (*((vpuint8_t)0x4000E000))  // RW, DVP control register0
#define R8_DVP_CR1              (*((vpuint8_t)0x4000E001))  // RW, DVP control register1
#define R8_DVP_INT_EN           (*((vpuint8_t)0x4000E002))  // RW, DVP interrupt enable register
#define R16_DVP_ROW_NUM         (*((vpuint16_t)0x4000E004)) // RW, DVP row number of a frame indicator register
#define R16_DVP_COL_NUM         (*((vpuint16_t)0x4000E006)) // RW, DVP col number of a frame indicator register
#define R32_DVP_DMA_BUF0        (*((vpuint32_t)0x4000E008)) // RW, DVP dma buffer0 addr
#define R32_DVP_DMA_BUF1        (*((vpuint32_t)0x4000E00c)) // RW, DVP dma buffer1 addr
#define R32_DVP_STATUS          (*((vpuint32_t)0x4000E010))
#define R8_DVP_INT_FLAG         (*((vpuint8_t)0x4000E010))  // RW1, DVP interrupt flag register
#define R8_DVP_FIFO_ST          (*((vpuint8_t)0x4000E011))  // RO, DVP receive fifo status
#define R16_DVP_ROW_CNT         (*((vpuint16_t)0x4000E014)) // RO, DVP row count value
#define R16_DVP_COL_CNT         (*((vpuint16_t)0x4000E016)) // RO, DVP col count value

/* DVP register address offset and bit define */
#define DVP_CR0                 0
#define RB_DVP_ENABLE           0x01        // RW, DVP enable
#define RB_DVP_V_POLAR          0x02        // RW, DVP VSYNC polarity control: 1 = invert, 0 = not invert
#define RB_DVP_H_POLAR          0x04        // RW, DVP HSYNC polarity control: 1 = invert, 0 = not invert
#define RB_DVP_P_POLAR          0x08        // RW, DVP PCLK polarity control: 1 = invert, 0 = not invert
#define RB_DVP_MSK_DAT_MOD      0x30
#define RB_DVP_D8_MOD           0x00        // RW, DVP 8bits data mode
#define RB_DVP_D10_MOD          0x10        // RW, DVP 10bits data mode
#define RB_DVP_D12_MOD          0x20        // RW, DVP 12bits data mode
#define RB_DVP_JPEG             0x40        // RW, DVP JPEG mode
#define RB_DVP_RAW_CM           0x80        // RW, DVP row count mode: 1 = count on falling edge of HSYNC, 0 = count on the end of col count
#define DVP_CR1                 1
#define RB_DVP_DMA_EN           0x01        // RW, DVP dma enable
#define RB_DVP_ALL_CLR          0x02        // RW, DVP all clear, high action
#define RB_DVP_RCV_CLR          0x04        // RW, DVP receive logic clear, high action
#define RB_DVP_BUF_TOG          0x08        // RW, DVP bug toggle by software, write 1 to toggle, ignored writing 0
#define DVP_INT_EN              2
#define RB_DVP_IE_STR_FRM       0x01        // RW, DVP frame start interrupt enable
#define RB_DVP_IE_ROW_DONE      0x02        // RW, DVP row received done interrupt enable
#define RB_DVP_IE_FRM_DONE      0x04        // RW, DVP frame received done interrupt enable
#define RB_DVP_IE_FIFO_OV       0x08        // RW, DVP receive fifo overflow interrupt enable
#define RB_DVP_IE_STP_FRM       0x10        // RW, DVP frame stop interrupt enable
#define DVP_ROW_NUM             3
#define DVP_DMA_BUF0            4
#define DVP_DMA_BUF1            5
#define DVP_INT_FLAG            6
#define RB_DVP_IF_STR_FRM       0x01        // RW1, interrupt flag for DVP frame start
#define RB_DVP_IF_ROW_DONE      0x02        // RW1, interrupt flag for DVP row receive done
#define RB_DVP_IF_FRM_DONE      0x04        // RW1, interrupt flag for DVP frame receive done
#define RB_DVP_IF_FIFO_OV       0x08        // RW1, interrupt flag for DVP receive fifo overflow
#define RB_DVP_IF_STP_FRM       0x10        // RW1, interrupt flag for DVP frame stop
#define DVP_FIFO_ST             7
#define RB_DVP_FIFO_RDY         0x01        // RO, DVP receive fifo ready
#define RB_DVP_FIFO_FULL        0x02        // RO, DVP receive fifo full
#define RB_DVP_FIFO_OV          0x04        // RO, DVP receive fifo overflow
#define RB_DVP_MSK_FIFO_CNT     0x70        // RO, DVP receive fifo count
#define DVP_ROW_CNT             8
#define DVP_COL_CNT             9

/* SPI Flash register */
#define R32_SPI_ROM_CTRL        (*((vpuint32_t)0x40001018))
#define R8_SPI_ROM_CTRL         (*((vpuint8_t)0x40001018))
#define R32_SPI_ROM_DATA        (*((vpuint32_t)0x40001014))   //RW
#define R8_SPI_ROM_DATA         (*((vpuint8_t)0x40001018))    //RW
#define R16_SPI_ROM_CR          (*((vpuint16_t)0x4000101A))   //RW
#define R8_SPI_ROM_CR           (*((vpuint8_t)0x4000101A))   //RW

/* SPI Flash register address offset and bit define */
#define SPI_ROM_DATA            0
#define SPI_ROM_CR              1
#define RB_ROM_SCS              0x0001
#define RB_ROM_SIO0_OE          0x0002
#define RB_ROM_RD_EN            0x0004
#define RB_ROM_WR8              0x0008
#define RB_ROM_DES_LONG         0x0100

/* EMMC register */
#define R16_EMMC_CLK_DIV        (*((vpuint16_t)(0x4000A038))) // SD clock divider register, [4:0]:divisor, sdclk1 = 480m/[4:0], default divisor is 20
// [8]:clk_oe, [8]==1 indicate supply SDCLK to sdcard, [8]==0 indicate close SDCLK, default clk_oe is 0
// [9]:sel_25m_100m, select 400k or 25~100m as SDCLK, [9]==1 indicate SDCLK = 480m/[4:0], [9]==0 indicate SDCLK = 480/[4:0]/64, default is 1
#define R32_EMMC_ARGUMENT       (*((vpuint32_t)(0x4000A000))) // SD 32bits command argument register
#define R16_EMMC_CMD_SET        (*((vpuint16_t)(0x4000A004))) // SD 16bits cmd setting register, [5:0] is the command index, [9:8] indicate the response tye, [10]==1 indicate need to check the response CRC7, [11]==1 indicate need to check the index of the response
#define R32_EMMC_RESPONSE0      (*((vpuint32_t)(0x4000A008))) // SD 128bits response register, [31:0] 32bits
#define R32_EMMC_RESPONSE1      (*((vpuint32_t)(0x4000A00c))) // SD 128bits response register, [63:32] 32bits
#define R32_EMMC_RESPONSE2      (*((vpuint32_t)(0x4000A010))) // SD 128bits response register, [95:64] 32bits
#define R32_EMMC_RESPONSE3      (*((vpuint32_t)(0x4000A014))) // SD 128bits response register, [127:96] 32bits, when response length is 48, the 32bit response data is stored in this register
#define R8_EMMC_CONTROL         (*((vpuint8_t)(0x4000A018)))  // SD 8bits control register, [1:0] number of data line will operate, [2]==1 soft reset all the inner logic, [3]==1 enable DMA, [4]==1 reset inner data tran/recv logic, [5]==1 @negedge sample cmd/dat[7:0] lines
#define R8_EMMC_TIMEOUT         (*((vpuint8_t)(0x4000A01c)))  // SD 8bits data timeout value, the real timeout time is 4194304*Tsdclk*value
#define R32_EMMC_STATUS         (*((vpuint32_t)(0x4000A020))) // SD status:[15:0] number of current successful tran/recv blocks, [16] current sd cmd line level, [17] current sd dat[0] line level
#define R16_EMMC_INT_FG         (*((vpuint16_t)(0x4000A024))) // SD 16bits interrupt flag register
#define R16_EMMC_INT_EN         (*((vpuint16_t)(0x4000A028))) // SD 16bits interrupt enable register
#define R32_EMMC_DMA_BEG1       (*((vpuint32_t)(0x4000A02C))) // SD 16bits DMA start address register when to operate
#define R32_EMMC_BLOCK_CFG      (*((vpuint32_t)(0x4000A030))) // SD 32bits data counter, [15:0] number of blocks this time will tran/recv, [27:16] block sise(byte number) of every block in this time tran/recv
#define R32_EMMC_TRAN_MODE      (*((vpuint32_t)(0x4000A034))) // SD TRANSFER MODE register, [0] direction of this time, 1-write sd, 0-read sd, [1] stop at block gap when multiple wr/rd, [2] this time is eMMC boot mode operation
#define R32_EMMC_DMA_BEG2       (*((vpuint32_t)(0x4000A03C)))

/* EMMC register address offset and bit define */
#define EMMC_CLK_DIV            0x38
#define RB_EMMC_PHASEINV        0x400       // invert chip output sdclk phase
#define RB_EMMC_CLKMode         0x200       // 1:25-100m 0:400k
#define RB_EMMC_CLKOE           0x100       // chip output sdclk oe
#define RB_EMMC_DIV_MASK        0x1F        // clk div
#define EMMC_ARGUMENT           0x00
#define EMMC_CMD_SET            0x04
#define RB_EMMC_CKIDX           0x800
#define RB_EMMC_CKCRC           0x400
#define RB_EMMC_RPTY_MASK       0x300
#define RB_EMMC_CMDIDX_MASK     0x3F
#define EMMC_RESPONSE0          0x08
#define EMMC_RESPONSE1          0x0c
#define EMMC_RESPONSE2          0x10
#define EMMC_RESPONSE3          0x14
#define EMMC_WRITE_CONT         0x14
#define EMMC_CONTROL            0x18
#define RB_EMMC_NEGSMP          0x0020      // controller use nagedge sample cmd, dat[7:0], when use UHS-I mode, timing is difficult to meet, use the negedge will be better, default is @posedge sample
#define RB_EMMC_RST_LGC         0x0010      // reset the data tran/recv logic, this bit is useful when block CRC error in multiple rd/wr situation, default is valid
#define RB_EMMC_DMAEN           0x0008      // enable the dma, if the 1# 2# 3# controller is to be used, should also open the 0# dma enable, 0# dma work as the whole enable, default dma is closed
#define RB_EMMC_ALL_CLR         0x0004      // reset all the inner logic, default is valid
#define RB_EMMC_LW_MASK         0x0003
#define bLW_OP_DAT8             0x0002      // use data line [7:0], can be set only in 0# 2# controller
#define bLW_OP_DAT4             0x0001      // use data line [3:0], the default is this value
#define bLW_OP_DAT0             0x0000      // use data line [0] only
#define EMMC_TIMEOUT            0x1C
#define RB_EMMC_TOCNT_MASK      0x000F
#define EMMC_STATUS             0x20        // SD status
#define RB_EMMC_DAT0STA         0x20000     // indicate dat[0] line is high level now
#define RB_EMMC_CMDSTA          0x10000     // indicate cmd line is high level now
#define EMMC_INT_FG             0x24
#define RB_EMMC_IF_SDIOINT      0x200       // interrupt from SDIO card inside
#define RB_EMMC_IF_FIFO_OV      0x100       // fifo overflow, when write sd, indicate empty overflow, when read sd, indicate full overflow
#define RB_EMMC_IF_BKGAP        0x080       // every block gap interrupt when multiple read/write, allow drive change the DMA address at this moment
#define RB_EMMC_IF_TRANDONE     0x040       // all the blocks have been tran/recv successfully
#define RB_EMMC_IF_TRANERR      0x020       // last block have encountered a CRC error
#define RB_EMMC_IF_DATTMO       0x010       // data line busy timeout
#define RB_EMMC_IF_CMDDONE      0x008       // when cmd hasn't response, indicate cmd has been sent, when cmd has a response, indicate cmd has bee sent and has received the response
#define RB_EMMC_IF_REIDX_ER     0x004       // indicate INDEX error of the response
#define RB_EMMC_IF_RECRC_WR     0x002       // indicate CRC error of the response
#define RB_EMMC_IF_RE_TMOUT     0x001       // indicate when expect the response, timeout
#define EMMC_INT_EN             0x28        // interrupt enable
#define RB_EMMC_IE_SDIOINT      0x200
#define RB_EMMC_IE_FIFO_OV      0x100
#define RB_EMMC_IE_BKGAP        0x080
#define RB_EMMC_IE_TRANDONE     0x040
#define RB_EMMC_IE_TRANERR      0x020
#define RB_EMMC_IE_DATTMO       0x010
#define RB_EMMC_IE_CMDDONE      0x008
#define RB_EMMC_IE_REIDX_ER     0x004
#define RB_EMMC_IE_RECRC_WR     0x002
#define RB_EMMC_IE_RE_TMOUT     0x001
#define EMMC_DMA_BEG1           0x2c
#define RB_EMMC_DMAAD1_MASK     0x1FFFF
#define EMMC_BLOCK_CFG          0x30
#define RB_EMMC_BKSIZE_MASK     0x01FF0000
#define RB_EMMC_BKNUM_MASK      0xFFFF
#define EMMC_TRAN_MODE          0x34        // tran mode
#define RB_EMMC_DULEDMA_EN      0x10000     // enable double buffer dma
#define RB_EMMC_DMATN_CNT       0x7f00
#define RB_EMMC_FIFO_RDY        0x00c0
#define RB_EMMC_AUTOGAPSTOP     0x00010     // enable auto set bTM_GAP_STOP when tran start
#define RB_EMMC_MODE_BOOT       0x00004     // enable emmc boot mode
#define RB_EMMC_GAP_STOP        0x00002     // set gap stop
#define RB_EMMC_DMA_DIR         0x00001     // set direction is controller to emmc card

/* ECED AES/SM4 register */
#define R16_ECEC_CTRL           (*((vpuint16_t)(0x40007000)))
#define RB_ECDC_DAT_MOD         0x02000     // source data and result data is bit endian
#define RB_ECDC_KLEN_MASK       0x0C00
#define RB_ECDC_CIPHER_MOD      0x0200      // 1:CTR mode 0:ECB mode
#define RB_ECDC_ALGRM_MOD       0x0100      // 1:AES 0:SM4
#define RB_ECDC_WRSRAM_EN       0x0080      // module dma enable
#define RB_ECDC_CLKDIV_MASK     0x0030
#define RB_ECDC_MODE_SEL        0x0008      // 1:decryption mode 0:encryption mode
#define RB_ECDC_WRPERI_EN       0x0004      // when read data from dma, 1:encrypt/decrypt 0:no action
#define RB_ECDC_RDPERI_EN       0x0002      // when write data to dma,  1:encrypt/decrypt 0:no action
#define RB_ECDC_KEYEX_EN        0x0001      // enable key expansion

#define R8_ECDC_INT_EN          (*((vpuint8_t)(0x40007002)))
#define RB_ECDC_IE_WRSRAM       0x04        // interrupt en
#define RB_ECDC_IE_SINGLE       0x02        // interrupt en
#define RB_ECDC_IE_EKDONE       0x01        // interrupt en

#define R8_ECDC_INT_FG          (*((vpuint8_t)(0x40007006)))
#define RB_ECDC_IF_WRSRAM       0x04        // interrupt en
#define RB_ECDC_IF_SINGLE       0x02        // interrupt en
#define RB_ECDC_IF_EKDONE       0x01        // interrupt en

//	the following 8*32-bit registers are used to store 128/192/256-bit key
#define R32_ECDC_KEY_255T224    (*((vpuint32_t)(0x40007008)))
#define R32_ECDC_KEY_223T192    (*((vpuint32_t)(0x4000700c)))
#define R32_ECDC_KEY_191T160    (*((vpuint32_t)(0x40007010)))
#define R32_ECDC_KEY_159T128    (*((vpuint32_t)(0x40007014)))
#define R32_ECDC_KEY_127T96     (*((vpuint32_t)(0x40007018)))
#define R32_ECDC_KEY_95T64      (*((vpuint32_t)(0x4000701c)))
#define R32_ECDC_KEY_63T32      (*((vpuint32_t)(0x40007020)))
#define R32_ECDC_KEY_31T0       (*((vpuint32_t)(0x40007024)))

//	the following 4*32-bit registers are used to store initial vector for CTR mode
#define R32_ECDC_IV_127T96      (*((vpuint32_t)(0x40007028)))
#define R32_ECDC_IV_95T64       (*((vpuint32_t)(0x4000702c)))
#define R32_ECDC_IV_63T32       (*((vpuint32_t)(0x40007030)))
#define R32_ECDC_IV_31T0        (*((vpuint32_t)(0x40007034)))

#define R32_ECDC_SGSD_127T96    (*((vpuint32_t)(0x40007040)))
#define R32_ECDC_SGSD_95T64     (*((vpuint32_t)(0x40007044)))
#define R32_ECDC_SGSD_63T32     (*((vpuint32_t)(0x40007048)))
#define R32_ECDC_SGSD_31T0      (*((vpuint32_t)(0x4000704C)))

#define R32_ECDC_SGRT_127T96    (*((vpuint32_t)(0x40007050)))
#define R32_ECDC_SGRT_95T64     (*((vpuint32_t)(0x40007054)))
#define R32_ECDC_SGRT_63T32     (*((vpuint32_t)(0x40007058)))
#define R32_ECDC_SGRT_31T0      (*((vpuint32_t)(0x4000705C)))

#define R32_ECDC_SRAM_ADDR      (*((vpuint32_t)(0x40007060)))
#define R32_ECDC_SRAM_LEN       (*((vpuint32_t)(0x40007064)))

/* Address space define */
#define BA_CODE                 ((puint32_t)0x00000000) // point code base address
#define SZ_CODE                 0x00080000            // code size, Min:32KB, Max:96KB
#define BA_SFR                  ((puint32_t)0x40000000) // point SFR base address
#define SZ_SFR                  0x00010000            // SFR size
#define BA_RAM                  ((puint32_t)0x20000000) // point RAM base address
#define SZ_RAM                  0x00004000            // RAM size
#define BA_RAMX                 ((puint32_t)0x20020000) // point RAMX base address
#define SZ_RAMX                 0x00018000            // RAMX size, Min:32KB, Max:96KB
#define BA_XBUS                 ((puint32_t)0x80000000) // point XBUS base address
#define SZ_XBUS                 0x00008000            // XBUS size

/*----- Reference Information --------------------------------------------*/
#define ID_CH569W               0x71        // chip ID for CH569W
#define ID_CH565W               0x73        // chip ID for CH565W

/* Interrupt routine address and interrupt number */
#define INT_ID_WDOG             16          // interrupt number for watch-dog timer or software
#define INT_ID_TMR0             17          // interrupt number for timer0
#define INT_ID_GPIO             18          // interrupt number for GPIO
#define INT_ID_SPI0             19          // interrupt number for SPI0
#define INT_ID_USBSS            20          // interrupt number for USBSS
#define INT_ID_LINK             21          // interrupt number for USBSS Linklayer
#define INT_ID_TMR1             22          // interrupt number for timer1
#define INT_ID_TMR2             23          // interrupt number for timer2
#define INT_ID_UART0            24          // interrupt number for UART0
#define INT_ID_USBHS            25          // interrupt number for USBHS
#define INT_ID_EMMC             26          // interrupt number for EMMC
#define INT_ID_DVP              27          // interrupt number for DVP
#define INT_ID_HSPI             28          // interrupt number for HSPI
#define INT_ID_SPI1             29          // interrupt number for SPI1
#define INT_ID_UART1            30          // interrupt number for UART1
#define INT_ID_UART2            31          // interrupt number for UART2
#define INT_ID_UART3            32          // interrupt number for UART3
#define INT_ID_SERDES           33          // interrupt number for SERDES
#define INT_ID_ETH              34          // interrupt number for ETH
#define INT_ID_PMT              35          // interrupt number for ETH power management
#define INT_ID_ECDC             36          // interrupt number for ECDC

#define INT_VEC_ENTRY_SZ        4                                  // size of each interrupt vector entry
#define INT_ADDR_WDOG           (INT_ID_WDOG * INT_VEC_ENTRY_SZ)   // interrupt vector address for watch-dog timer or software
#define INT_ADDR_TMR0           (INT_ID_TMR0 * INT_VEC_ENTRY_SZ)   // interrupt vector address for TMR0
#define INT_ADDR_GPIO           (INT_ID_GPIO * INT_VEC_ENTRY_SZ)   // interrupt vector address for GPIO
#define INT_ADDR_SPI0           (INT_ID_SPI0 * INT_VEC_ENTRY_SZ)   // interrupt vector address for SPI0
#define INT_ADDR_USBSS          (INT_ID_USBSS * INT_VEC_ENTRY_SZ)  // interrupt vector address for USBSS
#define INT_ADDR_LINK           (INT_ID_LINK * INT_VEC_ENTRY_SZ)   // interrupt vector address for USBSS Linklayer
#define INT_ADDR_TMR1           (INT_ID_TMR1 * INT_VEC_ENTRY_SZ)   // interrupt vector address for TMR1
#define INT_ADDR_TMR2           (INT_ID_TMR2 * INT_VEC_ENTRY_SZ)   // interrupt vector address for TMR2
#define INT_ADDR_UART0          (INT_ID_UART0 * INT_VEC_ENTRY_SZ)  // interrupt vector address for UART0
#define INT_ADDR_USBHS          (INT_ID_USBHS * INT_VEC_ENTRY_SZ)  // interrupt vector address for USBHS
#define INT_ADDR_EMMC           (INT_ID_EMMC * INT_VEC_ENTRY_SZ)   // interrupt vector address for EMMC
#define INT_ADDR_DVP            (INT_ID_DVP * INT_VEC_ENTRY_SZ)    // interrupt vector address for DVP
#define INT_ADDR_HSPI           (INT_ID_HSPI * INT_VEC_ENTRY_SZ)   // interrupt vector address for HSPI
#define INT_ADDR_SPI1           (INT_ID_SPI1 * INT_VEC_ENTRY_SZ)   // interrupt vector address for SPI1
#define INT_ADDR_UART1          (INT_ID_UART1 * INT_VEC_ENTRY_SZ)  // interrupt vector address for UART1
#define INT_ADDR_UART2          (INT_ID_UART2 * INT_VEC_ENTRY_SZ)  // interrupt vector address for UART2
#define INT_ADDR_UART3          (INT_ID_UART3 * INT_VEC_ENTRY_SZ)  // interrupt vector address for UART3
#define INT_ADDR_SERDES         (INT_ID_SERDES * INT_VEC_ENTRY_SZ) // interrupt vector address for SERDES
#define INT_ADDR_ETH            (INT_ID_ETH * INT_VEC_ENTRY_SZ)    // interrupt vector address for ETH
#define INT_ADDR_PMT            (INT_ID_PMT * INT_VEC_ENTRY_SZ)    // interrupt vector address for ETH power management
#define INT_ADDR_ECDC           (INT_ID_ECDC * INT_VEC_ENTRY_SZ)   // interrupt vector address for ECDC

#ifndef TABLE_IRQN
typedef enum IRQn
{
	Reset_IRQn = 1,
	NMI_IRQn = 2,      /*!< Non Maskable Interrupt   */
	EXC_IRQn = 3,      /*!< Exceptions Interrupt      */
	SysTick_IRQn = 12, /*!< System timer Interrupt  */
	SWI_IRQn = 14,     /*!< software Interrupt */
	WDOG_IRQn = 16,
	TMR0_IRQn = 17,
	GPIO_IRQn = 18,
	SPI0_IRQn = 19,
	USBSS_IRQn = 20,
	LINK_IRQn = 21,
	TMR1_IRQn = 22,
	TMR2_IRQn = 23,
	UART0_IRQn = 24,
	USBHS_IRQn = 25,
	EMMC_IRQn = 26,
	DVP_IRQn = 27,
	HSPI_IRQn = 28,
	SPI1_IRQn = 29,
	UART1_IRQn = 30,
	UART2_IRQn = 31,
	UART3_IRQn = 32,
	SERDES_IRQn = 33,
	ETH_IRQn = 34,
	PMT_IRQn = 35,
	ECDC_IRQn = 36,
} IRQn_Type;
#endif

#ifdef __cplusplus
}
#endif

#endif // __CH56xGPSFR_H__

#ifndef __CH56xUSBSFR_H__
#define __CH56xUSBSFR_H__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* usb addresses                                                              */
#define USB_BASE_ADDR         (0x40009000)

#define R32_USB_CONTROL       (*((vpuint32_t)(USB_BASE_ADDR + 0x000))) // USB control & interrupt enable & device address
#define R8_USB_CTRL           (*((vpuint8_t)(USB_BASE_ADDR + 0x000)))  // USB base control
#define R8_UHOST_CTRL         (*((vpuint8_t)(USB_BASE_ADDR + 0x001)))  // USB actual speed
#define R8_USB_INT_EN         (*((vpuint8_t)(USB_BASE_ADDR + 0x002)))  // USB interrupt enable
#define R8_USB_DEV_AD         (*((vpuint8_t)(USB_BASE_ADDR + 0x003)))  // USB device address
#define R32_USB_FRAME_NO      (*((vpuint32_t)(USB_BASE_ADDR + 0x004)))
#define R16_USB_FRAME_NO      (*((vpuint16_t)(USB_BASE_ADDR + 0x004)))
#define R8_USB_SUSPEND        (*((vpuint8_t)(USB_BASE_ADDR + 0x006)))
#define R32_USB_STATUS        (*((vpuint32_t)(USB_BASE_ADDR + 0x008))) // USB miscellaneous status & interrupt flag & interrupt status
#define R8_USB_SPD_TYPE       (*((vpuint8_t)(USB_BASE_ADDR + 0x008)))  // USB actual speed
#define R8_USB_MIS_ST         (*((vpuint8_t)(USB_BASE_ADDR + 0x009)))  // USB miscellaneous status
#define R8_USB_INT_FG         (*((vpuint8_t)(USB_BASE_ADDR + 0x00a)))  // USB interrupt flag
#define R8_USB_INT_ST         (*((vpuint8_t)(USB_BASE_ADDR + 0x00b)))  // USB interrupt status
#define R16_USB_RX_LEN        (*((vpuint16_t)(USB_BASE_ADDR + 0x00c))) // USB receiving length
#define R32_USB_BUF_MODE      (*((vpuint32_t)(USB_BASE_ADDR + 0x010))) // USB endpoint buffer mode
#define R8_UEP4_1_MOD         (*((vpuint8_t)(USB_BASE_ADDR + 0x010)))  // endpoint 4/1 mode
#define R8_UEP2_3_MOD         (*((vpuint8_t)(USB_BASE_ADDR + 0x011)))  // endpoint 2/3 mode
#define R8_UEP5_6_MOD         (*((vpuint8_t)(USB_BASE_ADDR + 0x012)))  // endpoint 5/6 mode
#define R8_UEP7_MOD           (*((vpuint8_t)(USB_BASE_ADDR + 0x013)))  // endpoint 7 mode
#define R8_UH_EP_MOD          R8_UEP2_3_MOD                          // host endpoint mode
#define R32_UEP0_RT_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x014))) // endpoint 0 DMA RX buffer address
#define R32_UEP1_RX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x018))) // endpoint 1 DMA RX buffer address
#define R32_UEP2_RX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x01c))) // endpoint 2 DMA RX buffer address
#define R32_UEP3_RX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x020))) // endpoint 3 DMA RX buffer address
#define R32_UEP4_RX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x024))) // endpoint 4 DMA RX buffer address
#define R32_UEP5_RX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x028))) // endpoint 5 DMA RX buffer address
#define R32_UEP6_RX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x02C))) // endpoint 6 DMA RX buffer address
#define R32_UEP7_RX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x030))) // endpoint 7 DMA RX buffer address
#define R32_UH_RX_DMA         R32_UEP2_RX_DMA                        // host rx endpoint buffer high address
#define R32_UH_TX_DMA         R32_UEP3_TX_DMA                        // host tx endpoint buffer high address
#define R32_UEP1_TX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x034))) // endpoint 1 DMA TX buffer address
#define R32_UEP2_TX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x038))) // endpoint 2 DMA TX buffer address
#define R32_UEP3_TX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x03C))) // endpoint 3 DMA TX buffer address
#define R32_UEP4_TX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x040))) // endpoint 4 DMA TX buffer address
#define R32_UEP5_TX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x044))) // endpoint 5 DMA TX buffer address
#define R32_UEP6_TX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x048))) // endpoint 6 DMA TX buffer address
#define R32_UEP7_TX_DMA       (*((vpuint32_t)(USB_BASE_ADDR + 0x04C))) // endpoint 7 DMA TX buffer address
#define R16_UEP0_MAX_LEN      (*((vpuint16_t)(USB_BASE_ADDR + 0x050)))
#define R16_UEP1_MAX_LEN      (*((vpuint16_t)(USB_BASE_ADDR + 0x054)))
#define R16_UEP2_MAX_LEN      (*((vpuint16_t)(USB_BASE_ADDR + 0x058)))
#define R16_UEP3_MAX_LEN      (*((vpuint16_t)(USB_BASE_ADDR + 0x05C)))
#define R16_UEP4_MAX_LEN      (*((vpuint16_t)(USB_BASE_ADDR + 0x060)))
#define R16_UEP5_MAX_LEN      (*((vpuint16_t)(USB_BASE_ADDR + 0x064)))
#define R16_UEP6_MAX_LEN      (*((vpuint16_t)(USB_BASE_ADDR + 0x068)))
#define R16_UEP7_MAX_LEN      (*((vpuint16_t)(USB_BASE_ADDR + 0x06C)))
#define R16_UH_RX_MAX_LEN     R16_UEP2_MAX_LEN
#define R32_USB_EP0_CTRL      (*((vpuint32_t)(USB_BASE_ADDR + 0x070))) // endpoint 0 control & transmittal length
#define R16_UEP0_T_LEN        (*((vpuint16_t)(USB_BASE_ADDR + 0x070))) // endpoint 0 transmittal length
#define R8_UEP0_TX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x072)))  // endpoint 0 tx control
#define R8_UEP0_RX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x073)))  // endpoint 0 rx control

#define R32_USB_EP1_CTRL      (*((vpuint32_t)(USB_BASE_ADDR + 0x074))) // endpoint 1 control & transmittal length
#define R16_UEP1_T_LEN        (*((vpuint16_t)(USB_BASE_ADDR + 0x074))) // endpoint 1 transmittal length
#define R8_UEP1_TX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x076)))  // endpoint 1 control
#define R8_UEP1_RX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x077)))  // endpoint 1 control

//#define R8_UH_SETUP             R8_UEP1_TX_CTRL	// host aux setup
#define R32_USB_EP2_CTRL      (*((vpuint32_t)(USB_BASE_ADDR + 0x078))) // endpoint 2 control & transmittal length
#define R16_UEP2_T_LEN        (*((vpuint16_t)(USB_BASE_ADDR + 0x078))) // endpoint 2 transmittal length
#define R8_UEP2_TX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x07A)))  // endpoint 2 control
#define R8_UEP2_RX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x07B)))  // endpoint 2 control

#define R16_UH_EP_PID         R16_UEP2_T_LEN                         // host endpoint and PID
#define R8_UH_RX_CTRL         R8_UEP2_RX_CTRL                        // host receiver endpoint control
#define R32_USB_EP3_CTRL      (*((vpuint32_t)(USB_BASE_ADDR + 0x07C))) // endpoint 3 control & transmittal length
#define R16_UEP3_T_LEN        (*((vpuint16_t)(USB_BASE_ADDR + 0x07C))) // endpoint 3 transmittal length
#define R8_UEP3_TX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x07E)))  // endpoint 3 control
#define R8_UEP3_RX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x07F)))  // endpoint 3 control

#define R16_UH_TX_LEN         R16_UEP3_T_LEN    // host transmittal endpoint transmittal length
#define R8_UH_TX_CTRL         R8_UEP3_TX_CTRL   // host transmittal endpoint control

#define R32_USB_EP4_CTRL      (*((vpuint32_t)(USB_BASE_ADDR + 0x080))) // endpoint 4 control & transmittal length
#define R16_UEP4_T_LEN        (*((vpuint16_t)(USB_BASE_ADDR + 0x080))) // endpoint 4 transmittal length
#define R8_UEP4_TX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x082)))  // endpoint 4 control
#define R8_UEP4_RX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x083)))  // endpoint 4 control

#define R16_UH_SPLIT_DATA     R16_UEP4_T_LEN

#define R32_USB_EP5_CTRL      (*((vpuint32_t)(USB_BASE_ADDR + 0x084))) // endpoint 5 control & transmittal length
#define R16_UEP5_T_LEN        (*((vpuint16_t)(USB_BASE_ADDR + 0x084))) // endpoint 5 transmittal length
#define R8_UEP5_TX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x086)))  // endpoint 5 control
#define R8_UEP5_RX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x087)))  // endpoint 5 control

#define R32_USB_EP6_CTRL      (*((vpuint32_t)(USB_BASE_ADDR + 0x088))) // endpoint 6 control & transmittal length
#define R16_UEP6_T_LEN        (*((vpuint16_t)(USB_BASE_ADDR + 0x088))) // endpoint 6 transmittal length
#define R8_UEP6_TX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x08A)))  // endpoint 6 control
#define R8_UEP6_RX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x08B)))  // endpoint 6 control

#define R32_USB_EP7_CTRL      (*((vpuint32_t)(USB_BASE_ADDR + 0x08C))) // endpoint 7 control & transmittal length
#define R16_UEP7_T_LEN        (*((vpuint16_t)(USB_BASE_ADDR + 0x08C))) // endpoint 7 transmittal length
#define R8_UEP7_TX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x08E)))  // endpoint 7 control
#define R8_UEP7_RX_CTRL       (*((vpuint8_t)(USB_BASE_ADDR + 0x08F)))  // endpoint 7 control

/*  USB register address offset and bit define */

/* USB base control registers: R8_USB_CTRL  */
#define RB_USB_HOST_MODE      0x80              // enable USB host mode: 0=device mode, 1=host mode
#define RB_USB_SPTP_MASK      0x60              // enable USB low speed: 00=full speed, 01=high speed, 10 =low speed
#define UCST_FS               0x00
#define UCST_HS               0x20
#define UCST_LS               0x40
#define RB_DEV_PU_EN          0x10              // USB device enable and internal pullup resistance enable
#define RB_USB_INT_BUSY       0x08              // enable automatic responding busy for device mode or automatic pause for host mode during interrupt flag UIF_TRANSFER valid
#define RB_USB_RESET_SIE      0x04              // force reset USB SIE, need software clear
#define RB_USB_CLR_ALL        0x02              // force clear FIFO and count of USB
#define RB_USB_DMA_EN         0x01              // DMA enable and DMA interrupt enable for USB

/* USB interrupt enable registers: R8_USB_INT_EN  */
#define RB_USB_IE_DEV_NAK     0x80              // enable interrupt for NAK responded for USB device mode
#define RB_USB_IE_ISOACT      0x40
#define RB_USB_IE_SETUPACT    0x20
#define RB_USB_IE_FIFOOV      0x10              // enable interrupt for FIFO overflow
#define RB_USB_IE_SOF         0x08              // enable interrupt for host SOF timer action for USB host mode
#define RB_USB_IE_SUSPEND     0x04              // enable interrupt for USB suspend or resume event
#define RB_USB_IE_TRANS       0x02              // enable interrupt for USB transfer completion
#define RB_USB_IE_DETECT      0x01              // enable interrupt for USB device detected event for USB host mode
#define RB_USB_IE_BUSRST      0x01              // enable interrupt for USB bus reset event for USB device mode

/* R8_USB_SUSPEND  */
//#define bUS_WAKE_UP 0x04  // wake up from suspend
#define RB_DEV_WAKEUP         0x02              //remote resume

/* R8_USB_SPD_TYPE  */
#define RB_USBSPEED_MASK      0x03
#define UST_FS                0x00              // USB_SPD_TYPE is full speed
#define UST_HS                0x01              // USB_SPD_TYPE is high speed
#define UST_LS                0x02              // USB_SPD_TYPE is low speed

/* ReadOnly, USB miscellaneous status registers:  R8_USB_MIS_ST  */
#define RB_USB_SOF_PRES       0x80              // ReadOnly: indicate host SOF timer presage status
#define RB_USB_SOF_ACT        0x40              // ReadOnly: indicate host SOF timer action status for USB host
#define RB_USB_SIE_FREE       0x20              // ReadOnly: indicate USB SIE free status
#define RB_USB_FIFO_RDY       0x10              // ReadOnly: indicate USB receiving FIFO ready status (not empty)
#define RB_USBBUS_RESET       0x08              // ReadOnly: indicate USB bus reset status
#define RB_USBBUS_SUSPEND     0x04              // ReadOnly: indicate USB suspend status
#define RB_USB_ATTACH         0x02              // ReadOnly: indicate device attached status on USB hub DP/DM
#define RB_USB_SPLIT_EN       0x01              // ReadOnly: indicate host allow SPLIT packet

/* USB interrupt flag registers:  R8_USB_INT_FG   */
#define RB_USB_IF_ISOACT      0x40
#define RB_USB_IF_SETUOACT    0x20
#define RB_USB_IF_FIFOOV      0x10              // FIFO overflow interrupt flag for USB, direct bit address clear or write 1 to clear
#define RB_USB_IF_HST_SOF     0x08              // host SOF timer interrupt flag for USB host, direct bit address clear or write 1 to clear
#define RB_USB_IF_SUSPEND     0x04              // USB suspend or resume event interrupt flag, direct bit address clear or write 1 to clear
#define RB_USB_IF_TRANSFER    0x02              // USB transfer completion interrupt flag, direct bit address clear or write 1 to clear
#define RB_USB_IF_DETECT      0x01              // device detected event interrupt flag for USB host mode, direct bit address clear or write 1 to clear
#define RB_USB_IF_BUSRST      0x01              // bus reset event interrupt flag for USB device mode, direct bit address clear or write 1 to clear

/* ReadOnly, USB interrupt status registers:  R8_USB_INT_ST  */
#define RB_USB_ST_NAK         0x80              // ReadOnly: indicate current USB transfer is NAK received for USB device mode
#define RB_USB_ST_TOGOK       0x40              // ReadOnly: indicate current USB transfer toggle is OK
#define RB_DEV_TOKEN_MASK     0x30              // ReadOnly: bit mask of current token PID code received for USB device mode
#define RB_DEV_ENDP_MASK      0x0F              // ReadOnly: bit mask of current transfer endpoint number for USB device mode
#define RB_HOST_RES_MASK      0x0F              // ReadOnly: bit mask of current transfer handshake response for USB host mode: 0000=no response, time out from device, others=handshake response PID received

#define UIS_TOKEN_OUT         0x00
#define UIS_TOKEN_SOF         0x10
#define UIS_TOKEN_IN          0x20
#define UIS_TOKEN_SETUP       0x30
// bUIS_TOKEN1 & bUIS_TOKEN0: current token PID code received for USB device mode
//   00: OUT token PID received
//   01: SOF token PID received
//   10: IN token PID received
//   11: SETUP token PID received

/* USB device endpoint 1/4 buffer mode registers: R8_UEP4_1_MOD */
#define RB_UEP1_RX_EN         0x80              // enable USB endpoint 1 receiving (OUT)
#define RB_UEP1_TX_EN         0x40              // enable USB endpoint 1 transmittal (IN)
#define RB_UEP1_BUF_MOD       0x10              // buffer mode of USB endpoint 1
// bUEPn_RX_EN & bUEPn_TX_EN & bUEPn_BUF_MOD: USB endpoint 1/2/3 buffer mode, buffer start address is UEPn_DMA
//   0 0 x:  disable endpoint and disable buffer
//   1 0 0:  512 bytes buffer for receiving (OUT endpoint)
//   1 0 1:  dual 512 bytes buffer by toggle bit bUEP_R_TOG selection for receiving (OUT endpoint), total=1024bytes
//   0 1 0:  512 bytes buffer for transmittal (IN endpoint)
//   0 1 1:  dual 512 bytes buffer by toggle bit bUEP_T_TOG selection for transmittal (IN endpoint), total=1024bytes
//   1 1 0:  512 bytes buffer for receiving (OUT endpoint) + 512 bytes buffer for transmittal (IN endpoint), total=1024bytes
//   1 1 1:  dual 512 bytes buffer by bUEP_R_TOG selection for receiving (OUT endpoint) + dual 512 bytes buffer by bUEP_T_TOG selection for transmittal (IN endpoint), total=2048bytes
#define RB_UEP4_RX_EN         0x08              // enable USB endpoint 4 receiving (OUT)
#define RB_UEP4_TX_EN         0x04              // enable USB endpoint 4 transmittal (IN)
#define RB_UEP4_BUF_MOD       0x01              // buffer mode of USB endpoint 4

/* USB device endpoint 2/3 buffer mode registers: R8_UEP2_3_MOD */
#define RB_UEP3_RX_EN         0x80              // enable USB endpoint 3 receiving (OUT)
#define RB_UEP3_TX_EN         0x40              // enable USB endpoint 3 transmittal (IN)
#define RB_UEP3_BUF_MOD       0x10              // buffer mode of USB endpoint 3
#define RB_UEP2_RX_EN         0x08              // enable USB endpoint 2 receiving (OUT)
#define RB_UEP2_TX_EN         0x04              // enable USB endpoint 2 transmittal (IN)
#define RB_UEP2_BUF_MOD       0x01              // buffer mode of USB endpoint 2

/* USB device endpoint 5/6 buffer mode registers: R8_UEP5_6_MOD */
#define RB_UEP6_RX_EN         0x80              // enable USB endpoint 6 receiving (OUT)
#define RB_UEP6_TX_EN         0x40              // enable USB endpoint 6 transmittal (IN)
#define RB_UEP6_BUF_MOD       0x10              // buffer mode of USB endpoint 6
#define RB_UEP5_RX_EN         0x08              // enable USB endpoint 5 receiving (OUT)
#define RB_UEP5_TX_EN         0x04              // enable USB endpoint 5 transmittal (IN)
#define RB_UEP5_BUF_MOD       0x01              // buffer mode of USB endpoint 5

/* USB device endpoint 7 buffer mode registers: R8_UEP7_MOD */
#define RB_UEP7_RX_EN         0x08              // enable USB endpoint 7 receiving (OUT)
#define RB_UEP7_TX_EN         0x04              // enable USB endpoint 7 transmittal (IN)
#define RB_UEP7_BUF_MOD       0x01              // buffer mode of USB endpoint 7

/* R8_UEPn_TX_CTRL  n=0-15 */
#define RB_UEP_T_AUTOTOG      0x20              // enable automatic toggle after successful transfer completion on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle
#define RB_UEP_T_TOG_MASK     0x18              // prepared data toggle flag of USB endpoint X transmittal (IN): 00=DATA0, 01=DATA1, 10=DATA2, 11=MDATA
#define RB_UEP_T_TOG_0        (0 << 3)
#define RB_UEP_T_TOG_1        (1 << 3)
#define RB_UEP_T_TOG_2        (2 << 3)
#define RB_UEP_T_TOG_M        (3 << 3)
#define RB_UEP_TRES_NO        (0x04) // expected no response, 1=enable, 0=disable, for non-zero endpoint isochronous transactions
#define RB_UEP_TRES_MASK      (0x03) // bit mask of handshake response type for USB endpoint X transmittal (IN)
#define UEP_T_RES_ACK         0x00
#define UEP_T_RES_NAK         0x02
#define UEP_T_RES_STALL       0x03
// bUEP_T_RES1 & bUEP_T_RES0: handshake response type for USB endpoint X transmittal (IN)
//   00: ACK (ready)
//   10: NAK (busy)
//   11: STALL (error)

/* R8_UEPn_RX_CTRL  n=0-15 */
#define RB_UEP_R_AUTOTOG      0x20              // enable automatic toggle after successful transfer completion on endpoint 1/2/3: 0=manual toggle, 1=automatic toggle
#define RB_UEP_R_TOG_MASK     0x18              // expected data toggle flag of USB endpoint X receiving (OUT): 00s=DATA0, 01=DATA1, 10=DATA2, 11=MDATA
#define RB_UEP_R_TOG_0        (0 << 3)
#define RB_UEP_R_TOG_1        (1 << 3)
#define RB_UEP_R_TOG_2        (2 << 3)
#define RB_UEP_R_TOG_M        (3 << 3)
#define RB_UEP_RRES_NO        (0x04) // prepared no response, 1=enable, 0=disable, for non-zero endpoint isochronous transactions
#define RB_UEP_RRES_MASK      (0x03) // bit mask of handshake response type for USB endpoint X receiving (OUT)
#define UEP_R_RES_ACK         (0x00)
#define UEP_R_RES_NAK         (0x02)
#define UEP_R_RES_STALL       (0x03)
#define UEP_R_RES_NYET        (0x01)
// bUEP_R_RES1 & bUEP_R_RES0: handshake response type for USB endpoint X receiving (OUT)
//   00: ACK (ready)
//   10: NAK (busy)
//   11: STALL (error)
//   01: NYET

// bUEP_T_TOG1 & bUEP_T_TOG0 / bUEP_R_TOG1 & bUEP_R_TOG0 : toggle flag
#define UEP_DATA0             (0x00 << 3)
#define UEP_DATA1             (0x01 << 3)
#define UEP_DATA2             (0x02 << 3)
#define UEP_MDATA             (0x03 << 3)

/*   R8_UHOST_CTRL */
#define RB_UH_AUTOSOF_EN      0x80              // USB host automatic SOF enable
#define RB_UH_BUS_RESUME      0x04
#define RB_UH_BUS_SUSPEND     0x02
#define RB_UH_BUS_RESET       0x01

/* USB host buffer mode registers: R8_UH_EP_MOD */
#define RB_UH_TX_EN           0x40              // enable USB host OUT endpoint transmittal
//#define bUH_EP_TBUF_MOD   0x10      // buffer mode of USB host OUT endpoint
// bUH_EP_TX_EN & bUH_EP_TBUF_MOD: USB host OUT endpoint buffer mode, buffer start address is UH_TX_DMA
//   0 x:  disable endpoint and disable buffer
//   1 0:  512 bytes buffer for transmittal (OUT endpoint)
//   1 1:  dual 512 bytes buffer by toggle bit bUH_T_TOG selection for transmittal (OUT endpoint), total=1024bytes
#define RB_UH_RX_EN           0x08              // enable USB host IN endpoint receiving
//#define bUH_EP_RBUF_MOD   0x01      // buffer mode of USB host IN endpoint
// bUH_EP_RX_EN & bUH_EP_RBUF_MOD: USB host IN endpoint buffer mode, buffer start address is UH_RX_DMA
//   0 x:  disable endpoint and disable buffer
//   1 0:  512 bytes buffer for receiving (IN endpoint)
//   1 1:  dual 512 bytes buffer by toggle bit bUH_R_TOG selection for receiving (IN endpoint), total=1024bytes

/* USB host PID registers:  R16_UH_EP_PID  */
#define RB_UH_TOKEN_MASK      0xF0              // bit mask of token PID for USB host transfer
#define RB_UH_EPNUM_MASK      0x0F              // bit mask of endpoint number for USB host transfer

/* USB host RX control registers: R8_UH_RX_CTRL  */
#define RB_UH_RDATA_NO        0x40              // expect no data packet, for high speed hub in host mode
#define RB_UH_R_AUTOTOG       0x20              // enable automatic toggle after successful receiver completion: 0=manual toggle, 1=automatic toggle
#define RB_UH_R_TOG_MASK      0x18              // expected data toggle flag of host receiving (IN): 00=DATA0, 01=DATA1, 10=DATA2, 11=MDATA
#define RB_UH_RRES_NO         0x04              // prepared no response, 1=enable, 0=disable, for non-zero endpoint isochronous transactions
#define RB_UH_RRES_MASK       0x03              // prepared handshake response type for host receiving (IN)
// bUH_R_RES1 & bUH_R_RES0: handshake response type for host receiving (IN)
//   00: ACK (ready)
//   10: NAK (busy)
//   11: STALL (error)

/* USB host TX control registers: R8_UH_TX_CTRL */
#define RB_UH_TDATA_NO        0x40              // prepared no data packet, for high speed hub in host mode
#define RB_UH_T_AUTOTOG       0x20              // enable automatic toggle after successful transfer completion: 0=manual toggle, 1=automatic toggle
#define RB_UH_T_TOG_MASK      0x18              // prepared data toggle flag of host transmittal (SETUP/OUT): 00=DATA0, 01=DATA1, 10=DATA2, 11=MDATA
#define RB_UH_TRES_NO         0x04              // expected no response, 1=enable, 0=disable, for non-zero endpoint isochronous transactions
#define RB_UH_TRES_MASK       0x03              // expected handshake response type for host transmittal (SETUP/OUT)
// bUH_T_RES1 & bUH_T_RES0: expected handshake response type for host transmittal (SETUP/OUT)
//   00: ACK (ready)
//   10: NAK (busy)
//   11: STALL (error)
//   01: NYET

// toggle flag
#define UH_DATA0              (0x00 << 3)
#define UH_DATA1              (0x01 << 3)
#define UH_DATA2              (0x02 << 3)
#define UH_MDATA              (0x03 << 3)

// handshake response
#define UH_ACK                0x00
#define UH_NAK                0x02
#define UH_STALL              0x03
#define UH_NYET               0x01

/*********************************************************/
/*                  USB 3.0                              */
/*********************************************************/
#ifndef __PACKED
#define __PACKED    __attribute__((packed))
#endif

#define USBSS_BASE    (0x40008000)

typedef struct __PACKED
{
	vuint32_t LINK_CFG;          // 0x40008000
	vuint32_t LINK_CTRL;         // 0x40008004
	vuint32_t LINK_INT_CTRL;     // 0x40008008
	vuint32_t LINK_INT_FLAG;     // 0x4000800C
	vuint32_t LINK_STATUS;       // 0x40008010
	vuint32_t LINK_HP_BUF_CTRL;  // 0x40008014
	vuint32_t LINK_ERR_STATUS;   // 0x40008018
	vuint32_t LINK_ERR_CNT;      // 0x4000801C
	vuint32_t USB_CONTROL;       // 0x40008020
	vuint32_t USB_STATUS;        // 0x40008024
	vuint32_t HOST_STATUS;       // 0x40008028
	vuint32_t USB_RX_LEN;        // 0x4000802C
	vuint32_t USB_ITP;           // 0x40008030
	vuint32_t USB_ITP_ADJ;       // 0x40008034
	vuint32_t LINK_ISO_DLY;      // 0x40008038
	vuint32_t LINK_STREAM_ID;    // 0x4000803C
	vuint32_t LINK_ROUTE_STRING; // 0x40008040
	vuint32_t USB_FC_CTRL;       // 0x40008044
	vuint32_t LMP_TX_DATA0;      // 0x40008048
	vuint32_t LMP_TX_DATA1;      // 0x4000804C
	vuint32_t LMP_TX_DATA2;      // 0x40008050
	vuint32_t LMP_PORT_CAP;      // 0x40008054
	vuint32_t LMP_RX_DATA0;      // 0x40008058
	vuint32_t LMP_RX_DATA1;      // 0x4000805C
	vuint32_t LMP_RX_DATA2;      // 0x40008060
	vuint32_t TP_RX_DATA0;       // 0x40008064
	vuint32_t TP_RX_DATA1;       // 0x40008068
	vuint32_t TP_RX_DATA2;       // 0x4000806C
	vuint32_t UEP_CFG;           // 0x40008070
	vuint32_t UEP0_DMA;          // 0x40008074
	vuint32_t UEP0_RX_CTRL;      // 0x40008078
	vuint32_t UEP0_TX_CTRL;      // 0x4000807C
	vuint32_t UEP1_TX_DMA;       // 0x40008080
	vuint32_t UEP1_RX_DMA;       // 0x40008084
	vuint32_t UEP1_RX_CTRL;      // 0x40008088
	vuint32_t UEP1_TX_CTRL;      // 0x4000808C
	vuint32_t UEP2_RX_DMA;       // 0x40008090
	vuint32_t UEP2_TX_DMA;       // 0x40008094
	vuint32_t UEP2_RX_CTRL;      // 0x40008098
	vuint32_t UEP2_TX_CTRL;      // 0x4000809C
	vuint32_t UEP3_TX_DMA;       // 0x400080A0
	vuint32_t UEP3_RX_DMA;       // 0x400080A4
	vuint32_t UEP3_RX_CTRL;      // 0x400080A8
	vuint32_t UEP3_TX_CTRL;      // 0x400080AC
	vuint32_t UEP4_TX_DMA;       // 0x400080B0
	vuint32_t UEP4_RX_DMA;       // 0x400080B4
	vuint32_t UEP4_RX_CTRL;      // 0x400080B8
	vuint32_t UEP4_TX_CTRL;      // 0x400080BC
	vuint32_t UEP5_TX_DMA;       // 0x400080C0
	vuint32_t UEP5_RX_DMA;       // 0x400080C4
	vuint32_t UEP5_RX_CTRL;      // 0x400080C8
	vuint32_t UEP5_TX_CTRL;      // 0x400080CC
	vuint32_t UEP6_TX_DMA;       // 0x400080D0
	vuint32_t UEP6_RX_DMA;       // 0x400080D4
	vuint32_t UEP6_RX_CTRL;      // 0x400080D8
	vuint32_t UEP6_TX_CTRL;      // 0x400080DC
	vuint32_t UEP7_TX_DMA;       // 0x400080E0
	vuint32_t UEP7_RX_DMA;       // 0x400080E4
	vuint32_t UEP7_RX_CTRL;      // 0x400080E8
	vuint32_t UEP7_TX_CTRL;      // 0x400080EC
	vuint32_t UX_EXIT_TIMER;     // 0x400080F0

} USBSS_TypeDef;

typedef struct __PACKED
{
	vuint32_t LINK_CFG;          // 0x40008000
	vuint32_t LINK_CTRL;         // 0x40008004
	vuint32_t LINK_INT_CTRL;     // 0x40008008
	vuint32_t LINK_INT_FLAG;     // 0x4000800C
	vuint32_t LINK_STATUS;       // 0x40008010
	vuint32_t LINK_HP_BUF_CTRL;  // 0x40008014
	vuint32_t LINK_ERR_STATUS;   // 0x40008018
	vuint32_t LINK_ERR_CNT;      // 0x4000801C
	vuint32_t USB_CONTROL;       // 0x40008020
	vuint32_t USB_STATUS;        // 0x40008024
	vuint32_t HOST_STATUS;       // 0x40008028
	vuint32_t USB_RX_LEN;        // 0x4000802C
	vuint32_t USB_ITP;           // 0x40008030
	vuint32_t USB_ITP_ADJ;       // 0x40008034
	vuint32_t LINK_ISO_DLY;      // 0x40008038
	vuint32_t LINK_STREAM_ID;    // 0x4000803C
	vuint32_t LINK_ROUTE_STRING; // 0x40008040
	vuint32_t USB_FC_CTRL;       // 0x40008044
	vuint32_t LMP_TX_DATA0;      // 0x40008048
	vuint32_t LMP_TX_DATA1;      // 0x4000804C
	vuint32_t LMP_TX_DATA2;      // 0x40008050
	vuint32_t LMP_PORT_CAP;      // 0x40008054
	vuint32_t LMP_RX_DATA0;      // 0x40008058
	vuint32_t LMP_RX_DATA1;      // 0x4000805C
	vuint32_t LMP_RX_DATA2;      // 0x40008060
	vuint32_t TP_RX_DATA0;       // 0x40008064
	vuint32_t TP_RX_DATA1;       // 0x40008068
	vuint32_t TP_RX_DATA2;       // 0x4000806C
	vuint32_t UEP_CFG;           // 0x40008070
	vuint32_t reserved0;         // 0x40008074
	vuint32_t reserved1;         // 0x40008078
	vuint32_t reserved2;         // 0x4000807C
	vuint32_t UH_TX_DMA;         // 0x40008080
	vuint32_t UH_RX_DMA;         // 0x40008084
	vuint32_t UH_RX_CTRL;        // 0x40008088
	vuint32_t UH_TX_CTRL;        // 0x4000808C
} USBSSH_TypeDef;

#define USBSS     ((USBSS_TypeDef *)USBSS_BASE)
#define USBSSH    ((USBSSH_TypeDef *)USBSS_BASE)

#ifdef __cplusplus
}
#endif

#endif // __CH56xUSBSFR_H__

#ifndef __USB_TYPE__
#define __USB_TYPE__

#ifdef __cplusplus
extern "C" {
#endif

/* 连接设备速度定义 */
#define USB_DEV_SPEED_LS    0x01  /* 当前为低速设备 */
#define USB_DEV_SPEED_FS    0x00  /* 当前为全速设备 */
#define USB_DEV_SPEED_HS    0x02

/* USB PID */
#ifndef USB_PID_SETUP
#define USB_PID_NULL     0x00  /* reserved PID */
#define USB_PID_PING     0x04
#define USB_PID_SOF      0x05
#define USB_PID_SETUP    0x0D
#define USB_PID_IN       0x09
#define USB_PID_OUT      0x01
#define USB_PID_ACK      0x02
#define USB_PID_NAK      0x0A
#define USB_PID_STALL    0x0E
#define USB_PID_NYET     0x06
#define USB_PID_DATA0    0x03
#define USB_PID_DATA1    0x0B
#define USB_PID_PRE      0x0C
#define USB_PID_ERR      0x0C
#define USB_PID_SPLIT    0x08
#define USB_PID_DATA0    0x03
#define USB_PID_DATA1    0x0B
#define USB_PID_DATA2    0x07
#define USB_PID_MDATA    0x0F
#endif

/* USB standard device request code */
#ifndef USB_GET_DESCRIPTOR
#define USB_GET_STATUS           0x00
#define USB_CLEAR_FEATURE        0x01
#define USB_SET_FEATURE          0x03
#define USB_SET_ADDRESS          0x05
#define USB_GET_DESCRIPTOR       0x06
#define USB_SET_DESCRIPTOR       0x07
#define USB_GET_CONFIGURATION    0x08
#define USB_SET_CONFIGURATION    0x09
#define USB_GET_INTERFACE        0x0A
#define USB_SET_INTERFACE        0x0B
#define USB_SYNCH_FRAME          0x0C
#endif

/* USB hub class request code */
#ifndef HUB_GET_DESCRIPTOR
#define HUB_GET_STATUS        0x00
#define HUB_CLEAR_FEATURE     0x01
#define HUB_GET_STATE         0x02
#define HUB_SET_FEATURE       0x03
#define HUB_GET_DESCRIPTOR    0x06
#define HUB_SET_DESCRIPTOR    0x07
#endif

/* USB HID class request code */
#ifndef HID_GET_REPORT
#define HID_GET_REPORT      0x01
#define HID_GET_IDLE        0x02
#define HID_GET_PROTOCOL    0x03
#define HID_SET_REPORT      0x09
#define HID_SET_IDLE        0x0A
#define HID_SET_PROTOCOL    0x0B
#endif

/* Bit define for USB request type */
#ifndef USB_REQ_TYP_MASK
#define USB_REQ_TYP_IN          0x80  /* control IN, device to host */
#define USB_REQ_TYP_OUT         0x00  /* control OUT, host to device */
#define USB_REQ_TYP_READ        0x80  /* control read, device to host */
#define USB_REQ_TYP_WRITE       0x00  /* control write, host to device */
#define USB_REQ_TYP_MASK        0x60  /* bit mask of request type */
#define USB_REQ_TYP_STANDARD    0x00
#define USB_REQ_TYP_CLASS       0x20
#define USB_REQ_TYP_VENDOR      0x40
#define USB_REQ_TYP_RESERVED    0x60
#define USB_REQ_RECIP_MASK      0x1F  /* bit mask of request recipient */
#define USB_REQ_RECIP_DEVICE    0x00
#define USB_REQ_RECIP_INTERF    0x01
#define USB_REQ_RECIP_ENDP      0x02
#define USB_REQ_RECIP_OTHER     0x03
#endif

/* USB request type for hub class request */
#ifndef HUB_GET_HUB_DESCRIPTOR
#define HUB_CLEAR_HUB_FEATURE     0x20
#define HUB_CLEAR_PORT_FEATURE    0x23
#define HUB_GET_BUS_STATE         0xA3
#define HUB_GET_HUB_DESCRIPTOR    0xA0
#define HUB_GET_HUB_STATUS        0xA0
#define HUB_GET_PORT_STATUS       0xA3
#define HUB_SET_HUB_DESCRIPTOR    0x20
#define HUB_SET_HUB_FEATURE       0x20
#define HUB_SET_PORT_FEATURE      0x23
#endif

/* Hub class feature selectors */
#ifndef HUB_PORT_RESET
#define HUB_C_HUB_LOCAL_POWER      0
#define HUB_C_HUB_OVER_CURRENT     1
#define HUB_PORT_CONNECTION        0
#define HUB_PORT_ENABLE            1
#define HUB_PORT_SUSPEND           2
#define HUB_PORT_OVER_CURRENT      3
#define HUB_PORT_RESET             4
#define HUB_PORT_POWER             8
#define HUB_PORT_LOW_SPEED         9
#define HUB_C_PORT_CONNECTION      16
#define HUB_C_PORT_ENABLE          17
#define HUB_C_PORT_SUSPEND         18
#define HUB_C_PORT_OVER_CURRENT    19
#define HUB_C_PORT_RESET           20
#endif

/* USB descriptor type */
#ifndef USB_DESCR_TYP_DEVICE
#define USB_DESCR_TYP_DEVICE     0x01
#define USB_DESCR_TYP_CONFIG     0x02
#define USB_DESCR_TYP_STRING     0x03
#define USB_DESCR_TYP_INTERF     0x04
#define USB_DESCR_TYP_ENDP       0x05
#define USB_DESCR_TYP_QUALIF     0x06
#define USB_DESCR_TYP_SPEED      0x07
#define USB_DESCR_TYP_OTG        0x09
#define USB_DESCR_TYP_HID        0x21
#define USB_DESCR_TYP_REPORT     0x22
#define USB_DESCR_TYP_PHYSIC     0x23
#define USB_DESCR_TYP_CS_INTF    0x24
#define USB_DESCR_TYP_CS_ENDP    0x25
#define USB_DESCR_TYP_HUB        0x29
#endif

/* USB device class */
#ifndef USB_DEV_CLASS_HUB
#define USB_DEV_CLASS_RESERVED     0x00
#define USB_DEV_CLASS_AUDIO        0x01
#define USB_DEV_CLASS_COMMUNIC     0x02
#define USB_DEV_CLASS_HID          0x03
#define USB_DEV_CLASS_MONITOR      0x04
#define USB_DEV_CLASS_PHYSIC_IF    0x05
#define USB_DEV_CLASS_POWER        0x06
#define USB_DEV_CLASS_PRINTER      0x07
#define USB_DEV_CLASS_STORAGE      0x08
#define USB_DEV_CLASS_HUB          0x09
#define USB_DEV_CLASS_VEN_SPEC     0xFF
#endif

/* USB endpoint type and attributes */
#ifndef USB_ENDP_TYPE_MASK
#define USB_ENDP_DIR_MASK      0x80
#define USB_ENDP_ADDR_MASK     0x0F
#define USB_ENDP_TYPE_MASK     0x03
#define USB_ENDP_TYPE_CTRL     0x00
#define USB_ENDP_TYPE_ISOCH    0x01
#define USB_ENDP_TYPE_BULK     0x02
#define USB_ENDP_TYPE_INTER    0x03
#endif

#ifndef USB_DEVICE_ADDR
#define USB_DEVICE_ADDR    0x02  /* 默认的USB设备地址 */
#endif
#ifndef DEFAULT_ENDP0_SIZE
#define DEFAULT_ENDP0_SIZE    8  /* default maximum packet size for endpoint 0 */
#endif
#ifndef MAX_PACKET_SIZE
#define MAX_PACKET_SIZE    512  /* maximum packet size */
#endif
#ifndef USB_BO_CBW_SIZE
#define USB_BO_CBW_SIZE    0x1F  /* 命令块CBW的总长度 */
#define USB_BO_CSW_SIZE    0x0D  /* 命令状态块CSW的总长度 */
#endif
#ifndef USB_BO_CBW_SIG0
#define USB_BO_CBW_SIG0    0x55  /* 命令块CBW识别标志'USBC' */
#define USB_BO_CBW_SIG1    0x53
#define USB_BO_CBW_SIG2    0x42
#define USB_BO_CBW_SIG3    0x43
#define USB_BO_CSW_SIG0    0x55  /* 命令状态块CSW识别标志'USBS' */
#define USB_BO_CSW_SIG1    0x53
#define USB_BO_CSW_SIG2    0x42
#define USB_BO_CSW_SIG3    0x53
#endif

#ifndef USB_SETUP_REQ
typedef struct __PACKED _USB_SETUP_REQ
{
	uint8_t  bRequestType;
	uint8_t  bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
} USB_SETUP_REQ, *PUSB_SETUP_REQ;
#endif

#ifndef USB_DEV_DESCR
typedef struct __PACKED _USB_DEVICE_DESCR
{
	uint8_t  bLength;
	uint8_t  bDescriptorType;
	uint16_t bcdUSB;
	uint8_t  bDeviceClass;
	uint8_t  bDeviceSubClass;
	uint8_t  bDeviceProtocol;
	uint8_t  bMaxPacketSize0;
	uint16_t idVendor;
	uint16_t idProduct;
	uint16_t bcdDevice;
	uint8_t  iManufacturer;
	uint8_t  iProduct;
	uint8_t  iSerialNumber;
	uint8_t  bNumConfigurations;
} USB_DEV_DESCR, *PUSB_DEV_DESCR;
#endif

#ifndef USB_CFG_DESCR
typedef struct __PACKED _USB_CONFIG_DESCR
{
	uint8_t  bLength;
	uint8_t  bDescriptorType;
	uint16_t wTotalLength;
	uint8_t  bNumInterfaces;
	uint8_t  bConfigurationValue;
	uint8_t  iConfiguration;
	uint8_t  bmAttributes;
	uint8_t  MaxPower;
} USB_CFG_DESCR, *PUSB_CFG_DESCR;
#endif

#ifndef USB_ITF_DESCR
typedef struct __PACKED _USB_INTERF_DESCR
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bInterfaceNumber;
	uint8_t bAlternateSetting;
	uint8_t bNumEndpoints;
	uint8_t bInterfaceClass;
	uint8_t bInterfaceSubClass;
	uint8_t bInterfaceProtocol;
	uint8_t iInterface;
} USB_ITF_DESCR, *PUSB_ITF_DESCR;
#endif

#ifndef USB_ENDP_DESCR
typedef struct __PACKED _USB_ENDPOINT_DESCR
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bEndpointAddress;
	uint8_t bmAttributes;
	uint8_t wMaxPacketSizeL;
	uint8_t wMaxPacketSizeH;
	uint8_t bInterval;
} USB_ENDP_DESCR, *PUSB_ENDP_DESCR;
#endif

#ifndef USB_CFG_DESCR_LONG
typedef struct __PACKED _USB_CONFIG_DESCR_LONG
{
	USB_CFG_DESCR  cfg_descr;
	USB_ITF_DESCR  itf_descr;
	USB_ENDP_DESCR endp_descr[2];
} USB_CFG_DESCR_LONG, *PUSB_CFG_DESCR_LONG;
#endif

#ifndef USB_HUB_DESCR
typedef struct __PACKED _USB_HUB_DESCR
{
	uint8_t bDescLength;
	uint8_t bDescriptorType;
	uint8_t bNbrPorts;
	uint8_t wHubCharacteristicsL;
	uint8_t wHubCharacteristicsH;
	uint8_t bPwrOn2PwrGood;
	uint8_t bHubContrCurrent;
	uint8_t DeviceRemovable;
	uint8_t PortPwrCtrlMask;
} USB_HUB_DESCR, *PUSB_HUB_DESCR;
#endif

#ifndef USB_HID_DESCR
typedef struct __PACKED _USB_HID_DESCR
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bcdHIDL;
	uint8_t bcdHIDH;
	uint8_t bCountryCode;
	uint8_t bNumDescriptors;
	uint8_t bDescriptorTypeX;
	uint8_t wDescriptorLengthL;
	uint8_t wDescriptorLengthH;
} USB_HID_DESCR, *PUSB_HID_DESCR;
#endif

#ifndef USB_DEV_QUAL_DESCR
typedef struct __PACKED _USB_DEVICE_QUALIFIER_DESCRIPTOR
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bcdUSBL;
	uint8_t bcdUSBH;
	uint8_t bDeviceClass;
	uint8_t bDeviceSubClass;
	uint8_t bDeviceProtocol;
	uint8_t bMaxPacketSize0;
	uint8_t bNumConfigurations;
	uint8_t bReserved;
} USB_DEV_QUAL_DESCR, *PUSB_DEV_QUAL_DESCR;
#endif

#ifndef USB_CFG_PWR_DESCR
typedef struct __PACKED _USB_CONFIGURATION_POWER_DESCRIPTOR
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t SelfPowerConsumedD0[3];
	uint8_t bPowerSummaryId;
	uint8_t bBusPowerSavingD1;
	uint8_t bSelfPowerSavingD1;
	uint8_t bBusPowerSavingD2;
	uint8_t bSelfPowerSavingD2;
	uint8_t bBusPowerSavingD3;
	uint8_t bSelfPowerSavingD3;
	uint8_t TransitionTimeFromD1L;
	uint8_t TransitionTimeFromD1H;
	uint8_t TransitionTimeFromD2L;
	uint8_t TransitionTimeFromD2H;
	uint8_t TransitionTimeFromD3L;
	uint8_t TransitionTimeFromD3H;
} USB_CFG_PWR_DESCR, *PUSB_CFG_PWR_DESCR;
#endif

#ifndef USB_ITF_PWR_DESCR
typedef struct __PACKED _USB_INTERFACE_POWER_DESCRIPTOR
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bmCapabilitiesFlags;
	uint8_t bBusPowerSavingD1;
	uint8_t bSelfPowerSavingD1;
	uint8_t bBusPowerSavingD2;
	uint8_t bSelfPowerSavingD2;
	uint8_t bBusPowerSavingD3;
	uint8_t bSelfPowerSavingD3;
	uint8_t TransitionTimeFromD1L;
	uint8_t TransitionTimeFromD1H;
	uint8_t TransitionTimeFromD2L;
	uint8_t TransitionTimeFromD2H;
	uint8_t TransitionTimeFromD3L;
	uint8_t TransitionTimeFromD3H;
} USB_ITF_PWR_DESCR, *PUSB_ITF_PWR_DESCR;
#endif

#define USB_BO_CBW_SIG    0x43425355  /* 命令块CBW识别标志'USBC' */
#define USB_BO_CSW_SIG    0x53425355  /* 命令状态块CSW识别标志'USBS' */

typedef struct __PACKED _UDISK_BOC_CBW
{
	uint32_t mCBW_Sig;
	uint32_t mCBW_Tag;
	uint32_t mCBW_DataLen; /* 输入: 数据传输长度 */
	uint8_t  mCBW_Flag;    /* 输入: 传输方向等标志 */
	uint8_t  mCBW_LUN;
	uint8_t  mCBW_CB_Len;     /* 输入: 命令块的长度,有效值是1到16 */
	uint8_t  mCBW_CB_Buf[16]; /* 输入: 命令块,该缓冲区最多为16个字节 */
} UDISK_BOC_CBW, *PUDISK_BOC_CBW;

typedef struct __PACKED _UDISK_BOC_CSW
{
	uint32_t mCSW_Sig;
	uint32_t mCSW_Tag;
	uint32_t mCSW_Residue; /* 返回: 剩余数据长度 */
	uint8_t  mCSW_Status;  /* 返回: 命令执行结果状态 */
} UDISK_BOC_CSW, *PUDISK_BOC_CSW;

#ifdef __cplusplus
}
#endif

#endif // __USB_TYPE__

#ifndef __CH56xSDSSFR_H__
#define __CH56xSDSSFR_H__

#ifdef __cplusplus
extern "C" {
#endif

#define SERDES_BASE    (0x4000B000)

typedef struct
{
	vuint32_t SDS_CTRL;     // 0x4000B000
	vuint32_t SDS_INT_EN;   // 0x4000B004
	vuint32_t SDS_STATUS;   // 0x4000B008
	vuint32_t SDS_RTX_CTRL; // 0x4000B00C
	vuint32_t SDS_RX_LEN0;  // 0x4000B010
	vuint32_t SDS_DATA0;    // 0x4000B014
	vuint32_t SDS_DMA0;     // 0x4000B018
	vuint32_t SDS_RX_LEN1;  // 0x4000B01C
	vuint32_t SDS_DATA1;    // 0x4000B020
	vuint32_t SDS_DMA1;     // 0x4000B024
} SDS_TypeDef;

#define SDS    ((SDS_TypeDef *)SERDES_BASE)

#ifdef __cplusplus
}
#endif

#endif // __CH56xSDSSFR_H__

#ifndef __CH56xETHSFR_H__
#define __CH56xETHSFR_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ETH_BASE        (0x4000C000)

/**
 * @brief  ETH MAC Init structure definition
 * @note   The user should not configure all the ETH_InitTypeDef structure's fields.
 *   By calling the ETH_StructInit function the structure抯 fields are set to their default values.
 *   Only the parameters that will be set to a non-default value should be configured.
 */

#define PHY_10M_EN      0
#define ETHMAC_Mode     0x00  //01： 100M    00：10M  10:1000M
#define TB_NUM          0x08

#define DMA_TPS_Mask    ((uint32_t)0x00700000)
#define DMA_RPS_Mask    ((uint32_t)0x000E0000)

typedef struct
{
	/**
	 * @brief / * MAC
	 */
	uint32_t ETH_AutoNegotiation; /*!< Selects or not the AutoNegotiation mode for the external PHY
                                       The AutoNegotiation allows an automatic setting of the Speed (10/100Mbps)
                                       and the mode (half/full-duplex).
                                       This parameter can be a value of @ref ETH_AutoNegotiation */

	uint32_t ETH_Watchdog; /*!< Selects or not the Watchdog timer
                                When enabled, the MAC allows no more then 2048 bytes to be received.
                                When disabled, the MAC can receive up to 16384 bytes.
                                This parameter can be a value of @ref ETH_watchdog */

	uint32_t ETH_Jabber; /*!< Selects or not Jabber timer
                              When enabled, the MAC allows no more then 2048 bytes to be sent.
                              When disabled, the MAC can send up to 16384 bytes.
                              This parameter can be a value of @ref ETH_Jabber */

	uint32_t ETH_InterFrameGap; /*!< Selects the minimum IFG between frames during transmission
                                     This parameter can be a value of @ref ETH_Inter_Frame_Gap */

	uint32_t ETH_CarrierSense; /*!< Selects or not the Carrier Sense
                                    This parameter can be a value of @ref ETH_Carrier_Sense */

	uint32_t ETH_Speed; /*!< Sets the Ethernet speed: 10/100 Mbps
                             This parameter can be a value of @ref ETH_Speed */

	uint32_t ETH_ReceiveOwn; /*!< Selects or not the ReceiveOwn
                                  ReceiveOwn allows the reception of frames when the TX_EN signal is asserted
                                  in Half-Duplex mode
                                  This parameter can be a value of @ref ETH_Receive_Own */

	uint32_t ETH_LoopbackMode; /*!< Selects or not the internal MAC MII Loopback mode
                                    This parameter can be a value of @ref ETH_Loop_Back_Mode */

	uint32_t ETH_Mode; /*!< Selects the MAC duplex mode: Half-Duplex or Full-Duplex mode
                            This parameter can be a value of @ref ETH_Duplex_Mode */

	uint32_t ETH_ChecksumOffload; /*!< Selects or not the IPv4 checksum checking for received frame payloads' TCP/UDP/ICMP headers.
                                       This parameter can be a value of @ref ETH_Checksum_Offload */

	uint32_t ETH_RetryTransmission; /*!< Selects or not the MAC attempt retries transmission, based on the settings of BL,
                                         when a colision occurs (Half-Duplex mode)
                                         This parameter can be a value of @ref ETH_Retry_Transmission */

	uint32_t ETH_AutomaticPadCRCStrip; /*!< Selects or not the Automatic MAC Pad/CRC Stripping
                                            This parameter can be a value of @ref ETH_Automatic_Pad_CRC_Strip */

	uint32_t ETH_BackOffLimit; /*!< Selects the BackOff limit value
                                    This parameter can be a value of @ref ETH_Back_Off_Limit */

	uint32_t ETH_DeferralCheck; /*!< Selects or not the deferral check function (Half-Duplex mode)
                                     This parameter can be a value of @ref ETH_Deferral_Check */

	uint32_t ETH_ReceiveAll; /*!< Selects or not all frames reception by the MAC (No fitering)
                                  This parameter can be a value of @ref ETH_Receive_All */

	uint32_t ETH_SourceAddrFilter; /*!< Selects the Source Address Filter mode
                                        This parameter can be a value of @ref ETH_Source_Addr_Filter */

	uint32_t ETH_PassControlFrames; /*!< Sets the forwarding mode of the control frames (including unicast and multicast PAUSE frames)
                                         This parameter can be a value of @ref ETH_Pass_Control_Frames */

	uint32_t ETH_BroadcastFramesReception; /*!< Selects or not the reception of Broadcast Frames
                                                This parameter can be a value of @ref ETH_Broadcast_Frames_Reception */

	uint32_t ETH_DestinationAddrFilter; /*!< Sets the destination filter mode for both unicast and multicast frames
                                             This parameter can be a value of @ref ETH_Destination_Addr_Filter */

	uint32_t ETH_PromiscuousMode; /*!< Selects or not the Promiscuous Mode
                                       This parameter can be a value of @ref ETH_Promiscuous_Mode */

	uint32_t ETH_MulticastFramesFilter; /*!< Selects the Multicast Frames filter mode: None/HashTableFilter/PerfectFilter/PerfectHashTableFilter
                                             This parameter can be a value of @ref ETH_Multicast_Frames_Filter */

	uint32_t ETH_UnicastFramesFilter; /*!< Selects the Unicast Frames filter mode: HashTableFilter/PerfectFilter/PerfectHashTableFilter
                                           This parameter can be a value of @ref ETH_Unicast_Frames_Filter */

	uint32_t ETH_HashTableHigh; /*!< This field holds the higher 32 bits of Hash table.  */

	uint32_t ETH_HashTableLow; /*!< This field holds the lower 32 bits of Hash table.  */

	uint32_t ETH_PauseTime; /*!< This field holds the value to be used in the Pause Time field in the
                                 transmit control frame */

	uint32_t ETH_ZeroQuantaPause; /*!< Selects or not the automatic generation of Zero-Quanta Pause Control frames
                                       This parameter can be a value of @ref ETH_Zero_Quanta_Pause */

	uint32_t ETH_PauseLowThreshold; /*!< This field configures the threshold of the PAUSE to be checked for
                                         automatic retransmission of PAUSE Frame
                                         This parameter can be a value of @ref ETH_Pause_Low_Threshold */

	uint32_t ETH_UnicastPauseFrameDetect; /*!< Selects or not the MAC detection of the Pause frames (with MAC Address0
                                               unicast address and unique multicast address)
                                               This parameter can be a value of @ref ETH_Unicast_Pause_Frame_Detect */

	uint32_t ETH_ReceiveFlowControl; /*!< Enables or disables the MAC to decode the received Pause frame and
                                          disable its transmitter for a specified time (Pause Time)
                                          This parameter can be a value of @ref ETH_Receive_Flow_Control */

	uint32_t ETH_TransmitFlowControl; /*!< Enables or disables the MAC to transmit Pause frames (Full-Duplex mode)
                                           or the MAC back-pressure operation (Half-Duplex mode)
                                           This parameter can be a value of @ref ETH_Transmit_Flow_Control */

	uint32_t ETH_VLANTagComparison; /*!< Selects the 12-bit VLAN identifier or the complete 16-bit VLAN tag for
                                         comparison and filtering
                                         This parameter can be a value of @ref ETH_VLAN_Tag_Comparison */

	uint32_t ETH_VLANTagIdentifier; /*!< Holds the VLAN tag identifier for receive frames */

	/**
	 * @brief / * DMA
	 */

	uint32_t ETH_DropTCPIPChecksumErrorFrame; /*!< Selects or not the Dropping of TCP/IP Checksum Error Frames
                                                   This parameter can be a value of @ref ETH_Drop_TCP_IP_Checksum_Error_Frame */

	uint32_t ETH_ReceiveStoreForward; /*!< Enables or disables the Receive store and forward mode
                                           This parameter can be a value of @ref ETH_Receive_Store_Forward */

	uint32_t ETH_FlushReceivedFrame; /*!< Enables or disables the flushing of received frames
                                          This parameter can be a value of @ref ETH_Flush_Received_Frame */

	uint32_t ETH_TransmitStoreForward; /*!< Enables or disables Transmit store and forward mode
                                            This parameter can be a value of @ref ETH_Transmit_Store_Forward */

	uint32_t ETH_TransmitThresholdControl; /*!< Selects or not the Transmit Threshold Control
                                                This parameter can be a value of @ref ETH_Transmit_Threshold_Control */

	uint32_t ETH_ForwardErrorFrames; /*!< Selects or not the forward to the DMA of erroneous frames
                                          This parameter can be a value of @ref ETH_Forward_Error_Frames */

	uint32_t ETH_ForwardUndersizedGoodFrames; /*!< Enables or disables the Rx FIFO to forward Undersized frames (frames with no Error
                                                   and length less than 64 bytes) including pad-bytes and CRC)
                                                   This parameter can be a value of @ref ETH_Forward_Undersized_Good_Frames */

	uint32_t ETH_ReceiveThresholdControl; /*!< Selects the threshold level of the Receive FIFO
                                               This parameter can be a value of @ref ETH_Receive_Threshold_Control */

	uint32_t ETH_SecondFrameOperate; /*!< Selects or not the Operate on second frame mode, which allows the DMA to process a second
                                          frame of Transmit data even before obtaining the status for the first frame.
                                          This parameter can be a value of @ref ETH_Second_Frame_Operate */

	uint32_t ETH_AddressAlignedBeats; /*!< Enables or disables the Address Aligned Beats
                                           This parameter can be a value of @ref ETH_Address_Aligned_Beats */

	uint32_t ETH_FixedBurst; /*!< Enables or disables the AHB Master interface fixed burst transfers
                                  This parameter can be a value of @ref ETH_Fixed_Burst */

	uint32_t ETH_RxDMABurstLength; /*!< Indicates the maximum number of beats to be transferred in one Rx DMA transaction
                                        This parameter can be a value of @ref ETH_Rx_DMA_Burst_Length */

	uint32_t ETH_TxDMABurstLength; /*!< Indicates sthe maximum number of beats to be transferred in one Tx DMA transaction
                                        This parameter can be a value of @ref ETH_Tx_DMA_Burst_Length */

	uint32_t ETH_DescriptorSkipLength; /*!< Specifies the number of word to skip between two unchained descriptors (Ring mode) */

	uint32_t ETH_DMAArbitration; /*!< Selects the DMA Tx/Rx arbitration
                                      This parameter can be a value of @ref ETH_DMA_Arbitration */
} ETH_InitTypeDef;

/**--------------------------------------------------------------------------**/
/**
 * @brief                           DMA descriptors types
 */
/**--------------------------------------------------------------------------**/

/**
 * @brief  ETH DMA Desciptors data structure definition
 */
typedef struct
{
	uint32_t Status;              /*!< Status */
	uint32_t ControlBufferSize;   /*!< Control and Buffer1, Buffer2 lengths */
	uint32_t Buffer1Addr;         /*!< Buffer1 address pointer */
	uint32_t Buffer2NextDescAddr; /*!< Buffer2 or next descriptor address pointer */
} ETH_DMADESCTypeDef;

/**
 * @}
 */

/** @defgroup ETH_Exported_Constants
 * @{
 */

/**
 * @brief Uncomment the line below if you want to use user defined Delay function
 *        (for precise timing), otherwise default _eth_delay_ function defined within
 *        this driver is used (less precise timing).
 */
/* #define USE_Delay */

#ifdef USE_Delay
#include "main.h"
#define _eth_delay_    Delay  /*!< User can provide more timing precise _eth_delay_ function */
#else
#define _eth_delay_    ETH_Delay  /*!< Default _eth_delay_ function with less precise timing */
#endif

/**--------------------------------------------------------------------------**/
/**
 * @brief                          ETH Frames defines
 */
/**--------------------------------------------------------------------------**/

/** @defgroup ENET_Buffers_setting
 * @{
 */
#define ETH_MAX_PACKET_SIZE                     1520  /*!< ETH_HEADER + ETH_EXTRA + MAX_ETH_PAYLOAD + ETH_CRC */
#define ETH_HEADER                              14    /*!< 6 byte Dest addr, 6 byte Src addr, 2 byte length/type */
#define ETH_CRC                                 4     /*!< Ethernet CRC */
#define ETH_EXTRA                               2     /*!< Extra bytes in some cases */
#define VLAN_TAG                                4     /*!< optional 802.1q VLAN Tag */
#define MIN_ETH_PAYLOAD                         46    /*!< Minimum Ethernet payload size */
#define MAX_ETH_PAYLOAD                         1500  /*!< Maximum Ethernet payload size */
#define JUMBO_FRAME_PAYLOAD                     9000  /*!< Jumbo frame payload size */

/**--------------------------------------------------------------------------**/
/**
 * @brief                 Ethernet DMA descriptors registers bits definition
 */
/**--------------------------------------------------------------------------**/

/**
@code
   DMA Tx Desciptor
  -----------------------------------------------------------------------------------------------
  TDES0 | OWN(31) | CTRL[30:26] | Reserved[25:24] | CTRL[23:20] | Reserved[19:17] | Status[16:0] |
  -----------------------------------------------------------------------------------------------
  TDES1 | Reserved[31:29] | Buffer2 ByteCount[28:16] | Reserved[15:13] | Buffer1 ByteCount[12:0] |
  -----------------------------------------------------------------------------------------------
  TDES2 |                         Buffer1 Address [31:0]                                         |
  -----------------------------------------------------------------------------------------------
  TDES3 |                   Buffer2 Address [31:0] / Next Desciptor Address [31:0]               |
  -----------------------------------------------------------------------------------------------
@endcode
*/

/**
 * @brief  Bit definition of TDES0 register: DMA Tx descriptor status register
 */
#define ETH_DMATxDesc_OWN                       ((uint32_t)0x80000000) /*!< OWN bit: descriptor is owned by DMA engine */
#define ETH_DMATxDesc_IC                        ((uint32_t)0x40000000) /*!< Interrupt on Completion */
#define ETH_DMATxDesc_LS                        ((uint32_t)0x20000000) /*!< Last Segment */
#define ETH_DMATxDesc_FS                        ((uint32_t)0x10000000) /*!< First Segment */
#define ETH_DMATxDesc_DC                        ((uint32_t)0x08000000) /*!< Disable CRC */
#define ETH_DMATxDesc_DP                        ((uint32_t)0x04000000) /*!< Disable Padding */
#define ETH_DMATxDesc_TTSE                      ((uint32_t)0x02000000) /*!< Transmit Time Stamp Enable */
#define ETH_DMATxDesc_CIC                       ((uint32_t)0x00C00000) /*!< Checksum Insertion Control: 4 cases */
#define ETH_DMATxDesc_CIC_ByPass                ((uint32_t)0x00000000) /*!< Do Nothing: Checksum Engine is bypassed */
#define ETH_DMATxDesc_CIC_IPV4Header            ((uint32_t)0x00400000) /*!< IPV4 header Checksum Insertion */
#define ETH_DMATxDesc_CIC_TCPUDPICMP_Segment    ((uint32_t)0x00800000) /*!< TCP/UDP/ICMP Checksum Insertion calculated over segment only */
#define ETH_DMATxDesc_CIC_TCPUDPICMP_Full       ((uint32_t)0x00C00000) /*!< TCP/UDP/ICMP Checksum Insertion fully calculated */
#define ETH_DMATxDesc_TER                       ((uint32_t)0x00200000) /*!< Transmit End of Ring */
#define ETH_DMATxDesc_TCH                       ((uint32_t)0x00100000) /*!< Second Address Chained */
#define ETH_DMATxDesc_TTSS                      ((uint32_t)0x00020000) /*!< Tx Time Stamp Status */
#define ETH_DMATxDesc_IHE                       ((uint32_t)0x00010000) /*!< IP Header Error */
#define ETH_DMATxDesc_ES                        ((uint32_t)0x00008000) /*!< Error summary: OR of the following bits: UE || ED || EC || LCO || NC || LCA || FF || JT */
#define ETH_DMATxDesc_JT                        ((uint32_t)0x00004000) /*!< Jabber Timeout */
#define ETH_DMATxDesc_FF                        ((uint32_t)0x00002000) /*!< Frame Flushed: DMA/MTL flushed the frame due */

#ifdef __cplusplus
}
#endif

#endif // __CH56xETHSFR_H__
