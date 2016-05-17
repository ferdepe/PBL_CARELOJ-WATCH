/**
 * @file    dataManagement.c
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

#include "dataManagement.h"

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

unsigned int DATAMANAGEMENT_idPantalla;
DATAMANAGEMENT_SENSOR_DATA DATAMANAGEMENT_SensorValues[NUMBER_SENSORS];

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

void APP_DATAMANAGEMENT_setIdPantalla(unsigned int nId){
	DATAMANAGEMENT_idPantalla = nId;
}

unsigned int APP_DATAMANAGEMENT_getIdPantalla(void){
	return DATAMANAGEMENT_idPantalla;
}

void APP_DATAMANAGEMENT_setSensorData(int nIdSensor, float fValue, int nUnits){
	DATAMANAGEMENT_SensorValues[nIdSensor].value = fValue;
	DATAMANAGEMENT_SensorValues[nIdSensor].units = nUnits;
}

DATAMANAGEMENT_SENSOR_DATA APP_DATAMANAGEMENT_getSensorData(int idSensor){
	return DATAMANAGEMENT_SensorValues[idSensor];
}

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/

