/*******************************************************************************
* File Name: INT_RISING.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_INT_RISING_H)
#define CY_ISR_INT_RISING_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void INT_RISING_Start(void);
void INT_RISING_StartEx(cyisraddress address);
void INT_RISING_Stop(void);

CY_ISR_PROTO(INT_RISING_Interrupt);

void INT_RISING_SetVector(cyisraddress address);
cyisraddress INT_RISING_GetVector(void);

void INT_RISING_SetPriority(uint8 priority);
uint8 INT_RISING_GetPriority(void);

void INT_RISING_Enable(void);
uint8 INT_RISING_GetState(void);
void INT_RISING_Disable(void);

void INT_RISING_SetPending(void);
void INT_RISING_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the INT_RISING ISR. */
#define INT_RISING_INTC_VECTOR            ((reg32 *) INT_RISING__INTC_VECT)

/* Address of the INT_RISING ISR priority. */
#define INT_RISING_INTC_PRIOR             ((reg8 *) INT_RISING__INTC_PRIOR_REG)

/* Priority of the INT_RISING interrupt. */
#define INT_RISING_INTC_PRIOR_NUMBER      INT_RISING__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable INT_RISING interrupt. */
#define INT_RISING_INTC_SET_EN            ((reg32 *) INT_RISING__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the INT_RISING interrupt. */
#define INT_RISING_INTC_CLR_EN            ((reg32 *) INT_RISING__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the INT_RISING interrupt state to pending. */
#define INT_RISING_INTC_SET_PD            ((reg32 *) INT_RISING__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the INT_RISING interrupt. */
#define INT_RISING_INTC_CLR_PD            ((reg32 *) INT_RISING__INTC_CLR_PD_REG)


#endif /* CY_ISR_INT_RISING_H */


/* [] END OF FILE */
