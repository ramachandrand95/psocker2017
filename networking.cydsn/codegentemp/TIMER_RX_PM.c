/*******************************************************************************
* File Name: TIMER_RX_PM.c
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

#include "TIMER_RX.h"

static TIMER_RX_backupStruct TIMER_RX_backup;


/*******************************************************************************
* Function Name: TIMER_RX_SaveConfig
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
*  TIMER_RX_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void TIMER_RX_SaveConfig(void) 
{
    #if (!TIMER_RX_UsingFixedFunction)
        TIMER_RX_backup.TimerUdb = TIMER_RX_ReadCounter();
        TIMER_RX_backup.InterruptMaskValue = TIMER_RX_STATUS_MASK;
        #if (TIMER_RX_UsingHWCaptureCounter)
            TIMER_RX_backup.TimerCaptureCounter = TIMER_RX_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!TIMER_RX_UDB_CONTROL_REG_REMOVED)
            TIMER_RX_backup.TimerControlRegister = TIMER_RX_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: TIMER_RX_RestoreConfig
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
*  TIMER_RX_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void TIMER_RX_RestoreConfig(void) 
{   
    #if (!TIMER_RX_UsingFixedFunction)

        TIMER_RX_WriteCounter(TIMER_RX_backup.TimerUdb);
        TIMER_RX_STATUS_MASK =TIMER_RX_backup.InterruptMaskValue;
        #if (TIMER_RX_UsingHWCaptureCounter)
            TIMER_RX_SetCaptureCount(TIMER_RX_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!TIMER_RX_UDB_CONTROL_REG_REMOVED)
            TIMER_RX_WriteControlRegister(TIMER_RX_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: TIMER_RX_Sleep
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
*  TIMER_RX_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void TIMER_RX_Sleep(void) 
{
    #if(!TIMER_RX_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(TIMER_RX_CTRL_ENABLE == (TIMER_RX_CONTROL & TIMER_RX_CTRL_ENABLE))
        {
            /* Timer is enabled */
            TIMER_RX_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            TIMER_RX_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    TIMER_RX_Stop();
    TIMER_RX_SaveConfig();
}


/*******************************************************************************
* Function Name: TIMER_RX_Wakeup
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
*  TIMER_RX_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void TIMER_RX_Wakeup(void) 
{
    TIMER_RX_RestoreConfig();
    #if(!TIMER_RX_UDB_CONTROL_REG_REMOVED)
        if(TIMER_RX_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                TIMER_RX_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
