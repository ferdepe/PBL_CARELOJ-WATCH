/**
 * @file    main.c
 * @brief   Fichero principal
 * @par		Logica
 *			- Inizializa las tareas y el hardware
 *			- Tarea para gestionar el control de la máquina de estados del reloj
 *			- Tarea para gestionar el envío de datos del reloj al exterior
 * @par		Flujo
 * @image	html diagrama.genral.jpg
 * @author  J. Barragán
 * @author  F. Domínguez
 * @author  M. Etxebeste
 * @date    19/02/2016
 * @todo	Implementar control entre tareas
 */


#include "tareaLogica.h"
#include "tareaEnvio.h"
#include "timer.h"
#include "axi-gpio.h"
#include "dataManagement.h"


int main()
{
    int pinActual;
	APP_DATAMANAGEMENT_initBuffers();

	HAL_TIMER_initTimer(100);

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
