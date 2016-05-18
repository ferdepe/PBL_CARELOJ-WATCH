/**
 * @file    dataManagement.h
 * @brief   Header de las funciones para el manejo de datos entre tareas
 * @par		Descripción de funciones:
 * 			En este fichero se declaran las funciones para poder escribir y leer sobre variables privadas
 * 			al fichero que permiten comunicar las tareas del programa de CARELOJ: Lógica, Envío y Pantalla
 * @version 1.6
 * @author  F. Domínguez
 * @date    17/05/2015
 * @todo    Revisras el id de la estructura DATAMANAGEMENT_SENSOR_DATA , si es necesario o no.
 */

#ifndef DATAMANAGEMENT_H_
#define DATAMANAGEMENT_H_

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "config.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

typedef struct{
	int north_degree;
	int north_min;
	float north_sec;
	int south_degree;
	int south_min;
	float south_sec;
}GPS_DATA;

typedef struct{
	CONFIG_SENSORS nId;
	float value;
}DATAMANAGEMENT_SENSOR_DATA;

typedef struct{
	int nIdUsuario;
	int nNumSensores;
	DATAMANAGEMENT_SENSOR_DATA valuesRegister[NUMBER_SENSORS];
	char bDatoPendEnv;
}DATAMANAGEMENT_DATA_SEND;

typedef struct{
	int nIdUsuario;
	float fValueBPM;
	GPS_DATA valuesGPS;
	char bDatoPendEnv;
}DATAMANAGEMENT_EMERGENCY_SEND;

/*****************************************************
*                 EXPORTED VARIABLES                 *
*****************************************************/

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/

void APP_DATAMANAGEMENT_initDataStructs(void);

void APP_DATAMANAGEMENT_setIdPantalla(unsigned int nId);
unsigned int APP_DATAMANAGEMENT_getIdPantalla(void);

void APP_DATAMANAGEMENT_setSensorData(int nIdSensor, float fValue);
DATAMANAGEMENT_SENSOR_DATA APP_DATAMANAGEMENT_getSensorData(int idSensor);

void APP_DATAMANAGEMENT_setDataToSend(int nIdSensor, float fValue);
DATAMANAGEMENT_SENSOR_DATA APP_DATAMANAGEMENT_getDataToSend(void);

void APP_DATAMANAGEMENT_setDataToEmergency(float nPulsaciones, GPS_DATA nValoresGPS);
DATAMANAGEMENT_SENSOR_DATA APP_DATAMANAGEMENT_getDataToEmergency(void);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* DATAMANAGEMENT_H_ */
