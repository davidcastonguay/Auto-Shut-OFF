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
    
    PWM_Start();
    
    /* Configure ISR */
//    PWM_isr_StartEx( PWM_isr );
    Push_Button_isr_StartEx( Push_Button_isr );

    /* Variables default values */
//    SetTimerSettings();
//    Second_in_Base_60 = ( DelayBeforeShutOff / OVERFLOW_PER_SECOND );
    Push_Button_Interrupt_Flag = 0;
    DelayBeforeShutOff = -1;
    Second_Counter = 0;
    Toggle_Counter = 0;
    Output_Value = LOW;
    SUPPLY_ENABLE_Write( ASSERTED_LOW );
    PWM_WriteCompare( 0 );
    R_Write( LED_ON );
    G_Write( LED_ON );
    B_Write( LED_OFF );
    
    #if( COMMUNICATION_LAYER == SERIAL_MODE )    
        SW_Tx_UART_PutString("/// Waiting for push button to be pressed");
        SW_Tx_UART_PutCRLF();
    //#else
    #endif

    for(;;)
    {
        /* Disabling the SUPPLY ENABLE if timeout has been reached */
        if( DelayBeforeShutOff == 0 )
        {
            if( Mode == 0 )
            {
                SUPPLY_ENABLE_Write( ASSERTED_LOW ); 
                PWM_WriteCompare( LOW_GLOW );
                
                #if( COMMUNICATION_LAYER == SERIAL_MODE )    
                    SW_Tx_UART_PutString("---Countdown terminated");
                    SW_Tx_UART_PutCRLF();
                    //#else
                #endif
                
                /* Managing LED states */
                R_Write( LED_ON );
                G_Write( LED_OFF );
                B_Write( LED_OFF );
                DelayBeforeShutOff = -1;
            }
            else
            {
                SetTimerSettings();
                /* Toggling from ON to OFF */
                if( Output_Value == HIGH )
                {
                    SUPPLY_ENABLE_Write( ASSERTED_LOW );
                    DelayBeforeShutOff = OFF_Time;
                    /* Managing LED states */
                    R_Write( LED_ON );
                    G_Write( LED_ON );
                    B_Write( LED_OFF );
                    Output_Value = LOW;
                }
                /* Toggling from OFF to ON */
                else
                {
                    SUPPLY_ENABLE_Write( ASSERTED_HIGH );
                    DelayBeforeShutOff = ON_Time;
                    /* Managing LED states */
                    R_Write( LED_OFF );
                    G_Write( LED_ON );
                    B_Write( LED_OFF );
                    Output_Value = HIGH;
                    Toggle_Counter++;
                }
                
//                SetTimerSettings();
                Second_in_Base_60 = ( DelayBeforeShutOff / OVERFLOW_PER_SECOND );
                PWM_isr_StartEx(PWM_isr);
                PWM_ClearInterrupt(PWM_INTR_MASK_TC);
            }
        }
        else
        {
            if( PWM_isr_GetState() == 1 )
            {
                /* Toggling PWM Compare value depending on second counter value */
                if( Second_Counter < ( SECOND_COUNT / 2 ) )
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
        if( Overflow_Counter >= 200 )
        {
            if( ( Push_Button_Event == BUTTON_HOLD_DOWN ) && ( Push_Button_State_Value == 1 ) )
            {
                Push_Button_Event = BUTTON_RELEASED;
                SW_Tx_UART_PutString("+++Push Button Event: Released");
                SW_Tx_UART_PutCRLF();
            }
            else if( ( Push_Button_Interrupt_Flag == 1 ) && ( Push_Button_State_Value == 1 ) )
            {
                Push_Button_Event = BUTTON_CLICK_EVENT;
                SW_Tx_UART_PutString("+++Push Button Event: Click");
                SW_Tx_UART_PutCRLF();
            }
            else if( ( Push_Button_Interrupt_Flag >= 2 ) && ( Push_Button_State_Value == 1 ) )
            {
                Push_Button_Event = BUTTON_DOUBLE_CLICK_EVENT;
                SW_Tx_UART_PutString("+++Push Button Event: Double Click");
                SW_Tx_UART_PutCRLF();
            }
            else if( ( Push_Button_Interrupt_Flag == 1 ) && ( Push_Button_State_Value == 0 ) )
            {
                Push_Button_Event = BUTTON_HOLD_DOWN;
                SW_Tx_UART_PutString("+++Push Button Event: Hold Down");
                SW_Tx_UART_PutCRLF();
            }
            else
            {
                /* Continue */
//                Push_Button_Event = BUTTON_NO_EVENT;
//                SW_Tx_UART_PutString("+++Push Button Event: Click");
//                SW_Tx_UART_PutCRLF();
            }
            
            Overflow_Counter = 0;
            Push_Button_Interrupt_Flag = 0;
        }
        else
        {
            /* Continue */
        }
        
        /* Check if push button has been toggled */
        if( ( Push_Button_Interrupt_Flag == 1 ) && ( PWM_isr_GetState() == 0 ) )
        {
            #if( COMMUNICATION_LAYER == SERIAL_MODE )    
                SW_Tx_UART_PutString("/// Countdown to extinction");
                SW_Tx_UART_PutCRLF();
                //#else
            #endif
            
            /* Activating the output */
            SUPPLY_ENABLE_Write( ASSERTED_HIGH ); 
            
            /* Clearing the pushbutton interrupt flag */
            Push_Button_Interrupt_Flag = 0;
            
            /* Resetting the counter if timeout occured */
            SetTimerSettings();
            Second_in_Base_60 = ( DelayBeforeShutOff / OVERFLOW_PER_SECOND );
            Second_Counter = 0;
            Toggle_Counter = 0;
            Output_Value = HIGH;
  
            /* Restarting the interrupt if it has been stopped */
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
                if( Mode == 0 )
                {
                    SW_Tx_UART_PutString("Shutt-off;");
                }
                else
                {
                    SW_Tx_UART_PutString("Toggle;");
//                    SW_Tx_UART_PutCRLF();
                    SW_Tx_UART_PutString("Toggle Count: ");
                    SW_Tx_UART_PutHexInt( Toggle_Counter >> 16 );
                    SW_Tx_UART_PutHexInt( Toggle_Counter );
                    SW_Tx_UART_PutString(";");
                }
//                SW_Tx_UART_PutCRLF();
                SW_Tx_UART_PutString("Look-Up Table Address: ");
                SW_Tx_UART_PutHexInt( Look_Up_Table_Address );
                SW_Tx_UART_PutString(";");
//                SW_Tx_UART_PutCRLF();
                SW_Tx_UART_PutString("Seconds remaning: ");
                SW_Tx_UART_PutHexInt( Second_in_Base_60 );
                SW_Tx_UART_PutString(";");
//                SW_Tx_UART_PutCRLF();
                
                if( Output_Value == HIGH )
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
                I2C_Status = STS_CMD_FAIL;
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
    if( DelayBeforeShutOff <= 1 )
    {
        DelayBeforeShutOff = 0;
        Second_in_Base_60 = 0;
        Push_Button_Interrupt_Flag = 0;
        PWM_isr_Stop();
    }
    else
    {
        DelayBeforeShutOff--;
    }
    
    /* Second in base 60 timer */
    if( Second_Counter == SECOND_COUNT )
    {
        Second_Counter = 0;
        Second_in_Base_60--;
        #if( COMMUNICATION_LAYER == SERIAL_MODE )
            UART_TX_Flag = 1;
        //#else
        #endif
    }
    else
    {
        Second_Counter++;
    }
    
    /* Incrementing the overflow counter for button processor */
    if( Overflow_Counter > 200 )
    {
        Overflow_Counter = 0;
    }
    else
    {
        Overflow_Counter++;
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
        Push_Button_State_Value = 0;
        Push_Button_Interrupt_Flag++;
    }
    else
    {
        Push_Button_State_Value = 1;
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
            I2C_I2CSlaveSetAddress( cmdparam );
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
        ON_Time_Look_Up_Table[ 15 ] =   0x0009C720;
        
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
        Mode = 0;
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
        Mode = 1;
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
    Look_Up_Table_Address = GetTimeBitsValue();
    Look_Up_Table_Address = Look_Up_Table_Address & 0x0F;
    
    /* Setting the Look-Up Table properly */
    SetLookUpTable();
    
    /* Setting ON-time and OFF-time accordingly */
    if( Mode == 0 )
    {
        DelayBeforeShutOff = ON_Time_Look_Up_Table[ Look_Up_Table_Address ] * OVERFLOW_PER_SECOND;
        ON_Time = DelayBeforeShutOff;
        #if( COMMUNICATION_LAYER == SERIAL_MODE )  
        SW_Tx_UART_PutString("---Time to shut-OFF: ");
//        SW_Tx_UART_PutHexInt( ON_Time >> 16 );
        SW_Tx_UART_PutHexInt( ( ON_Time / OVERFLOW_PER_SECOND ) );
        SW_Tx_UART_PutCRLF();
        //#else
        #endif
    }
    else
    {
        ON_Time = ON_Time_Look_Up_Table[ Look_Up_Table_Address ] * OVERFLOW_PER_SECOND;
        OFF_Time = OFF_Time_Look_Up_Table[ Look_Up_Table_Address ] * OVERFLOW_PER_SECOND;
        DelayBeforeShutOff = ON_Time;
        #if( COMMUNICATION_LAYER == SERIAL_MODE )
        SW_Tx_UART_PutString("---Toggle On time: ");
//        SW_Tx_UART_PutHexInt( ON_Time >> 16 );
        SW_Tx_UART_PutHexInt( ( ON_Time / OVERFLOW_PER_SECOND ) );
        SW_Tx_UART_PutString(";");
        SW_Tx_UART_PutString("Toggle OFF time: ");
//        SW_Tx_UART_PutHexInt( OFF_Time >> 16 );
        SW_Tx_UART_PutHexInt( ( OFF_Time / OVERFLOW_PER_SECOND ) );
        SW_Tx_UART_PutCRLF();
        //#else
        #endif
    }
}
//#else
#endif


/* [] END OF FILE */
