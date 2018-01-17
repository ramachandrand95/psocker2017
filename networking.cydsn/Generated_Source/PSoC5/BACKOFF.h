/*******************************************************************************
* File Name: BACKOFF.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_BACKOFF_H)
#define CY_Timer_v2_60_BACKOFF_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 BACKOFF_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define BACKOFF_Resolution                 16u
#define BACKOFF_UsingFixedFunction         0u
#define BACKOFF_UsingHWCaptureCounter      0u
#define BACKOFF_SoftwareCaptureMode        0u
#define BACKOFF_SoftwareTriggerMode        0u
#define BACKOFF_UsingHWEnable              0u
#define BACKOFF_EnableTriggerMode          0u
#define BACKOFF_InterruptOnCaptureCount    0u
#define BACKOFF_RunModeUsed                0u
#define BACKOFF_ControlRegRemoved          0u

#if defined(BACKOFF_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define BACKOFF_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (BACKOFF_UsingFixedFunction)
    #define BACKOFF_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define BACKOFF_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End BACKOFF_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!BACKOFF_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (BACKOFF_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!BACKOFF_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}BACKOFF_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    BACKOFF_Start(void) ;
void    BACKOFF_Stop(void) ;

void    BACKOFF_SetInterruptMode(uint8 interruptMode) ;
uint8   BACKOFF_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define BACKOFF_GetInterruptSource() BACKOFF_ReadStatusRegister()

#if(!BACKOFF_UDB_CONTROL_REG_REMOVED)
    uint8   BACKOFF_ReadControlRegister(void) ;
    void    BACKOFF_WriteControlRegister(uint8 control) ;
#endif /* (!BACKOFF_UDB_CONTROL_REG_REMOVED) */

uint16  BACKOFF_ReadPeriod(void) ;
void    BACKOFF_WritePeriod(uint16 period) ;
uint16  BACKOFF_ReadCounter(void) ;
void    BACKOFF_WriteCounter(uint16 counter) ;
uint16  BACKOFF_ReadCapture(void) ;
void    BACKOFF_SoftwareCapture(void) ;

#if(!BACKOFF_UsingFixedFunction) /* UDB Prototypes */
    #if (BACKOFF_SoftwareCaptureMode)
        void    BACKOFF_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!BACKOFF_UsingFixedFunction) */

    #if (BACKOFF_SoftwareTriggerMode)
        void    BACKOFF_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (BACKOFF_SoftwareTriggerMode) */

    #if (BACKOFF_EnableTriggerMode)
        void    BACKOFF_EnableTrigger(void) ;
        void    BACKOFF_DisableTrigger(void) ;
    #endif /* (BACKOFF_EnableTriggerMode) */


    #if(BACKOFF_InterruptOnCaptureCount)
        void    BACKOFF_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (BACKOFF_InterruptOnCaptureCount) */

    #if (BACKOFF_UsingHWCaptureCounter)
        void    BACKOFF_SetCaptureCount(uint8 captureCount) ;
        uint8   BACKOFF_ReadCaptureCount(void) ;
    #endif /* (BACKOFF_UsingHWCaptureCounter) */

    void BACKOFF_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void BACKOFF_Init(void)          ;
void BACKOFF_Enable(void)        ;
void BACKOFF_SaveConfig(void)    ;
void BACKOFF_RestoreConfig(void) ;
void BACKOFF_Sleep(void)         ;
void BACKOFF_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define BACKOFF__B_TIMER__CM_NONE 0
#define BACKOFF__B_TIMER__CM_RISINGEDGE 1
#define BACKOFF__B_TIMER__CM_FALLINGEDGE 2
#define BACKOFF__B_TIMER__CM_EITHEREDGE 3
#define BACKOFF__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define BACKOFF__B_TIMER__TM_NONE 0x00u
#define BACKOFF__B_TIMER__TM_RISINGEDGE 0x04u
#define BACKOFF__B_TIMER__TM_FALLINGEDGE 0x08u
#define BACKOFF__B_TIMER__TM_EITHEREDGE 0x0Cu
#define BACKOFF__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define BACKOFF_INIT_PERIOD             9u
#define BACKOFF_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << BACKOFF_CTRL_CAP_MODE_SHIFT))
#define BACKOFF_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << BACKOFF_CTRL_TRIG_MODE_SHIFT))
#if (BACKOFF_UsingFixedFunction)
    #define BACKOFF_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << BACKOFF_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << BACKOFF_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define BACKOFF_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << BACKOFF_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << BACKOFF_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << BACKOFF_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (BACKOFF_UsingFixedFunction) */
#define BACKOFF_INIT_CAPTURE_COUNT      (2u)
#define BACKOFF_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << BACKOFF_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (BACKOFF_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define BACKOFF_STATUS         (*(reg8 *) BACKOFF_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define BACKOFF_STATUS_MASK    (*(reg8 *) BACKOFF_TimerHW__SR0 )
    #define BACKOFF_CONTROL        (*(reg8 *) BACKOFF_TimerHW__CFG0)
    #define BACKOFF_CONTROL2       (*(reg8 *) BACKOFF_TimerHW__CFG1)
    #define BACKOFF_CONTROL2_PTR   ( (reg8 *) BACKOFF_TimerHW__CFG1)
    #define BACKOFF_RT1            (*(reg8 *) BACKOFF_TimerHW__RT1)
    #define BACKOFF_RT1_PTR        ( (reg8 *) BACKOFF_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define BACKOFF_CONTROL3       (*(reg8 *) BACKOFF_TimerHW__CFG2)
        #define BACKOFF_CONTROL3_PTR   ( (reg8 *) BACKOFF_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define BACKOFF_GLOBAL_ENABLE  (*(reg8 *) BACKOFF_TimerHW__PM_ACT_CFG)
    #define BACKOFF_GLOBAL_STBY_ENABLE  (*(reg8 *) BACKOFF_TimerHW__PM_STBY_CFG)

    #define BACKOFF_CAPTURE_LSB         (* (reg16 *) BACKOFF_TimerHW__CAP0 )
    #define BACKOFF_CAPTURE_LSB_PTR       ((reg16 *) BACKOFF_TimerHW__CAP0 )
    #define BACKOFF_PERIOD_LSB          (* (reg16 *) BACKOFF_TimerHW__PER0 )
    #define BACKOFF_PERIOD_LSB_PTR        ((reg16 *) BACKOFF_TimerHW__PER0 )
    #define BACKOFF_COUNTER_LSB         (* (reg16 *) BACKOFF_TimerHW__CNT_CMP0 )
    #define BACKOFF_COUNTER_LSB_PTR       ((reg16 *) BACKOFF_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define BACKOFF_BLOCK_EN_MASK                     BACKOFF_TimerHW__PM_ACT_MSK
    #define BACKOFF_BLOCK_STBY_EN_MASK                BACKOFF_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define BACKOFF_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define BACKOFF_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define BACKOFF_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define BACKOFF_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define BACKOFF_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define BACKOFF_CTRL_ENABLE                        ((uint8)((uint8)0x01u << BACKOFF_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define BACKOFF_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define BACKOFF_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << BACKOFF_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define BACKOFF_CTRL_MODE_SHIFT                 0x01u
        #define BACKOFF_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << BACKOFF_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define BACKOFF_CTRL_RCOD_SHIFT        0x02u
        #define BACKOFF_CTRL_ENBL_SHIFT        0x00u
        #define BACKOFF_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define BACKOFF_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << BACKOFF_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define BACKOFF_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << BACKOFF_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define BACKOFF_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << BACKOFF_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define BACKOFF_CTRL_RCOD       ((uint8)((uint8)0x03u << BACKOFF_CTRL_RCOD_SHIFT))
        #define BACKOFF_CTRL_ENBL       ((uint8)((uint8)0x80u << BACKOFF_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define BACKOFF_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define BACKOFF_RT1_MASK                        ((uint8)((uint8)0x03u << BACKOFF_RT1_SHIFT))
    #define BACKOFF_SYNC                            ((uint8)((uint8)0x03u << BACKOFF_RT1_SHIFT))
    #define BACKOFF_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define BACKOFF_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << BACKOFF_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define BACKOFF_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << BACKOFF_SYNCDSI_SHIFT))

    #define BACKOFF_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << BACKOFF_CTRL_MODE_SHIFT))
    #define BACKOFF_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << BACKOFF_CTRL_MODE_SHIFT))
    #define BACKOFF_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << BACKOFF_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define BACKOFF_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define BACKOFF_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define BACKOFF_STATUS_TC_INT_MASK_SHIFT        (BACKOFF_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define BACKOFF_STATUS_CAPTURE_INT_MASK_SHIFT   (BACKOFF_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define BACKOFF_STATUS_TC                       ((uint8)((uint8)0x01u << BACKOFF_STATUS_TC_SHIFT))
    #define BACKOFF_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << BACKOFF_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define BACKOFF_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << BACKOFF_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define BACKOFF_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << BACKOFF_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define BACKOFF_STATUS              (* (reg8 *) BACKOFF_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define BACKOFF_STATUS_MASK         (* (reg8 *) BACKOFF_TimerUDB_rstSts_stsreg__MASK_REG)
    #define BACKOFF_STATUS_AUX_CTRL     (* (reg8 *) BACKOFF_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define BACKOFF_CONTROL             (* (reg8 *) BACKOFF_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(BACKOFF_Resolution <= 8u) /* 8-bit Timer */
        #define BACKOFF_CAPTURE_LSB         (* (reg8 *) BACKOFF_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define BACKOFF_CAPTURE_LSB_PTR       ((reg8 *) BACKOFF_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define BACKOFF_PERIOD_LSB          (* (reg8 *) BACKOFF_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define BACKOFF_PERIOD_LSB_PTR        ((reg8 *) BACKOFF_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define BACKOFF_COUNTER_LSB         (* (reg8 *) BACKOFF_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define BACKOFF_COUNTER_LSB_PTR       ((reg8 *) BACKOFF_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(BACKOFF_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define BACKOFF_CAPTURE_LSB         (* (reg16 *) BACKOFF_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define BACKOFF_CAPTURE_LSB_PTR       ((reg16 *) BACKOFF_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define BACKOFF_PERIOD_LSB          (* (reg16 *) BACKOFF_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define BACKOFF_PERIOD_LSB_PTR        ((reg16 *) BACKOFF_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define BACKOFF_COUNTER_LSB         (* (reg16 *) BACKOFF_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define BACKOFF_COUNTER_LSB_PTR       ((reg16 *) BACKOFF_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define BACKOFF_CAPTURE_LSB         (* (reg16 *) BACKOFF_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define BACKOFF_CAPTURE_LSB_PTR       ((reg16 *) BACKOFF_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define BACKOFF_PERIOD_LSB          (* (reg16 *) BACKOFF_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define BACKOFF_PERIOD_LSB_PTR        ((reg16 *) BACKOFF_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define BACKOFF_COUNTER_LSB         (* (reg16 *) BACKOFF_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define BACKOFF_COUNTER_LSB_PTR       ((reg16 *) BACKOFF_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(BACKOFF_Resolution <= 24u)/* 24-bit Timer */
        #define BACKOFF_CAPTURE_LSB         (* (reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define BACKOFF_CAPTURE_LSB_PTR       ((reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define BACKOFF_PERIOD_LSB          (* (reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define BACKOFF_PERIOD_LSB_PTR        ((reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define BACKOFF_COUNTER_LSB         (* (reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define BACKOFF_COUNTER_LSB_PTR       ((reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define BACKOFF_CAPTURE_LSB         (* (reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define BACKOFF_CAPTURE_LSB_PTR       ((reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define BACKOFF_PERIOD_LSB          (* (reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define BACKOFF_PERIOD_LSB_PTR        ((reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define BACKOFF_COUNTER_LSB         (* (reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define BACKOFF_COUNTER_LSB_PTR       ((reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define BACKOFF_CAPTURE_LSB         (* (reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define BACKOFF_CAPTURE_LSB_PTR       ((reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define BACKOFF_PERIOD_LSB          (* (reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define BACKOFF_PERIOD_LSB_PTR        ((reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define BACKOFF_COUNTER_LSB         (* (reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define BACKOFF_COUNTER_LSB_PTR       ((reg32 *) BACKOFF_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define BACKOFF_COUNTER_LSB_PTR_8BIT       ((reg8 *) BACKOFF_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (BACKOFF_UsingHWCaptureCounter)
        #define BACKOFF_CAP_COUNT              (*(reg8 *) BACKOFF_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define BACKOFF_CAP_COUNT_PTR          ( (reg8 *) BACKOFF_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define BACKOFF_CAPTURE_COUNT_CTRL     (*(reg8 *) BACKOFF_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define BACKOFF_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) BACKOFF_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (BACKOFF_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define BACKOFF_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define BACKOFF_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define BACKOFF_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define BACKOFF_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define BACKOFF_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define BACKOFF_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << BACKOFF_CTRL_INTCNT_SHIFT))
    #define BACKOFF_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << BACKOFF_CTRL_TRIG_MODE_SHIFT))
    #define BACKOFF_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << BACKOFF_CTRL_TRIG_EN_SHIFT))
    #define BACKOFF_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << BACKOFF_CTRL_CAP_MODE_SHIFT))
    #define BACKOFF_CTRL_ENABLE                    ((uint8)((uint8)0x01u << BACKOFF_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define BACKOFF_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define BACKOFF_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define BACKOFF_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define BACKOFF_STATUS_TC_INT_MASK_SHIFT       BACKOFF_STATUS_TC_SHIFT
    #define BACKOFF_STATUS_CAPTURE_INT_MASK_SHIFT  BACKOFF_STATUS_CAPTURE_SHIFT
    #define BACKOFF_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define BACKOFF_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define BACKOFF_STATUS_FIFOFULL_INT_MASK_SHIFT BACKOFF_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define BACKOFF_STATUS_TC                      ((uint8)((uint8)0x01u << BACKOFF_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define BACKOFF_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << BACKOFF_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define BACKOFF_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << BACKOFF_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define BACKOFF_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << BACKOFF_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define BACKOFF_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << BACKOFF_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define BACKOFF_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << BACKOFF_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define BACKOFF_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << BACKOFF_STATUS_FIFOFULL_SHIFT))

    #define BACKOFF_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define BACKOFF_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define BACKOFF_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define BACKOFF_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define BACKOFF_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define BACKOFF_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_BACKOFF_H */


/* [] END OF FILE */
