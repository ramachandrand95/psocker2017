/*******************************************************************************
* File Name: BACKOFF_PM.c
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

#include "BACKOFF.h"

static BACKOFF_backupStruct BACKOFF_backup;


/*******************************************************************************
* Function Name: BACKOFF_SaveConfig
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
*  BACKOFF_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BACKOFF_SaveConfig(void) 
{
    #if (!BACKOFF_UsingFixedFunction)
        BACKOFF_backup.TimerUdb = BACKOFF_ReadCounter();
        BACKOFF_backup.InterruptMaskValue = BACKOFF_STATUS_MASK;
        #if (BACKOFF_UsingHWCaptureCounter)
            BACKOFF_backup.TimerCaptureCounter = BACKOFF_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!BACKOFF_UDB_CONTROL_REG_REMOVED)
            BACKOFF_backup.TimerControlRegister = BACKOFF_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: BACKOFF_RestoreConfig
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
*  BACKOFF_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BACKOFF_RestoreConfig(void) 
{   
    #if (!BACKOFF_UsingFixedFunction)

        BACKOFF_WriteCounter(BACKOFF_backup.TimerUdb);
        BACKOFF_STATUS_MASK =BACKOFF_backup.InterruptMaskValue;
        #if (BACKOFF_UsingHWCaptureCounter)
            BACKOFF_SetCaptureCount(BACKOFF_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!BACKOFF_UDB_CONTROL_REG_REMOVED)
            BACKOFF_WriteControlRegister(BACKOFF_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: BACKOFF_Sleep
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
*  BACKOFF_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void BACKOFF_Sleep(void) 
{
    #if(!BACKOFF_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(BACKOFF_CTRL_ENABLE == (BACKOFF_CONTROL & BACKOFF_CTRL_ENABLE))
        {
            /* Timer is enabled */
            BACKOFF_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            BACKOFF_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    BACKOFF_Stop();
    BACKOFF_SaveConfig();
}


/*******************************************************************************
* Function Name: BACKOFF_Wakeup
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
*  BACKOFF_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BACKOFF_Wakeup(void) 
{
    BACKOFF_RestoreConfig();
    #if(!BACKOFF_UDB_CONTROL_REG_REMOVED)
        if(BACKOFF_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                BACKOFF_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
