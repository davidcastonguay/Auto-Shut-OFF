/*******************************************************************************
* File Name: G.h  
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

#if !defined(CY_PINS_G_H) /* Pins G_H */
#define CY_PINS_G_H

#include "cytypes.h"
#include "cyfitter.h"
#include "G_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    G_Write(uint8 value) ;
void    G_SetDriveMode(uint8 mode) ;
uint8   G_ReadDataReg(void) ;
uint8   G_Read(void) ;
uint8   G_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define G_DRIVE_MODE_BITS        (3)
#define G_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - G_DRIVE_MODE_BITS))

#define G_DM_ALG_HIZ         (0x00u)
#define G_DM_DIG_HIZ         (0x01u)
#define G_DM_RES_UP          (0x02u)
#define G_DM_RES_DWN         (0x03u)
#define G_DM_OD_LO           (0x04u)
#define G_DM_OD_HI           (0x05u)
#define G_DM_STRONG          (0x06u)
#define G_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define G_MASK               G__MASK
#define G_SHIFT              G__SHIFT
#define G_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define G_PS                     (* (reg32 *) G__PS)
/* Port Configuration */
#define G_PC                     (* (reg32 *) G__PC)
/* Data Register */
#define G_DR                     (* (reg32 *) G__DR)
/* Input Buffer Disable Override */
#define G_INP_DIS                (* (reg32 *) G__PC2)


#if defined(G__INTSTAT)  /* Interrupt Registers */

    #define G_INTSTAT                (* (reg32 *) G__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define G_DRIVE_MODE_SHIFT       (0x00u)
#define G_DRIVE_MODE_MASK        (0x07u << G_DRIVE_MODE_SHIFT)


#endif /* End Pins G_H */


/* [] END OF FILE */
