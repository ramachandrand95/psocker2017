/*******************************************************************************
* File Name: COLL_GEN_TIMER_PM.c
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

#include "COLL_GEN_TIMER.h"

static COLL_GEN_TIMER_backupStruct COLL_GEN_TIMER_backup;


/*******************************************************************************
* Function Name: COLL_GEN_TIMER_SaveConfig
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
*  COLL_GEN_TIMER_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void COLL_GEN_TIMER_SaveConfig(void) 
{
    #if (!COLL_GEN_TIMER_UsingFixedFunction)
        COLL_GEN_TIMER_backup.TimerUdb = COLL_GEN_TIMER_ReadCounter();
        COLL_GEN_TIMER_backup.InterruptMaskValue = COLL_GEN_TIMER_STATUS_MASK;
        #if (COLL_GEN_TIMER_UsingHWCaptureCounter)
            COLL_GEN_TIMER_backup.TimerCaptureCounter = COLL_GEN_TIMER_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!COLL_GEN_TIMER_UDB_CONTROL_REG_REMOVED)
            COLL_GEN_TIMER_backup.TimerControlRegister = COLL_GEN_TIMER_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: COLL_GEN_TIMER_RestoreConfig
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
*  COLL_GEN_TIMER_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void COLL_GEN_TIMER_RestoreConfig(void) 
{   
    #if (!COLL_GEN_TIMER_UsingFixedFunction)

        COLL_GEN_TIMER_WriteCounter(COLL_GEN_TIMER_backup.TimerUdb);
        COLL_GEN_TIMER_STATUS_MASK =COLL_GEN_TIMER_backup.InterruptMaskValue;
        #if (COLL_GEN_TIMER_UsingHWCaptureCounter)
            COLL_GEN_TIMER_SetCaptureCount(COLL_GEN_TIMER_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!COLL_GEN_TIMER_UDB_CONTROL_REG_REMOVED)
            COLL_GEN_TIMER_WriteControlRegister(COLL_GEN_TIMER_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: COLL_GEN_TIMER_Sleep
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
*  COLL_GEN_TIMER_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void COLL_GEN_TIMER_Sleep(void) 
{
    #if(!COLL_GEN_TIMER_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(COLL_GEN_TIMER_CTRL_ENABLE == (COLL_GEN_TIMER_CONTROL & COLL_GEN_TIMER_CTRL_ENABLE))
        {
            /* Timer is enabled */
            COLL_GEN_TIMER_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            COLL_GEN_TIMER_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    COLL_GEN_TIMER_Stop();
    COLL_GEN_TIMER_SaveConfig();
}


/*******************************************************************************
* Function Name: COLL_GEN_TIMER_Wakeup
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
*  COLL_GEN_TIMER_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void COLL_GEN_TIMER_Wakeup(void) 
{
    COLL_GEN_TIMER_RestoreConfig();
    #if(!COLL_GEN_TIMER_UDB_CONTROL_REG_REMOVED)
        if(COLL_GEN_TIMER_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                COLL_GEN_TIMER_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
