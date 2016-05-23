/*****************************************************
* FILE NAME: tarea_control.c                         *
*                                                    *
* PURPOSE: Conjunto de funciones para la implemen-   *
*          tación de la tarea de comunicación res-   *
*          ponsable de interactuar con las estaciones*
*          adyacentes                                *
*                                                    *
* AUTHOR: Fernando Domínguez                         *
*                                                    *
* DATE: 10/01/2015     VERSION: 1.1                  *
*                                                    *
*****************************************************/

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "tareaEnvio.h"
#include "funcionesEnvio.h"
#include "dataToSend.h"
#include "config.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
/**
 * @fn      void APP_TAREAENVIO_ejecutaTarea(void)
 * @brief   Función que llama a la ejecución de la tarea que atiende al envío
 * @par		Descripción de la función:
 * 			Esta función se encarga de ejecutar la tarea de envío de datos al exterior. A partir de dos buffers:
 * 			-Buffer de datos recogidos de los sensores que irá a la base de datos médica
 * 			-Búfer de datos recogidos en la petición de emergencia
 * @param   void
 * @return  void
*/
void APP_TAREAENVIO_ejecutaTarea(void){

	int isData = 0;
	unsigned char bufferDatosSensores[3];
	unsigned char bufferDatosEmergencia[3];


	isData = 1;
	if (isData){
		//ENVIAR DATOS A FUNCIONES DE ENVIO POR INTERNET
		APP_FUNCIONESENVIO_send("Datos de Sensor",bufferDatosSensores);
	}

	isData = 1;
	if (isData){
		//ENVIAR DATOS A FUNCIONES DE ENVIO POR GPRS
		APP_FUNCIONESENVIO_send("Datos de Emergencia",bufferDatosEmergencia);
	}
}

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/


