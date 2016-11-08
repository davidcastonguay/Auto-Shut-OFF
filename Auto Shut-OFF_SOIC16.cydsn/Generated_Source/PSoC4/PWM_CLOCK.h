/*******************************************************************************
* File Name: PWM_CLOCK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_PWM_CLOCK_H)
#define CY_CLOCK_PWM_CLOCK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void PWM_CLOCK_StartEx(uint32 alignClkDiv);
#define PWM_CLOCK_Start() \
    PWM_CLOCK_StartEx(PWM_CLOCK__PA_DIV_ID)

#else

void PWM_CLOCK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void PWM_CLOCK_Stop(void);

void PWM_CLOCK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 PWM_CLOCK_GetDividerRegister(void);
uint8  PWM_CLOCK_GetFractionalDividerRegister(void);

#define PWM_CLOCK_Enable()                         PWM_CLOCK_Start()
#define PWM_CLOCK_Disable()                        PWM_CLOCK_Stop()
#define PWM_CLOCK_SetDividerRegister(clkDivider, reset)  \
    PWM_CLOCK_SetFractionalDividerRegister((clkDivider), 0u)
#define PWM_CLOCK_SetDivider(clkDivider)           PWM_CLOCK_SetDividerRegister((clkDivider), 1u)
#define PWM_CLOCK_SetDividerValue(clkDivider)      PWM_CLOCK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define PWM_CLOCK_DIV_ID     PWM_CLOCK__DIV_ID

#define PWM_CLOCK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define PWM_CLOCK_CTRL_REG   (*(reg32 *)PWM_CLOCK__CTRL_REGISTER)
#define PWM_CLOCK_DIV_REG    (*(reg32 *)PWM_CLOCK__DIV_REGISTER)

#define PWM_CLOCK_CMD_DIV_SHIFT          (0u)
#define PWM_CLOCK_CMD_PA_DIV_SHIFT       (8u)
#define PWM_CLOCK_CMD_DISABLE_SHIFT      (30u)
#define PWM_CLOCK_CMD_ENABLE_SHIFT       (31u)

#define PWM_CLOCK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << PWM_CLOCK_CMD_DISABLE_SHIFT))
#define PWM_CLOCK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << PWM_CLOCK_CMD_ENABLE_SHIFT))

#define PWM_CLOCK_DIV_FRAC_MASK  (0x000000F8u)
#define PWM_CLOCK_DIV_FRAC_SHIFT (3u)
#define PWM_CLOCK_DIV_INT_MASK   (0xFFFFFF00u)
#define PWM_CLOCK_DIV_INT_SHIFT  (8u)

#else 

#define PWM_CLOCK_DIV_REG        (*(reg32 *)PWM_CLOCK__REGISTER)
#define PWM_CLOCK_ENABLE_REG     PWM_CLOCK_DIV_REG
#define PWM_CLOCK_DIV_FRAC_MASK  PWM_CLOCK__FRAC_MASK
#define PWM_CLOCK_DIV_FRAC_SHIFT (16u)
#define PWM_CLOCK_DIV_INT_MASK   PWM_CLOCK__DIVIDER_MASK
#define PWM_CLOCK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_PWM_CLOCK_H) */

/* [] END OF FILE */
