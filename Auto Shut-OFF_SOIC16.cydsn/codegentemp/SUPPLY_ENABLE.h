/*******************************************************************************
* File Name: SUPPLY_ENABLE.h  
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

#if !defined(CY_PINS_SUPPLY_ENABLE_H) /* Pins SUPPLY_ENABLE_H */
#define CY_PINS_SUPPLY_ENABLE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SUPPLY_ENABLE_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SUPPLY_ENABLE_Write(uint8 value) ;
void    SUPPLY_ENABLE_SetDriveMode(uint8 mode) ;
uint8   SUPPLY_ENABLE_ReadDataReg(void) ;
uint8   SUPPLY_ENABLE_Read(void) ;
uint8   SUPPLY_ENABLE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SUPPLY_ENABLE_DRIVE_MODE_BITS        (3)
#define SUPPLY_ENABLE_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SUPPLY_ENABLE_DRIVE_MODE_BITS))

#define SUPPLY_ENABLE_DM_ALG_HIZ         (0x00u)
#define SUPPLY_ENABLE_DM_DIG_HIZ         (0x01u)
#define SUPPLY_ENABLE_DM_RES_UP          (0x02u)
#define SUPPLY_ENABLE_DM_RES_DWN         (0x03u)
#define SUPPLY_ENABLE_DM_OD_LO           (0x04u)
#define SUPPLY_ENABLE_DM_OD_HI           (0x05u)
#define SUPPLY_ENABLE_DM_STRONG          (0x06u)
#define SUPPLY_ENABLE_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define SUPPLY_ENABLE_MASK               SUPPLY_ENABLE__MASK
#define SUPPLY_ENABLE_SHIFT              SUPPLY_ENABLE__SHIFT
#define SUPPLY_ENABLE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SUPPLY_ENABLE_PS                     (* (reg32 *) SUPPLY_ENABLE__PS)
/* Port Configuration */
#define SUPPLY_ENABLE_PC                     (* (reg32 *) SUPPLY_ENABLE__PC)
/* Data Register */
#define SUPPLY_ENABLE_DR                     (* (reg32 *) SUPPLY_ENABLE__DR)
/* Input Buffer Disable Override */
#define SUPPLY_ENABLE_INP_DIS                (* (reg32 *) SUPPLY_ENABLE__PC2)


#if defined(SUPPLY_ENABLE__INTSTAT)  /* Interrupt Registers */

    #define SUPPLY_ENABLE_INTSTAT                (* (reg32 *) SUPPLY_ENABLE__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define SUPPLY_ENABLE_DRIVE_MODE_SHIFT       (0x00u)
#define SUPPLY_ENABLE_DRIVE_MODE_MASK        (0x07u << SUPPLY_ENABLE_DRIVE_MODE_SHIFT)


#endif /* End Pins SUPPLY_ENABLE_H */


/* [] END OF FILE */
