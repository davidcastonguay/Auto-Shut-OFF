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
#define FIRMWARE_VERSION                (0x0003)            // The firmware version
#define HIGH                            (1u)                // High value
#define LOW                             (0u)                // Low Value
#define ASSERTED_HIGH                   (0u)                // Asserted High value for P-Channel MOSFET
#define ASSERTED_LOW                    (1u)                // Asserted Low value for P-Channel MOSFET
#define LED_ON                          (0u)
#define LED_OFF                         (1u)
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
#define SHUT_OFF                        (0x00u)             // The shut-off operating mode
#define TOGGLE                          (0x01u)             // The toggle operating mode
#define SLEEP_PIN_MODE                  (0x00u)             // The Sleep I/O configuration
#define AWAKEN_PIN_MODE                 (0x01u)             // The Awaken I/O configuration

/* Those defines must be commented/uncommented accordingly prior to building the project */
/* The used communication layer */
/* Uncomment the line according to the enabled layer in the schematic */
#define COMMUNICATION_LAYER             (SERIAL_MODE)
//#define COMMUNICATION_LAYER             (I2C_MODE)
//#define COMMUNICATION_LAYER             (0x00u)

/* The used IC Package */
/* Uncomment the line according to the device selected in the device selector */
//#define IC_PACKAGE                      (SOIC_8)
#define IC_PACKAGE                      (SOIC_16)

/* I2C Defines */
#define BUFFER_SIZE                     (0x02u)             // The packet buffer size
#define PACKET_SIZE                     (BUFFER_SIZE)       // The packet size
#define PACKET_CMD_POS                  (0x00u)             // The Command position in the buffer
#define PACKET_PARAM_POS                (0x01u)             // The command parameter position in the buffer
#define PACKET_STS_POS                  (PACKET_PARAM_POS)    // The status position in the buffer
#define STS_CMD_DONE                    (0x00u)             // Status: Command Done
#define STS_CMD_FAIL                    (0xFFu)             // Status: Command Failed
#define STS_CMD_BUTTON_EVENT            (0x10u)             // Status: Push Button Event

/* Registers Address Defines */
#define SET_PEN_REG                     (0x00u)             // Command: Set output enabled LOW power Enabled output HIGH
#define SET_PWM_OUT_REG                 (0x01u)             // Command: Set the direction for PWM output
#define SET_MODE_REG                    (0x02u)             // Command: Set the operating mode
#define SET_SHUT_OFF_DELAY_MSB_REG      (0x03u)             // Command: Set the Shut-OFF delay MSB
#define SET_SHUT_OFF_DELAY_THRDB_REG    (0x04u)             // Command: Set the Shut-OFF delay third byte
#define SET_SHUT_OFF_DELAY_SCNDB_REG    (0x05u)             // Command: Set the Shut-OFF delay second byte
#define SET_SHUT_OFF_DELAY_LSB_REG      (0x06u)             // Command: Set the Shut-OFF delay LSB
#define SET_ON_TIME_DELAY_MSB_REG       (0x07u)             // Command: Set the ON Time delay MSB    
#define SET_ON_TIME_DELAY_THRDB_REG     (0x08u)             // Command: Set the ON Time delay third byte
#define SET_ON_TIME_DELAY_SCNDB_REG     (0x09u)             // Command: Set the ON Time delay second byte
#define SET_ON_TIME_DELAY_LSB_REG       (0x0Au)             // Command: Set the ON Time delay LSB
#define SET_OFF_TIME_DELAY_MSB_REG      (0x0Bu)             // Command: Set the OFF Time delay MSB
#define SET_OFF_TIME_DELAY_THRDB_REG    (0x0Cu)             // Command: Set the OFF Time delay third byte
#define SET_OFF_TIME_DELAY_SCNDB_REG    (0x0Du)             // Command: Set the OFF Time delay second byte    
#define SET_OFF_TIME_DELAY_LSB_REG      (0x0Eu)             // Command: Set the OFF Time delay LSB
#define SET_DEVICE_ADDRESS_REG          (0x0Fu)             // Register: Device address
#define SET_DELAY_BEFORE_SHUT_OFF_REG   (0x10u)             // Register: Delay before shut-off
#define SET_ON_TIME_REG                 (0x11u)             // Register: ON Time 
#define SET_OFF_TIME_REG                (0x12u)             // Register: OFF Time 
#define TOGGLE_COUNTER_REG              (0x13u)             // Register: Toggle counter
#define PUSH_BUTTON_STATE_VALUE_REG     (0x14u)             // Register: Push button state value
#define SECOND_COUNTER_REG              (0x15u)             // Register: Second Counter
#define SECOND_IN_BASE_60_REG           (0x17u)             // Register: Second in base 60
#define PUSH_BUTTON_INTERRUPT_FLAG_REG  (0x18u)             // Register: Push button interrupt flag
#define LOOK_UP_TABLE_ADDRESS_REG       (0x19u)             // Register: Look up table address
#define OVERFLOW_COUNTER_REG            (0x1Au)             // Register: Overflow Counter
#define PUSH_BUTTON_EVENT_REG           (0x1Bu)             // Register: Push button event
#define FIRMWARE_VERSION_REG            (0x1Cu)             // Register: The firmware version
#define SLEEP_FLAG_REG                  (0x1Du)             // Register: The sleep mode

/* Push Button Events Defines */
#define BUTTON_NO_EVENT                 (0x00u)             // Status; Push button no event
#define BUTTON_CLICK_EVENT              (0xC0u)             // Status: Push button click event
#define BUTTON_DOUBLE_CLICK_EVENT       (0xDCu)             // Status: Push button double-click event 
#define BUTTON_HOLD_DOWN                (0xBDu)             // Status: Push button hold down event
#define BUTTON_RELEASED                 (0xBEu)             // Status: Push button released event

#if( IC_PACKAGE == SOIC_16 )
uint32  ON_Time_Look_Up_Table[ 16 ];                        // The ON Time Look-Up Table for timer settings when using time bits inputs
uint32  OFF_Time_Look_Up_Table[ 16 ];                       // The OFF Time Look-Up Table for timer settings when using time bits inputs
uint32  Parameters_Register[ 32 ];                          // The parameters register
//#else
#endif

#if( COMMUNICATION_LAYER == SERIAL_MODE )
    uint8   UART_TX_Flag;
    uint8   UART_Buffer[ 32 ];
    uint8   UART_Tx_Size;
#endif 

#if( COMMUNICATION_LAYER == I2C_MODE )
/* I2C slave read and write buffers */
    uint8 i2cReadBuffer [BUFFER_SIZE] = {STS_CMD_FAIL, STS_CMD_FAIL};
    uint8 i2cWriteBuffer[BUFFER_SIZE];
    uint8 I2C_Status;
//#else
#endif

/***************************************
*        Functions Prototypes
****************************************/
CY_ISR_PROTO(PWM_isr);
CY_ISR_PROTO(Push_Button_isr);
void SetDefaultRegisterValues( void );
#if( COMMUNICATION_LAYER == I2C_MODE )
    uint8 ExecuteI2CCommand( uint32 cmd, uint8 cmdparam );
//#else
#endif    

#if( IC_PACKAGE == SOIC_16 )
void  SetPinDriveMode( uint8 pMode );
uint8 GetTimeBitsValue( void );
void  SetLookUpTable( void );
void  SetTimerSettings( void );
//#else
#endif


/* [] END OF FILE */
