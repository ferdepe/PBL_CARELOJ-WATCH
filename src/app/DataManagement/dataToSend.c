/**
 * @file    dataToSend.c
 * @brief   Fuente de las funciones para el manejo de datos entre tareas
 * @par		Descripción de funciones:
 * 			En este fichero se implementan las funciones para poder escribir y leer sobre variables privadas
 * 			al fichero que permiten comunicar las tareas del programa de CARELOJ: Lógica, Envío y Pantalla
 * @version 1.6
 * @author  F. Domínguez
 * @date    17/05/2015
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "dataToSend.h"
#include "dataSensors.h"

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

static DATAMANAGEMENT_DATA_SEND dataToSend;
static DATAMANAGEMENT_EMERGENCY_SEND emergencyToSend;

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
void APP_DATA_TOSEND_initStructs(void){
	/* Init estructura Datos */
	dataToSend.nIdUsuario =ID_DISP;
	dataToSend.nNumSensores = NUMBER_SENSORS;
	dataToSend.bDatoPendEnv = 0;

	/* Init estructura Emergencia */
	emergencyToSend.nIdUsuario =ID_DISP;
	emergencyToSend.bDatoPendEnv = 0;

}

/*******************ENVÍO NORMAL*********************/

void APP_DATA_DATA_TOSEND_setDataToSend(int nIdSensor){
	dataToSend.valuesRegister[nIdSensor] = APP_DATA_SENSORS_getSensorData(nIdSensor);
}
DATAMANAGEMENT_DATA_SEND APP_DATA_TOSEND_getDataToSend(void){
	return dataToSend;
}
unsigned int APP_DATA_TOSEND_readyToSendData(void){
	dataToSend.bDatoPendEnv = 1;
	return RETURN_OK;
}

unsigned int APP_DATA_TOSEND_dataSentOK(void){
	dataToSend.bDatoPendEnv = 0;
	return RETURN_OK;
}

/*****************ENVÍO EMERGENCIA*******************/

void APP_DATA_TOSEND_setDataToEmergency(float nPulsaciones, GPS_DATA nValoresGPS){
	emergencyToSend.fValueBPM = nPulsaciones;
	emergencyToSend.valuesGPS = nValoresGPS;
}

DATAMANAGEMENT_EMERGENCY_SEND APP_DATA_TOSEND_getDataToEmergency(void){
	return emergencyToSend;
}

unsigned int APP_DATA_TOSEND_readyToSendEmergency(void){
	emergencyToSend.bDatoPendEnv = 1;
	return RETURN_OK;
}
unsigned int APP_DATA_TOSEND_dataSentEmergency(void){
	emergencyToSend.bDatoPendEnv = 0;
	return RETURN_OK;
}


/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/

