/**
 * @file    dataSensor.h
 * @brief   Header de las funciones para el manejo de datos entre tareas
 * @par		Descripci�n de funciones:
 * 			En este fichero se declaran las funciones para poder escribir y leer sobre variables privadas
 * 			al fichero que permiten comunicar las tareas del programa de CARELOJ: L�gica, Env�o y Pantalla
 * @version 1.6
 * @author  F. Dom�nguez
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

/*****************************************************
*                 EXPORTED VARIABLES                 *
*****************************************************/

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/

void APP_DATA_SENSORS_setSensorData(int nIdSensor, float fValue);
DATAMANAGEMENT_SENSOR_DATA APP_DATA_SENSORS_getSensorData(int idSensor);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* DATASENSORS_H_ */
