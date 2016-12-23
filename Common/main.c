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
#include <math.h>

int main()
{
    
    /* Enabling global interrupts */
    CyGlobalIntEnable;
    
    /* Starting all devices */
    PWM_CLOCK_Start();
    
    /* Starting components */
    #if( COMMUNICATION_LAYER == I2C_MODE )
        I2C_I2CSlaveInitReadBuf (i2cReadBuffer,  BUFFER_SIZE);
        I2C_I2CSlaveInitWriteBuf(i2cWriteBuffer, BUFFER_SIZE);
        I2C_Start();
        I2C_Status = STS_CMD_FAIL;
    //#else
    #endif
        
    #if( COMMUNICATION_LAYER == SERIAL_MODE )    
        SW_Tx_UART_Start();  
        UART_TX_Flag = 0;
        CyDelayUs( 2000 );
        SW_Tx_UART_PutString("/// Power-up");
        SW_Tx_UART_PutCRLF();
        SW_Tx_UART_PutString("///Firmware version: ");
        SW_Tx_UART_PutHexInt( FIRMWARE_VERSION );
        SW_Tx_UART_PutCRLF();
    //#else
    #endif
    
    #if( IC_PACKAGE == SOIC_16 )
        R_Write( 1 );
        G_Write( 1 );
        B_Write( 1 );
    //#else
    #endif
    
    /* Configure initial state */
    PWM_Start();
    Push_Button_isr_StartEx( Push_Button_isr );
    Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 0;
    Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] = 0xFFFFFFFFu;
    Parameters_Register[ SECOND_COUNTER_REG ] = 0;
    Parameters_Register[ TOGGLE_COUNTER_REG ] = 0;
    Parameters_Register[ SET_PEN_REG ] = LOW;
    SUPPLY_ENABLE_Write( ASSERTED_LOW );
    PWM_WriteCompare( 0 );
    R_Write( LED_ON );
    G_Write( LED_OFF );
    B_Write( LED_OFF );
    
    #if( COMMUNICATION_LAYER == SERIAL_MODE )    
        SW_Tx_UART_PutString("/// Waiting for push button to be pressed");
        SW_Tx_UART_PutCRLF();
    //#else
    #endif
    
    #if( COMMUNICATION_LAYER == SERIAL_MODE )    
        SW_Tx_UART_PutString("---Deep Sleep");
        SW_Tx_UART_PutCRLF();
        //#else
    #endif
        
    CySysPmDeepSleep();

    for(;;)
    {
        /* Disabling the SUPPLY ENABLE if timeout has been reached */
        if( Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] == 0 )
        {
            if( Parameters_Register[ SET_MODE_REG ] == SHUT_OFF )
            {
                SUPPLY_ENABLE_Write( ASSERTED_LOW ); 
                
                #if( COMMUNICATION_LAYER == SERIAL_MODE )    
                    SW_Tx_UART_PutString("---Countdown terminated");
                    SW_Tx_UART_PutCRLF();
                    //#else
                #endif
                
                /* Managing LED states */
                R_Write( LED_ON );
                G_Write( LED_OFF );
                B_Write( LED_OFF );
                Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] = 0xFFFFFFFFu;
                
                #if( COMMUNICATION_LAYER == SERIAL_MODE )    
                    SW_Tx_UART_PutString("---Deep Sleep");
                    SW_Tx_UART_PutCRLF();
                    //#else
                #endif
                
                CySysPmDeepSleep();
            }
            else
            {
                SetTimerSettings();
                /* Toggling from ON to OFF */
                if( Parameters_Register[ SET_PEN_REG ] == HIGH )
                {
                    SUPPLY_ENABLE_Write( ASSERTED_LOW );
                    Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] = Parameters_Register[ SET_OFF_TIME_REG ];
                    /* Managing LED states */
                    R_Write( LED_ON );
                    G_Write( LED_ON );
                    B_Write( LED_OFF );
                    Parameters_Register[ SET_PEN_REG ] = LOW;
                }
                /* Toggling from OFF to ON */
                else
                {
                    SUPPLY_ENABLE_Write( ASSERTED_HIGH );
                    Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] = Parameters_Register[ SET_ON_TIME_REG ];
                    /* Managing LED states */
                    R_Write( LED_OFF );
                    G_Write( LED_ON );
                    B_Write( LED_OFF );
                    Parameters_Register[ SET_PEN_REG ] = HIGH;
                    Parameters_Register[ TOGGLE_COUNTER_REG ]++;
                }
                
                Parameters_Register[ SECOND_IN_BASE_60_REG ] = ( Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] / OVERFLOW_PER_SECOND );
                PWM_isr_StartEx(PWM_isr);
                PWM_ClearInterrupt(PWM_INTR_MASK_TC);
            }
        }
        else
        {
            if( PWM_isr_GetState() == 1 )
            {
                /* Toggling PWM Compare value depending on second counter value */
                if( Parameters_Register[ SECOND_COUNTER_REG ] < ( SECOND_COUNT / 2 ) )
                {
//                    PWM_WriteCompare( MID_GLOW );
                    B_Write( LED_OFF );
                }
                else
                {
//                    PWM_WriteCompare( HIGH_GLOW );
                    B_Write( LED_ON );
                }
            }
            else
            {
                /* Continue */
            }
        }
        
        /* Processing push button events */
        if( Parameters_Register[ OVERFLOW_COUNTER_REG ] >= 200 )
        {
            if( ( Parameters_Register[ PUSH_BUTTON_EVENT_REG ] == BUTTON_HOLD_DOWN ) && ( Parameters_Register[ PUSH_BUTTON_STATE_VALUE_REG ] == 1 ) )
            {
                Parameters_Register[ PUSH_BUTTON_EVENT_REG ] = BUTTON_RELEASED;
                #if( COMMUNICATION_LAYER == SERIAL_MODE ) 
                    SW_Tx_UART_PutString("+++Push Button Event: Released");
                    SW_Tx_UART_PutCRLF();
                #endif
            }
            else if( ( Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] == 1 ) && ( Parameters_Register[ PUSH_BUTTON_STATE_VALUE_REG ] == 1 ) )
            {
                Parameters_Register[ PUSH_BUTTON_EVENT_REG ] = BUTTON_CLICK_EVENT;
                #if( COMMUNICATION_LAYER == SERIAL_MODE ) 
                    SW_Tx_UART_PutString("+++Push Button Event: Click");
                    SW_Tx_UART_PutCRLF();
                #endif
            }
            else if( ( Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] >= 2 ) && ( Parameters_Register[ PUSH_BUTTON_STATE_VALUE_REG ] == 1 ) )
            {
                Parameters_Register[ PUSH_BUTTON_EVENT_REG ] = BUTTON_DOUBLE_CLICK_EVENT;
                #if( COMMUNICATION_LAYER == SERIAL_MODE ) 
                    SW_Tx_UART_PutString("+++Push Button Event: Double Click");
                    SW_Tx_UART_PutCRLF();
                #endif
            }
            else if( ( Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] == 1 ) && ( Parameters_Register[ PUSH_BUTTON_STATE_VALUE_REG ] == 0 ) )
            {
                Parameters_Register[ PUSH_BUTTON_EVENT_REG ] = BUTTON_HOLD_DOWN;
                #if( COMMUNICATION_LAYER == SERIAL_MODE ) 
                    SW_Tx_UART_PutString("+++Push Button Event: Hold Down");
                    SW_Tx_UART_PutCRLF();
                #endif
            }
            else
            {
                /* Continue */
//                Push_Button_Event = BUTTON_NO_EVENT;
//                SW_Tx_UART_PutString("+++Push Button Event: Click");
//                SW_Tx_UART_PutCRLF();
            }
            
            Parameters_Register[ OVERFLOW_COUNTER_REG ] = 0;
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 0;
        }
        else
        {
            /* Continue */
        }
        
        /* Check if push button has been toggled */
        if( ( Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] == 1 ) && ( PWM_isr_GetState() == 0 ) )
        {
            #if( COMMUNICATION_LAYER == SERIAL_MODE )    
                SW_Tx_UART_PutString("/// Countdown to extinction");
                SW_Tx_UART_PutCRLF();
                //#else
            #endif
            
            /* Activating the output */
            SUPPLY_ENABLE_Write( ASSERTED_HIGH ); 
            
            /* Clearing the pushbutton interrupt flag */
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 0;
            
            /* Resetting the counter if timeout occured */
            SetTimerSettings();
            Parameters_Register[ SECOND_IN_BASE_60_REG ] = ( Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] / OVERFLOW_PER_SECOND );
            Parameters_Register[ SECOND_COUNTER_REG ] = 0;
            Parameters_Register[ TOGGLE_COUNTER_REG ] = 0;
            Parameters_Register[ SET_PEN_REG ] = HIGH;
  
            /* Restarting the interrupt if it has been stopped */
            PWM_Start();
            PWM_isr_StartEx(PWM_isr);
            PWM_ClearInterrupt(PWM_INTR_MASK_TC);
            
            /* Managing LED states */
            R_Write( LED_OFF );
            G_Write( LED_ON );
            B_Write( LED_OFF );
        }
        else
        {
            /* Continue */
        }
        
        /* Check if we must send info over UART */
        #if( COMMUNICATION_LAYER == SERIAL_MODE )
            if( UART_TX_Flag == 1 )
            {
//                SW_Tx_UART_PutString("--------------------------");
//                SW_Tx_UART_PutCRLF();
                SW_Tx_UART_PutString("---Operating Mode: ");
                if( Parameters_Register[ SET_MODE_REG ] == SHUT_OFF )
                {
                    SW_Tx_UART_PutString("Shutt-off;");
                }
                else
                {
                    SW_Tx_UART_PutString("Toggle;");
//                    SW_Tx_UART_PutCRLF();
                    SW_Tx_UART_PutString("Toggle Count: ");
                    SW_Tx_UART_PutHexInt( Parameters_Register[ TOGGLE_COUNTER_REG ] >> 16 );
                    SW_Tx_UART_PutHexInt( Parameters_Register[ TOGGLE_COUNTER_REG ] );
                    SW_Tx_UART_PutString(";");
                }
//                SW_Tx_UART_PutCRLF();
                SW_Tx_UART_PutString("Look-Up Table Address: ");
                SW_Tx_UART_PutHexInt( Parameters_Register[ LOOK_UP_TABLE_ADDRESS_REG ] );
                SW_Tx_UART_PutString(";");
//                SW_Tx_UART_PutCRLF();
                SW_Tx_UART_PutString("Seconds remaning: ");
                SW_Tx_UART_PutHexInt( Parameters_Register[ SECOND_IN_BASE_60_REG ] );
                SW_Tx_UART_PutString(";");
                
                if( Parameters_Register[ SET_PEN_REG ] == HIGH )
                {
                    SW_Tx_UART_PutString("Output = High;");
                    SW_Tx_UART_PutCRLF(); 
                }
                else
                {
                    SW_Tx_UART_PutString("Output = Low;");
                    SW_Tx_UART_PutCRLF();
                }

                UART_TX_Flag = 0;
            }
            else
            {
                /* Continue */
            }
        //#else
        #endif
        
        /* Check if we must send info over I2C */
        #if( COMMUNICATION_LAYER == I2C_MODE )
            if (0u != (I2C_I2CSlaveStatus() & I2C_I2C_SSTAT_WR_CMPLT))
            {
                /* Check packet length */
                if (PACKET_SIZE == I2C_I2CSlaveGetWriteBufSize())
                {
                    /* Check start and end of packet markers */
//                    if ((i2cWriteBuffer[PACKET_SOP_POS] == PACKET_SOP) &&
//                    (i2cWriteBuffer[PACKET_EOP_POS] == PACKET_EOP))
//                    {
                        I2C_Status = ExecuteI2CCommand(i2cWriteBuffer[PACKET_CMD_POS], i2cWriteBuffer[PACKET_PARAM_POS] );
//                    }
                }
            
                /* Clear slave write buffer and status */
                I2C_I2CSlaveClearWriteBuf();
                (void) I2C_I2CSlaveClearWriteStatus();
            
                /* Update read buffer */
                /* Sending the echo to the Host */
                i2cReadBuffer[PACKET_CMD_POS] = i2cWriteBuffer[PACKET_CMD_POS];
                i2cReadBuffer[PACKET_STS_POS] = i2cWriteBuffer[PACKET_PARAM_POS];
                //I2C_Status = STS_CMD_FAIL;
            }

            /* Read complete: expose buffer to master */
            if (0u != (I2C_I2CSlaveStatus() & I2C_I2C_SSTAT_RD_CMPLT))
            {
                /* Clear slave read buffer and status */
                I2C_I2CSlaveClearReadBuf();
                (void) I2C_I2CSlaveClearReadStatus();
            }
        #endif
        
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
    /* Decrementing the timer */
    if( Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] <= 1 )
    {
        Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] = 0;
        Parameters_Register[ SECOND_IN_BASE_60_REG ] = 0;
        Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 0;
        PWM_isr_Stop();
    }
    else
    {
        Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ]--;
    }
    
    /* Second in base 60 timer */
    if( Parameters_Register[ SECOND_COUNTER_REG ] == SECOND_COUNT )
    {
        Parameters_Register[ SECOND_COUNTER_REG ] = 0;
        Parameters_Register[ SECOND_IN_BASE_60_REG ]--;
        #if( COMMUNICATION_LAYER == SERIAL_MODE )
            UART_TX_Flag = 1;
        //#else
        #endif
    }
    else
    {
        Parameters_Register[ SECOND_COUNTER_REG ]++;
    }
    
    /* Incrementing the overflow counter for button processor */
    if( Parameters_Register[ OVERFLOW_COUNTER_REG ] > 200 )
    {
        Parameters_Register[ OVERFLOW_COUNTER_REG ] = 0;
    }
    else
    {
        Parameters_Register[ OVERFLOW_COUNTER_REG ]++;
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
    /* Waiting for the state to stabilize */
    CyDelayUs( 5000 );
    
    /* Reading the state */
    if( PUSH_BUTTON_INPUT_Read() == 0 )
    {
        Parameters_Register[ PUSH_BUTTON_STATE_VALUE_REG ] = 0;
        Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ]++;
    }
    else
    {
        Parameters_Register[ PUSH_BUTTON_STATE_VALUE_REG ] = 1;
    }
    
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
#if( COMMUNICATION_LAYER == I2C_MODE )
uint8 ExecuteI2CCommand( uint32 cmd, uint8 cmdparam )
{
    uint8 status;
    uint32 lvalue = 0;

    status = STS_CMD_DONE;

    /* Execute received command */
    switch (cmd)
    {
        case SET_PEN_REG:
            Parameters_Register[ SET_PEN_REG ] = cmdparam;
            SUPPLY_ENABLE_Write( Parameters_Register[ SET_PEN_REG ] ); 
            break;

        case SET_PWM_OUT_REG:
            Parameters_Register[ SET_PWM_OUT_REG ] = cmdparam;
            break;

        case SET_MODE_REG:
            Parameters_Register[ SET_MODE_REG ] = cmdparam;
            break;

        case SET_SHUT_OFF_DELAY_MSB_REG:
            Parameters_Register[ SET_SHUT_OFF_DELAY_MSB_REG ] = cmdparam;
            lvalue = Parameters_Register[ SET_SHUT_OFF_DELAY_MSB_REG ] << 24;
            Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] += lvalue;
            PWM_isr_Stop();
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 1;
            break;
        
        case SET_SHUT_OFF_DELAY_THRDB_REG:
            Parameters_Register[ SET_SHUT_OFF_DELAY_THRDB_REG ] = cmdparam;
            lvalue = Parameters_Register[ SET_SHUT_OFF_DELAY_THRDB_REG ] << 16;
            Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] += lvalue;
            PWM_isr_Stop();
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 1;
            break;
        
        case SET_SHUT_OFF_DELAY_SCNDB_REG:
            Parameters_Register[ SET_SHUT_OFF_DELAY_SCNDB_REG ] = cmdparam;
            lvalue = Parameters_Register[ SET_SHUT_OFF_DELAY_SCNDB_REG ] << 8;
            Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] += lvalue;
            PWM_isr_Stop();
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 1;
            break;
        
        case SET_SHUT_OFF_DELAY_LSB_REG:
            Parameters_Register[ SET_SHUT_OFF_DELAY_LSB_REG ] = cmdparam;
            Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] += Parameters_Register[ SET_SHUT_OFF_DELAY_LSB_REG ];
            PWM_isr_Stop();
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 1;
            break;
        
        case SET_ON_TIME_DELAY_MSB_REG:
            Parameters_Register[ SET_ON_TIME_DELAY_MSB_REG ] = cmdparam;
            lvalue = Parameters_Register[ SET_ON_TIME_DELAY_MSB_REG ] << 24;
            Parameters_Register[ SET_ON_TIME_REG ] += lvalue;
            PWM_isr_Stop();
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 1;
            break;
        
        case SET_ON_TIME_DELAY_THRDB_REG:
            Parameters_Register[ SET_ON_TIME_DELAY_THRDB_REG ] = cmdparam;
            lvalue = Parameters_Register[ SET_ON_TIME_DELAY_THRDB_REG ] << 16;
            Parameters_Register[ SET_ON_TIME_REG ] += lvalue;
            PWM_isr_Stop();
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 1;
            break;
        
        case SET_ON_TIME_DELAY_SCNDB_REG:
            Parameters_Register[ SET_ON_TIME_DELAY_SCNDB_REG ] = cmdparam;
            lvalue = Parameters_Register[ SET_ON_TIME_DELAY_SCNDB_REG ] << 8;
            Parameters_Register[ SET_ON_TIME_REG ] += lvalue;
            PWM_isr_Stop();
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 1;
            break;
        
        case SET_ON_TIME_DELAY_LSB_REG:
            Parameters_Register[ SET_ON_TIME_DELAY_LSB_REG ] = cmdparam;
            Parameters_Register[ SET_ON_TIME_REG ] += Parameters_Register[ SET_ON_TIME_DELAY_LSB_REG ];
            PWM_isr_Stop();
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 1;
            break;
        
        case SET_OFF_TIME_DELAY_MSB_REG:
            Parameters_Register[ SET_OFF_TIME_DELAY_MSB_REG ] = cmdparam;
            lvalue = Parameters_Register[ SET_OFF_TIME_DELAY_MSB_REG ] << 24;
            Parameters_Register[ SET_OFF_TIME_REG ] += lvalue;
            PWM_isr_Stop();
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 1;
            break;
        
        case SET_OFF_TIME_DELAY_THRDB_REG:
            Parameters_Register[ SET_OFF_TIME_DELAY_THRDB_REG ] = cmdparam;
            lvalue = Parameters_Register[ SET_OFF_TIME_DELAY_MSB_REG ] << 16;
            Parameters_Register[ SET_OFF_TIME_REG ] += lvalue;
            PWM_isr_Stop();
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 1;
            break;
        
        case SET_OFF_TIME_DELAY_SCNDB_REG:
            Parameters_Register[ SET_OFF_TIME_DELAY_SCNDB_REG ] = cmdparam;
            lvalue = Parameters_Register[ SET_OFF_TIME_DELAY_SCNDB_REG ] << 8;
            Parameters_Register[ SET_OFF_TIME_REG ] += lvalue;
            PWM_isr_Stop();
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 1;
            break;
            
        case SET_OFF_TIME_DELAY_LSB_REG:
            Parameters_Register[ SET_OFF_TIME_DELAY_LSB_REG ] = cmdparam;
            Parameters_Register[ SET_OFF_TIME_REG ] += cmdparam;
            PWM_isr_Stop();
            Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 1;
        
        case SET_DEVICE_ADDRESS_REG:
            Parameters_Register[ SET_DEVICE_ADDRESS_REG ] = cmdparam;
            break;
            
        case STS_CMD_BUTTON_EVENT:
            status = Parameters_Register[ STS_CMD_BUTTON_EVENT ];
            break;

        default:
            status = STS_CMD_FAIL;
            break;
    }

    return (status);
}
//#else
#endif

/*******************************************************************************
* Function Name: GetTimeBitsValue
********************************************************************************
* Summary:
*  Reads the time bits to calculate the delay before shut-off.
*
* Parameters:
*  None.
*
* Return:
*  Returns the hex value of the time bits inputs with mode input as MSB
*
*******************************************************************************/
#if( IC_PACKAGE == SOIC_16 )
uint8 GetTimeBitsValue( void )
{
    uint8 lTime = 0;
   
    if( Time_Bit_0_Read() == 1 )
    {
        lTime += pow( 2 , 0 );
    }
    else
    {
        lTime += 0;
    }
    
    if( Time_Bit_1_Read() == 1 )
    {
        lTime += pow( 2 , 1 );
    }
    else
    {
        lTime += 0;
    }
    
    if( Time_Bit_2_Read() == 1 )
    {
        lTime += pow( 2 , 2 );
    }
    else
    {
        lTime += 0;
    }
    
    if( Time_Bit_3_Read() == 1 )
    {
        lTime += pow( 2 , 3 );
    }
    else
    {
        lTime += 0;
    }
    
    if( Mode_Read() == 1 )
    {
        lTime += pow( 2 , 4 );
    }
    else
    {
        lTime += 0;
    }
    
    return lTime;
}
//#else
#endif

/*******************************************************************************
* Function Name: SetLookUpTable
********************************************************************************
* Summary:
*  Sets the Look-Up Table according to the mode and time bits inputs.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
#if( IC_PACKAGE == SOIC_16 )
void  SetLookUpTable( void )
{
    uint8 lmode_bit = 0;
    
    lmode_bit = GetTimeBitsValue();
    lmode_bit = lmode_bit & 0x10;
    lmode_bit = lmode_bit >> 4;
    
    switch (lmode_bit)
    {
        /*  Mode bit is not set so we're in Shut-Off Mode */
        case 0x00:
        ON_Time_Look_Up_Table[ 0 ] =    0x0000000A;
        ON_Time_Look_Up_Table[ 1 ] =    0x0000001E;
        ON_Time_Look_Up_Table[ 2 ] =    0x0000003C;
        ON_Time_Look_Up_Table[ 3 ] =    0x00000078;
        ON_Time_Look_Up_Table[ 4 ] =    0x000000F0;
        ON_Time_Look_Up_Table[ 5 ] =    0x000001E0;
        ON_Time_Look_Up_Table[ 6 ] =    0x00000384;
        ON_Time_Look_Up_Table[ 7 ] =    0x00000708;
        ON_Time_Look_Up_Table[ 8 ] =    0x00000E10;
        ON_Time_Look_Up_Table[ 9 ] =    0x00001C20;
        ON_Time_Look_Up_Table[ 10 ] =   0x00002A30;
        ON_Time_Look_Up_Table[ 11 ] =   0x00003840;
        ON_Time_Look_Up_Table[ 12 ] =   0x00005460;
        ON_Time_Look_Up_Table[ 13 ] =   0x00007080;
        ON_Time_Look_Up_Table[ 14 ] =   0x0000A8C0;
        ON_Time_Look_Up_Table[ 15 ] =   0x0000FD20;
        
        OFF_Time_Look_Up_Table[ 0 ] =   0x00000000;
        OFF_Time_Look_Up_Table[ 1 ] =   0x00000000;
        OFF_Time_Look_Up_Table[ 2 ] =   0x00000000;
        OFF_Time_Look_Up_Table[ 3 ] =   0x00000000;
        OFF_Time_Look_Up_Table[ 4 ] =   0x00000000;
        OFF_Time_Look_Up_Table[ 5 ] =   0x00000000;
        OFF_Time_Look_Up_Table[ 6 ] =   0x00000000;
        OFF_Time_Look_Up_Table[ 7 ] =   0x00000000;
        OFF_Time_Look_Up_Table[ 8 ] =   0x00000000;
        OFF_Time_Look_Up_Table[ 9 ] =   0x00000000;
        OFF_Time_Look_Up_Table[ 10 ] =  0x00000000;
        OFF_Time_Look_Up_Table[ 11 ] =  0x00000000;
        OFF_Time_Look_Up_Table[ 12 ] =  0x00000000;
        OFF_Time_Look_Up_Table[ 13 ] =  0x00000000;
        OFF_Time_Look_Up_Table[ 14 ] =  0x00000000;
        OFF_Time_Look_Up_Table[ 15 ] =  0x00000000;
        Parameters_Register[ SET_MODE_REG ] = SHUT_OFF;
        break;
        
        /*  Mode bit is set so we're in Toggle Mode */
        case 0x01:
        ON_Time_Look_Up_Table[ 0 ] =    0x00000001;
        ON_Time_Look_Up_Table[ 1 ] =    0x00000001;
        ON_Time_Look_Up_Table[ 2 ] =    0x00000005;
        ON_Time_Look_Up_Table[ 3 ] =    0x0000000A;
        ON_Time_Look_Up_Table[ 4 ] =    0x0000000A;
        ON_Time_Look_Up_Table[ 5 ] =    0x0000000A;
        ON_Time_Look_Up_Table[ 6 ] =    0x0000000A;
        ON_Time_Look_Up_Table[ 7 ] =    0x0000000A;
        ON_Time_Look_Up_Table[ 8 ] =    0x0000000A;
        ON_Time_Look_Up_Table[ 9 ] =    0x0000000A;
        ON_Time_Look_Up_Table[ 10 ] =   0x0000001E;
        ON_Time_Look_Up_Table[ 11 ] =   0x0000003C;
        ON_Time_Look_Up_Table[ 12 ] =   0x0000003C;
        ON_Time_Look_Up_Table[ 13 ] =   0x0000003C;
        ON_Time_Look_Up_Table[ 14 ] =   0x000000F0;
        ON_Time_Look_Up_Table[ 15 ] =   0x000000F0;
        
        OFF_Time_Look_Up_Table[ 0 ] =   0x00000001;
        OFF_Time_Look_Up_Table[ 1 ] =   0x0000000A;
        OFF_Time_Look_Up_Table[ 2 ] =   0x0000012C;
        OFF_Time_Look_Up_Table[ 3 ] =   0x0000003C;
        OFF_Time_Look_Up_Table[ 4 ] =   0x00000708;
        OFF_Time_Look_Up_Table[ 5 ] =   0x00000E10;
        OFF_Time_Look_Up_Table[ 6 ] =   0x00001C20;
        OFF_Time_Look_Up_Table[ 7 ] =   0x00003840;
        OFF_Time_Look_Up_Table[ 8 ] =   0x00005460;
        OFF_Time_Look_Up_Table[ 9 ] =   0x0000A8C0;
        OFF_Time_Look_Up_Table[ 10 ] =  0x00000384;
        OFF_Time_Look_Up_Table[ 11 ] =  0x00000E10;
        OFF_Time_Look_Up_Table[ 12 ] =  0x00003840;
        OFF_Time_Look_Up_Table[ 13 ] =  0x0000A8C0;
        OFF_Time_Look_Up_Table[ 14 ] =  0x00000E10;
        OFF_Time_Look_Up_Table[ 15 ] =  0x00003840;
        Parameters_Register[ SET_MODE_REG ] = TOGGLE;
        break;
    }
}
//#else
#endif

/*******************************************************************************
* Function Name: SetTimerSettings
********************************************************************************
* Summary:
*  Sets the timer parameters according to time bits and mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
#if( IC_PACKAGE == SOIC_16 )
void  SetTimerSettings( void )
{
    //uint8 lAddress = 0;
    
    /* Reading the time bits and masking the mode input */
    Parameters_Register[ LOOK_UP_TABLE_ADDRESS_REG ] = GetTimeBitsValue();
    Parameters_Register[ LOOK_UP_TABLE_ADDRESS_REG ] = Parameters_Register[ LOOK_UP_TABLE_ADDRESS_REG ] & 0x0F;
    
    /* Setting the Look-Up Table properly */
    SetLookUpTable();
    
    /* Setting ON-time and OFF-time accordingly */
    if( Parameters_Register[ SET_MODE_REG ] == SHUT_OFF )
    {
        Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] = ON_Time_Look_Up_Table[ Parameters_Register[ LOOK_UP_TABLE_ADDRESS_REG ] ] * OVERFLOW_PER_SECOND;
        Parameters_Register[ SET_ON_TIME_REG ] = Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ];
        #if( COMMUNICATION_LAYER == SERIAL_MODE )  
        SW_Tx_UART_PutString("---Time to shut-OFF: ");
//        SW_Tx_UART_PutHexInt( ON_Time >> 16 );
        SW_Tx_UART_PutHexInt( ( Parameters_Register[ SET_ON_TIME_REG ] / OVERFLOW_PER_SECOND ) );
        SW_Tx_UART_PutCRLF();
        //#else
        #endif
    }
    else
    {
        Parameters_Register[ SET_ON_TIME_REG ] = ON_Time_Look_Up_Table[ Parameters_Register[ LOOK_UP_TABLE_ADDRESS_REG ] ] * OVERFLOW_PER_SECOND;
        Parameters_Register[ SET_OFF_TIME_REG ] = OFF_Time_Look_Up_Table[ Parameters_Register[ LOOK_UP_TABLE_ADDRESS_REG ] ] * OVERFLOW_PER_SECOND;
        Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] = Parameters_Register[ SET_ON_TIME_REG ];
        #if( COMMUNICATION_LAYER == SERIAL_MODE )
        SW_Tx_UART_PutString("---Toggle On time: ");
        SW_Tx_UART_PutHexInt( ( Parameters_Register[ SET_ON_TIME_REG ] / OVERFLOW_PER_SECOND ) );
        SW_Tx_UART_PutString(";");
        SW_Tx_UART_PutString("Toggle OFF time: ");
        SW_Tx_UART_PutHexInt( ( Parameters_Register[ SET_OFF_TIME_REG ] / OVERFLOW_PER_SECOND ) );
        SW_Tx_UART_PutCRLF();
        //#else
        #endif
    }
}
//#else
#endif

/*******************************************************************************
* Function Name: SetDefaultRegisterValues
********************************************************************************
* Summary:
*  Sets the default values in the register table
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SetDefaultRegisterValues( void )
{
    Parameters_Register[ SET_PEN_REG ] = ASSERTED_LOW;
    Parameters_Register[ SET_PWM_OUT_REG ] = 0x00u;
    Parameters_Register[ SET_MODE_REG ] = SHUT_OFF;
    Parameters_Register[ SET_SHUT_OFF_DELAY_MSB_REG ] = 0x00u;
    Parameters_Register[ SET_SHUT_OFF_DELAY_THRDB_REG ] = 0x00u;
    Parameters_Register[ SET_SHUT_OFF_DELAY_SCNDB_REG ] = 0x00u;
    Parameters_Register[ SET_SHUT_OFF_DELAY_LSB_REG ] = 0x00u;
    Parameters_Register[ SET_ON_TIME_DELAY_MSB_REG ] = 0x00u;
    Parameters_Register[ SET_ON_TIME_DELAY_THRDB_REG ] = 0x00u;
    Parameters_Register[ SET_ON_TIME_DELAY_SCNDB_REG ] = 0x00u;
    Parameters_Register[ SET_ON_TIME_DELAY_LSB_REG ] = 0x00u;
    Parameters_Register[ SET_OFF_TIME_DELAY_MSB_REG ] = 0x00u;
    Parameters_Register[ SET_OFF_TIME_DELAY_THRDB_REG ] = 0x00u;
    Parameters_Register[ SET_OFF_TIME_DELAY_SCNDB_REG ] = 0x00u;
    Parameters_Register[ SET_OFF_TIME_DELAY_LSB_REG ] = 0x00u;
    Parameters_Register[ SET_DEVICE_ADDRESS_REG ] = 0x08u;
    Parameters_Register[ SET_DELAY_BEFORE_SHUT_OFF_REG ] = 0xFFFFFFFFu;
    Parameters_Register[ SET_ON_TIME_REG ] = 0x00u;
    Parameters_Register[ SET_OFF_TIME_REG ] = 0x00u;
    Parameters_Register[ TOGGLE_COUNTER_REG ] = 0x00u;
    Parameters_Register[ PUSH_BUTTON_STATE_VALUE_REG ] = 0x00u;
    Parameters_Register[ SECOND_IN_BASE_60_REG ] = 0x00u;
    Parameters_Register[ PUSH_BUTTON_INTERRUPT_FLAG_REG ] = 0x00u;
    Parameters_Register[ LOOK_UP_TABLE_ADDRESS_REG ] = 0x00u;
    Parameters_Register[ OVERFLOW_COUNTER_REG ] = 0x00u;
    Parameters_Register[ PUSH_BUTTON_EVENT_REG ] = BUTTON_NO_EVENT;
    Parameters_Register[ FIRMWARE_VERSION_REG ] = FIRMWARE_VERSION;
}


/* [] END OF FILE */
