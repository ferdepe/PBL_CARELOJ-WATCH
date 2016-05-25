/**
 * @file    dataSensors.h
 * @brief   Header de las funciones para el manejo del envío de datos de los sensores.
 * @par		Descripción de funciones:
 * 			En este fichero se declaran las funciones encargadas de reunir los datos
 * 			relacionados con los sensores y su envío. Se declaran las estructuran que
 * 			lo posibilitan.
 * @version 1.0
 * @author  F. Domínguez
 * @date    24/05/2016
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
/**
 * @struct     DATAMANAGEMENT_SENSOR_DATA
 * @brief      Almacena el tipo y dato de cada sensor.
 * @par        Descripción:
 *             - CONFIG_SENSORS nId indica el tipo de sensor
 *             - float value indica la magnitud medida del sensor.
 * @author     F. Domínguez
 * @date       24/05/2016
 */
typedef struct{
	CONFIG_SENSORS nId;
	float value;
}DATAMANAGEMENT_SENSOR_DATA;

/**
 * @struct     DATAMANAGEMENT_DATA_SEND
 * @brief      Almacena la información a ser mandada de los sensores.
 * @par        Descripción:
 *             - int nIdUsuario es el identificador del dispositivo asignado
 *             - int nNumSensores es el número de sensores asociados al dispositivo.
 *             - DATAMANAGEMENT_SENSOR_DATA valuesRegister[NUMBER_SENSORS] son los valores almacenados del sensor
 *             - unsigned int bDatoPendEnv flag que indica si hay dato a enviar o no.
 * @author     F. Domínguez
 * @date       24/05/2016
 */
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
