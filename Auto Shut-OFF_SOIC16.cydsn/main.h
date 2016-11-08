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
#define HIGH                            (1u)
#define LOW                             (0u)
#define DEFAULT_TIMEOUT                 (0x2EE0u)        // 1 minute default timeout value
#define LOW_GLOW                        (0x3A98u)        // Low intensity LED glow - ¼ of 60000
#define MID_GLOW                        (0x7530u)        // High intensity LED glow - ½ of 60000
#define HIGH_GLOW                       (0xEA60u)        // Highest intensity LED glow - 60000
#define SECOND_COUNT                    (0xC8u)          // Interrupt counter for 1 second
#define MINUTE_COUNT                    (0x2EE0u)        // Interrupt counter for 1 minute
#define OVERFLOW_PER_SECOND             (0xC8u)

/* I2C Defines */
#define BUFFER_SIZE                     (0x04u)
#define PACKET_SIZE                     (BUFFER_SIZE)
#define PACKET_SOP_POS                  (0x00u)
#define PACKET_CMD_POS                  (0x01u)
#define PACKET_PARAM_POS                (0x02u)
#define PACKET_STS_POS                  (PACKET_CMD_POS)
#define PACKET_EOP_POS                  (0x03u)
#define PACKET_SOP                      (0x01u)
#define PACKET_EOP                      (0x17u)
#define STS_CMD_DONE                    (0x00u)
#define STS_CMD_FAIL                    (0xFFu)
#define STS_CMD_BUTTON_EVENT            (0x10u)
#define CMD_SET_OUPUT_ON                (0x00u)
#define CMD_SET_OUTPUT_OFF              (0x01u)
#define CMD_SET_MODE                    (0x02u)
#define CMD_SET_SHUT_OFF_DELAY_MSB      (0x03u)
#define CMD_SET_SHUT_OFF_DELAY_THRDB    (0x04u)
#define CMD_SET_SHUT_OFF_DELAY_SCNDB    (0x05u)
#define CMD_SET_SHUT_OFF_DELAY_LSB      (0x06u)
#define CMD_SET_ON_TIME_DELAY_MSB       (0x07u)
#define CMD_SET_ON_TIME_DELAY_THRDB     (0x08u)
#define CMD_SET_ON_TIME_DELAY_SCNDB     (0x09u)
#define CMD_SET_ON_TIME_DELAY_LSB       (0x0Au)
#define CMD_SET_OFF_TIME_DELAY_MSB      (0x0Bu)
#define CMD_SET_OFF_TIME_DELAY_THRDB    (0x0Cu)
#define CMD_SET_OFF_TIME_DELAY_SCNDB    (0x0Du)
#define CMD_SET_OFF_TIME_DELAY_LSB      (0x0Eu)
#define CMD_SET_DEVICE_ADDRESS          (0x0Fu)

/***************************************
*         Global Variables
****************************************/
uint32  DelayBeforeShutOff;                           // The timeout value for Supply Enable output shutdown
uint32  ON_Time;
uint32  OFF_Time;
uint8   RESET_TIMEOUT_FLAG;                         // The reset timeout flag set in ON_OFF_INPUT_INTERRUPT
uint8   ON_OFF_Input_Value;             
uint8   Second_Counter;
uint8   Mode;
uint8   Second_in_Base_60;
uint8   Push_Button_Interrupt_Flag;
uint8   UART_TX_Flag;
uint8   UART_Buffer[ 32 ];
uint8   UART_Tx_Size;
uint8   I2C_Status;

/***************************************
*        Functions Prototypes
****************************************/
CY_ISR_PROTO(PWM_isr);
CY_ISR_PROTO(Push_Button_isr);
uint8 ExecuteI2CCommand( uint32 cmd, uint8 cmdparam );

/* [] END OF FILE */
