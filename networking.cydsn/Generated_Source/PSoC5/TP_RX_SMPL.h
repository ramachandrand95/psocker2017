/*******************************************************************************
* File Name: TP_RX_SMPL.h  
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

#if !defined(CY_PINS_TP_RX_SMPL_H) /* Pins TP_RX_SMPL_H */
#define CY_PINS_TP_RX_SMPL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TP_RX_SMPL_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TP_RX_SMPL__PORT == 15 && ((TP_RX_SMPL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TP_RX_SMPL_Write(uint8 value);
void    TP_RX_SMPL_SetDriveMode(uint8 mode);
uint8   TP_RX_SMPL_ReadDataReg(void);
uint8   TP_RX_SMPL_Read(void);
void    TP_RX_SMPL_SetInterruptMode(uint16 position, uint16 mode);
uint8   TP_RX_SMPL_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TP_RX_SMPL_SetDriveMode() function.
     *  @{
     */
        #define TP_RX_SMPL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TP_RX_SMPL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TP_RX_SMPL_DM_RES_UP          PIN_DM_RES_UP
        #define TP_RX_SMPL_DM_RES_DWN         PIN_DM_RES_DWN
        #define TP_RX_SMPL_DM_OD_LO           PIN_DM_OD_LO
        #define TP_RX_SMPL_DM_OD_HI           PIN_DM_OD_HI
        #define TP_RX_SMPL_DM_STRONG          PIN_DM_STRONG
        #define TP_RX_SMPL_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TP_RX_SMPL_MASK               TP_RX_SMPL__MASK
#define TP_RX_SMPL_SHIFT              TP_RX_SMPL__SHIFT
#define TP_RX_SMPL_WIDTH              1u

/* Interrupt constants */
#if defined(TP_RX_SMPL__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TP_RX_SMPL_SetInterruptMode() function.
     *  @{
     */
        #define TP_RX_SMPL_INTR_NONE      (uint16)(0x0000u)
        #define TP_RX_SMPL_INTR_RISING    (uint16)(0x0001u)
        #define TP_RX_SMPL_INTR_FALLING   (uint16)(0x0002u)
        #define TP_RX_SMPL_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TP_RX_SMPL_INTR_MASK      (0x01u) 
#endif /* (TP_RX_SMPL__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TP_RX_SMPL_PS                     (* (reg8 *) TP_RX_SMPL__PS)
/* Data Register */
#define TP_RX_SMPL_DR                     (* (reg8 *) TP_RX_SMPL__DR)
/* Port Number */
#define TP_RX_SMPL_PRT_NUM                (* (reg8 *) TP_RX_SMPL__PRT) 
/* Connect to Analog Globals */                                                  
#define TP_RX_SMPL_AG                     (* (reg8 *) TP_RX_SMPL__AG)                       
/* Analog MUX bux enable */
#define TP_RX_SMPL_AMUX                   (* (reg8 *) TP_RX_SMPL__AMUX) 
/* Bidirectional Enable */                                                        
#define TP_RX_SMPL_BIE                    (* (reg8 *) TP_RX_SMPL__BIE)
/* Bit-mask for Aliased Register Access */
#define TP_RX_SMPL_BIT_MASK               (* (reg8 *) TP_RX_SMPL__BIT_MASK)
/* Bypass Enable */
#define TP_RX_SMPL_BYP                    (* (reg8 *) TP_RX_SMPL__BYP)
/* Port wide control signals */                                                   
#define TP_RX_SMPL_CTL                    (* (reg8 *) TP_RX_SMPL__CTL)
/* Drive Modes */
#define TP_RX_SMPL_DM0                    (* (reg8 *) TP_RX_SMPL__DM0) 
#define TP_RX_SMPL_DM1                    (* (reg8 *) TP_RX_SMPL__DM1)
#define TP_RX_SMPL_DM2                    (* (reg8 *) TP_RX_SMPL__DM2) 
/* Input Buffer Disable Override */
#define TP_RX_SMPL_INP_DIS                (* (reg8 *) TP_RX_SMPL__INP_DIS)
/* LCD Common or Segment Drive */
#define TP_RX_SMPL_LCD_COM_SEG            (* (reg8 *) TP_RX_SMPL__LCD_COM_SEG)
/* Enable Segment LCD */
#define TP_RX_SMPL_LCD_EN                 (* (reg8 *) TP_RX_SMPL__LCD_EN)
/* Slew Rate Control */
#define TP_RX_SMPL_SLW                    (* (reg8 *) TP_RX_SMPL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TP_RX_SMPL_PRTDSI__CAPS_SEL       (* (reg8 *) TP_RX_SMPL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TP_RX_SMPL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TP_RX_SMPL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TP_RX_SMPL_PRTDSI__OE_SEL0        (* (reg8 *) TP_RX_SMPL__PRTDSI__OE_SEL0) 
#define TP_RX_SMPL_PRTDSI__OE_SEL1        (* (reg8 *) TP_RX_SMPL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TP_RX_SMPL_PRTDSI__OUT_SEL0       (* (reg8 *) TP_RX_SMPL__PRTDSI__OUT_SEL0) 
#define TP_RX_SMPL_PRTDSI__OUT_SEL1       (* (reg8 *) TP_RX_SMPL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TP_RX_SMPL_PRTDSI__SYNC_OUT       (* (reg8 *) TP_RX_SMPL__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TP_RX_SMPL__SIO_CFG)
    #define TP_RX_SMPL_SIO_HYST_EN        (* (reg8 *) TP_RX_SMPL__SIO_HYST_EN)
    #define TP_RX_SMPL_SIO_REG_HIFREQ     (* (reg8 *) TP_RX_SMPL__SIO_REG_HIFREQ)
    #define TP_RX_SMPL_SIO_CFG            (* (reg8 *) TP_RX_SMPL__SIO_CFG)
    #define TP_RX_SMPL_SIO_DIFF           (* (reg8 *) TP_RX_SMPL__SIO_DIFF)
#endif /* (TP_RX_SMPL__SIO_CFG) */

/* Interrupt Registers */
#if defined(TP_RX_SMPL__INTSTAT)
    #define TP_RX_SMPL_INTSTAT            (* (reg8 *) TP_RX_SMPL__INTSTAT)
    #define TP_RX_SMPL_SNAP               (* (reg8 *) TP_RX_SMPL__SNAP)
    
	#define TP_RX_SMPL_0_INTTYPE_REG 		(* (reg8 *) TP_RX_SMPL__0__INTTYPE)
#endif /* (TP_RX_SMPL__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TP_RX_SMPL_H */


/* [] END OF FILE */
