/*******************************************************************************
* File Name: TP_OXFF.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_TP_OXFF_H) /* Pins TP_OXFF_H */
#define CY_PINS_TP_OXFF_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TP_OXFF_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TP_OXFF__PORT == 15 && ((TP_OXFF__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TP_OXFF_Write(uint8 value);
void    TP_OXFF_SetDriveMode(uint8 mode);
uint8   TP_OXFF_ReadDataReg(void);
uint8   TP_OXFF_Read(void);
void    TP_OXFF_SetInterruptMode(uint16 position, uint16 mode);
uint8   TP_OXFF_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TP_OXFF_SetDriveMode() function.
     *  @{
     */
        #define TP_OXFF_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TP_OXFF_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TP_OXFF_DM_RES_UP          PIN_DM_RES_UP
        #define TP_OXFF_DM_RES_DWN         PIN_DM_RES_DWN
        #define TP_OXFF_DM_OD_LO           PIN_DM_OD_LO
        #define TP_OXFF_DM_OD_HI           PIN_DM_OD_HI
        #define TP_OXFF_DM_STRONG          PIN_DM_STRONG
        #define TP_OXFF_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TP_OXFF_MASK               TP_OXFF__MASK
#define TP_OXFF_SHIFT              TP_OXFF__SHIFT
#define TP_OXFF_WIDTH              1u

/* Interrupt constants */
#if defined(TP_OXFF__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TP_OXFF_SetInterruptMode() function.
     *  @{
     */
        #define TP_OXFF_INTR_NONE      (uint16)(0x0000u)
        #define TP_OXFF_INTR_RISING    (uint16)(0x0001u)
        #define TP_OXFF_INTR_FALLING   (uint16)(0x0002u)
        #define TP_OXFF_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TP_OXFF_INTR_MASK      (0x01u) 
#endif /* (TP_OXFF__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TP_OXFF_PS                     (* (reg8 *) TP_OXFF__PS)
/* Data Register */
#define TP_OXFF_DR                     (* (reg8 *) TP_OXFF__DR)
/* Port Number */
#define TP_OXFF_PRT_NUM                (* (reg8 *) TP_OXFF__PRT) 
/* Connect to Analog Globals */                                                  
#define TP_OXFF_AG                     (* (reg8 *) TP_OXFF__AG)                       
/* Analog MUX bux enable */
#define TP_OXFF_AMUX                   (* (reg8 *) TP_OXFF__AMUX) 
/* Bidirectional Enable */                                                        
#define TP_OXFF_BIE                    (* (reg8 *) TP_OXFF__BIE)
/* Bit-mask for Aliased Register Access */
#define TP_OXFF_BIT_MASK               (* (reg8 *) TP_OXFF__BIT_MASK)
/* Bypass Enable */
#define TP_OXFF_BYP                    (* (reg8 *) TP_OXFF__BYP)
/* Port wide control signals */                                                   
#define TP_OXFF_CTL                    (* (reg8 *) TP_OXFF__CTL)
/* Drive Modes */
#define TP_OXFF_DM0                    (* (reg8 *) TP_OXFF__DM0) 
#define TP_OXFF_DM1                    (* (reg8 *) TP_OXFF__DM1)
#define TP_OXFF_DM2                    (* (reg8 *) TP_OXFF__DM2) 
/* Input Buffer Disable Override */
#define TP_OXFF_INP_DIS                (* (reg8 *) TP_OXFF__INP_DIS)
/* LCD Common or Segment Drive */
#define TP_OXFF_LCD_COM_SEG            (* (reg8 *) TP_OXFF__LCD_COM_SEG)
/* Enable Segment LCD */
#define TP_OXFF_LCD_EN                 (* (reg8 *) TP_OXFF__LCD_EN)
/* Slew Rate Control */
#define TP_OXFF_SLW                    (* (reg8 *) TP_OXFF__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TP_OXFF_PRTDSI__CAPS_SEL       (* (reg8 *) TP_OXFF__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TP_OXFF_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TP_OXFF__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TP_OXFF_PRTDSI__OE_SEL0        (* (reg8 *) TP_OXFF__PRTDSI__OE_SEL0) 
#define TP_OXFF_PRTDSI__OE_SEL1        (* (reg8 *) TP_OXFF__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TP_OXFF_PRTDSI__OUT_SEL0       (* (reg8 *) TP_OXFF__PRTDSI__OUT_SEL0) 
#define TP_OXFF_PRTDSI__OUT_SEL1       (* (reg8 *) TP_OXFF__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TP_OXFF_PRTDSI__SYNC_OUT       (* (reg8 *) TP_OXFF__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TP_OXFF__SIO_CFG)
    #define TP_OXFF_SIO_HYST_EN        (* (reg8 *) TP_OXFF__SIO_HYST_EN)
    #define TP_OXFF_SIO_REG_HIFREQ     (* (reg8 *) TP_OXFF__SIO_REG_HIFREQ)
    #define TP_OXFF_SIO_CFG            (* (reg8 *) TP_OXFF__SIO_CFG)
    #define TP_OXFF_SIO_DIFF           (* (reg8 *) TP_OXFF__SIO_DIFF)
#endif /* (TP_OXFF__SIO_CFG) */

/* Interrupt Registers */
#if defined(TP_OXFF__INTSTAT)
    #define TP_OXFF_INTSTAT            (* (reg8 *) TP_OXFF__INTSTAT)
    #define TP_OXFF_SNAP               (* (reg8 *) TP_OXFF__SNAP)
    
	#define TP_OXFF_0_INTTYPE_REG 		(* (reg8 *) TP_OXFF__0__INTTYPE)
#endif /* (TP_OXFF__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TP_OXFF_H */


/* [] END OF FILE */
