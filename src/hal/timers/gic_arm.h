/**
 * @file      gic_arm.h
 * @brief     Short description.
 * @par		  Descripción del fichero:
 * 			  par1
 *            par2
 * @author    F. Domínguez
 * @date      dd/mm/yyyy
 * @version   1.0
 */

#ifndef GIC_ARM_H_
#define GIC_ARM_H_

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "xscugic.h"
#include "xparameters.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *j
*****************************************************/

#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*                 EXPORTED VARIABLES                 *
*****************************************************/

extern XScuGic IntcInstance;		/* Interrupt Controller Instance */

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/

int HAL_GIC_SetupInterruptSystem();
void HAL_GIC_EnableProcessorARMInterrupt();
int HAL_GIC_ConnectIntRoutine(u32 Int_Id, Xil_InterruptHandler Handler, void *CallBackRef);
void HAL_GIC_EnableIntForDevice(u32 Int_Id);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* GIC_ARM_H_ */
