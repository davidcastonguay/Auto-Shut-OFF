/*******************************************************************************
* File Name: G.c  
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
#include "G.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        G_PC =   (G_PC & \
                                (uint32)(~(uint32)(G_DRIVE_MODE_IND_MASK << (G_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (G_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: G_Write
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
void G_Write(uint8 value) 
{
    uint8 drVal = (uint8)(G_DR & (uint8)(~G_MASK));
    drVal = (drVal | ((uint8)(value << G_SHIFT) & G_MASK));
    G_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: G_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  G_DM_STRONG     Strong Drive 
*  G_DM_OD_HI      Open Drain, Drives High 
*  G_DM_OD_LO      Open Drain, Drives Low 
*  G_DM_RES_UP     Resistive Pull Up 
*  G_DM_RES_DWN    Resistive Pull Down 
*  G_DM_RES_UPDWN  Resistive Pull Up/Down 
*  G_DM_DIG_HIZ    High Impedance Digital 
*  G_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void G_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(G__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: G_Read
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
*  Macro G_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 G_Read(void) 
{
    return (uint8)((G_PS & G_MASK) >> G_SHIFT);
}


/*******************************************************************************
* Function Name: G_ReadDataReg
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
uint8 G_ReadDataReg(void) 
{
    return (uint8)((G_DR & G_MASK) >> G_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(G_INTSTAT) 

    /*******************************************************************************
    * Function Name: G_ClearInterrupt
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
    uint8 G_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(G_INTSTAT & G_MASK);
		G_INTSTAT = maskedStatus;
        return maskedStatus >> G_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
