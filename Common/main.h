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
/***************************************
*            Includes
****************************************/
#include <project.h>

/***************************************
*            Defines
****************************************/
#define HIGH                            (1u)                // High value
#define LOW                             (0u)                // Low Value
#define DEFAULT_TIMEOUT                 (0x2EE0u)           // 1 minute default timeout value
#define LOW_GLOW                        (0x3A98u)           // Low intensity LED glow - ¼ of 60000
#define MID_GLOW                        (0x7530u)           // High intensity LED glow - ½ of 60000
#define HIGH_GLOW                       (0xEA60u)           // Highest intensity LED glow - 60000
#define SECOND_COUNT                    (0xC8u)             // Interrupt counter for 1 second
#define MINUTE_COUNT                    (0x2EE0u)           // Interrupt counter for 1 minute
#define OVERFLOW_PER_SECOND             (0xC8u)             // 200 PWM Timer Overlfow per second
#define SOIC_8                          (0x08U)             // The SOIC-8 IC Package Define
#define SOIC_16                         (0x16U)             // The SOIC-16 IC Package Define
#define SERIAL_MODE                     (0x0Au)             // The serial TX communication layer 
#define I2C_MODE                        (0x0Bu)             // The I2C communication layer

/* Those defines must be commented/uncommented accordingly prior to building the project */
/* The used communication layer */
/* Uncomment the line according to the enabled layer in the schematic */
#define COMMUNICATION_LAYER             (SERIAL_MODE)
//#define COMMUNICATION_LAYER             (I2C_MODE)

/* The used IC Package */
/* Uncomment the line according to the device selected in the device selector */
//#define IC_PACKAGE                      (SOIC_8)
#define IC_PACKAGE                      (SOIC_16)

/* I2C Defines */
#define BUFFER_SIZE                     (0x04u)             // The packet buffer size
#define PACKET_SIZE                     (BUFFER_SIZE)       // The packet size
#define PACKET_SOP_POS                  (0x00u)             // The Start of Packet position in the buffer
#define PACKET_CMD_POS                  (0x01u)             // The Command position in the buffer
#define PACKET_PARAM_POS                (0x02u)             // The command parameter position in the buffer
#define PACKET_STS_POS                  (PACKET_CMD_POS)    // The status position in the buffer
#define PACKET_EOP_POS                  (0x03u)             // The End of Packet in the buffer
#define PACKET_SOP                      (0x01u)             // The Start of Packet Value
#define PACKET_EOP                      (0x17u)             // The End of Packet Value
#define STS_CMD_DONE                    (0x00u)             // Status: Command Done
#define STS_CMD_FAIL                    (0xFFu)             // Status: Command Failed
#define STS_CMD_BUTTON_EVENT            (0x10u)             // Status: Push Button Event
#define CMD_SET_OUPUT_ON                (0x00u)             // Command: Set output enabled HIGH
#define CMD_SET_OUTPUT_OFF              (0x01u)             // Command: Set output enabled LOW
#define CMD_SET_MODE                    (0x02u)             // Command: Set the operating mode
#define CMD_SET_SHUT_OFF_DELAY_MSB      (0x03u)             // Command: Set the Shut-OFF delay MSB
#define CMD_SET_SHUT_OFF_DELAY_THRDB    (0x04u)             // Command: Set the Shut-OFF delay third byte
#define CMD_SET_SHUT_OFF_DELAY_SCNDB    (0x05u)             // Command: Set the Shut-OFF delay second byte
#define CMD_SET_SHUT_OFF_DELAY_LSB      (0x06u)             // Command: Set the Shut-OFF delay LSB
#define CMD_SET_ON_TIME_DELAY_MSB       (0x07u)             // Command: Set the ON Time delay MSB    
#define CMD_SET_ON_TIME_DELAY_THRDB     (0x08u)             // Command: Set the ON Time delay third byte
#define CMD_SET_ON_TIME_DELAY_SCNDB     (0x09u)             // Command: Set the ON Time delay second byte
#define CMD_SET_ON_TIME_DELAY_LSB       (0x0Au)             // Command: Set the ON Time delay LSB
#define CMD_SET_OFF_TIME_DELAY_MSB      (0x0Bu)             // Command: Set the OFF Time delay MSB
#define CMD_SET_OFF_TIME_DELAY_THRDB    (0x0Cu)             // Command: Set the OFF Time delay third byte
#define CMD_SET_OFF_TIME_DELAY_SCNDB    (0x0Du)             // Command: Set the OFF Time delay second byte    
#define CMD_SET_OFF_TIME_DELAY_LSB      (0x0Eu)             // Command: Set the OFF Time delay LSB
#define CMD_SET_DEVICE_ADDRESS          (0x0Fu)             // Command: Set device address

/***************************************
*         Global Variables
****************************************/
uint32  DelayBeforeShutOff;                                 // The timeout value variable
uint32  ON_Time;                                            // The toggle mode ON Time variable
uint32  OFF_Time;                                           // The toggle mode OFF Time variable
uint8   Push_Button_State_Value;                            // The push button state value             
uint8   Second_Counter;                                     // The second counter
uint8   Mode;                                               // The operating mode
uint8   Second_in_Base_60;                                  // The second in base 60 for serial output
uint8   Push_Button_Interrupt_Flag;                         // The push button interrupt occurance flag
#if( IC_PACKAGE == SOIC_16 )
uint32  Time_Bits_Look_Up_Table_Row[ 32 ];                  // The Look-Up Table Row for timer settings when using time bits inputs
uint32  Time_Bits_Look_Up_Table_Col[ 32 ];                  // The Look-Up Table Column for timer settings when using time bits inputs
#else
#endif

#if( COMMUNICATION_LAYER == I2C_MODE )
/* I2C slave read and write buffers */
    uint8 i2cReadBuffer [BUFFER_SIZE] = {PACKET_SOP, STS_CMD_FAIL, STS_CMD_FAIL, PACKET_EOP};
    uint8 i2cWriteBuffer[BUFFER_SIZE];
    uint8 I2C_Status;
#else
    uint8   UART_TX_Flag;
    uint8   UART_Buffer[ 32 ];
    uint8   UART_Tx_Size;
#endif 

/***************************************
*        Functions Prototypes
****************************************/
CY_ISR_PROTO(PWM_isr);
CY_ISR_PROTO(Push_Button_isr);
#if( COMMUNICATION_LAYER == I2C_MODE )
    uint8 ExecuteI2CCommand( uint32 cmd, uint8 cmdparam );
#else
#endif    

#if( IC_PACKAGE == SOIC_16 )
uint8 GetTimeBitsValue( void );
#else
#endif

/***************************************
*        Time Bits Look-Up Table
****************************************/



/* [] END OF FILE */
