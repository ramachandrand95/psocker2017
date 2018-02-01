/*******************************************************************************
* File Name: OXFF_GEN_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "OXFF_GEN.h"

static OXFF_GEN_backupStruct OXFF_GEN_backup;


/*******************************************************************************
* Function Name: OXFF_GEN_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  OXFF_GEN_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void OXFF_GEN_SaveConfig(void) 
{
    #if (!OXFF_GEN_UsingFixedFunction)
        OXFF_GEN_backup.TimerUdb = OXFF_GEN_ReadCounter();
        OXFF_GEN_backup.InterruptMaskValue = OXFF_GEN_STATUS_MASK;
        #if (OXFF_GEN_UsingHWCaptureCounter)
            OXFF_GEN_backup.TimerCaptureCounter = OXFF_GEN_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!OXFF_GEN_UDB_CONTROL_REG_REMOVED)
            OXFF_GEN_backup.TimerControlRegister = OXFF_GEN_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: OXFF_GEN_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  OXFF_GEN_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void OXFF_GEN_RestoreConfig(void) 
{   
    #if (!OXFF_GEN_UsingFixedFunction)

        OXFF_GEN_WriteCounter(OXFF_GEN_backup.TimerUdb);
        OXFF_GEN_STATUS_MASK =OXFF_GEN_backup.InterruptMaskValue;
        #if (OXFF_GEN_UsingHWCaptureCounter)
            OXFF_GEN_SetCaptureCount(OXFF_GEN_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!OXFF_GEN_UDB_CONTROL_REG_REMOVED)
            OXFF_GEN_WriteControlRegister(OXFF_GEN_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: OXFF_GEN_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  OXFF_GEN_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void OXFF_GEN_Sleep(void) 
{
    #if(!OXFF_GEN_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(OXFF_GEN_CTRL_ENABLE == (OXFF_GEN_CONTROL & OXFF_GEN_CTRL_ENABLE))
        {
            /* Timer is enabled */
            OXFF_GEN_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            OXFF_GEN_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    OXFF_GEN_Stop();
    OXFF_GEN_SaveConfig();
}


/*******************************************************************************
* Function Name: OXFF_GEN_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  OXFF_GEN_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void OXFF_GEN_Wakeup(void) 
{
    OXFF_GEN_RestoreConfig();
    #if(!OXFF_GEN_UDB_CONTROL_REG_REMOVED)
        if(OXFF_GEN_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                OXFF_GEN_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
