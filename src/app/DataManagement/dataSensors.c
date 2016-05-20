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

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

void APP_DATA_SENSORS_setSensorData(int nIdSensor, float fValue){
	sensorValues[nIdSensor].nId = nIdSensor;
	sensorValues[nIdSensor].value = fValue;
}

DATAMANAGEMENT_SENSOR_DATA APP_DATA_SENSORS_getSensorData(int idSensor){
	return sensorValues[idSensor];
}


/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/


