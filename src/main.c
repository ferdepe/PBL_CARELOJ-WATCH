/**
 * @file    main.c
 * @brief   Fichero principal
 * @par		Logica
 *			- Inicializa las tareas y el hardware
 *			- Tarea para gestionar el control de la m�quina de estados del reloj
 *			- Tarea para gestionar el env�o de datos del reloj al exterior
 * @par		Flujo
 * @image	html diagrama.genral.jpg
 * @author  F. Dom�nguez
 * @date    19/02/2016
 * @todo	Implementar control entre tareas
 * @todo    A�adir tarea de control de pantalla
 * @todo    Crear funci�n para la inicializaci�n
 */


#include "tareaLogica.h"
#include "tareaEnvio.h"
#include "timer_scugic.h"
#include "Timer_TTC.h"
#include "Adc.h"
#include "axi-gpio.h"
#include "dataToSend.h"


int main()
{

	HAL_TIMER_SCUGIC_initTimer(100);
	HAL_TIMER_TTC_initTimer();
	HAL_ADC_Init();
	APP_DATA_TOSEND_initStructs();

	while(1){
		APP_TAREALOGICA_ejecutaTarea();
		APP_TAREAENVIO_ejecutaTarea();
		/*
		pinActual = HAL_AXI_GPIO_readAxiButtonPin(0);
		HAL_AXI_GPIO_writeAxiLedPin(0,pinActual);
		pinActual = HAL_AXI_GPIO_readAxiButtonPin(2);
		HAL_AXI_GPIO_writeAxiLedPin(2,pinActual);
	    */
	}

    return 0;
}
