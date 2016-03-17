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
#include "dataManagement.h"
#include "config.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/


STATIC_CIRCULAR_BUFFER dataBuffer_envioDatos;
STATIC_CIRCULAR_BUFFER dataBuffer_envioEmergencia;


/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/
STATIC_CIRCULAR_BUFFER DATAMANAGEMENT_envioEmergencia;
STATIC_CIRCULAR_BUFFER DATAMANAGEMENT_envioDatos;

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
	unsigned char bufferDatosSensores[LONG_TRAMA_DATOS];
	unsigned char bufferDatosEmergencia[LONG_TRAMA_DATOS];


	isData = APP_DATAMANAGEMENT_readFromBuffer(&DATAMANAGEMENT_envioDatos, bufferDatosSensores);
	if (isData){
		//ENVIAR DATOS A FUNCIONES DE ENVIO POR INTERNET
	}

	isData = APP_DATAMANAGEMENT_readFromBuffer(&DATAMANAGEMENT_envioEmergencia, bufferDatosEmergencia);
	if (isData){
		//ENVIAR DATOS A FUNCIONES DE ENVIO POR GPRS
	}
}

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/


