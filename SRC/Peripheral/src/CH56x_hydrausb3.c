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
#include "CH56x_common.h"
#include "CH56x_hydrausb3.h"

/*******************************************************************************
 * @fn     hydrausb3_gpio_init
 *
 * @brief  Initializes HydraUSB3 board (mainly GPIO)
 *
 * @return None
 **/
void hydrausb3_gpio_init(void)
{
	#define GPIOA_Pins (GPIO_Pin_All & ~(GPIO_Pin_7 | GPIO_Pin_8) ) /* All GPIOA except Pin7 & Pin8 used by UART1 */

	/* Configure all GPIO to safe state Input Floating */
	GPIOA_ModeCfg(GPIOA_Pins, GPIO_ModeIN_Floating);
	GPIOB_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_Floating);

	/* Configure ULED(PB22) */
	GPIOB_ResetBits(ULED_PIN);
	GPIOB_ModeCfg(ULED_PIN, GPIO_Highspeed_PP_8mA); // Output

	/* Configure UBTN(PB23) Input Floating */
	GPIOB_ResetBits(UBTN_PIN);
	GPIOB_ModeCfg(UBTN_PIN, GPIO_ModeIN_Floating); // Input floating

	/* Configure PB24 Input Pull-up (0=ON, 1=OFF) */
	GPIOB_ResetBits(GPIO_Pin_24);
	GPIOB_ModeCfg(GPIO_Pin_24, GPIO_ModeIN_PU_NSMT); // Pull-up input
}

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
void hydrausb3_gpio_cfg(e_HydraUSB3_PortPinType gpioPortPin, GPIOModeTypeDef mode)
{
	uint32_t pinBit = (gpioPortPin&HYDRAUSB3_PINBIT_MASK);
	/* Read Port Pin */
	if((gpioPortPin & HYDRAUSB3_PORTB_FLAG) == 0) // PA
	{
		GPIOA_ModeCfg(pinBit, mode);
	}
	else // PB
	{
		GPIOB_ModeCfg(pinBit, mode);
	}
}

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
int hydrausb3_gpio_read(e_HydraUSB3_PortPinType gpioPortPin)
{
	uint32_t pinBit = (gpioPortPin&HYDRAUSB3_PINBIT_MASK);
	/* Read Port Pin */
	if((gpioPortPin & HYDRAUSB3_PORTB_FLAG) == 0) // PA
	{
		return GPIOA_ReadPortPin(pinBit);
	}
	else // PB
	{
		return GPIOB_ReadPortPin(pinBit);
	}
}

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
void hydrausb3_gpio_set(e_HydraUSB3_PortPinType gpioPortPin)
{
	uint32_t pinBit = (gpioPortPin&HYDRAUSB3_PINBIT_MASK);
	/* Read Port Pin */
	if((gpioPortPin & HYDRAUSB3_PORTB_FLAG) == 0) // PA
	{
		R32_PA_OUT |= pinBit;
	}
	else // PB
	{
		R32_PB_OUT |= pinBit;
	}
}

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
void hydrausb3_gpio_clr(e_HydraUSB3_PortPinType gpioPortPin)
{
	uint32_t pinBit = (gpioPortPin&HYDRAUSB3_PINBIT_MASK);
	/* Read Port Pin */
	if((gpioPortPin & HYDRAUSB3_PORTB_FLAG) == 0) // PA
	{
		R32_PA_CLR |= pinBit;
	}
	else // PB
	{
		R32_PB_CLR |= pinBit;
	}
}

/*******************************************************************************
 * @fn     hydrausb3_ubtn
 *
 * @brief  Read HydraUSB3 state of button UBTN
 *         Precondition: call to hydrausb3_init()
 *
 * @return  0 (pin low), !0 (pin high)
 **/
int hydrausb3_ubtn(void)
{
	return GPIOB_ReadPortPin(UBTN_PIN);
}

/*******************************************************************************
 * @fn     hydrausb3_is_PB24_ON
 *
 * @brief  Read HydraUSB3 state of PB24 Switch
 *         Precondition: call to hydrausb3_init()
 *
 * @return 0 (PB24 Switch OFF), 1 (PB24 Switch ON)
 **/
int hydrausb3_pb24(void)
{
	if(GPIOB_ReadPortPin(GPIO_Pin_24) == 0)
	{
		return 1; /* Logic Reversed with PullUp */
	}
	else
	{
		return 0; /* Logic Reversed with PullUp */
	}
}

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
int hydrausb3_sync2boards(e_HydraUSB3_PortPinType gpio1, e_HydraUSB3_PortPinType gpio2, e_HYDRAUSB3_TypeDef type)
{
	int i;
	/******************************************/
	/* Start Synchronization between 2 Boards */
	/* SYNC_GPIO1 & SYNC_GPIO2 signals        */
	/******************************************/
	if(hydrausb3_pb24() == 0)
	{
		i = 0;
		/* Configure gpio1 as input pull-down */
		hydrausb3_gpio_clr(gpio1);
		hydrausb3_gpio_cfg(gpio1, GPIO_ModeIN_PD_SMT); // Input
		/* Configure gpio2 as output */
		hydrausb3_gpio_clr(gpio2);
		hydrausb3_gpio_cfg(gpio2, GPIO_Highspeed_PP_8mA); // Output
		hydrausb3_gpio_set(gpio2); // Set state to "1"
		/* Wait Device Synchronization signal "1" (ACK) on gpio1 */
		while(1)
		{
			if(i++ > HYDRAUSB3_SYNCHRO_TIMEOUT)
			{
				break;
			}
			if(hydrausb3_gpio_read(gpio1) != 0)
			{
				break;
			}
		}
	}
	else
	{
		i = 0;
		/* Configure gpio2 as input pull-down */
		hydrausb3_gpio_clr(gpio2);
		hydrausb3_gpio_cfg(gpio2, GPIO_ModeIN_PD_SMT); // Input
		/* Configure gpio1 as output */
		hydrausb3_gpio_clr(gpio1);
		hydrausb3_gpio_cfg(gpio1, GPIO_Highspeed_PP_8mA); // Output
		hydrausb3_gpio_set(gpio1); // Set state to "1"
		/* Wait Device Synchro signal "1" (ACK) on gpio2 */
		while(1)
		{
			if(i++ > HYDRAUSB3_SYNCHRO_TIMEOUT)
			{
				break;
			}
			if(hydrausb3_gpio_read(gpio2) != 0)
			{
				break;
			}
		}
	}
	/* Configure to safe state */
	hydrausb3_gpio_cfg(gpio1, GPIO_ModeIN_Floating); // Input
	hydrausb3_gpio_cfg(gpio2, GPIO_ModeIN_Floating); // Input

	if(i >= HYDRAUSB3_SYNCHRO_TIMEOUT)
	{
		return 0; /* Timeout */
	}
	else
	{
		return i; // OK
	}
}
