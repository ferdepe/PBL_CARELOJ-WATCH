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
#include "lwip_tcp.h"
#include "dataEmergency.h"

#include "netif/xadapter.h"

static GPS_DATA gps = {.north_degree=10, .south_degree= 34};
static DATAMANAGEMENT_EMERGENCY_SEND emergencySend = {.nIdUsuario= 32323435, .fValueBPM= 225.3, .bDatoPendEnv =1};

struct netif host_netif;
struct netif *time_netif;

int main()
{
	HAL_GIC_SetupInterruptSystem();
	HAL_TIMER_SCUGIC_TimerSetup();
	//HAL_TIMER_TTC_TimerSetup(1);
	HAL_LWIP_TCP_init();
	HAL_GIC_EnableProcessorARMInterrupt();
    HAL_ADC_Init();
    HAL_DISPLAY_init();
    HAL_ACELEROMETRO_init();


    emergencySend.valuesGPS = gps;

	HAL_LWIP_TCP_setBuffEnvio((char*)&emergencySend,sizeof(DATAMANAGEMENT_EMERGENCY_SEND));
	HAL_LWIP_TCP_launchClient();


    while(1){
		APP_TAREALOGICA_ejecutaTarea();
//		APP_TAREAENVIO_ejecutaTarea();
//	    APP_TAREAPANTALLA_ejecutaTarea();

	    HAL_LWIP_TCP_refreshIO();

	}
    return 0;
}
