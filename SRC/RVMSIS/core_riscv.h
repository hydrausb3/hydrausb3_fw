/********************************** (C) COPYRIGHT  *******************************
* File Name          : core_riscv.h
* Author             : WCH, bvernoux
* Version            : V1.0.1
* Date               : 2022/07/30
* Description        : RISC-V Core Peripheral Access Layer Header File
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Copyright (c) 2022 Benjamin VERNOUX
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#ifndef __CORE_RV3A_H__
#define __CORE_RV3A_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include "CH56xSFR.H"

/* IO definitions */
#ifdef __cplusplus
  #define     __I     volatile                /*!< defines 'read only' permissions      */
#else
  #define     __I     volatile const          /*!< defines 'read only' permissions     */
#endif
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */
#define   RV_STATIC_INLINE  static  inline

//typedef enum {SUCCESS = 0, ERROR = !SUCCESS} ErrorStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

/* memory mapped structure for Program Fast Interrupt Controller (PFIC) */
typedef struct __attribute__((packed)) {
    __I  UINT32 ISR[8];
    __I  UINT32 IPR[8];
    __IO UINT32 ITHRESDR;
    __IO UINT32 FIBADDRR;
    __IO UINT32 CFGR;
    __I  UINT32 GISR;
    UINT8 RESERVED0[0x10];
    __IO UINT32 FIOFADDRR[4];
    UINT8 RESERVED1[0x90];
    __O  UINT32 IENR[8];
    UINT8 RESERVED2[0x60];
    __O  UINT32 IRER[8];
    UINT8 RESERVED3[0x60];
    __O  UINT32 IPSR[8];
    UINT8 RESERVED4[0x60];
    __O  UINT32 IPRR[8];
    UINT8 RESERVED5[0x60];
    __IO UINT32 IACTR[8];
    UINT8 RESERVED6[0xE0];
    __IO UINT8 IPRIOR[256];
    UINT8 RESERVED7[0x810];
    __IO UINT32 SCTLR;
}PFIC_Type;

/* memory mapped structure for SysTick */
typedef struct __attribute__((packed))
{
    __IO UINT32 CTLR;
    __IO UINT64 CNT;
    __IO UINT64 CMP;
    __IO UINT32 CNTFG;
}SysTick_Type;


#define PFIC            ((PFIC_Type *) 0xE000E000 )
#define SysTick         ((SysTick_Type *) 0xE000F000)

#define PFIC_KEY1       ((UINT32)0xFA050000)
#define	PFIC_KEY2		((UINT32)0xBCAF0000)
#define	PFIC_KEY3		((UINT32)0xBEEF0000)


/*********************************************************************
 * @fn      __NOP
 *
 * @brief   nop
 *
 * @return  none
 */
RV_STATIC_INLINE void __NOP()
{
  __asm volatile ("nop");
}

/*********************************************************************
 * @fn      PFIC_EnableIRQ
 *
 * @brief   Enable Interrupt
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  none
 */
RV_STATIC_INLINE void PFIC_EnableIRQ(IRQn_Type IRQn){
    PFIC->IENR[((UINT32)(IRQn) >> 5)] = (1 << ((UINT32)(IRQn) & 0x1F));
}

/*********************************************************************
 * @fn      PFIC_DisableIRQ
 *
 * @brief   Disable Interrupt
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  none
 */
RV_STATIC_INLINE void PFIC_DisableIRQ(IRQn_Type IRQn){
    UINT32 t;

    t = PFIC->ITHRESDR;
    PFIC->ITHRESDR = 0x10;
    PFIC->IRER[((UINT32)(IRQn) >> 5)] = (1 << ((UINT32)(IRQn) & 0x1F));
    PFIC->ITHRESDR = t;
}

/*********************************************************************
 * @fn      PFIC_GetStatusIRQ
 *
 * @brief   Get Interrupt Enable State
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  1 - Interrupt Enable
 *          0 - Interrupt Disable
 */
RV_STATIC_INLINE UINT32 PFIC_GetStatusIRQ(IRQn_Type IRQn){
    return((UINT32) ((PFIC->ISR[(UINT32)(IRQn) >> 5] & (1 << ((UINT32)(IRQn) & 0x1F)))?1:0));
}

/*********************************************************************
 * @fn      PFIC_GetPendingIRQ
 *
 * @brief   Get Interrupt Pending State
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  1 - Interrupt Pending Enable
 *          0 - Interrupt Pending Disable
 */
RV_STATIC_INLINE UINT32 PFIC_GetPendingIRQ(IRQn_Type IRQn)
{
    return((UINT32) ((PFIC->IPR[(UINT32)(IRQn) >> 5] & (1 << ((UINT32)(IRQn) & 0x1F)))?1:0));
}

/*********************************************************************
 * @fn      PFIC_SetPendingIRQ
 *
 * @brief   Set Interrupt Pending
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  None
 */
RV_STATIC_INLINE void PFIC_SetPendingIRQ(IRQn_Type IRQn){
    PFIC->IPSR[((UINT32)(IRQn) >> 5)] = (1 << ((UINT32)(IRQn) & 0x1F));
}

/*********************************************************************
 * @fn      PFIC_ClearPendingIRQ
 *
 * @brief   Clear Interrupt Pending
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  None
 */
RV_STATIC_INLINE void PFIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    PFIC->IPRR[((UINT32)(IRQn) >> 5)] = (1 << ((UINT32)(IRQn) & 0x1F));
}

/*********************************************************************
 * @fn      PFIC_GetActive
 *
 * @brief   Get Interrupt Active State
 *
 * @param   IRQn: Interrupt Numbers
 *
 * @return  1 - Interrupt Active
 *          0 - Interrupt No Active
 */
RV_STATIC_INLINE UINT32 PFIC_GetActive(IRQn_Type IRQn){
    return((UINT32)((PFIC->IACTR[(UINT32)(IRQn) >> 5] & (1 << ((UINT32)(IRQn) & 0x1F)))?1:0));
}

/*********************************************************************
 * @fn      PFIC_SetPriority
 *
 * @brief   Set Interrupt Priority
 *
 * @param   IRQn - Interrupt Numbers
 *          priority -
 *              bit7 - pre-emption priority
 *              bit6~bit4 - subpriority
 * @return  None
 */
RV_STATIC_INLINE void PFIC_SetPriority(IRQn_Type IRQn, UINT8 priority){
    PFIC->IPRIOR[(UINT32)(IRQn)] = priority;
}

/*********************************************************************
 * @fn      __SEV
 *
 * @brief   Wait for Events
 *
 * @return  None
 */
__attribute__( ( always_inline ) ) RV_STATIC_INLINE void __SEV(void){
    PFIC->SCTLR |= (1<<3);
}

/*********************************************************************
 * @fn      __WFI
 *
 * @brief   Wait for Interrupt
 *
 * @return  None
 */
__attribute__( ( always_inline ) ) RV_STATIC_INLINE void __WFI(void){
    PFIC->SCTLR &= ~(1<<3);	// wfi
    asm volatile ("wfi");
}

/*********************************************************************
 * @fn      __WFE
 *
 * @brief   Wait for Events
 *
 * @return  None
 */
__attribute__( ( always_inline ) ) RV_STATIC_INLINE void __WFE(void){
    PFIC->SCTLR |= (1<<3)|(1<<5);		// (wfi->wfe)+(__sev)
    asm volatile ("wfi");
    PFIC->SCTLR |= (1<<3);
    asm volatile ("wfi");
}

/*********************************************************************
 * @fn      PFIC_SetFastIRQ
 *
 * @brief   Set VTF Interrupt
 *
 * @param   add - VTF interrupt service function base address.
 *          IRQn -Interrupt Numbers
 *          num - VTF Interrupt Numbers
 * @return  None
 */
RV_STATIC_INLINE void PFIC_SetFastIRQ(UINT32 addr, IRQn_Type IRQn, UINT8 num){
    if(num > 3)  return ;
    PFIC->FIBADDRR = addr;
    PFIC->FIOFADDRR[num] = ((UINT32)IRQn<<24)|(addr&0xfffff);
}

/*********************************************************************
 * @fn      PFIC_SystemReset
 *
 * @brief   Initiate a system reset request
 *
 * @return  None
 */
RV_STATIC_INLINE void PFIC_SystemReset(void){
    PFIC->CFGR = PFIC_KEY3|(1<<7);
}

/*********************************************************************
 * @fn      PFIC_HaltPushCfg
 *
 * @brief   Enable Hardware Stack
 *
 * @param   NewState - DISABLE or ENABLE
 
 * @return  None
 */
RV_STATIC_INLINE void PFIC_HaltPushCfg(FunctionalState NewState){
    if (NewState != DISABLE){
        PFIC->CFGR = PFIC_KEY1;
    }
    else{
        PFIC->CFGR = PFIC_KEY1|(1<<0);
    }
}

/*********************************************************************
 * @fn      PFIC_INTNestCfg
 *
 * @brief   Enable Interrupt Nesting
 *
 * @param   NewState - DISABLE or ENABLE
 
 * @return  None
 */
RV_STATIC_INLINE void PFIC_INTNestCfg(FunctionalState NewState){
    if (NewState != DISABLE){
        PFIC->CFGR = PFIC_KEY1;
    }
    else{
        PFIC->CFGR = PFIC_KEY1|(1<<1);
    }
}


#define SysTick_LOAD_RELOAD_Msk            (0xFFFFFFFFFFFFFFFFULL)
#define SysTick_CTRL_RELOAD_Msk            (1 << 8)
#define SysTick_CTRL_CLKSOURCE_Msk         (1 << 2)
#define SysTick_CTRL_TICKINT_Msk           (1 << 1)
#define SysTick_CTRL_ENABLE_Msk            (1 << 0)


RV_STATIC_INLINE uint32_t SysTick_Config( UINT64 ticks ){
  if ((ticks - 1) > SysTick_LOAD_RELOAD_Msk)  return (1);      /* Reload value impossible */

  SysTick->CMP  = ticks - 1;                                  /* set reload register */
  PFIC_EnableIRQ( SysTick_IRQn );
  SysTick->CTLR  = SysTick_CTRL_RELOAD_Msk    |
                   SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
  return (0);                                                  /* Function successful */
}


/* Core_Exported_Functions */  
extern uint32_t __get_FFLAGS(void);
extern void __set_FFLAGS(uint32_t value);
extern uint32_t __get_FRM(void);
extern void __set_FRM(uint32_t value);
extern uint32_t __get_FCSR(void);
extern void __set_FCSR(uint32_t value);
extern uint32_t __get_MSTATUS(void);
extern void __set_MSTATUS(uint32_t value);
extern uint32_t __get_MISA(void);
extern void __set_MISA(uint32_t value);
extern uint32_t __get_MIE(void);
extern void __set_MIE(uint32_t value);
extern uint32_t __get_MTVEC(void);
extern void __set_MTVEC(uint32_t value);
extern uint32_t __get_MSCRATCH(void);
extern void __set_MSCRATCH(uint32_t value);
extern uint32_t __get_MEPC(void);
extern void __set_MEPC(uint32_t value);
extern uint32_t __get_MCAUSE(void);
extern void __set_MCAUSE(uint32_t value);
extern uint32_t __get_MTVAL(void);
extern void __set_MTVAL(uint32_t value);
extern uint32_t __get_MIP(void);
extern void __set_MIP(uint32_t value);
/*
extern uint32_t __get_MCYCLE(void);
extern void __set_MCYCLE(uint32_t value);
extern uint32_t __get_MCYCLEH(void);
extern void __set_MCYCLEH(uint32_t value);
*/
extern uint32_t __get_MINSTRET(void);
extern void __set_MINSTRET(uint32_t value);
extern uint32_t __get_MINSTRETH(void);
extern void __set_MINSTRETH(uint32_t value);
extern uint32_t __get_MVENDORID(void);
extern uint32_t __get_MARCHID(void);
extern uint32_t __get_MIMPID(void);
extern uint32_t __get_MHARTID(void);
extern uint32_t __get_SP(void);

#ifdef __cplusplus
}
#endif


#endif/* __CORE_RV3A_H__ */





