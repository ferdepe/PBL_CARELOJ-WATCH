/**
 * @file    main.c
 * @brief   Fichero principal
 * @par		Logica
 *			- Inicializa las tareas y el hardware
 *			- Tarea para gestionar el control de la máquina de estados del reloj
 *			- Tarea para gestionar el envío de datos del reloj al exterior
 * @par		Flujo
 * @image	html diagrama.genral.jpg
 * @author  F. Domínguez
 * @date    19/02/2016
 * @todo	Implementar control entre tareas
 * @todo    Añadir tarea de control de pantalla
 * @todo    Crear función para la inicialización
 */


#include "tareaLogica.h"
#include "tareaEnvio.h"
#include "tareaPantalla.h"
#include "gic_arm.h"
#include "timer_scugic.h"
#include "timer_ttc.h"
#include "Adc.h"
#include "axi-gpio.h"
#include "dataDisplay.h"
#include "display.h"
#include "acelerometro.h"
#include "funcionesEnvio.h"

int main()
{
	HAL_GIC_SetupInterruptSystem();
	APP_TAREAENVIO_init();
	HAL_TIMER_TTC_TimerSetup(1);
	HAL_GIC_EnableProcessorARMInterrupt();
    HAL_ADC_Init();
    HAL_DISPLAY_init();
    HAL_ACELEROMETRO_init();


    while(1){
		APP_TAREALOGICA_ejecutaTarea();
		APP_TAREAENVIO_ejecutaTarea();	    
		APP_TAREAPANTALLA_ejecutaTarea();
	}
    return 0;
}
