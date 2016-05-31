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
#include "tareaPantalla.h"
#include "timer_scugic.h"
#include "Timer_TTC.h"
#include "Adc.h"
#include "axi-gpio.h"
#include "pantalla.h"
#include "display.h"

int main()
{
	HAL_TIMER_SCUGIC_initTimer(1000);
	HAL_TIMER_TTC_initTimer();
    HAL_ADC_Init();
    HAL_DISPLAY_init();

    while(1){
		APP_TAREALOGICA_ejecutaTarea();
		APP_TAREAENVIO_ejecutaTarea();
	    APP_TAREAPANTALLA_ejecutaTarea();
	}
    return 0;
}
