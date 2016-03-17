/*****************************************************
* FILE NAME: tarea_control.c                         *
*                                                    *
* PURPOSE: Conjunto de funciones para la implemen-   *
*          taci�n de la tarea de comunicaci�n res-   *
*          ponsable de interactuar con las estaciones*
*          adyacentes                                *
*                                                    *
* AUTHOR: Fernando Dom�nguez                         *
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
 * @brief   Funci�n que llama a la ejecuci�n de la tarea que atiende al env�o
 * @par		Descripci�n de la funci�n:
 * 			Esta funci�n se encarga de ejecutar la tarea de env�o de datos al exterior. A partir de dos buffers:
 * 			-Buffer de datos recogidos de los sensores que ir� a la base de datos m�dica
 * 			-B�fer de datos recogidos en la petici�n de emergencia
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


