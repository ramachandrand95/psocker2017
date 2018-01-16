/*******************************************************************************
* File Name: TIMER_RZ_PM.c
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

#include "TIMER_RZ.h"

static TIMER_RZ_backupStruct TIMER_RZ_backup;


/*******************************************************************************
* Function Name: TIMER_RZ_SaveConfig
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
*  TIMER_RZ_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TIMER_RZ_SaveConfig(void) 
{
    #if (!TIMER_RZ_UsingFixedFunction)
        TIMER_RZ_backup.TimerUdb = TIMER_RZ_ReadCounter();
        TIMER_RZ_backup.InterruptMaskValue = TIMER_RZ_STATUS_MASK;
        #if (TIMER_RZ_UsingHWCaptureCounter)
            TIMER_RZ_backup.TimerCaptureCounter = TIMER_RZ_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!TIMER_RZ_UDB_CONTROL_REG_REMOVED)
            TIMER_RZ_backup.TimerControlRegister = TIMER_RZ_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TIMER_RZ_RestoreConfig
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
*  TIMER_RZ_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TIMER_RZ_RestoreConfig(void) 
{   
    #if (!TIMER_RZ_UsingFixedFunction)

        TIMER_RZ_WriteCounter(TIMER_RZ_backup.TimerUdb);
        TIMER_RZ_STATUS_MASK =TIMER_RZ_backup.InterruptMaskValue;
        #if (TIMER_RZ_UsingHWCaptureCounter)
            TIMER_RZ_SetCaptureCount(TIMER_RZ_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!TIMER_RZ_UDB_CONTROL_REG_REMOVED)
            TIMER_RZ_WriteControlRegister(TIMER_RZ_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TIMER_RZ_Sleep
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
*  TIMER_RZ_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TIMER_RZ_Sleep(void) 
{
    #if(!TIMER_RZ_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(TIMER_RZ_CTRL_ENABLE == (TIMER_RZ_CONTROL & TIMER_RZ_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TIMER_RZ_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TIMER_RZ_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TIMER_RZ_Stop();
    TIMER_RZ_SaveConfig();
}


/*******************************************************************************
* Function Name: TIMER_RZ_Wakeup
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
*  TIMER_RZ_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TIMER_RZ_Wakeup(void) 
{
    TIMER_RZ_RestoreConfig();
    #if(!TIMER_RZ_UDB_CONTROL_REG_REMOVED)
        if(TIMER_RZ_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TIMER_RZ_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
