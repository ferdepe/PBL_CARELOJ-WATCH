/**
 * @file      timer_ttc.c
 * @brief     Short description.
 * @par		  Descripción de la función:
 * 			  par1
 *            par2
 * @author    F.Domínguez
 * @date      dd/mm/yyyy
 * @version   1.0
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "timer_ttc.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/
#define TTC_TICK_DEVICE_ID	XPAR_XTTCPS_0_DEVICE_ID
#define TTC_TICK_INTR_ID	XPAR_XTTCPS_0_INTR

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

typedef struct {
	u32 OutputHz;	/* Output frequency */
	u16 Interval;	/* Interval value */
	u8 Prescaler;	/* Prescaler value */
	u16 Options;	/* Option settings */
} TmrCntrSetup;

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/

static int SetupTimer(int DeviceID);
static void TickHandler(void *CallBackRef);

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

XScuGic IntcInstance;
static XTtcPs TtcPsInst;
static TmrCntrSetup SettingsTable;

static int CountTimerTTC;

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

int HAL_TIMER_TTC_TimerSetup(unsigned int nHz)
{
	int Status;
	TmrCntrSetup *TimerSetup;
	XTtcPs *TtcPsTick;

	SettingsTable.OutputHz = nHz;

	TimerSetup = &SettingsTable;

	/*
	 * Set up appropriate options for Ticker: interval mode without
	 * waveform output.
	 */
	TimerSetup->Options |= (XTTCPS_OPTION_INTERVAL_MODE |
					      XTTCPS_OPTION_WAVE_DISABLE);

	/*
	 * Calling the timer setup routine
	 *  . initialize device
	 *  . set options
	 */
	Status = SetupTimer(TTC_TICK_DEVICE_ID);
	if(Status != XST_SUCCESS) {
		return Status;
	}

	TtcPsTick = &TtcPsInst;

	/*
	 * Connect to the interrupt controller
	 */
	Status = HAL_GIC_ConnectIntRoutine(TTC_TICK_INTR_ID,
		(Xil_ExceptionHandler)TickHandler, (void *)TtcPsTick);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Enable the interrupt for the Timer counter
	 */
	HAL_GIC_EnableIntForDevice(TTC_TICK_INTR_ID);

	/*
	 * Enable the interrupts for the tick timer/counter
	 * We only care about the interval timeout.
	 */
	XTtcPs_EnableInterrupts(TtcPsTick, XTTCPS_IXR_INTERVAL_MASK);

	/*
	 * Start the tick timer/counter
	 */
	XTtcPs_Start(TtcPsTick);

	return Status;
}

int HAL_TIMER_TTC_GetTimerCount(void){
	return CountTimerTTC;
}


/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/
static int SetupTimer(int DeviceID)
{
	int Status;
	XTtcPs_Config *Config;
	XTtcPs *Timer;
	TmrCntrSetup *TimerSetup;

	TimerSetup = &SettingsTable;

	Timer = &TtcPsInst;
	/*
	 * Stop the timer first
	 */
	XTtcPs_Stop(Timer);

	/*
	 * Look up the configuration based on the device identifier
	 */
	Config = XTtcPs_LookupConfig(DeviceID);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	/*
	 * Initialize the device
	 */
	Status = XTtcPs_CfgInitialize(Timer, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Set the options
	 */
	XTtcPs_SetOptions(Timer, TimerSetup->Options);

	/*
	 * Timer frequency is preset in the TimerSetup structure,
	 * however, the value is not reflected in its other fields, such as
	 * IntervalValue and PrescalerValue. The following call will map the
	 * frequency to the interval and prescaler values.
	 */
	XTtcPs_CalcIntervalFromFreq(Timer, TimerSetup->OutputHz,
		&(TimerSetup->Interval), &(TimerSetup->Prescaler));

	/*
	 * Set the interval and prescale
	 */
	XTtcPs_SetInterval(Timer, TimerSetup->Interval);
	XTtcPs_SetPrescaler(Timer, TimerSetup->Prescaler);

	return XST_SUCCESS;
}

static void TickHandler(void *CallBackRef)
{
	u32 StatusEvent;

	/*
	 * Read the interrupt status, then write it back to clear the interrupt.
	 */
	StatusEvent = XTtcPs_GetInterruptStatus((XTtcPs *)CallBackRef);
	XTtcPs_ClearInterruptStatus((XTtcPs *)CallBackRef, StatusEvent);

	CountTimerTTC++;

}
