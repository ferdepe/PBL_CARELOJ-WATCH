/**
 * @file    dataSensor.h
 * @brief   Header de las funciones para el manejo de datos entre tareas
 * @par		Descripción de funciones:
 * 			En este fichero se declaran las funciones para poder escribir y leer sobre variables privadas
 * 			al fichero que permiten comunicar las tareas del programa de CARELOJ: Lógica, Envío y Pantalla
 * @version 1.6
 * @author  F. Domínguez
 * @date    17/05/2015
 * @todo    Revisras el id de la estructura DATAMANAGEMENT_SENSOR_DATA , si es necesario o no.
 */

#ifndef DATASENSORS_H_
#define DATASENSORS_H_

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
	CONFIG_SENSORS nId;
	float value;
}DATAMANAGEMENT_SENSOR_DATA;

typedef struct{
	int nIdUsuario;
	int nNumSensores;
	DATAMANAGEMENT_SENSOR_DATA valuesRegister[NUMBER_SENSORS];
	unsigned int bDatoPendEnv;
}DATAMANAGEMENT_DATA_SEND;

/*****************************************************
*                 EXPORTED VARIABLES                 *
*****************************************************/

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/

void APP_DATA_SENSORS_setSensorData(int nIdSensor, float fValue);
DATAMANAGEMENT_SENSOR_DATA APP_DATA_SENSORS_getSensorData(int idSensor);
DATAMANAGEMENT_DATA_SEND APP_DATA_SENSORS_getDataToSend(void);
void APP_DATA_SENSORS_dataSent(void);
int APP_DATA_SENSORS_dataReady(void);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* DATASENSORS_H_ */
