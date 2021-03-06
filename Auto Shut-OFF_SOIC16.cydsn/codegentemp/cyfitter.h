#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include "cydevice_trm.h"

/* B */
#define B__0__DR CYREG_GPIO_PRT1_DR
#define B__0__DR_CLR CYREG_GPIO_PRT1_DR_CLR
#define B__0__DR_INV CYREG_GPIO_PRT1_DR_INV
#define B__0__DR_SET CYREG_GPIO_PRT1_DR_SET
#define B__0__HSIOM CYREG_HSIOM_PORT_SEL1
#define B__0__HSIOM_MASK 0x0000F000u
#define B__0__HSIOM_SHIFT 12u
#define B__0__INTCFG CYREG_GPIO_PRT1_INTR_CFG
#define B__0__INTR CYREG_GPIO_PRT1_INTR
#define B__0__INTR_CFG CYREG_GPIO_PRT1_INTR_CFG
#define B__0__INTSTAT CYREG_GPIO_PRT1_INTR
#define B__0__MASK 0x08u
#define B__0__PC CYREG_GPIO_PRT1_PC
#define B__0__PC2 CYREG_GPIO_PRT1_PC2
#define B__0__PORT 1u
#define B__0__PS CYREG_GPIO_PRT1_PS
#define B__0__SHIFT 3u
#define B__DR CYREG_GPIO_PRT1_DR
#define B__DR_CLR CYREG_GPIO_PRT1_DR_CLR
#define B__DR_INV CYREG_GPIO_PRT1_DR_INV
#define B__DR_SET CYREG_GPIO_PRT1_DR_SET
#define B__INTCFG CYREG_GPIO_PRT1_INTR_CFG
#define B__INTR CYREG_GPIO_PRT1_INTR
#define B__INTR_CFG CYREG_GPIO_PRT1_INTR_CFG
#define B__INTSTAT CYREG_GPIO_PRT1_INTR
#define B__MASK 0x08u
#define B__PC CYREG_GPIO_PRT1_PC
#define B__PC2 CYREG_GPIO_PRT1_PC2
#define B__PORT 1u
#define B__PS CYREG_GPIO_PRT1_PS
#define B__SHIFT 3u

/* G */
#define G__0__DR CYREG_GPIO_PRT1_DR
#define G__0__DR_CLR CYREG_GPIO_PRT1_DR_CLR
#define G__0__DR_INV CYREG_GPIO_PRT1_DR_INV
#define G__0__DR_SET CYREG_GPIO_PRT1_DR_SET
#define G__0__HSIOM CYREG_HSIOM_PORT_SEL1
#define G__0__HSIOM_MASK 0x00000F00u
#define G__0__HSIOM_SHIFT 8u
#define G__0__INTCFG CYREG_GPIO_PRT1_INTR_CFG
#define G__0__INTR CYREG_GPIO_PRT1_INTR
#define G__0__INTR_CFG CYREG_GPIO_PRT1_INTR_CFG
#define G__0__INTSTAT CYREG_GPIO_PRT1_INTR
#define G__0__MASK 0x04u
#define G__0__PC CYREG_GPIO_PRT1_PC
#define G__0__PC2 CYREG_GPIO_PRT1_PC2
#define G__0__PORT 1u
#define G__0__PS CYREG_GPIO_PRT1_PS
#define G__0__SHIFT 2u
#define G__DR CYREG_GPIO_PRT1_DR
#define G__DR_CLR CYREG_GPIO_PRT1_DR_CLR
#define G__DR_INV CYREG_GPIO_PRT1_DR_INV
#define G__DR_SET CYREG_GPIO_PRT1_DR_SET
#define G__INTCFG CYREG_GPIO_PRT1_INTR_CFG
#define G__INTR CYREG_GPIO_PRT1_INTR
#define G__INTR_CFG CYREG_GPIO_PRT1_INTR_CFG
#define G__INTSTAT CYREG_GPIO_PRT1_INTR
#define G__MASK 0x04u
#define G__PC CYREG_GPIO_PRT1_PC
#define G__PC2 CYREG_GPIO_PRT1_PC2
#define G__PORT 1u
#define G__PS CYREG_GPIO_PRT1_PS
#define G__SHIFT 2u

/* R */
#define R__0__DR CYREG_GPIO_PRT0_DR
#define R__0__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define R__0__DR_INV CYREG_GPIO_PRT0_DR_INV
#define R__0__DR_SET CYREG_GPIO_PRT0_DR_SET
#define R__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define R__0__HSIOM_MASK 0x0F000000u
#define R__0__HSIOM_SHIFT 24u
#define R__0__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define R__0__INTR CYREG_GPIO_PRT0_INTR
#define R__0__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define R__0__INTSTAT CYREG_GPIO_PRT0_INTR
#define R__0__MASK 0x40u
#define R__0__PC CYREG_GPIO_PRT0_PC
#define R__0__PC2 CYREG_GPIO_PRT0_PC2
#define R__0__PORT 0u
#define R__0__PS CYREG_GPIO_PRT0_PS
#define R__0__SHIFT 6u
#define R__DR CYREG_GPIO_PRT0_DR
#define R__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define R__DR_INV CYREG_GPIO_PRT0_DR_INV
#define R__DR_SET CYREG_GPIO_PRT0_DR_SET
#define R__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define R__INTR CYREG_GPIO_PRT0_INTR
#define R__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define R__INTSTAT CYREG_GPIO_PRT0_INTR
#define R__MASK 0x40u
#define R__PC CYREG_GPIO_PRT0_PC
#define R__PC2 CYREG_GPIO_PRT0_PC2
#define R__PORT 0u
#define R__PS CYREG_GPIO_PRT0_PS
#define R__SHIFT 6u

/* PWM_CLOCK */
#define PWM_CLOCK__CTRL_REGISTER CYREG_PERI_PCLK_CTL3
#define PWM_CLOCK__DIV_ID 0x00000040u
#define PWM_CLOCK__DIV_REGISTER CYREG_PERI_DIV_16_CTL0
#define PWM_CLOCK__PA_DIV_ID 0x000000FFu

/* PWM_cy_m0s8_tcpwm_1 */
#define PWM_cy_m0s8_tcpwm_1__CC CYREG_TCPWM_CNT_CC
#define PWM_cy_m0s8_tcpwm_1__CC_BUFF CYREG_TCPWM_CNT_CC_BUFF
#define PWM_cy_m0s8_tcpwm_1__COUNTER CYREG_TCPWM_CNT_COUNTER
#define PWM_cy_m0s8_tcpwm_1__CTRL CYREG_TCPWM_CNT_CTRL
#define PWM_cy_m0s8_tcpwm_1__INTR CYREG_TCPWM_CNT_INTR
#define PWM_cy_m0s8_tcpwm_1__INTR_MASK CYREG_TCPWM_CNT_INTR_MASK
#define PWM_cy_m0s8_tcpwm_1__INTR_MASKED CYREG_TCPWM_CNT_INTR_MASKED
#define PWM_cy_m0s8_tcpwm_1__INTR_SET CYREG_TCPWM_CNT_INTR_SET
#define PWM_cy_m0s8_tcpwm_1__PERIOD CYREG_TCPWM_CNT_PERIOD
#define PWM_cy_m0s8_tcpwm_1__PERIOD_BUFF CYREG_TCPWM_CNT_PERIOD_BUFF
#define PWM_cy_m0s8_tcpwm_1__STATUS CYREG_TCPWM_CNT_STATUS
#define PWM_cy_m0s8_tcpwm_1__TCPWM_CMD CYREG_TCPWM_CMD
#define PWM_cy_m0s8_tcpwm_1__TCPWM_CMDCAPTURE_MASK 0x01u
#define PWM_cy_m0s8_tcpwm_1__TCPWM_CMDCAPTURE_SHIFT 0u
#define PWM_cy_m0s8_tcpwm_1__TCPWM_CMDRELOAD_MASK 0x100u
#define PWM_cy_m0s8_tcpwm_1__TCPWM_CMDRELOAD_SHIFT 8u
#define PWM_cy_m0s8_tcpwm_1__TCPWM_CMDSTART_MASK 0x1000000u
#define PWM_cy_m0s8_tcpwm_1__TCPWM_CMDSTART_SHIFT 24u
#define PWM_cy_m0s8_tcpwm_1__TCPWM_CMDSTOP_MASK 0x10000u
#define PWM_cy_m0s8_tcpwm_1__TCPWM_CMDSTOP_SHIFT 16u
#define PWM_cy_m0s8_tcpwm_1__TCPWM_CTRL CYREG_TCPWM_CTRL
#define PWM_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK 0x01u
#define PWM_cy_m0s8_tcpwm_1__TCPWM_CTRL_SHIFT 0u
#define PWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE CYREG_TCPWM_INTR_CAUSE
#define PWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE_MASK 0x01u
#define PWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE_SHIFT 0u
#define PWM_cy_m0s8_tcpwm_1__TCPWM_NUMBER 0u
#define PWM_cy_m0s8_tcpwm_1__TR_CTRL0 CYREG_TCPWM_CNT_TR_CTRL0
#define PWM_cy_m0s8_tcpwm_1__TR_CTRL1 CYREG_TCPWM_CNT_TR_CTRL1
#define PWM_cy_m0s8_tcpwm_1__TR_CTRL2 CYREG_TCPWM_CNT_TR_CTRL2

/* PWM_isr */
#define PWM_isr__INTC_CLR_EN_REG CYREG_CM0_ICER
#define PWM_isr__INTC_CLR_PD_REG CYREG_CM0_ICPR
#define PWM_isr__INTC_MASK 0x100u
#define PWM_isr__INTC_NUMBER 8u
#define PWM_isr__INTC_PRIOR_MASK 0xC0u
#define PWM_isr__INTC_PRIOR_NUM 3u
#define PWM_isr__INTC_PRIOR_REG CYREG_CM0_IPR2
#define PWM_isr__INTC_SET_EN_REG CYREG_CM0_ISER
#define PWM_isr__INTC_SET_PD_REG CYREG_CM0_ISPR

/* PWM_OUTPUT */
#define PWM_OUTPUT__0__DR CYREG_GPIO_PRT1_DR
#define PWM_OUTPUT__0__DR_CLR CYREG_GPIO_PRT1_DR_CLR
#define PWM_OUTPUT__0__DR_INV CYREG_GPIO_PRT1_DR_INV
#define PWM_OUTPUT__0__DR_SET CYREG_GPIO_PRT1_DR_SET
#define PWM_OUTPUT__0__HSIOM CYREG_HSIOM_PORT_SEL1
#define PWM_OUTPUT__0__HSIOM_MASK 0x000000F0u
#define PWM_OUTPUT__0__HSIOM_SHIFT 4u
#define PWM_OUTPUT__0__INTCFG CYREG_GPIO_PRT1_INTR_CFG
#define PWM_OUTPUT__0__INTR CYREG_GPIO_PRT1_INTR
#define PWM_OUTPUT__0__INTR_CFG CYREG_GPIO_PRT1_INTR_CFG
#define PWM_OUTPUT__0__INTSTAT CYREG_GPIO_PRT1_INTR
#define PWM_OUTPUT__0__MASK 0x02u
#define PWM_OUTPUT__0__PC CYREG_GPIO_PRT1_PC
#define PWM_OUTPUT__0__PC2 CYREG_GPIO_PRT1_PC2
#define PWM_OUTPUT__0__PORT 1u
#define PWM_OUTPUT__0__PS CYREG_GPIO_PRT1_PS
#define PWM_OUTPUT__0__SHIFT 1u
#define PWM_OUTPUT__DR CYREG_GPIO_PRT1_DR
#define PWM_OUTPUT__DR_CLR CYREG_GPIO_PRT1_DR_CLR
#define PWM_OUTPUT__DR_INV CYREG_GPIO_PRT1_DR_INV
#define PWM_OUTPUT__DR_SET CYREG_GPIO_PRT1_DR_SET
#define PWM_OUTPUT__INTCFG CYREG_GPIO_PRT1_INTR_CFG
#define PWM_OUTPUT__INTR CYREG_GPIO_PRT1_INTR
#define PWM_OUTPUT__INTR_CFG CYREG_GPIO_PRT1_INTR_CFG
#define PWM_OUTPUT__INTSTAT CYREG_GPIO_PRT1_INTR
#define PWM_OUTPUT__MASK 0x02u
#define PWM_OUTPUT__PC CYREG_GPIO_PRT1_PC
#define PWM_OUTPUT__PC2 CYREG_GPIO_PRT1_PC2
#define PWM_OUTPUT__PORT 1u
#define PWM_OUTPUT__PS CYREG_GPIO_PRT1_PS
#define PWM_OUTPUT__SHIFT 1u

/* Mode */
#define Mode__0__DR CYREG_GPIO_PRT0_DR
#define Mode__0__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define Mode__0__DR_INV CYREG_GPIO_PRT0_DR_INV
#define Mode__0__DR_SET CYREG_GPIO_PRT0_DR_SET
#define Mode__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define Mode__0__HSIOM_MASK 0x000000F0u
#define Mode__0__HSIOM_SHIFT 4u
#define Mode__0__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define Mode__0__INTR CYREG_GPIO_PRT0_INTR
#define Mode__0__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define Mode__0__INTSTAT CYREG_GPIO_PRT0_INTR
#define Mode__0__MASK 0x02u
#define Mode__0__PC CYREG_GPIO_PRT0_PC
#define Mode__0__PC2 CYREG_GPIO_PRT0_PC2
#define Mode__0__PORT 0u
#define Mode__0__PS CYREG_GPIO_PRT0_PS
#define Mode__0__SHIFT 1u
#define Mode__DR CYREG_GPIO_PRT0_DR
#define Mode__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define Mode__DR_INV CYREG_GPIO_PRT0_DR_INV
#define Mode__DR_SET CYREG_GPIO_PRT0_DR_SET
#define Mode__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define Mode__INTR CYREG_GPIO_PRT0_INTR
#define Mode__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define Mode__INTSTAT CYREG_GPIO_PRT0_INTR
#define Mode__MASK 0x02u
#define Mode__PC CYREG_GPIO_PRT0_PC
#define Mode__PC2 CYREG_GPIO_PRT0_PC2
#define Mode__PORT 0u
#define Mode__PS CYREG_GPIO_PRT0_PS
#define Mode__SHIFT 1u

/* SW_Tx_UART_tx */
#define SW_Tx_UART_tx__0__DR CYREG_GPIO_PRT3_DR
#define SW_Tx_UART_tx__0__DR_CLR CYREG_GPIO_PRT3_DR_CLR
#define SW_Tx_UART_tx__0__DR_INV CYREG_GPIO_PRT3_DR_INV
#define SW_Tx_UART_tx__0__DR_SET CYREG_GPIO_PRT3_DR_SET
#define SW_Tx_UART_tx__0__HSIOM CYREG_HSIOM_PORT_SEL3
#define SW_Tx_UART_tx__0__HSIOM_MASK 0x0000000Fu
#define SW_Tx_UART_tx__0__HSIOM_SHIFT 0u
#define SW_Tx_UART_tx__0__INTCFG CYREG_GPIO_PRT3_INTR_CFG
#define SW_Tx_UART_tx__0__INTR CYREG_GPIO_PRT3_INTR
#define SW_Tx_UART_tx__0__INTR_CFG CYREG_GPIO_PRT3_INTR_CFG
#define SW_Tx_UART_tx__0__INTSTAT CYREG_GPIO_PRT3_INTR
#define SW_Tx_UART_tx__0__MASK 0x01u
#define SW_Tx_UART_tx__0__PC CYREG_GPIO_PRT3_PC
#define SW_Tx_UART_tx__0__PC2 CYREG_GPIO_PRT3_PC2
#define SW_Tx_UART_tx__0__PORT 3u
#define SW_Tx_UART_tx__0__PS CYREG_GPIO_PRT3_PS
#define SW_Tx_UART_tx__0__SHIFT 0u
#define SW_Tx_UART_tx__DR CYREG_GPIO_PRT3_DR
#define SW_Tx_UART_tx__DR_CLR CYREG_GPIO_PRT3_DR_CLR
#define SW_Tx_UART_tx__DR_INV CYREG_GPIO_PRT3_DR_INV
#define SW_Tx_UART_tx__DR_SET CYREG_GPIO_PRT3_DR_SET
#define SW_Tx_UART_tx__INTCFG CYREG_GPIO_PRT3_INTR_CFG
#define SW_Tx_UART_tx__INTR CYREG_GPIO_PRT3_INTR
#define SW_Tx_UART_tx__INTR_CFG CYREG_GPIO_PRT3_INTR_CFG
#define SW_Tx_UART_tx__INTSTAT CYREG_GPIO_PRT3_INTR
#define SW_Tx_UART_tx__MASK 0x01u
#define SW_Tx_UART_tx__PC CYREG_GPIO_PRT3_PC
#define SW_Tx_UART_tx__PC2 CYREG_GPIO_PRT3_PC2
#define SW_Tx_UART_tx__PORT 3u
#define SW_Tx_UART_tx__PS CYREG_GPIO_PRT3_PS
#define SW_Tx_UART_tx__SHIFT 0u

/* Time_Bit_0 */
#define Time_Bit_0__0__DR CYREG_GPIO_PRT0_DR
#define Time_Bit_0__0__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define Time_Bit_0__0__DR_INV CYREG_GPIO_PRT0_DR_INV
#define Time_Bit_0__0__DR_SET CYREG_GPIO_PRT0_DR_SET
#define Time_Bit_0__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define Time_Bit_0__0__HSIOM_MASK 0x00F00000u
#define Time_Bit_0__0__HSIOM_SHIFT 20u
#define Time_Bit_0__0__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define Time_Bit_0__0__INTR CYREG_GPIO_PRT0_INTR
#define Time_Bit_0__0__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define Time_Bit_0__0__INTSTAT CYREG_GPIO_PRT0_INTR
#define Time_Bit_0__0__MASK 0x20u
#define Time_Bit_0__0__PC CYREG_GPIO_PRT0_PC
#define Time_Bit_0__0__PC2 CYREG_GPIO_PRT0_PC2
#define Time_Bit_0__0__PORT 0u
#define Time_Bit_0__0__PS CYREG_GPIO_PRT0_PS
#define Time_Bit_0__0__SHIFT 5u
#define Time_Bit_0__DR CYREG_GPIO_PRT0_DR
#define Time_Bit_0__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define Time_Bit_0__DR_INV CYREG_GPIO_PRT0_DR_INV
#define Time_Bit_0__DR_SET CYREG_GPIO_PRT0_DR_SET
#define Time_Bit_0__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define Time_Bit_0__INTR CYREG_GPIO_PRT0_INTR
#define Time_Bit_0__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define Time_Bit_0__INTSTAT CYREG_GPIO_PRT0_INTR
#define Time_Bit_0__MASK 0x20u
#define Time_Bit_0__PC CYREG_GPIO_PRT0_PC
#define Time_Bit_0__PC2 CYREG_GPIO_PRT0_PC2
#define Time_Bit_0__PORT 0u
#define Time_Bit_0__PS CYREG_GPIO_PRT0_PS
#define Time_Bit_0__SHIFT 5u

/* Time_Bit_1 */
#define Time_Bit_1__0__DR CYREG_GPIO_PRT1_DR
#define Time_Bit_1__0__DR_CLR CYREG_GPIO_PRT1_DR_CLR
#define Time_Bit_1__0__DR_INV CYREG_GPIO_PRT1_DR_INV
#define Time_Bit_1__0__DR_SET CYREG_GPIO_PRT1_DR_SET
#define Time_Bit_1__0__HSIOM CYREG_HSIOM_PORT_SEL1
#define Time_Bit_1__0__HSIOM_MASK 0x0F000000u
#define Time_Bit_1__0__HSIOM_SHIFT 24u
#define Time_Bit_1__0__INTCFG CYREG_GPIO_PRT1_INTR_CFG
#define Time_Bit_1__0__INTR CYREG_GPIO_PRT1_INTR
#define Time_Bit_1__0__INTR_CFG CYREG_GPIO_PRT1_INTR_CFG
#define Time_Bit_1__0__INTSTAT CYREG_GPIO_PRT1_INTR
#define Time_Bit_1__0__MASK 0x40u
#define Time_Bit_1__0__PC CYREG_GPIO_PRT1_PC
#define Time_Bit_1__0__PC2 CYREG_GPIO_PRT1_PC2
#define Time_Bit_1__0__PORT 1u
#define Time_Bit_1__0__PS CYREG_GPIO_PRT1_PS
#define Time_Bit_1__0__SHIFT 6u
#define Time_Bit_1__DR CYREG_GPIO_PRT1_DR
#define Time_Bit_1__DR_CLR CYREG_GPIO_PRT1_DR_CLR
#define Time_Bit_1__DR_INV CYREG_GPIO_PRT1_DR_INV
#define Time_Bit_1__DR_SET CYREG_GPIO_PRT1_DR_SET
#define Time_Bit_1__INTCFG CYREG_GPIO_PRT1_INTR_CFG
#define Time_Bit_1__INTR CYREG_GPIO_PRT1_INTR
#define Time_Bit_1__INTR_CFG CYREG_GPIO_PRT1_INTR_CFG
#define Time_Bit_1__INTSTAT CYREG_GPIO_PRT1_INTR
#define Time_Bit_1__MASK 0x40u
#define Time_Bit_1__PC CYREG_GPIO_PRT1_PC
#define Time_Bit_1__PC2 CYREG_GPIO_PRT1_PC2
#define Time_Bit_1__PORT 1u
#define Time_Bit_1__PS CYREG_GPIO_PRT1_PS
#define Time_Bit_1__SHIFT 6u

/* Time_Bit_2 */
#define Time_Bit_2__0__DR CYREG_GPIO_PRT1_DR
#define Time_Bit_2__0__DR_CLR CYREG_GPIO_PRT1_DR_CLR
#define Time_Bit_2__0__DR_INV CYREG_GPIO_PRT1_DR_INV
#define Time_Bit_2__0__DR_SET CYREG_GPIO_PRT1_DR_SET
#define Time_Bit_2__0__HSIOM CYREG_HSIOM_PORT_SEL1
#define Time_Bit_2__0__HSIOM_MASK 0xF0000000u
#define Time_Bit_2__0__HSIOM_SHIFT 28u
#define Time_Bit_2__0__INTCFG CYREG_GPIO_PRT1_INTR_CFG
#define Time_Bit_2__0__INTR CYREG_GPIO_PRT1_INTR
#define Time_Bit_2__0__INTR_CFG CYREG_GPIO_PRT1_INTR_CFG
#define Time_Bit_2__0__INTSTAT CYREG_GPIO_PRT1_INTR
#define Time_Bit_2__0__MASK 0x80u
#define Time_Bit_2__0__PC CYREG_GPIO_PRT1_PC
#define Time_Bit_2__0__PC2 CYREG_GPIO_PRT1_PC2
#define Time_Bit_2__0__PORT 1u
#define Time_Bit_2__0__PS CYREG_GPIO_PRT1_PS
#define Time_Bit_2__0__SHIFT 7u
#define Time_Bit_2__DR CYREG_GPIO_PRT1_DR
#define Time_Bit_2__DR_CLR CYREG_GPIO_PRT1_DR_CLR
#define Time_Bit_2__DR_INV CYREG_GPIO_PRT1_DR_INV
#define Time_Bit_2__DR_SET CYREG_GPIO_PRT1_DR_SET
#define Time_Bit_2__INTCFG CYREG_GPIO_PRT1_INTR_CFG
#define Time_Bit_2__INTR CYREG_GPIO_PRT1_INTR
#define Time_Bit_2__INTR_CFG CYREG_GPIO_PRT1_INTR_CFG
#define Time_Bit_2__INTSTAT CYREG_GPIO_PRT1_INTR
#define Time_Bit_2__MASK 0x80u
#define Time_Bit_2__PC CYREG_GPIO_PRT1_PC
#define Time_Bit_2__PC2 CYREG_GPIO_PRT1_PC2
#define Time_Bit_2__PORT 1u
#define Time_Bit_2__PS CYREG_GPIO_PRT1_PS
#define Time_Bit_2__SHIFT 7u

/* Time_Bit_3 */
#define Time_Bit_3__0__DR CYREG_GPIO_PRT2_DR
#define Time_Bit_3__0__DR_CLR CYREG_GPIO_PRT2_DR_CLR
#define Time_Bit_3__0__DR_INV CYREG_GPIO_PRT2_DR_INV
#define Time_Bit_3__0__DR_SET CYREG_GPIO_PRT2_DR_SET
#define Time_Bit_3__0__HSIOM CYREG_HSIOM_PORT_SEL2
#define Time_Bit_3__0__HSIOM_MASK 0x0000000Fu
#define Time_Bit_3__0__HSIOM_SHIFT 0u
#define Time_Bit_3__0__INTCFG CYREG_GPIO_PRT2_INTR_CFG
#define Time_Bit_3__0__INTR CYREG_GPIO_PRT2_INTR
#define Time_Bit_3__0__INTR_CFG CYREG_GPIO_PRT2_INTR_CFG
#define Time_Bit_3__0__INTSTAT CYREG_GPIO_PRT2_INTR
#define Time_Bit_3__0__MASK 0x01u
#define Time_Bit_3__0__PC CYREG_GPIO_PRT2_PC
#define Time_Bit_3__0__PC2 CYREG_GPIO_PRT2_PC2
#define Time_Bit_3__0__PORT 2u
#define Time_Bit_3__0__PS CYREG_GPIO_PRT2_PS
#define Time_Bit_3__0__SHIFT 0u
#define Time_Bit_3__DR CYREG_GPIO_PRT2_DR
#define Time_Bit_3__DR_CLR CYREG_GPIO_PRT2_DR_CLR
#define Time_Bit_3__DR_INV CYREG_GPIO_PRT2_DR_INV
#define Time_Bit_3__DR_SET CYREG_GPIO_PRT2_DR_SET
#define Time_Bit_3__INTCFG CYREG_GPIO_PRT2_INTR_CFG
#define Time_Bit_3__INTR CYREG_GPIO_PRT2_INTR
#define Time_Bit_3__INTR_CFG CYREG_GPIO_PRT2_INTR_CFG
#define Time_Bit_3__INTSTAT CYREG_GPIO_PRT2_INTR
#define Time_Bit_3__MASK 0x01u
#define Time_Bit_3__PC CYREG_GPIO_PRT2_PC
#define Time_Bit_3__PC2 CYREG_GPIO_PRT2_PC2
#define Time_Bit_3__PORT 2u
#define Time_Bit_3__PS CYREG_GPIO_PRT2_PS
#define Time_Bit_3__SHIFT 0u

/* SUPPLY_ENABLE */
#define SUPPLY_ENABLE__0__DR CYREG_GPIO_PRT0_DR
#define SUPPLY_ENABLE__0__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define SUPPLY_ENABLE__0__DR_INV CYREG_GPIO_PRT0_DR_INV
#define SUPPLY_ENABLE__0__DR_SET CYREG_GPIO_PRT0_DR_SET
#define SUPPLY_ENABLE__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define SUPPLY_ENABLE__0__HSIOM_MASK 0x000F0000u
#define SUPPLY_ENABLE__0__HSIOM_SHIFT 16u
#define SUPPLY_ENABLE__0__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define SUPPLY_ENABLE__0__INTR CYREG_GPIO_PRT0_INTR
#define SUPPLY_ENABLE__0__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define SUPPLY_ENABLE__0__INTSTAT CYREG_GPIO_PRT0_INTR
#define SUPPLY_ENABLE__0__MASK 0x10u
#define SUPPLY_ENABLE__0__PC CYREG_GPIO_PRT0_PC
#define SUPPLY_ENABLE__0__PC2 CYREG_GPIO_PRT0_PC2
#define SUPPLY_ENABLE__0__PORT 0u
#define SUPPLY_ENABLE__0__PS CYREG_GPIO_PRT0_PS
#define SUPPLY_ENABLE__0__SHIFT 4u
#define SUPPLY_ENABLE__DR CYREG_GPIO_PRT0_DR
#define SUPPLY_ENABLE__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define SUPPLY_ENABLE__DR_INV CYREG_GPIO_PRT0_DR_INV
#define SUPPLY_ENABLE__DR_SET CYREG_GPIO_PRT0_DR_SET
#define SUPPLY_ENABLE__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define SUPPLY_ENABLE__INTR CYREG_GPIO_PRT0_INTR
#define SUPPLY_ENABLE__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define SUPPLY_ENABLE__INTSTAT CYREG_GPIO_PRT0_INTR
#define SUPPLY_ENABLE__MASK 0x10u
#define SUPPLY_ENABLE__PC CYREG_GPIO_PRT0_PC
#define SUPPLY_ENABLE__PC2 CYREG_GPIO_PRT0_PC2
#define SUPPLY_ENABLE__PORT 0u
#define SUPPLY_ENABLE__PS CYREG_GPIO_PRT0_PS
#define SUPPLY_ENABLE__SHIFT 4u

/* Push_Button_isr */
#define Push_Button_isr__INTC_CLR_EN_REG CYREG_CM0_ICER
#define Push_Button_isr__INTC_CLR_PD_REG CYREG_CM0_ICPR
#define Push_Button_isr__INTC_MASK 0x01u
#define Push_Button_isr__INTC_NUMBER 0u
#define Push_Button_isr__INTC_PRIOR_MASK 0xC0u
#define Push_Button_isr__INTC_PRIOR_NUM 3u
#define Push_Button_isr__INTC_PRIOR_REG CYREG_CM0_IPR0
#define Push_Button_isr__INTC_SET_EN_REG CYREG_CM0_ISER
#define Push_Button_isr__INTC_SET_PD_REG CYREG_CM0_ISPR

/* PUSH_BUTTON_INPUT */
#define PUSH_BUTTON_INPUT__0__DR CYREG_GPIO_PRT0_DR
#define PUSH_BUTTON_INPUT__0__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define PUSH_BUTTON_INPUT__0__DR_INV CYREG_GPIO_PRT0_DR_INV
#define PUSH_BUTTON_INPUT__0__DR_SET CYREG_GPIO_PRT0_DR_SET
#define PUSH_BUTTON_INPUT__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define PUSH_BUTTON_INPUT__0__HSIOM_MASK 0x00000F00u
#define PUSH_BUTTON_INPUT__0__HSIOM_SHIFT 8u
#define PUSH_BUTTON_INPUT__0__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define PUSH_BUTTON_INPUT__0__INTR CYREG_GPIO_PRT0_INTR
#define PUSH_BUTTON_INPUT__0__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define PUSH_BUTTON_INPUT__0__INTSTAT CYREG_GPIO_PRT0_INTR
#define PUSH_BUTTON_INPUT__0__MASK 0x04u
#define PUSH_BUTTON_INPUT__0__PC CYREG_GPIO_PRT0_PC
#define PUSH_BUTTON_INPUT__0__PC2 CYREG_GPIO_PRT0_PC2
#define PUSH_BUTTON_INPUT__0__PORT 0u
#define PUSH_BUTTON_INPUT__0__PS CYREG_GPIO_PRT0_PS
#define PUSH_BUTTON_INPUT__0__SHIFT 2u
#define PUSH_BUTTON_INPUT__DR CYREG_GPIO_PRT0_DR
#define PUSH_BUTTON_INPUT__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define PUSH_BUTTON_INPUT__DR_INV CYREG_GPIO_PRT0_DR_INV
#define PUSH_BUTTON_INPUT__DR_SET CYREG_GPIO_PRT0_DR_SET
#define PUSH_BUTTON_INPUT__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define PUSH_BUTTON_INPUT__INTR CYREG_GPIO_PRT0_INTR
#define PUSH_BUTTON_INPUT__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define PUSH_BUTTON_INPUT__INTSTAT CYREG_GPIO_PRT0_INTR
#define PUSH_BUTTON_INPUT__MASK 0x04u
#define PUSH_BUTTON_INPUT__PC CYREG_GPIO_PRT0_PC
#define PUSH_BUTTON_INPUT__PC2 CYREG_GPIO_PRT0_PC2
#define PUSH_BUTTON_INPUT__PORT 0u
#define PUSH_BUTTON_INPUT__PS CYREG_GPIO_PRT0_PS
#define PUSH_BUTTON_INPUT__SHIFT 2u
#define PUSH_BUTTON_INPUT__SNAP CYREG_GPIO_PRT0_INTR

/* Miscellaneous */
#define CY_PROJECT_NAME "Auto Shut-OFF_SOIC16"
#define CY_VERSION "PSoC Creator  3.3 CP3"
#define CYDEV_BANDGAP_VOLTAGE 1.200
#define CYDEV_BCLK__HFCLK__HZ 12000000U
#define CYDEV_BCLK__HFCLK__KHZ 12000U
#define CYDEV_BCLK__HFCLK__MHZ 12U
#define CYDEV_BCLK__SYSCLK__HZ 12000000U
#define CYDEV_BCLK__SYSCLK__KHZ 12000U
#define CYDEV_BCLK__SYSCLK__MHZ 12U
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PANTHER 19u
#define CYDEV_CHIP_DIE_PSOC4A 11u
#define CYDEV_CHIP_DIE_PSOC5LP 18u
#define CYDEV_CHIP_DIE_TMA4 2u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC4
#define CYDEV_CHIP_JTAG_ID 0x0A43119Au
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 11u
#define CYDEV_CHIP_MEMBER_4C 16u
#define CYDEV_CHIP_MEMBER_4D 7u
#define CYDEV_CHIP_MEMBER_4E 4u
#define CYDEV_CHIP_MEMBER_4F 12u
#define CYDEV_CHIP_MEMBER_4G 2u
#define CYDEV_CHIP_MEMBER_4H 10u
#define CYDEV_CHIP_MEMBER_4I 15u
#define CYDEV_CHIP_MEMBER_4J 8u
#define CYDEV_CHIP_MEMBER_4K 9u
#define CYDEV_CHIP_MEMBER_4L 14u
#define CYDEV_CHIP_MEMBER_4M 13u
#define CYDEV_CHIP_MEMBER_4N 6u
#define CYDEV_CHIP_MEMBER_4O 5u
#define CYDEV_CHIP_MEMBER_4U 3u
#define CYDEV_CHIP_MEMBER_5A 18u
#define CYDEV_CHIP_MEMBER_5B 17u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_4D
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_MEMBER_USED
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REV_TMA4_ES 17u
#define CYDEV_CHIP_REV_TMA4_ES2 33u
#define CYDEV_CHIP_REV_TMA4_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4C_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4D_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4E_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0u
#define CYDEV_CHIP_REVISION_4G_ES 17u
#define CYDEV_CHIP_REVISION_4G_ES2 33u
#define CYDEV_CHIP_REVISION_4G_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4H_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4I_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4J_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4K_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4L_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4M_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4N_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4O_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4U_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_4D_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REVISION_USED
#define CYDEV_CONFIG_READ_ACCELERATOR 1
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_DEBUG_PROTECT_KILL 4
#define CYDEV_DEBUG_PROTECT_OPEN 1
#define CYDEV_DEBUG_PROTECT CYDEV_DEBUG_PROTECT_OPEN
#define CYDEV_DEBUG_PROTECT_PROTECTED 2
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_Disable
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_ENABLE 0
#define CYDEV_DFT_SELECT_CLK0 8u
#define CYDEV_DFT_SELECT_CLK1 9u
#define CYDEV_HEAP_SIZE 0x80
#define CYDEV_IMO_TRIMMED_BY_USB 0u
#define CYDEV_IMO_TRIMMED_BY_WCO 0u
#define CYDEV_IS_EXPORTING_CODE 0
#define CYDEV_IS_IMPORTING_CODE 0
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LAUNCHER 5
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER 4
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_STACK_SIZE 0x0200
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 1
#define CYDEV_VDD 3.3
#define CYDEV_VDD_MV 3300
#define CYDEV_WDT_GENERATE_ISR 0u
#define CYIPBLOCK_m0s8cpussv2_VERSION 1
#define CYIPBLOCK_m0s8ioss_VERSION 1
#define CYIPBLOCK_m0s8peri_VERSION 1
#define CYIPBLOCK_m0s8scb_VERSION 1
#define CYIPBLOCK_m0s8tcpwm_VERSION 2
#define CYIPBLOCK_s8srsslt_VERSION 1
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
