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
#include "tareaPantalla.h"#include "timer_scugic.h"
#include "axi-gpio.h"
#include "dataToSend.h"

int main()
{
	APP_DATA_TOSEND_initStructs();
	APP_PANTALLA_init();
	HAL_TIMER_SCUGIC_initTimer(1000);
	while(1){
		APP_TAREALOGICA_ejecutaTarea();
		APP_TAREAENVIO_ejecutaTarea();
		LIBS_WATCH_updateTime();
	    APP_TAREAPANTALLA_ejecutaTarea();
	}
    return 0;
}
