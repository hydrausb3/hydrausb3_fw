/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_bsp.h
* Author             : bvernoux
* Version            : V1.0
* Date               : 2022/07/30
* Description        : This file contains all the functions prototypes for
*                      Board Support Package(BSP) for HydraUSB3 Dev Board
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#ifndef __CH56X_HYDRAUSB3_H__
#define __CH56X_HYDRAUSB3_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "CH56xSFR.h"

/* Macros for ULED / UBTN */
/* ULED PB22 */
#define ULED_PIN (GPIO_Pin_22)
#define ULED_ON() (GPIOB_SetBits(GPIO_Pin_22))
#define ULED_OFF() (GPIOB_ResetBits(GPIO_Pin_22))
/* UBTN PB23 */
#define UBTN_PIN (GPIO_Pin_23)

/* Used by hydrausb3_sync2boards() */
#define HYDRAUSB3_SYNCHRO_TIMEOUT (12000000) // About 700ms at 120MHz with -O3 / -Os

/* Definition of GPIO PORTA/PORTB Flag used in e_HydraUSB3_PortPinType */
#define HYDRAUSB3_PORTA_FLAG (0x00000000)
#define HYDRAUSB3_PORTB_FLAG (0x80000000)
#define HYDRAUSB3_PINBIT_MASK (0x7FFFFFFF)

/* HydraUSB3 (CH569W) Port Pin definition */
typedef enum
{
	PA0  = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_0 ),
	PA1  = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_1 ),
	PA2  = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_2 ),
	PA3  = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_3 ),
	PA4  = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_4 ),
	PA5  = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_5 ),
	PA6  = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_6 ),
	/*
	// Reserved for UART1
	PA7  = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_7 ),
	PA8  = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_8 ),
	*/
	PA9  = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_9 ),
	PA10 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_10),
	PA11 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_11),
	PA12 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_12),
	PA13 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_13),
	PA14 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_14),
	PA15 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_15),
	PA16 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_16),
	PA17 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_17),
	PA18 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_18),
	PA19 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_19),
	PA20 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_20),
	PA21 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_21),
	PA22 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_22),
	PA23 = (HYDRAUSB3_PORTA_FLAG | GPIO_Pin_23),

	PB0  = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_0 ),
	PB1  = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_1 ),
	PB2  = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_2 ),
	PB3  = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_3 ),
	PB4  = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_4 ),
	PB5  = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_5 ),
	PB6  = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_6 ),
	PB7  = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_7 ),
	PB8  = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_8 ),
	PB9  = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_9 ),
	PB10 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_10),
	PB11 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_11),
	PB12 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_12),
	PB13 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_13),
	PB14 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_14),
	PB15 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_15),
	PB16 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_16),
	PB17 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_17),
	PB18 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_18),
	PB19 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_19),
	PB20 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_20),
	PB21 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_21),
	PB22 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_22),
	PB23 = (HYDRAUSB3_PORTB_FLAG | GPIO_Pin_23)
} e_HydraUSB3_PortPinType;

/**
  * @brief  HydraUSB3 Dual board type
  */
typedef enum
{
	HYDRAUSB3_HOST = 0, /* HOST = Primary/main board */
	HYDRAUSB3_DEVICE = 1, /* DEVICE = Secondary board */
} e_HYDRAUSB3_TypeDef;

/*******************************************************************************
 * @fn     hydrausb3_gpio_init
 *
 * @brief  Initializes HydraUSB3 board (mainly GPIO)
 *
 * @return None
 **/
void hydrausb3_gpio_init(void);

/*******************************************************************************
 * @fn     hydrausb3_gpio_cfg
 *
 * @brief  Initializes GPIO Port Pin mode
 *
 * @param  gpioPortPin - GPIO to configure
 *         mode - GPIO mode
 *
 * @return None
 **/
void hydrausb3_gpio_cfg(e_HydraUSB3_PortPinType gpioPortPin, GPIOModeTypeDef mode);

/*******************************************************************************
 * @fn     hydrausb3_gpio_read
 *
 * @brief  Read GPIO PortPin state
 *         Precondition: call to hydrausb3_gpio_cfg()
 *
 * @param  gpioPortPin - GPIO state to read
 *
 * @return 0 (pin low), !0 (pin high)
 **/
int hydrausb3_gpio_read(e_HydraUSB3_PortPinType gpioPortPin);

/*******************************************************************************
 * @fn     hydrausb3_gpio_set
 *
 * @brief  Set GPIO PortPin state
 *         Precondition: call to hydrausb3_gpio_cfg()
 *
 * @param  gpioPortPin - GPIO state to set to '1'
 *
 * @return None
 **/
void hydrausb3_gpio_set(e_HydraUSB3_PortPinType gpioPortPin);

/*******************************************************************************
 * @fn     hydrausb3_gpio_clr
 *
 * @brief  Read GPIO PortPin state
 *         Precondition: call to hydrausb3_gpio_cfg()
 *
 * @param  gpioPortPin - GPIO state to clear/reset to '0'
 *
 * @return None
 **/
void hydrausb3_gpio_clr(e_HydraUSB3_PortPinType gpioPortPin);

/*******************************************************************************
 * @fn     hydrausb3_ubtn
 *
 * @brief  Read HydraUSB3 state of button UBTN
 *         Precondition: call to hydrausb3_init()
 *
 * @return 0 (pin low), !0 (pin high)
 **/
int hydrausb3_ubtn(void);

/*******************************************************************************
 * @fn     hydrausb3_is_PB24_ON
 *
 * @brief  Read HydraUSB3 state of PB24 Switch
 *         Precondition: call to hydrausb3_init()
 *
 * @return 0 (PB24 Switch OFF), 1 (PB24 Switch ON)
 **/
int hydrausb3_pb24(void);

/*******************************************************************************
 * @fn     hydrausb3_sync2boards
 *
 * @brief  Synchronize 2x HydraUSB3 boards connected together(one on top of another)
 *         Precondition:
 *         - HOST / Main board shall have PB24 not populated
 *         - DEVICE / Secondary board shall have PB24 populate (with Short/Jumper)
 *
 * @param  gpio1 - 1st GPIO to be used for synchronization
 *         gpio2 - 2nd GPIO to be used for synchronization
 *         type - Type of Board
 *              - HOST / Main board shall have PB24 not populated
 *              - DEVICE / Secondary board shall have PB24 populate (with Short/Jumper)
 *
 * @return !=0 if success or 0 in case of error(timeout)
 **/
int hydrausb3_sync2boards(e_HydraUSB3_PortPinType gpio1, e_HydraUSB3_PortPinType gpio2, e_HYDRAUSB3_TypeDef type);

#ifdef __cplusplus
}
#endif

#endif  // __CH56X_HYDRAUSB3_H__	
