/*******************************************************************************
* File Name: PUSH_BUTTON_INPUT.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PUSH_BUTTON_INPUT_H) /* Pins PUSH_BUTTON_INPUT_H */
#define CY_PINS_PUSH_BUTTON_INPUT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PUSH_BUTTON_INPUT_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PUSH_BUTTON_INPUT_Write(uint8 value) ;
void    PUSH_BUTTON_INPUT_SetDriveMode(uint8 mode) ;
uint8   PUSH_BUTTON_INPUT_ReadDataReg(void) ;
uint8   PUSH_BUTTON_INPUT_Read(void) ;
uint8   PUSH_BUTTON_INPUT_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PUSH_BUTTON_INPUT_DRIVE_MODE_BITS        (3)
#define PUSH_BUTTON_INPUT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PUSH_BUTTON_INPUT_DRIVE_MODE_BITS))

#define PUSH_BUTTON_INPUT_DM_ALG_HIZ         (0x00u)
#define PUSH_BUTTON_INPUT_DM_DIG_HIZ         (0x01u)
#define PUSH_BUTTON_INPUT_DM_RES_UP          (0x02u)
#define PUSH_BUTTON_INPUT_DM_RES_DWN         (0x03u)
#define PUSH_BUTTON_INPUT_DM_OD_LO           (0x04u)
#define PUSH_BUTTON_INPUT_DM_OD_HI           (0x05u)
#define PUSH_BUTTON_INPUT_DM_STRONG          (0x06u)
#define PUSH_BUTTON_INPUT_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define PUSH_BUTTON_INPUT_MASK               PUSH_BUTTON_INPUT__MASK
#define PUSH_BUTTON_INPUT_SHIFT              PUSH_BUTTON_INPUT__SHIFT
#define PUSH_BUTTON_INPUT_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PUSH_BUTTON_INPUT_PS                     (* (reg32 *) PUSH_BUTTON_INPUT__PS)
/* Port Configuration */
#define PUSH_BUTTON_INPUT_PC                     (* (reg32 *) PUSH_BUTTON_INPUT__PC)
/* Data Register */
#define PUSH_BUTTON_INPUT_DR                     (* (reg32 *) PUSH_BUTTON_INPUT__DR)
/* Input Buffer Disable Override */
#define PUSH_BUTTON_INPUT_INP_DIS                (* (reg32 *) PUSH_BUTTON_INPUT__PC2)


#if defined(PUSH_BUTTON_INPUT__INTSTAT)  /* Interrupt Registers */

    #define PUSH_BUTTON_INPUT_INTSTAT                (* (reg32 *) PUSH_BUTTON_INPUT__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define PUSH_BUTTON_INPUT_DRIVE_MODE_SHIFT       (0x00u)
#define PUSH_BUTTON_INPUT_DRIVE_MODE_MASK        (0x07u << PUSH_BUTTON_INPUT_DRIVE_MODE_SHIFT)


#endif /* End Pins PUSH_BUTTON_INPUT_H */


/* [] END OF FILE */
