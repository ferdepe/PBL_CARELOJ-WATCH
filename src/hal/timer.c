/**
 * @file    timer.c
 * @brief   Implementación para manejar un único timer
 * @par		Descripción del fichero:
 *          Las funciones aquí implementadas permiten implementar
 *          un timer que provocará una interrupción cada
 *          x msecs indicados
 * @author  F. Domínguez
 * @date    04/03/2016
 * @version 1.0
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/
#include "timer.h"
#include "xil_printf.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "xparameters.h"
#include "simpleScheduler.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/
#define INTC_DEVICE_ID      XPAR_SCUGIC_SINGLE_DEVICE_ID
#define TIMER_DEVICE_ID     XPAR_SCUTIMER_DEVICE_ID
#define INTC_BASE_ADDR      XPAR_SCUGIC_CPU_BASEADDR
#define INTC_DIST_BASE_ADDR XPAR_SCUGIC_DIST_BASEADDR
#define TIMER_IRPT_INTR     XPAR_SCUTIMER_INTR

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/
static void HAL_TIMER_enable_interrupts();
static void HAL_TIMER_setup_interrupts();
static void HAL_TIMER_setup_timer(int msecs);
static void HAL_TIMER_timer_callback(XScuTimer * TimerInstance); //Añado static
/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/
static unsigned int count = 0;
static float step = 0;
static XScuTimer TimerInstance; //Elemento al que se le asigna una iterrupción del timer. Representará un timer.

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
void HAL_TIMER_initTimer(unsigned int msecs) {
#ifdef ZYNQ_7000
	/*
	 * Se inicializa primero el timer,
	 * luego las interrupciones
	 * y por último las lanzamos
	 */
	HAL_TIMER_setup_timer(msecs);
	HAL_TIMER_setup_interrupts();
	HAL_TIMER_enable_interrupts();
#endif
}

/*
 * Devuelve el valor acumulado de interrupciones del timer
 */
unsigned int HAL_TIMER_getTimerCount() {
	return count;
}

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/
/*
 * Aumenta un contador cuando se produce la interrupción del timer
 */
void HAL_TIMER_timer_callback(XScuTimer * TimerInstance) {
	count++;
#ifdef SIMPLE_SCHEDULER
	SIMPLE_SCHEDULER_update();
#endif
	XScuTimer_ClearInterruptStatus(TimerInstance); //Pone flag a 0
}

/*
 * Configura el timer para que haga interrupción cada "msecs"
 * milisegundos.
 */
static void HAL_TIMER_setup_timer(int msecs) {
#ifdef ZYNQ_7000
	int Status = XST_SUCCESS;
	XScuTimer_Config *ConfigPtr;
	int TimerLoadValue = 0;
	step = 1000 / msecs;

	//Inicializacion
	ConfigPtr = XScuTimer_LookupConfig(TIMER_DEVICE_ID);
	Status = XScuTimer_CfgInitialize(&TimerInstance, ConfigPtr,
			ConfigPtr->BaseAddr);

	if (Status != XST_SUCCESS) {
		xil_printf("In %s: Scutimer Cfg initialization failed...\r\n",
				__func__);
		return;
	}

	Status = XScuTimer_SelfTest(&TimerInstance);

	if (Status != XST_SUCCESS) {
		xil_printf("In %s: Scutimer Self test failed...\r\n", __func__);
		return;
	}

	XScuTimer_EnableAutoReload(&TimerInstance);
	/*El dos es debido  que el clock del timer va a la mitad del de la cpu*/
	TimerLoadValue = XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / (step * 2);
	XScuTimer_LoadTimer(&TimerInstance, TimerLoadValue);
#endif
	return;

}

/*
 * Configura las interrupciones
 */
static void HAL_TIMER_setup_interrupts() {
#ifdef ZYNQ_7000
	Xil_ExceptionInit();

	XScuGic_DeviceInitialize(INTC_DEVICE_ID);

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT,
			(Xil_ExceptionHandler) XScuGic_DeviceInterruptHandler,
			(void *) INTC_DEVICE_ID);
	/*Conecte*/
	XScuGic_RegisterHandler(INTC_BASE_ADDR, TIMER_IRPT_INTR,
			(Xil_ExceptionHandler) HAL_TIMER_timer_callback,
			(void *) &TimerInstance);
	//Habilita la interrupción para el scu timer
	XScuGic_EnableIntr(INTC_DIST_BASE_ADDR, TIMER_IRPT_INTR);
#endif
	return;
}

/*
 * Habilita las interrupciones
 */
static void HAL_TIMER_enable_interrupts() {
#ifdef ZYNQ_7000
	/* Enable non-critical exceptions.*/
	Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
	XScuTimer_EnableInterrupt(&TimerInstance);
	XScuTimer_Start(&TimerInstance);
#endif
	return;

}
