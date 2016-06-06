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
#include "funcionesEnvio.h"
#include "dataSensors.h"
#include "dataEmergency.h"
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
void APP_TAREAENVIO_init(void){
	APP_FUNCIONESENVIO_initChannel();
}

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

	DATAMANAGEMENT_DATA_SEND dataToSend;
	DATAMANAGEMENT_EMERGENCY_SEND emergencyToSend;
	unsigned int len_datos = sizeof(DATAMANAGEMENT_DATA_SEND);
	unsigned int len_emergencia = sizeof(DATAMANAGEMENT_EMERGENCY_SEND);


	if (APP_DATA_SENSORS_dataReady()){
		//ENVIAR DATOS A FUNCIONES DE ENVIO POR INTERNET
		dataToSend = APP_DATA_SENSORS_getDataToSend();
		APP_FUNCIONESENVIO_send((char*)&dataToSend, len_datos);
		APP_DATA_SENSORS_dataSent();

	}

	if (APP_DATA_EMERGENCY_dataReady()){
		//ENVIAR DATOS A FUNCIONES DE ENVIO POR GPRS
		emergencyToSend = APP_DATA_EMERGENCY_getDataToEmergency();
		APP_FUNCIONESENVIO_send((char*)&emergencyToSend, len_emergencia);
		APP_DATA_EMERGENCY_emergencySent();
	}

	APP_FUNCIONESENVIO_refresh();
}

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/


