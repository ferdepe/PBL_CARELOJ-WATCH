/**
 * @file      timer_scugic.c
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

#include "timer_scugic.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/
#define TIMER_DEVICE_ID		XPAR_XSCUTIMER_0_DEVICE_ID
#define TIMER_IRPT_INTR		XPAR_SCUTIMER_INTR

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/

static int InterruptSetup(void);
static void TimerIntrHandler(void *CallBackRef);

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

XScuGic IntcInstance;
XScuTimer TimerInstance;
static int CountTimerSCUGIC;

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

int HAL_TIMER_SCUGIC_TimerSetup(int nHz){

	int Status;

	XScuTimer_Config *ConfigPtr;

	/*
	 * Initialize the Scu Private Timer driver.
	 */
	ConfigPtr = XScuTimer_LookupConfig(TIMER_DEVICE_ID);

	/*
	 * This is where the virtual address would be used, this example
	 * uses physical address.
	 */
	Status = XScuTimer_CfgInitialize(&TimerInstance, ConfigPtr,
					ConfigPtr->BaseAddr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XScuTimer_SelfTest(&TimerInstance);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	InterruptSetup();

	/*
	 * Enable Auto reload mode.
	 */
	XScuTimer_EnableAutoReload(&TimerInstance);

	/*
	 * Load the timer counter register.
	 */

	XScuTimer_LoadTimer(&TimerInstance, XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / (2*nHz));

	/*
	 * Start the timer counter and then wait for it
	 * to timeout a number of times.
	 */
	XScuTimer_Start(&TimerInstance);

	return XST_SUCCESS;
}


int HAL_TIMER_SCUGIC_GetTimerCount(void){
	return CountTimerSCUGIC;
}

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/
static int InterruptSetup(void){

	int Status;
	/*
	 * Connect the device driver handler that will be called when an
	 * interrupt for the device occurs, the handler defined above performs
	 * the specific interrupt processing for the device.
	 */

	Status = HAL_GIC_ConnectIntRoutine(TIMER_IRPT_INTR,
				(Xil_ExceptionHandler)TimerIntrHandler,
				(void *)&TimerInstance);
	if (Status != XST_SUCCESS) {
		return Status;
	}

	/*
	 * Enable the interrupt for the device.
	 */
	HAL_GIC_EnableIntForDevice(TIMER_IRPT_INTR);

	/*
	 * Enable the timer interrupts for timer mode.
	 */
	XScuTimer_EnableInterrupt(&TimerInstance);

	return XST_SUCCESS;
}

static void TimerIntrHandler(void *CallBackRef)
{
	XScuTimer *TimerInstancePtr = (XScuTimer *) CallBackRef;

	/*
	 * Check if the timer counter has expired, checking is not necessary
	 * since that's the reason this function is executed, this just shows
	 * how the callback reference can be used as a pointer to the instance
	 * of the timer counter that expired, increment a shared variable so
	 * the main thread of execution can see the timer expired.
	 */

	CountTimerSCUGIC++;
	XScuTimer_ClearInterruptStatus(TimerInstancePtr);

}
