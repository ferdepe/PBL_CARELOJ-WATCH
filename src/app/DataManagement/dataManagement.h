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
	//CONFIG_SENSORS id;
	float value;
	CONFIG_UNITS units;
}DATAMANAGEMENT_SENSOR_DATA;

/*****************************************************
*                 EXPORTED VARIABLES                 *
*****************************************************/

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/

void APP_DATAMANAGEMENT_setIdPantalla(unsigned int nId);
unsigned int APP_DATAMANAGEMENT_getIdPantalla(void);
void APP_DATAMANAGEMENT_setSensorData(int nIdSensor, float fValue, int nUnits);
DATAMANAGEMENT_SENSOR_DATA APP_DATAMANAGEMENT_getSensorData(int idSensor);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* DATAMANAGEMENT_H_ */
