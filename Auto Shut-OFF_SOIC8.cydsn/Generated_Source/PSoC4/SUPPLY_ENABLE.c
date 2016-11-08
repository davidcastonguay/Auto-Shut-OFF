/*******************************************************************************
* File Name: SUPPLY_ENABLE.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "SUPPLY_ENABLE.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        SUPPLY_ENABLE_PC =   (SUPPLY_ENABLE_PC & \
                                (uint32)(~(uint32)(SUPPLY_ENABLE_DRIVE_MODE_IND_MASK << (SUPPLY_ENABLE_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (SUPPLY_ENABLE_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: SUPPLY_ENABLE_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void SUPPLY_ENABLE_Write(uint8 value) 
{
    uint8 drVal = (uint8)(SUPPLY_ENABLE_DR & (uint8)(~SUPPLY_ENABLE_MASK));
    drVal = (drVal | ((uint8)(value << SUPPLY_ENABLE_SHIFT) & SUPPLY_ENABLE_MASK));
    SUPPLY_ENABLE_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: SUPPLY_ENABLE_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SUPPLY_ENABLE_DM_STRONG     Strong Drive 
*  SUPPLY_ENABLE_DM_OD_HI      Open Drain, Drives High 
*  SUPPLY_ENABLE_DM_OD_LO      Open Drain, Drives Low 
*  SUPPLY_ENABLE_DM_RES_UP     Resistive Pull Up 
*  SUPPLY_ENABLE_DM_RES_DWN    Resistive Pull Down 
*  SUPPLY_ENABLE_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SUPPLY_ENABLE_DM_DIG_HIZ    High Impedance Digital 
*  SUPPLY_ENABLE_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SUPPLY_ENABLE_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(SUPPLY_ENABLE__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: SUPPLY_ENABLE_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro SUPPLY_ENABLE_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SUPPLY_ENABLE_Read(void) 
{
    return (uint8)((SUPPLY_ENABLE_PS & SUPPLY_ENABLE_MASK) >> SUPPLY_ENABLE_SHIFT);
}


/*******************************************************************************
* Function Name: SUPPLY_ENABLE_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 SUPPLY_ENABLE_ReadDataReg(void) 
{
    return (uint8)((SUPPLY_ENABLE_DR & SUPPLY_ENABLE_MASK) >> SUPPLY_ENABLE_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SUPPLY_ENABLE_INTSTAT) 

    /*******************************************************************************
    * Function Name: SUPPLY_ENABLE_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 SUPPLY_ENABLE_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(SUPPLY_ENABLE_INTSTAT & SUPPLY_ENABLE_MASK);
		SUPPLY_ENABLE_INTSTAT = maskedStatus;
        return maskedStatus >> SUPPLY_ENABLE_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
