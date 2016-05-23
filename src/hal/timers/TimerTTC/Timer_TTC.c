
/**
 * @file      Timer.c
 * @brief     Implementacion de la logica del timer e interrupciones.
 * @par		  Descripción de la función:
 * 			  par1
 *            par2
 * @author    Mikel Etxebeste
 * @date      18/05/2016
 * @version   1.0
 * @todo      todo
 * @bug       bug
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include <stdio.h>
//#include "platform.h"
#include "Xscugic.h"
#include "xscutimer.h"
#include "xttcps.h"
#include "xparameters.h"
#include "Timer_TTC.h"
#include "xil_types.h"
#include "Xil_exception.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

#define TTC_DEVICE_ID       XPAR_XTTCPS_0_DEVICE_ID
#define TTC_INTR_ID         XPAR_XTTCPS_0_INTR
#define INTC_DEVICE_ID      XPAR_SCUGIC_SINGLE_DEVICE_ID

//#define TIMER_DEVICE_ID XPAR_XSCUTIMER_0_DEVICE_ID
//#define INTC_DEVICE_ID XPAR_SCUGIC_SINGLE_DEVICE_ID
//#define TIMER_IRPT_INTR XPAR_SCUTIMER_INTR
//#define TIMER_LOAD_VALUE (10*(XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / 2))

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/
 /**
 * @struct     TmrCntrSetup
 * @brief      Estructura definida mayormente para indicar la frecuencia de interrupcion del timer y en que opción se va usar.
 * @par        Descripción:
 *             - OutputHz: Frecuencia de salida
 *             - Interval: Valor del intervalo
 *             - Prescaler: Valor del prescalar.
 *             - Options: opciones de setting del timer.
 * @author     author
 * @date       dd/mm/yyyy
*/
typedef struct
{
            u32 OutputHz;           /* Output frequency */
            u16 Interval;           /* Interval value */
            u8 Prescaler;           /* Prescaler value */
            u16 Options;            /* Option settings */
} TmrCntrSetup;

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/

/**
 * @fn         SetupInterruptSystemTTC
 * @brief      Es el Set Up para que la interrupción del timer se inicialice.
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @param[1]   XScuGic *PunteroAlaInstancia
 * @param[2]   XTtcPs *PunteroDeLaInterrupcion.
 * @author     Mikel Etxebeste
 * @date       18/05/2016
 **/
static void SetupInterruptSystemTTC(XScuGic *GicInstancePtr, XTtcPs *TtcPsInt);
/**
 * @fn         TickHandler
 * @brief      Es el código que se hace cuando salta la interrupción.
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @param[1]  void CallBack de la función
 * @author     Mikel Etxebeste
 * @date       18/05/2016
 **/
static void TickHandler(void *CallBackRef);
/**
 * @fn         Empezar_Timer
 * @brief      Es el Set Up para que la interrupción del timer se inicialice.
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @author     Mikel Etxebeste
 * @date       18/05/2016
 **/
void Empezar_Timer();

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/
/**
* @var       Intc
* @brief     Instancia al sistema de interrupcion.
* @author    Mikel Etxebeste
* @date      18/05/2016
*/
static XScuGic Intc;
/**
* @var       cnt
* @brief     Counter para contar el numero de interrupciones.
* @author    Mikel Etxebeste
* @date      18/05/2016
*/
static int cnt = 0;
/**
* @var       Timer
* @brief     Instancia para utilizar el Timer.
* @author    Mikel Etxebeste
* @date      18/05/2016
*/
XTtcPs Timer;

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

void HAL_TIMER_TTC_initTimer(){

	static TmrCntrSetup SettingsTable[1] =
	{
	            {1, 10, 0, 0},           /* Ticker timer counter initial setup, only output freq */
	};

	long int delay, ust_limit = 83333323;
	int i, Status;

	XTtcPs_Config *Config;
	TmrCntrSetup *TimerSetup;


	TimerSetup = &SettingsTable[TTC_DEVICE_ID];
	XTtcPs_Stop(&Timer);
	XTtcPs_ResetCounterValue(&Timer);

	printf("Microcarsil Timer TCC \n\r");

	//initialise the timer
	Config = XTtcPs_LookupConfig(TTC_DEVICE_ID);
	XTtcPs_CfgInitialize(&Timer, Config, Config->BaseAddress);

	TimerSetup->Options |= (XTTCPS_OPTION_INTERVAL_MODE | XTTCPS_OPTION_WAVE_DISABLE);

	XTtcPs_SetOptions(&Timer, TimerSetup->Options);
	XTtcPs_CalcIntervalFromFreq(&Timer, TimerSetup->OutputHz,&(TimerSetup->Interval), &(TimerSetup->Prescaler));

	XTtcPs_SetInterval(&Timer, TimerSetup->Interval);
	XTtcPs_SetPrescaler(&Timer, TimerSetup->Prescaler);

	SetupInterruptSystemTTC(&Intc, &Timer);

	Empezar_Timer();
}

unsigned int HAL_TIMER_TTC_getCount(){
	return cnt;
}
/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/


void Empezar_Timer(){

	XTtcPs_Start(&Timer);

	 //XScuTimer_Start(&Timer);

}

static void SetupInterruptSystemTTC(XScuGic *GicInstancePtr, XTtcPs *TtcPsInt)
{

            XScuGic_Config *IntcConfig; //GIC config
            Xil_ExceptionInit();

            //initialise the GIC
            IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);

            XScuGic_CfgInitialize(GicInstancePtr, IntcConfig, IntcConfig->CpuBaseAddress);

            //connect to the hardware
            Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XScuGic_InterruptHandler, GicInstancePtr);

            XScuGic_Connect(GicInstancePtr, TTC_INTR_ID,(Xil_ExceptionHandler)TickHandler, (void *)TtcPsInt);


            XScuGic_Enable(GicInstancePtr, TTC_INTR_ID);
            XTtcPs_EnableInterrupts(TtcPsInt, XTTCPS_IXR_INTERVAL_MASK);

            //XTtcPs_Start(TtcPsInt);

            // Enable interrupts in the Processor.
            Xil_ExceptionEnableMask(XIL_EXCEPTION_IRQ);
}


static void TickHandler(void *CallBackRef)
{
            u32 StatusEvent;
            //static int cntinterno = 0;
            StatusEvent = XTtcPs_GetInterruptStatus((XTtcPs *)CallBackRef);
            XTtcPs_ClearInterruptStatus((XTtcPs *)CallBackRef, StatusEvent);

            //printf("cnt = %d\n\r", cnt++);
            cnt++;

            //XTtcPs_Start(&Timer);

}



