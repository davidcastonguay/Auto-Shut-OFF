/*******************************************************************************
* File Name: PUSH_BUTTON_INPUT.c  
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
#include "PUSH_BUTTON_INPUT.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        PUSH_BUTTON_INPUT_PC =   (PUSH_BUTTON_INPUT_PC & \
                                (uint32)(~(uint32)(PUSH_BUTTON_INPUT_DRIVE_MODE_IND_MASK << (PUSH_BUTTON_INPUT_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (PUSH_BUTTON_INPUT_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: PUSH_BUTTON_INPUT_Write
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
void PUSH_BUTTON_INPUT_Write(uint8 value) 
{
    uint8 drVal = (uint8)(PUSH_BUTTON_INPUT_DR & (uint8)(~PUSH_BUTTON_INPUT_MASK));
    drVal = (drVal | ((uint8)(value << PUSH_BUTTON_INPUT_SHIFT) & PUSH_BUTTON_INPUT_MASK));
    PUSH_BUTTON_INPUT_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: PUSH_BUTTON_INPUT_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  PUSH_BUTTON_INPUT_DM_STRONG     Strong Drive 
*  PUSH_BUTTON_INPUT_DM_OD_HI      Open Drain, Drives High 
*  PUSH_BUTTON_INPUT_DM_OD_LO      Open Drain, Drives Low 
*  PUSH_BUTTON_INPUT_DM_RES_UP     Resistive Pull Up 
*  PUSH_BUTTON_INPUT_DM_RES_DWN    Resistive Pull Down 
*  PUSH_BUTTON_INPUT_DM_RES_UPDWN  Resistive Pull Up/Down 
*  PUSH_BUTTON_INPUT_DM_DIG_HIZ    High Impedance Digital 
*  PUSH_BUTTON_INPUT_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void PUSH_BUTTON_INPUT_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(PUSH_BUTTON_INPUT__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: PUSH_BUTTON_INPUT_Read
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
*  Macro PUSH_BUTTON_INPUT_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PUSH_BUTTON_INPUT_Read(void) 
{
    return (uint8)((PUSH_BUTTON_INPUT_PS & PUSH_BUTTON_INPUT_MASK) >> PUSH_BUTTON_INPUT_SHIFT);
}


/*******************************************************************************
* Function Name: PUSH_BUTTON_INPUT_ReadDataReg
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
uint8 PUSH_BUTTON_INPUT_ReadDataReg(void) 
{
    return (uint8)((PUSH_BUTTON_INPUT_DR & PUSH_BUTTON_INPUT_MASK) >> PUSH_BUTTON_INPUT_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PUSH_BUTTON_INPUT_INTSTAT) 

    /*******************************************************************************
    * Function Name: PUSH_BUTTON_INPUT_ClearInterrupt
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
    uint8 PUSH_BUTTON_INPUT_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(PUSH_BUTTON_INPUT_INTSTAT & PUSH_BUTTON_INPUT_MASK);
		PUSH_BUTTON_INPUT_INTSTAT = maskedStatus;
        return maskedStatus >> PUSH_BUTTON_INPUT_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
