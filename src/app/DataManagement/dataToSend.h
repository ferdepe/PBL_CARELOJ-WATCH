/**
 * @file    dataToSend.h
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
#include "dataSensors.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

#define RETURN_OK 0

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

void APP_DATA_TOSEND_initStructs(void);

void APP_DATA_DATA_TOSEND_setDataToSend(int nIdSensor);
DATAMANAGEMENT_DATA_SEND APP_DATA_TOSEND_getDataToSend(void);
unsigned int APP_DATA_TOSEND_readyToSendData(void);
unsigned int APP_DATA_TOSEND_dataSentOK(void);

void APP_DATA_TOSEND_setDataToEmergency(float nPulsaciones, GPS_DATA nValoresGPS);
DATAMANAGEMENT_EMERGENCY_SEND APP_DATA_TOSEND_getDataToEmergency(void);
unsigned int APP_DATA_TOSEND_readyToSendEmergency(void);
unsigned int APP_DATA_TOSEND_dataSentEmergency(void);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* DATAMANAGEMENT_H_ */
