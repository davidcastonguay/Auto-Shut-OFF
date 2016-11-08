/*******************************************************************************
* File Name: R.h  
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

#if !defined(CY_PINS_R_H) /* Pins R_H */
#define CY_PINS_R_H

#include "cytypes.h"
#include "cyfitter.h"
#include "R_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    R_Write(uint8 value) ;
void    R_SetDriveMode(uint8 mode) ;
uint8   R_ReadDataReg(void) ;
uint8   R_Read(void) ;
uint8   R_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define R_DRIVE_MODE_BITS        (3)
#define R_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - R_DRIVE_MODE_BITS))

#define R_DM_ALG_HIZ         (0x00u)
#define R_DM_DIG_HIZ         (0x01u)
#define R_DM_RES_UP          (0x02u)
#define R_DM_RES_DWN         (0x03u)
#define R_DM_OD_LO           (0x04u)
#define R_DM_OD_HI           (0x05u)
#define R_DM_STRONG          (0x06u)
#define R_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define R_MASK               R__MASK
#define R_SHIFT              R__SHIFT
#define R_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define R_PS                     (* (reg32 *) R__PS)
/* Port Configuration */
#define R_PC                     (* (reg32 *) R__PC)
/* Data Register */
#define R_DR                     (* (reg32 *) R__DR)
/* Input Buffer Disable Override */
#define R_INP_DIS                (* (reg32 *) R__PC2)


#if defined(R__INTSTAT)  /* Interrupt Registers */

    #define R_INTSTAT                (* (reg32 *) R__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define R_DRIVE_MODE_SHIFT       (0x00u)
#define R_DRIVE_MODE_MASK        (0x07u << R_DRIVE_MODE_SHIFT)


#endif /* End Pins R_H */


/* [] END OF FILE */
