/*******************************************************************************
* File Name: OXFF_GEN.h
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

#if !defined(CY_Timer_v2_60_OXFF_GEN_H)
#define CY_Timer_v2_60_OXFF_GEN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 OXFF_GEN_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define OXFF_GEN_Resolution                 16u
#define OXFF_GEN_UsingFixedFunction         0u
#define OXFF_GEN_UsingHWCaptureCounter      0u
#define OXFF_GEN_SoftwareCaptureMode        0u
#define OXFF_GEN_SoftwareTriggerMode        0u
#define OXFF_GEN_UsingHWEnable              0u
#define OXFF_GEN_EnableTriggerMode          0u
#define OXFF_GEN_InterruptOnCaptureCount    0u
#define OXFF_GEN_RunModeUsed                0u
#define OXFF_GEN_ControlRegRemoved          0u

#if defined(OXFF_GEN_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define OXFF_GEN_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (OXFF_GEN_UsingFixedFunction)
    #define OXFF_GEN_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define OXFF_GEN_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End OXFF_GEN_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!OXFF_GEN_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (OXFF_GEN_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!OXFF_GEN_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}OXFF_GEN_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    OXFF_GEN_Start(void) ;
void    OXFF_GEN_Stop(void) ;

void    OXFF_GEN_SetInterruptMode(uint8 interruptMode) ;
uint8   OXFF_GEN_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define OXFF_GEN_GetInterruptSource() OXFF_GEN_ReadStatusRegister()

#if(!OXFF_GEN_UDB_CONTROL_REG_REMOVED)
    uint8   OXFF_GEN_ReadControlRegister(void) ;
    void    OXFF_GEN_WriteControlRegister(uint8 control) ;
#endif /* (!OXFF_GEN_UDB_CONTROL_REG_REMOVED) */

uint16  OXFF_GEN_ReadPeriod(void) ;
void    OXFF_GEN_WritePeriod(uint16 period) ;
uint16  OXFF_GEN_ReadCounter(void) ;
void    OXFF_GEN_WriteCounter(uint16 counter) ;
uint16  OXFF_GEN_ReadCapture(void) ;
void    OXFF_GEN_SoftwareCapture(void) ;

#if(!OXFF_GEN_UsingFixedFunction) /* UDB Prototypes */
    #if (OXFF_GEN_SoftwareCaptureMode)
        void    OXFF_GEN_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!OXFF_GEN_UsingFixedFunction) */

    #if (OXFF_GEN_SoftwareTriggerMode)
        void    OXFF_GEN_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (OXFF_GEN_SoftwareTriggerMode) */

    #if (OXFF_GEN_EnableTriggerMode)
        void    OXFF_GEN_EnableTrigger(void) ;
        void    OXFF_GEN_DisableTrigger(void) ;
    #endif /* (OXFF_GEN_EnableTriggerMode) */


    #if(OXFF_GEN_InterruptOnCaptureCount)
        void    OXFF_GEN_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (OXFF_GEN_InterruptOnCaptureCount) */

    #if (OXFF_GEN_UsingHWCaptureCounter)
        void    OXFF_GEN_SetCaptureCount(uint8 captureCount) ;
        uint8   OXFF_GEN_ReadCaptureCount(void) ;
    #endif /* (OXFF_GEN_UsingHWCaptureCounter) */

    void OXFF_GEN_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void OXFF_GEN_Init(void)          ;
void OXFF_GEN_Enable(void)        ;
void OXFF_GEN_SaveConfig(void)    ;
void OXFF_GEN_RestoreConfig(void) ;
void OXFF_GEN_Sleep(void)         ;
void OXFF_GEN_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define OXFF_GEN__B_TIMER__CM_NONE 0
#define OXFF_GEN__B_TIMER__CM_RISINGEDGE 1
#define OXFF_GEN__B_TIMER__CM_FALLINGEDGE 2
#define OXFF_GEN__B_TIMER__CM_EITHEREDGE 3
#define OXFF_GEN__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define OXFF_GEN__B_TIMER__TM_NONE 0x00u
#define OXFF_GEN__B_TIMER__TM_RISINGEDGE 0x04u
#define OXFF_GEN__B_TIMER__TM_FALLINGEDGE 0x08u
#define OXFF_GEN__B_TIMER__TM_EITHEREDGE 0x0Cu
#define OXFF_GEN__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define OXFF_GEN_INIT_PERIOD             49u
#define OXFF_GEN_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << OXFF_GEN_CTRL_CAP_MODE_SHIFT))
#define OXFF_GEN_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << OXFF_GEN_CTRL_TRIG_MODE_SHIFT))
#if (OXFF_GEN_UsingFixedFunction)
    #define OXFF_GEN_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << OXFF_GEN_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << OXFF_GEN_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define OXFF_GEN_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << OXFF_GEN_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << OXFF_GEN_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << OXFF_GEN_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (OXFF_GEN_UsingFixedFunction) */
#define OXFF_GEN_INIT_CAPTURE_COUNT      (2u)
#define OXFF_GEN_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << OXFF_GEN_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (OXFF_GEN_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define OXFF_GEN_STATUS         (*(reg8 *) OXFF_GEN_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define OXFF_GEN_STATUS_MASK    (*(reg8 *) OXFF_GEN_TimerHW__SR0 )
    #define OXFF_GEN_CONTROL        (*(reg8 *) OXFF_GEN_TimerHW__CFG0)
    #define OXFF_GEN_CONTROL2       (*(reg8 *) OXFF_GEN_TimerHW__CFG1)
    #define OXFF_GEN_CONTROL2_PTR   ( (reg8 *) OXFF_GEN_TimerHW__CFG1)
    #define OXFF_GEN_RT1            (*(reg8 *) OXFF_GEN_TimerHW__RT1)
    #define OXFF_GEN_RT1_PTR        ( (reg8 *) OXFF_GEN_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define OXFF_GEN_CONTROL3       (*(reg8 *) OXFF_GEN_TimerHW__CFG2)
        #define OXFF_GEN_CONTROL3_PTR   ( (reg8 *) OXFF_GEN_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define OXFF_GEN_GLOBAL_ENABLE  (*(reg8 *) OXFF_GEN_TimerHW__PM_ACT_CFG)
    #define OXFF_GEN_GLOBAL_STBY_ENABLE  (*(reg8 *) OXFF_GEN_TimerHW__PM_STBY_CFG)

    #define OXFF_GEN_CAPTURE_LSB         (* (reg16 *) OXFF_GEN_TimerHW__CAP0 )
    #define OXFF_GEN_CAPTURE_LSB_PTR       ((reg16 *) OXFF_GEN_TimerHW__CAP0 )
    #define OXFF_GEN_PERIOD_LSB          (* (reg16 *) OXFF_GEN_TimerHW__PER0 )
    #define OXFF_GEN_PERIOD_LSB_PTR        ((reg16 *) OXFF_GEN_TimerHW__PER0 )
    #define OXFF_GEN_COUNTER_LSB         (* (reg16 *) OXFF_GEN_TimerHW__CNT_CMP0 )
    #define OXFF_GEN_COUNTER_LSB_PTR       ((reg16 *) OXFF_GEN_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define OXFF_GEN_BLOCK_EN_MASK                     OXFF_GEN_TimerHW__PM_ACT_MSK
    #define OXFF_GEN_BLOCK_STBY_EN_MASK                OXFF_GEN_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define OXFF_GEN_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define OXFF_GEN_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define OXFF_GEN_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define OXFF_GEN_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define OXFF_GEN_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define OXFF_GEN_CTRL_ENABLE                        ((uint8)((uint8)0x01u << OXFF_GEN_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define OXFF_GEN_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define OXFF_GEN_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << OXFF_GEN_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define OXFF_GEN_CTRL_MODE_SHIFT                 0x01u
        #define OXFF_GEN_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << OXFF_GEN_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define OXFF_GEN_CTRL_RCOD_SHIFT        0x02u
        #define OXFF_GEN_CTRL_ENBL_SHIFT        0x00u
        #define OXFF_GEN_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define OXFF_GEN_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << OXFF_GEN_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define OXFF_GEN_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << OXFF_GEN_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define OXFF_GEN_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << OXFF_GEN_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define OXFF_GEN_CTRL_RCOD       ((uint8)((uint8)0x03u << OXFF_GEN_CTRL_RCOD_SHIFT))
        #define OXFF_GEN_CTRL_ENBL       ((uint8)((uint8)0x80u << OXFF_GEN_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define OXFF_GEN_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define OXFF_GEN_RT1_MASK                        ((uint8)((uint8)0x03u << OXFF_GEN_RT1_SHIFT))
    #define OXFF_GEN_SYNC                            ((uint8)((uint8)0x03u << OXFF_GEN_RT1_SHIFT))
    #define OXFF_GEN_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define OXFF_GEN_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << OXFF_GEN_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define OXFF_GEN_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << OXFF_GEN_SYNCDSI_SHIFT))

    #define OXFF_GEN_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << OXFF_GEN_CTRL_MODE_SHIFT))
    #define OXFF_GEN_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << OXFF_GEN_CTRL_MODE_SHIFT))
    #define OXFF_GEN_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << OXFF_GEN_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define OXFF_GEN_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define OXFF_GEN_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define OXFF_GEN_STATUS_TC_INT_MASK_SHIFT        (OXFF_GEN_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define OXFF_GEN_STATUS_CAPTURE_INT_MASK_SHIFT   (OXFF_GEN_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define OXFF_GEN_STATUS_TC                       ((uint8)((uint8)0x01u << OXFF_GEN_STATUS_TC_SHIFT))
    #define OXFF_GEN_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << OXFF_GEN_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define OXFF_GEN_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << OXFF_GEN_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define OXFF_GEN_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << OXFF_GEN_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define OXFF_GEN_STATUS              (* (reg8 *) OXFF_GEN_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define OXFF_GEN_STATUS_MASK         (* (reg8 *) OXFF_GEN_TimerUDB_rstSts_stsreg__MASK_REG)
    #define OXFF_GEN_STATUS_AUX_CTRL     (* (reg8 *) OXFF_GEN_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define OXFF_GEN_CONTROL             (* (reg8 *) OXFF_GEN_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(OXFF_GEN_Resolution <= 8u) /* 8-bit Timer */
        #define OXFF_GEN_CAPTURE_LSB         (* (reg8 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define OXFF_GEN_CAPTURE_LSB_PTR       ((reg8 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define OXFF_GEN_PERIOD_LSB          (* (reg8 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define OXFF_GEN_PERIOD_LSB_PTR        ((reg8 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define OXFF_GEN_COUNTER_LSB         (* (reg8 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define OXFF_GEN_COUNTER_LSB_PTR       ((reg8 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(OXFF_GEN_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define OXFF_GEN_CAPTURE_LSB         (* (reg16 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define OXFF_GEN_CAPTURE_LSB_PTR       ((reg16 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define OXFF_GEN_PERIOD_LSB          (* (reg16 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define OXFF_GEN_PERIOD_LSB_PTR        ((reg16 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define OXFF_GEN_COUNTER_LSB         (* (reg16 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define OXFF_GEN_COUNTER_LSB_PTR       ((reg16 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define OXFF_GEN_CAPTURE_LSB         (* (reg16 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define OXFF_GEN_CAPTURE_LSB_PTR       ((reg16 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define OXFF_GEN_PERIOD_LSB          (* (reg16 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define OXFF_GEN_PERIOD_LSB_PTR        ((reg16 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define OXFF_GEN_COUNTER_LSB         (* (reg16 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define OXFF_GEN_COUNTER_LSB_PTR       ((reg16 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(OXFF_GEN_Resolution <= 24u)/* 24-bit Timer */
        #define OXFF_GEN_CAPTURE_LSB         (* (reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define OXFF_GEN_CAPTURE_LSB_PTR       ((reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define OXFF_GEN_PERIOD_LSB          (* (reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define OXFF_GEN_PERIOD_LSB_PTR        ((reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define OXFF_GEN_COUNTER_LSB         (* (reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define OXFF_GEN_COUNTER_LSB_PTR       ((reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define OXFF_GEN_CAPTURE_LSB         (* (reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define OXFF_GEN_CAPTURE_LSB_PTR       ((reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define OXFF_GEN_PERIOD_LSB          (* (reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define OXFF_GEN_PERIOD_LSB_PTR        ((reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define OXFF_GEN_COUNTER_LSB         (* (reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define OXFF_GEN_COUNTER_LSB_PTR       ((reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define OXFF_GEN_CAPTURE_LSB         (* (reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define OXFF_GEN_CAPTURE_LSB_PTR       ((reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define OXFF_GEN_PERIOD_LSB          (* (reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define OXFF_GEN_PERIOD_LSB_PTR        ((reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define OXFF_GEN_COUNTER_LSB         (* (reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define OXFF_GEN_COUNTER_LSB_PTR       ((reg32 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define OXFF_GEN_COUNTER_LSB_PTR_8BIT       ((reg8 *) OXFF_GEN_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (OXFF_GEN_UsingHWCaptureCounter)
        #define OXFF_GEN_CAP_COUNT              (*(reg8 *) OXFF_GEN_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define OXFF_GEN_CAP_COUNT_PTR          ( (reg8 *) OXFF_GEN_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define OXFF_GEN_CAPTURE_COUNT_CTRL     (*(reg8 *) OXFF_GEN_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define OXFF_GEN_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) OXFF_GEN_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (OXFF_GEN_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define OXFF_GEN_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define OXFF_GEN_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define OXFF_GEN_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define OXFF_GEN_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define OXFF_GEN_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define OXFF_GEN_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << OXFF_GEN_CTRL_INTCNT_SHIFT))
    #define OXFF_GEN_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << OXFF_GEN_CTRL_TRIG_MODE_SHIFT))
    #define OXFF_GEN_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << OXFF_GEN_CTRL_TRIG_EN_SHIFT))
    #define OXFF_GEN_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << OXFF_GEN_CTRL_CAP_MODE_SHIFT))
    #define OXFF_GEN_CTRL_ENABLE                    ((uint8)((uint8)0x01u << OXFF_GEN_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define OXFF_GEN_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define OXFF_GEN_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define OXFF_GEN_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define OXFF_GEN_STATUS_TC_INT_MASK_SHIFT       OXFF_GEN_STATUS_TC_SHIFT
    #define OXFF_GEN_STATUS_CAPTURE_INT_MASK_SHIFT  OXFF_GEN_STATUS_CAPTURE_SHIFT
    #define OXFF_GEN_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define OXFF_GEN_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define OXFF_GEN_STATUS_FIFOFULL_INT_MASK_SHIFT OXFF_GEN_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define OXFF_GEN_STATUS_TC                      ((uint8)((uint8)0x01u << OXFF_GEN_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define OXFF_GEN_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << OXFF_GEN_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define OXFF_GEN_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << OXFF_GEN_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define OXFF_GEN_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << OXFF_GEN_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define OXFF_GEN_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << OXFF_GEN_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define OXFF_GEN_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << OXFF_GEN_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define OXFF_GEN_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << OXFF_GEN_STATUS_FIFOFULL_SHIFT))

    #define OXFF_GEN_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define OXFF_GEN_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define OXFF_GEN_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define OXFF_GEN_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define OXFF_GEN_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define OXFF_GEN_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_OXFF_GEN_H */


/* [] END OF FILE */
