/**
 * @file    dataEmergency.h
 * @brief   Header de las funciones para el manejo del envío de datos de Emergencia.
 * @par		Descripción de funciones:
 * 			En este fichero se declaran las funciones para poder escribir y leer sobre
 * 			la variable privada en forma de estructura encargada de reunir todos los datos
 * 			necesarios a enviar durante el protocolo de Emergencia.
 * @version 1.0
 * @author  F. Domínguez
 * @date    24/05/2016
 */

#ifndef DATAEMERGENCY_H_
#define DATAEMERGENCY_H_

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
 * @struct     GPS_DATA
 * @brief      Almacena las coordenadas del GPS
 * @par        Descripción:
 *             - Grados, minutos y segundos NORTE
 *             - float value indica la magnitud medida del sensor.
 * @author     F. Domínguez
 * @date       25/05/2016
 */
typedef struct{
	int north_degree;
	int north_min;
	//float north_sec;
	int south_degree;
	int south_min;
	//float south_sec;
}GPS_DATA;

/**
 * @struct     DATAMANAGEMENT_EMERGENCY_SEND
 * @brief      Almacena la información a ser mandada de los sensores.
 * @par        Descripción:
 *             - int nIdUsuario es el identificador del dispositivo asignado
 *             - float fValueBPM
 *             - GPS_DATA valuesGPS
 *             - unsigned int bDatoPendEnv flag que indica si hay datos de emergencia a enviar o no.
 * @author     F. Domínguez
 * @date       24/05/2016
 */
typedef struct{
	int nIdUsuario;
	float fValueBPM;
	GPS_DATA valuesGPS;
	unsigned int bDatoPendEnv;
}DATAMANAGEMENT_EMERGENCY_SEND;

/*****************************************************
*                 EXPORTED VARIABLES                 *
*****************************************************/

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/
void APP_DATA_EMERGENCY_setDataToEmergency(float nPulsaciones, GPS_DATA nValoresGPS);
DATAMANAGEMENT_EMERGENCY_SEND APP_DATA_EMERGENCY_getDataToEmergency(void);
int APP_DATA_EMERGENCY_dataReady(void);
void APP_DATA_EMERGENCY_emergencySent(void);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* DATAEMERGENCY_H_ */
