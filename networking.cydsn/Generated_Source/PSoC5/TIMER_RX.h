/*******************************************************************************
* File Name: TIMER_RX.h
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

#if !defined(CY_Timer_v2_60_TIMER_RX_H)
#define CY_Timer_v2_60_TIMER_RX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 TIMER_RX_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define TIMER_RX_Resolution                 16u
#define TIMER_RX_UsingFixedFunction         0u
#define TIMER_RX_UsingHWCaptureCounter      0u
#define TIMER_RX_SoftwareCaptureMode        0u
#define TIMER_RX_SoftwareTriggerMode        0u
#define TIMER_RX_UsingHWEnable              0u
#define TIMER_RX_EnableTriggerMode          0u
#define TIMER_RX_InterruptOnCaptureCount    0u
#define TIMER_RX_RunModeUsed                0u
#define TIMER_RX_ControlRegRemoved          0u

#if defined(TIMER_RX_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define TIMER_RX_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (TIMER_RX_UsingFixedFunction)
    #define TIMER_RX_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define TIMER_RX_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End TIMER_RX_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!TIMER_RX_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (TIMER_RX_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!TIMER_RX_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}TIMER_RX_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    TIMER_RX_Start(void) ;
void    TIMER_RX_Stop(void) ;

void    TIMER_RX_SetInterruptMode(uint8 interruptMode) ;
uint8   TIMER_RX_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define TIMER_RX_GetInterruptSource() TIMER_RX_ReadStatusRegister()

#if(!TIMER_RX_UDB_CONTROL_REG_REMOVED)
    uint8   TIMER_RX_ReadControlRegister(void) ;
    void    TIMER_RX_WriteControlRegister(uint8 control) ;
#endif /* (!TIMER_RX_UDB_CONTROL_REG_REMOVED) */

uint16  TIMER_RX_ReadPeriod(void) ;
void    TIMER_RX_WritePeriod(uint16 period) ;
uint16  TIMER_RX_ReadCounter(void) ;
void    TIMER_RX_WriteCounter(uint16 counter) ;
uint16  TIMER_RX_ReadCapture(void) ;
void    TIMER_RX_SoftwareCapture(void) ;

#if(!TIMER_RX_UsingFixedFunction) /* UDB Prototypes */
    #if (TIMER_RX_SoftwareCaptureMode)
        void    TIMER_RX_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!TIMER_RX_UsingFixedFunction) */

    #if (TIMER_RX_SoftwareTriggerMode)
        void    TIMER_RX_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (TIMER_RX_SoftwareTriggerMode) */

    #if (TIMER_RX_EnableTriggerMode)
        void    TIMER_RX_EnableTrigger(void) ;
        void    TIMER_RX_DisableTrigger(void) ;
    #endif /* (TIMER_RX_EnableTriggerMode) */


    #if(TIMER_RX_InterruptOnCaptureCount)
        void    TIMER_RX_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (TIMER_RX_InterruptOnCaptureCount) */

    #if (TIMER_RX_UsingHWCaptureCounter)
        void    TIMER_RX_SetCaptureCount(uint8 captureCount) ;
        uint8   TIMER_RX_ReadCaptureCount(void) ;
    #endif /* (TIMER_RX_UsingHWCaptureCounter) */

    void TIMER_RX_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void TIMER_RX_Init(void)          ;
void TIMER_RX_Enable(void)        ;
void TIMER_RX_SaveConfig(void)    ;
void TIMER_RX_RestoreConfig(void) ;
void TIMER_RX_Sleep(void)         ;
void TIMER_RX_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define TIMER_RX__B_TIMER__CM_NONE 0
#define TIMER_RX__B_TIMER__CM_RISINGEDGE 1
#define TIMER_RX__B_TIMER__CM_FALLINGEDGE 2
#define TIMER_RX__B_TIMER__CM_EITHEREDGE 3
#define TIMER_RX__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define TIMER_RX__B_TIMER__TM_NONE 0x00u
#define TIMER_RX__B_TIMER__TM_RISINGEDGE 0x04u
#define TIMER_RX__B_TIMER__TM_FALLINGEDGE 0x08u
#define TIMER_RX__B_TIMER__TM_EITHEREDGE 0x0Cu
#define TIMER_RX__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define TIMER_RX_INIT_PERIOD             51u
#define TIMER_RX_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << TIMER_RX_CTRL_CAP_MODE_SHIFT))
#define TIMER_RX_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << TIMER_RX_CTRL_TRIG_MODE_SHIFT))
#if (TIMER_RX_UsingFixedFunction)
    #define TIMER_RX_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << TIMER_RX_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << TIMER_RX_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define TIMER_RX_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << TIMER_RX_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TIMER_RX_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TIMER_RX_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (TIMER_RX_UsingFixedFunction) */
#define TIMER_RX_INIT_CAPTURE_COUNT      (2u)
#define TIMER_RX_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << TIMER_RX_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (TIMER_RX_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define TIMER_RX_STATUS         (*(reg8 *) TIMER_RX_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define TIMER_RX_STATUS_MASK    (*(reg8 *) TIMER_RX_TimerHW__SR0 )
    #define TIMER_RX_CONTROL        (*(reg8 *) TIMER_RX_TimerHW__CFG0)
    #define TIMER_RX_CONTROL2       (*(reg8 *) TIMER_RX_TimerHW__CFG1)
    #define TIMER_RX_CONTROL2_PTR   ( (reg8 *) TIMER_RX_TimerHW__CFG1)
    #define TIMER_RX_RT1            (*(reg8 *) TIMER_RX_TimerHW__RT1)
    #define TIMER_RX_RT1_PTR        ( (reg8 *) TIMER_RX_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define TIMER_RX_CONTROL3       (*(reg8 *) TIMER_RX_TimerHW__CFG2)
        #define TIMER_RX_CONTROL3_PTR   ( (reg8 *) TIMER_RX_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define TIMER_RX_GLOBAL_ENABLE  (*(reg8 *) TIMER_RX_TimerHW__PM_ACT_CFG)
    #define TIMER_RX_GLOBAL_STBY_ENABLE  (*(reg8 *) TIMER_RX_TimerHW__PM_STBY_CFG)

    #define TIMER_RX_CAPTURE_LSB         (* (reg16 *) TIMER_RX_TimerHW__CAP0 )
    #define TIMER_RX_CAPTURE_LSB_PTR       ((reg16 *) TIMER_RX_TimerHW__CAP0 )
    #define TIMER_RX_PERIOD_LSB          (* (reg16 *) TIMER_RX_TimerHW__PER0 )
    #define TIMER_RX_PERIOD_LSB_PTR        ((reg16 *) TIMER_RX_TimerHW__PER0 )
    #define TIMER_RX_COUNTER_LSB         (* (reg16 *) TIMER_RX_TimerHW__CNT_CMP0 )
    #define TIMER_RX_COUNTER_LSB_PTR       ((reg16 *) TIMER_RX_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define TIMER_RX_BLOCK_EN_MASK                     TIMER_RX_TimerHW__PM_ACT_MSK
    #define TIMER_RX_BLOCK_STBY_EN_MASK                TIMER_RX_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define TIMER_RX_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define TIMER_RX_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define TIMER_RX_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define TIMER_RX_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define TIMER_RX_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define TIMER_RX_CTRL_ENABLE                        ((uint8)((uint8)0x01u << TIMER_RX_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define TIMER_RX_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define TIMER_RX_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << TIMER_RX_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define TIMER_RX_CTRL_MODE_SHIFT                 0x01u
        #define TIMER_RX_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << TIMER_RX_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define TIMER_RX_CTRL_RCOD_SHIFT        0x02u
        #define TIMER_RX_CTRL_ENBL_SHIFT        0x00u
        #define TIMER_RX_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define TIMER_RX_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << TIMER_RX_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define TIMER_RX_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << TIMER_RX_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define TIMER_RX_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << TIMER_RX_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define TIMER_RX_CTRL_RCOD       ((uint8)((uint8)0x03u << TIMER_RX_CTRL_RCOD_SHIFT))
        #define TIMER_RX_CTRL_ENBL       ((uint8)((uint8)0x80u << TIMER_RX_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define TIMER_RX_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define TIMER_RX_RT1_MASK                        ((uint8)((uint8)0x03u << TIMER_RX_RT1_SHIFT))
    #define TIMER_RX_SYNC                            ((uint8)((uint8)0x03u << TIMER_RX_RT1_SHIFT))
    #define TIMER_RX_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define TIMER_RX_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << TIMER_RX_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define TIMER_RX_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << TIMER_RX_SYNCDSI_SHIFT))

    #define TIMER_RX_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << TIMER_RX_CTRL_MODE_SHIFT))
    #define TIMER_RX_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << TIMER_RX_CTRL_MODE_SHIFT))
    #define TIMER_RX_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << TIMER_RX_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TIMER_RX_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TIMER_RX_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TIMER_RX_STATUS_TC_INT_MASK_SHIFT        (TIMER_RX_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TIMER_RX_STATUS_CAPTURE_INT_MASK_SHIFT   (TIMER_RX_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define TIMER_RX_STATUS_TC                       ((uint8)((uint8)0x01u << TIMER_RX_STATUS_TC_SHIFT))
    #define TIMER_RX_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << TIMER_RX_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define TIMER_RX_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << TIMER_RX_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define TIMER_RX_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << TIMER_RX_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define TIMER_RX_STATUS              (* (reg8 *) TIMER_RX_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define TIMER_RX_STATUS_MASK         (* (reg8 *) TIMER_RX_TimerUDB_rstSts_stsreg__MASK_REG)
    #define TIMER_RX_STATUS_AUX_CTRL     (* (reg8 *) TIMER_RX_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define TIMER_RX_CONTROL             (* (reg8 *) TIMER_RX_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(TIMER_RX_Resolution <= 8u) /* 8-bit Timer */
        #define TIMER_RX_CAPTURE_LSB         (* (reg8 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define TIMER_RX_CAPTURE_LSB_PTR       ((reg8 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define TIMER_RX_PERIOD_LSB          (* (reg8 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define TIMER_RX_PERIOD_LSB_PTR        ((reg8 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define TIMER_RX_COUNTER_LSB         (* (reg8 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define TIMER_RX_COUNTER_LSB_PTR       ((reg8 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(TIMER_RX_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define TIMER_RX_CAPTURE_LSB         (* (reg16 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define TIMER_RX_CAPTURE_LSB_PTR       ((reg16 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define TIMER_RX_PERIOD_LSB          (* (reg16 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define TIMER_RX_PERIOD_LSB_PTR        ((reg16 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define TIMER_RX_COUNTER_LSB         (* (reg16 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define TIMER_RX_COUNTER_LSB_PTR       ((reg16 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define TIMER_RX_CAPTURE_LSB         (* (reg16 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define TIMER_RX_CAPTURE_LSB_PTR       ((reg16 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define TIMER_RX_PERIOD_LSB          (* (reg16 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define TIMER_RX_PERIOD_LSB_PTR        ((reg16 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define TIMER_RX_COUNTER_LSB         (* (reg16 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define TIMER_RX_COUNTER_LSB_PTR       ((reg16 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(TIMER_RX_Resolution <= 24u)/* 24-bit Timer */
        #define TIMER_RX_CAPTURE_LSB         (* (reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define TIMER_RX_CAPTURE_LSB_PTR       ((reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define TIMER_RX_PERIOD_LSB          (* (reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define TIMER_RX_PERIOD_LSB_PTR        ((reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define TIMER_RX_COUNTER_LSB         (* (reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define TIMER_RX_COUNTER_LSB_PTR       ((reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define TIMER_RX_CAPTURE_LSB         (* (reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define TIMER_RX_CAPTURE_LSB_PTR       ((reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define TIMER_RX_PERIOD_LSB          (* (reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define TIMER_RX_PERIOD_LSB_PTR        ((reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define TIMER_RX_COUNTER_LSB         (* (reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define TIMER_RX_COUNTER_LSB_PTR       ((reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define TIMER_RX_CAPTURE_LSB         (* (reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define TIMER_RX_CAPTURE_LSB_PTR       ((reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define TIMER_RX_PERIOD_LSB          (* (reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define TIMER_RX_PERIOD_LSB_PTR        ((reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define TIMER_RX_COUNTER_LSB         (* (reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define TIMER_RX_COUNTER_LSB_PTR       ((reg32 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define TIMER_RX_COUNTER_LSB_PTR_8BIT       ((reg8 *) TIMER_RX_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (TIMER_RX_UsingHWCaptureCounter)
        #define TIMER_RX_CAP_COUNT              (*(reg8 *) TIMER_RX_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TIMER_RX_CAP_COUNT_PTR          ( (reg8 *) TIMER_RX_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TIMER_RX_CAPTURE_COUNT_CTRL     (*(reg8 *) TIMER_RX_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define TIMER_RX_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) TIMER_RX_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (TIMER_RX_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define TIMER_RX_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define TIMER_RX_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define TIMER_RX_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define TIMER_RX_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define TIMER_RX_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define TIMER_RX_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << TIMER_RX_CTRL_INTCNT_SHIFT))
    #define TIMER_RX_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << TIMER_RX_CTRL_TRIG_MODE_SHIFT))
    #define TIMER_RX_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << TIMER_RX_CTRL_TRIG_EN_SHIFT))
    #define TIMER_RX_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << TIMER_RX_CTRL_CAP_MODE_SHIFT))
    #define TIMER_RX_CTRL_ENABLE                    ((uint8)((uint8)0x01u << TIMER_RX_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define TIMER_RX_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define TIMER_RX_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define TIMER_RX_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define TIMER_RX_STATUS_TC_INT_MASK_SHIFT       TIMER_RX_STATUS_TC_SHIFT
    #define TIMER_RX_STATUS_CAPTURE_INT_MASK_SHIFT  TIMER_RX_STATUS_CAPTURE_SHIFT
    #define TIMER_RX_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define TIMER_RX_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define TIMER_RX_STATUS_FIFOFULL_INT_MASK_SHIFT TIMER_RX_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define TIMER_RX_STATUS_TC                      ((uint8)((uint8)0x01u << TIMER_RX_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define TIMER_RX_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << TIMER_RX_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TIMER_RX_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << TIMER_RX_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TIMER_RX_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << TIMER_RX_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define TIMER_RX_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << TIMER_RX_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define TIMER_RX_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << TIMER_RX_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TIMER_RX_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << TIMER_RX_STATUS_FIFOFULL_SHIFT))

    #define TIMER_RX_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define TIMER_RX_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define TIMER_RX_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define TIMER_RX_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define TIMER_RX_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define TIMER_RX_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_TIMER_RX_H */


/* [] END OF FILE */
