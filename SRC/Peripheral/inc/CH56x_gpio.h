/********************************** (C) COPYRIGHT *******************************
* File Name          : CH56x_gpio.h
* Author             : WCH, bvernoux
* Version            : V1.2
* Date               : 2022/08/07
* Description
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#ifndef __CH56x_GPIO_H__
#define __CH56x_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO_Pin_0   (0x00000001) /*!< Pin 0 selected */
#define GPIO_Pin_1   (0x00000002) /*!< Pin 1 selected */
#define GPIO_Pin_2   (0x00000004) /*!< Pin 2 selected */
#define GPIO_Pin_3   (0x00000008) /*!< Pin 3 selected */
#define GPIO_Pin_4   (0x00000010) /*!< Pin 4 selected */
#define GPIO_Pin_5   (0x00000020) /*!< Pin 5 selected */
#define GPIO_Pin_6   (0x00000040) /*!< Pin 6 selected */
#define GPIO_Pin_7   (0x00000080) /*!< Pin 7 selected */
#define GPIO_Pin_8   (0x00000100) /*!< Pin 8 selected */
#define GPIO_Pin_9   (0x00000200) /*!< Pin 9 selected */
#define GPIO_Pin_10  (0x00000400) /*!< Pin 10 selected */
#define GPIO_Pin_11  (0x00000800) /*!< Pin 11 selected */
#define GPIO_Pin_12  (0x00001000) /*!< Pin 12 selected */
#define GPIO_Pin_13  (0x00002000) /*!< Pin 13 selected */
#define GPIO_Pin_14  (0x00004000) /*!< Pin 14 selected */
#define GPIO_Pin_15  (0x00008000) /*!< Pin 15 selected */
#define GPIO_Pin_16  (0x00010000) /*!< Pin 16 selected */
#define GPIO_Pin_17  (0x00020000) /*!< Pin 17 selected */
#define GPIO_Pin_18  (0x00040000) /*!< Pin 18 selected */
#define GPIO_Pin_19  (0x00080000) /*!< Pin 19 selected */
#define GPIO_Pin_20  (0x00100000) /*!< Pin 20 selected */
#define GPIO_Pin_21  (0x00200000) /*!< Pin 21 selected */
#define GPIO_Pin_22  (0x00400000) /*!< Pin 22 selected */
#define GPIO_Pin_23  (0x00800000) /*!< Pin 23 selected */
#define GPIO_Pin_24  (0x01000000) /*!< Pin 24 selected */
#define GPIO_Pin_All (0xFFFFFFFF) /*!< All pins selected */

/**
  * @brief  GPIO mode structure configuration
  */
typedef enum
{
	GPIO_ModeIN_Floating, // floating input
	GPIO_ModeIN_PU_NSMT,
	GPIO_ModeIN_PD_NSMT,
	GPIO_ModeIN_PU_SMT,
	GPIO_ModeIN_PD_SMT,
	GPIO_Slowascent_PP_8mA,
	GPIO_Slowascent_PP_16mA,
	GPIO_Highspeed_PP_8mA,
	GPIO_Highspeed_PP_16mA,
	GPIO_ModeOut_OP_8mA,
	GPIO_ModeOut_OP_16mA,
} GPIOModeTypeDef;

/**
  * @brief  GPIO interrupt structure configuration
  */
typedef enum
{
	GPIO_ITMode_LowLevel,  // Low level trigger
	GPIO_ITMode_HighLevel, // High level trigger
	GPIO_ITMode_FallEdge,  // Falling edge trigger
	GPIO_ITMode_RiseEdge,  // Rising edge trigger

} GPIOITModeTpDef;

/**
  * @brief  GPIOMCO structure configuration
  */
typedef enum
{
	MCO_125 = 0,
	MCO_25 = 4,
	MCO_2d5 = 0xC,
} MCOMode;

void GPIOA_ModeCfg(uint32_t pin, GPIOModeTypeDef mode); /* GPIOA Port Pin Mode Configuration */
void GPIOB_ModeCfg(uint32_t pin, GPIOModeTypeDef mode); /* GPIOB Port Pin Mode Configuration */
#define	GPIOA_ResetBits(pin) (R32_PA_CLR |= pin) /* GPIOA Port pin output deasserted */
#define	GPIOA_SetBits(pin) (R32_PA_OUT |= pin) /* GPIOA Port pin output set high */
#define	GPIOB_ResetBits(pin) (R32_PB_CLR |= pin) /* GPIOB Port pin output deasserted */
#define	GPIOB_SetBits(pin) (R32_PB_OUT |= pin) /* GPIOB Port pin output set high */
#define	GPIOA_InverseBits(pin) (R32_PA_OUT ^= pin) /* GPIOA Port pin output level flip */
#define	GPIOB_InverseBits(pin) (R32_PB_OUT ^= pin) /* GPIOB Port pin output level flip */
#define	GPIOA_ReadPort() (R32_PA_PIN) /* GPIOA Port 32-bit data is returned, the lower 16 bits are valid */
#define	GPIOB_ReadPort() (R32_PB_PIN) /* GPIOB Port 32-bit data is returned, the lower 24 bits are valid */
#define	GPIOA_ReadPortPin(pin) (R32_PA_PIN&pin) /* GPIOA Port pin status, 0-pin low, (!0)-pin high */
#define	GPIOB_ReadPortPin(pin) (R32_PB_PIN&pin) /* GPIOB Port pin status, 0-pin low, (!0)-pin high */

void GPIOA_ITModeCfg(uint32_t pin, GPIOITModeTpDef mode);	/* GPIOA Pin Interrupt Mode Configuration */
void GPIOB_ITModeCfg(uint32_t pin, GPIOITModeTpDef mode);	/* GPIOB Pin Interrupt Mode Configuration */
#define	GPIOA_ReadITFlagPort() (R8_GPIO_INT_FLAG) /* Read GPIOA Port Interrupt Flag Status */
#define	GPIOB_ReadITFlagPort() (R8_GPIO_INT_FLAG) /* Read GPIOB Port Interrupt Flag Status */

/************************************* Read interrupt flag ************************************/
#define	GPIOA_2_ReadITFlagBit() (R8_GPIO_INT_FLAG & 0x01) /* Read GPIOA port pin interrupt flag status */
#define	GPIOA_3_ReadITFlagBit() (R8_GPIO_INT_FLAG & 0x02)
#define	GPIOA_4_ReadITFlagBit() (R8_GPIO_INT_FLAG & 0x04)

#define	GPIOB_3_ReadITFlagBit() (R8_GPIO_INT_FLAG & 0x08) /* Read GPIOB port pin interrupt flag status */
#define	GPIOB_4_ReadITFlagBit() (R8_GPIO_INT_FLAG & 0x10)
#define	GPIOB_11_ReadITFlagBit() (R8_GPIO_INT_FLAG & 0x20)
#define	GPIOB_12_ReadITFlagBit() (R8_GPIO_INT_FLAG & 0x40)
#define	GPIOB_15_ReadITFlagBit() (R8_GPIO_INT_FLAG & 0x80)

/************************************* Clear interrupt flag ************************************/
#define	GPIOA_2_ClearITFlagBit() (R8_GPIO_INT_FLAG = 0x01) /* Clear GPIOA port pin interrupt flag status */
#define	GPIOA_3_ClearITFlagBit() (R8_GPIO_INT_FLAG = 0x02)
#define	GPIOA_4_ClearITFlagBit() (R8_GPIO_INT_FLAG = 0x04)

#define	GPIOB_3_ClearITFlagBit() (R8_GPIO_INT_FLAG = 0x08) /* Clear GPIOB port pin interrupt flag status */
#define	GPIOB_4_ClearITFlagBit() (R8_GPIO_INT_FLAG = 0x10)
#define	GPIOB_11_ClearITFlagBit() (R8_GPIO_INT_FLAG = 0x20)
#define	GPIOB_12_ClearITFlagBit() (R8_GPIO_INT_FLAG = 0x40)
#define	GPIOB_15_ClearITFlagBit() (R8_GPIO_INT_FLAG = 0x80)

void GPIOPinRemap(uint8_t s, uint16_t perph); /* Peripheral Function Pin Mapping */
void GPIOMco(uint8_t s, uint16_t freq); /* MCO function */

#ifdef __cplusplus
}
#endif

#endif  // __CH56x_GPIO_H__
