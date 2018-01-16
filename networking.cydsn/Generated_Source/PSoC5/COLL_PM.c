/*******************************************************************************
* File Name: COLL_PM.c
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

#include "COLL.h"

static COLL_backupStruct COLL_backup;


/*******************************************************************************
* Function Name: COLL_SaveConfig
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
*  COLL_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void COLL_SaveConfig(void) 
{
    #if (!COLL_UsingFixedFunction)
        COLL_backup.TimerUdb = COLL_ReadCounter();
        COLL_backup.InterruptMaskValue = COLL_STATUS_MASK;
        #if (COLL_UsingHWCaptureCounter)
            COLL_backup.TimerCaptureCounter = COLL_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!COLL_UDB_CONTROL_REG_REMOVED)
            COLL_backup.TimerControlRegister = COLL_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: COLL_RestoreConfig
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
*  COLL_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void COLL_RestoreConfig(void) 
{   
    #if (!COLL_UsingFixedFunction)

        COLL_WriteCounter(COLL_backup.TimerUdb);
        COLL_STATUS_MASK =COLL_backup.InterruptMaskValue;
        #if (COLL_UsingHWCaptureCounter)
            COLL_SetCaptureCount(COLL_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!COLL_UDB_CONTROL_REG_REMOVED)
            COLL_WriteControlRegister(COLL_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: COLL_Sleep
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
*  COLL_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void COLL_Sleep(void) 
{
    #if(!COLL_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(COLL_CTRL_ENABLE == (COLL_CONTROL & COLL_CTRL_ENABLE))
        {
            /* Timer is enabled */
            COLL_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            COLL_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    COLL_Stop();
    COLL_SaveConfig();
}


/*******************************************************************************
* Function Name: COLL_Wakeup
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
*  COLL_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void COLL_Wakeup(void) 
{
    COLL_RestoreConfig();
    #if(!COLL_UDB_CONTROL_REG_REMOVED)
        if(COLL_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                COLL_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
