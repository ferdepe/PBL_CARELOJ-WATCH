/**
 * @file    dataSensor.c
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

static DATAMANAGEMENT_SENSOR_DATA sensorValues[NUMBER_SENSORS];
static DATAMANAGEMENT_DATA_SEND dataToSend = {.nIdUsuario = ID_DISP ,.nNumSensores = NUMBER_SENSORS ,.bDatoPendEnv = 0};

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

void APP_DATA_SENSORS_setSensorData(int nIdSensor, float fValue){
	dataToSend.valuesRegister[nIdSensor].nId = sensorValues[nIdSensor].nId = nIdSensor;
	dataToSend.valuesRegister[nIdSensor].value = sensorValues[nIdSensor].value = fValue;
	dataToSend.bDatoPendEnv = 1;
}

DATAMANAGEMENT_SENSOR_DATA APP_DATA_SENSORS_getSensorData(int idSensor){
	return sensorValues[idSensor];
}

DATAMANAGEMENT_DATA_SEND APP_DATA_SENSORS_getDataToSend(void){
	return dataToSend;
}

int APP_DATA_SENSORS_dataReady(void){
	return dataToSend.bDatoPendEnv;
}

void APP_DATA_SENSORS_dataSent(void){
	dataToSend.bDatoPendEnv = 0;
}


/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/


