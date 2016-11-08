/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* All includes, defines and global variables are declared in main.h */
#include "main.h"
#include <stdio.h>

/* I2C slave read and write buffers */
uint8 i2cReadBuffer [BUFFER_SIZE] = {PACKET_SOP, STS_CMD_FAIL, STS_CMD_FAIL, PACKET_EOP};
uint8 i2cWriteBuffer[BUFFER_SIZE];

int main()
{
    /* Enabling global interrupts */
    CyGlobalIntEnable;
    
    /* Starting all devices */
    PWM_CLOCK_Start();
    
    /* Starting components */
    I2C_I2CSlaveInitReadBuf (i2cReadBuffer,  BUFFER_SIZE);
    I2C_I2CSlaveInitWriteBuf(i2cWriteBuffer, BUFFER_SIZE);
    I2C_Start();
    PWM_Start();
//    SW_Tx_UART_Start();
    
    /* Configure ISR */
    PWM_isr_StartEx( PWM_isr );
    Push_Button_isr_StartEx( Push_Button_isr );

    /* Variables default values */
    DelayBeforeShutOff = DEFAULT_TIMEOUT;
    Second_in_Base_60 = ( DelayBeforeShutOff / OVERFLOW_PER_SECOND );
    Push_Button_Interrupt_Flag = 0;
    Second_Counter = 0;
    UART_TX_Flag = 0;
    I2C_Status = 0xFE;

    for(;;)
    {
        /* Disabling the SUPPLY ENABLE if timeout has been reached */
        if( DelayBeforeShutOff == 0 )
        {
            SUPPLY_ENABLE_Write( LOW ); 
            PWM_WriteCompare( LOW_GLOW );
        }
        else
        {
            /* Continue */
        }
        
        /* Check if push button has been toggled */
        if( Push_Button_Interrupt_Flag == 1 )
        {
            /* Activating the output */
            SUPPLY_ENABLE_Write( HIGH ); 
            
            /* Clearing the pushbutton interrupt flag */
            Push_Button_Interrupt_Flag = 0;
            
            /* Resetting the counter if timeout occured */
            DelayBeforeShutOff = DEFAULT_TIMEOUT;
            Second_in_Base_60 = ( DelayBeforeShutOff / OVERFLOW_PER_SECOND );
  
            /* Restarting the interrupt if it has been stopped */
            PWM_isr_StartEx(PWM_isr);
            PWM_ClearInterrupt(PWM_INTR_MASK_TC);
        }
        else
        {
            /* Toggling PWM Compare value depending on seconf counter value */
            if( DelayBeforeShutOff != 0 )
            {
                if( Second_Counter < ( SECOND_COUNT / 2 ) )
                {
                    PWM_WriteCompare( MID_GLOW );
                }
                else
                {
                    PWM_WriteCompare( HIGH_GLOW );
                }
                
            }
            else
            {
                /* Continue */
            }
        }
        
        /* Check if we must send info over UART */
//        if( UART_TX_Flag == 1 )
//        {
//            SW_Tx_UART_PutString("--------------------------");
//            SW_Tx_UART_PutCRLF();
//            SW_Tx_UART_PutString("Operating Mode: ");
//            if( Mode == 0 )
//            {
//                SW_Tx_UART_PutString("Shuttoff");
//            }
//            else
//            {
//                SW_Tx_UART_PutString("Toggle");
//            }
//            SW_Tx_UART_PutCRLF();
//            SW_Tx_UART_PutString("Seconds remaning: ");
//            SW_Tx_UART_PutHexInt( Second_in_Base_60 );
//            SW_Tx_UART_PutCRLF();
//            UART_TX_Flag = 0;
//        }
//        else
//        {
//            /* Continue */
//        }
        
        /* I2C Decode Received Packets */
        
        if (0u != (I2C_I2CSlaveStatus() & I2C_I2C_SSTAT_WR_CMPLT))
        {
            /* Check packet length */
            if (PACKET_SIZE == I2C_I2CSlaveGetWriteBufSize())
            {
                /* Check start and end of packet markers */
                if ((i2cWriteBuffer[PACKET_SOP_POS] == PACKET_SOP) &&
                    (i2cWriteBuffer[PACKET_EOP_POS] == PACKET_EOP))
                {
                    I2C_Status = ExecuteI2CCommand(i2cWriteBuffer[PACKET_CMD_POS], i2cWriteBuffer[PACKET_PARAM_POS] );
                }
            }

            /* Clear slave write buffer and status */
            I2C_I2CSlaveClearWriteBuf();
            (void) I2C_I2CSlaveClearWriteStatus();

            /* Update read buffer */
            i2cReadBuffer[PACKET_STS_POS] = I2C_Status;
            i2cReadBuffer[PACKET_PARAM_POS] = i2cWriteBuffer[PACKET_PARAM_POS];
            I2C_Status = STS_CMD_FAIL;
        }

        /* Read complete: expose buffer to master */
        if (0u != (I2C_I2CSlaveStatus() & I2C_I2C_SSTAT_RD_CMPLT))
        {
            /* Clear slave read buffer and status */
            I2C_I2CSlaveClearReadBuf();
            (void) I2C_I2CSlaveClearReadStatus();
        }
    }
}

/*******************************************************************************
* Function Name: PWM_isr
********************************************************************************
* Summary:
*  PWM module TC interrupt routine code
*
* Parameters: None.
*
* Return: None.
*
*******************************************************************************/
CY_ISR(PWM_isr)
{
    if( DelayBeforeShutOff <= 1 )
    {
        DelayBeforeShutOff = 0;
        Second_in_Base_60 = 0;
        PWM_isr_Stop();
    }
    else
    {
        DelayBeforeShutOff--;
    }
    
    if( Second_Counter == SECOND_COUNT )
    {
        Second_Counter = 0;
        Second_in_Base_60--;
        UART_TX_Flag = 1;
    }
    else
    {
        Second_Counter++;
    }

    /* Clear interrupt status in an interrupt controller */
    PWM_ClearInterrupt(PWM_INTR_MASK_TC);
}


/*******************************************************************************
* Function Name: Push_Button_isr
********************************************************************************
* Summary:
*  Push Button ISR routine code
*
* Parameters: None.
*
* Return: None.
*
*******************************************************************************/
CY_ISR_PROTO(Push_Button_isr)
{
    Push_Button_Interrupt_Flag = 1;
    PUSH_BUTTON_INPUT_ClearInterrupt();
}

/*******************************************************************************
* Function Name: ExecuteI2CCommand
********************************************************************************
* Summary:
*  Executes received command to control the LED color and returns status.
*  If the command is unknown, the LED color is not changed.
*
* Parameters:
*  cmd: command to execute. Available commands:

*
* Return:
*  Returns status of command execution. There are two statuses
*  - STS_CMD_DONE: command is executed successfully.
*  - STS_CMD_FAIL: unknown command
*
*******************************************************************************/
uint8 ExecuteI2CCommand( uint32 cmd, uint8 cmdparam )
{
    uint8 status;

    status = STS_CMD_DONE;

    /* Execute received command */
    switch (cmd)
    {
        case CMD_SET_OUPUT_ON:
            SUPPLY_ENABLE_Write( HIGH ); 
            break;

        case CMD_SET_OUTPUT_OFF:
            SUPPLY_ENABLE_Write( LOW ); 
            break;

        case CMD_SET_MODE:
            Mode = i2cReadBuffer[ PACKET_CMD_POS ];
            break;

        case CMD_SET_SHUT_OFF_DELAY_MSB:
            DelayBeforeShutOff = cmdparam;
            DelayBeforeShutOff = DelayBeforeShutOff << 24;
            break;
        
        case CMD_SET_SHUT_OFF_DELAY_THRDB:
            DelayBeforeShutOff = cmdparam;
            DelayBeforeShutOff = DelayBeforeShutOff << 16;
            break;
        
        case CMD_SET_SHUT_OFF_DELAY_SCNDB:
            DelayBeforeShutOff = cmdparam;
            DelayBeforeShutOff = DelayBeforeShutOff << 8;
            break;
        
        case CMD_SET_SHUT_OFF_DELAY_LSB:
            DelayBeforeShutOff += cmdparam;
            break;
        
        case CMD_SET_ON_TIME_DELAY_MSB:
            ON_Time = cmdparam;
            ON_Time = ON_Time << 24;
            break;
        
        case CMD_SET_ON_TIME_DELAY_THRDB:
            ON_Time = cmdparam;
            ON_Time = ON_Time << 16;
            break;
        
        case CMD_SET_ON_TIME_DELAY_SCNDB:
            ON_Time = cmdparam;
            ON_Time = ON_Time << 8;
            break;
        
        case CMD_SET_ON_TIME_DELAY_LSB:
            ON_Time += cmdparam;
            break;
        
        case CMD_SET_OFF_TIME_DELAY_MSB:
            OFF_Time = cmdparam;
            OFF_Time = OFF_Time << 24;
            break;
        
        case CMD_SET_OFF_TIME_DELAY_THRDB:
            OFF_Time = cmdparam;
            OFF_Time = OFF_Time << 16;
            break;
        
        case CMD_SET_OFF_TIME_DELAY_SCNDB:
            OFF_Time = cmdparam;
            OFF_Time = OFF_Time << 8;
            break;
        
        case CMD_SET_OFF_TIME_DELAY_LSB:
            OFF_Time += cmdparam;
            break;
        
        case CMD_SET_DEVICE_ADDRESS:
            //I2C_I2CSlaveSetAddress( cmdparam );
            break;
            
        case STS_CMD_BUTTON_EVENT:
            /* To be added */
            break;

        default:
            status = STS_CMD_FAIL;
            break;
    }

    return (status);
}


/* [] END OF FILE */
