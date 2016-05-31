/**
 * @file      gic_arm.c
 * @brief     Short description.
 * @par		  Descripción de la función:
 * 			  par1
 *            par2
 * @author    F. Domínguez
 * @date      dd/mm/yyyy
 * @version   1.0
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "gic_arm.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/

//Declaración funciones privadas

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

//variables globales, precedidas de static (privada)

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

int HAL_GIC_SetupInterruptSystem(void){
	int Status;

	XScuGic_Config *IntcConfig;

	/*
	 * Initialize the interrupt controller driver so that it is ready to
	 * use.
	 */
	IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
	if (NULL == IntcConfig) {
		return XST_FAILURE;
	}

	Status = XScuGic_CfgInitialize(&IntcInstance, IntcConfig,
					IntcConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	Xil_ExceptionInit();



	/*
	 * Connect the interrupt controller interrupt handler to the hardware
	 * interrupt handling logic in the processor.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
				(Xil_ExceptionHandler)XScuGic_InterruptHandler,
				&IntcInstance);

	return XST_SUCCESS;
}
void HAL_GIC_EnableProcessorARMInterrupt(){
	Xil_ExceptionEnable();
}
int HAL_GIC_ConnectIntRoutine(u32 Int_Id, Xil_InterruptHandler Handler, void *CallBackRef){
	int Status;

	Status = XScuGic_Connect(&IntcInstance, Int_Id, Handler,CallBackRef);

	if (Status != XST_SUCCESS) {
		return Status;
	}

	return XST_SUCCESS;
}

void HAL_GIC_EnableIntForDevice(u32 Int_Id){
	XScuGic_Enable(&IntcInstance, Int_Id);
}
/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/

//Funciones privadas


