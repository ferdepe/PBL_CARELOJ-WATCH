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

unsigned int nIdPantalla;
DATAMANAGEMENT_SENSOR_DATA sensorValues[NUMBER_SENSORS];
DATAMANAGEMENT_DATA_SEND dataToSend;
DATAMANAGEMENT_EMERGENCY_SEND emergencyToSend;

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
void APP_DATAMANAGEMENT_initDataStructs(void){
	/* Init estructura Datos */
	dataToSend.nIdUsuario =ID_DISP;
	dataToSend.nNumSensores = NUMBER_SENSORS;
	dataToSend.bDatoPendEnv = 0;

	/* Init estructura Emergencia */
	dataToSend.nIdUsuario =ID_DISP;
	dataToSend.bDatoPendEnv = 0;

	/* Otros */
	nIdPantalla = 0;
}

void APP_DATAMANAGEMENT_setIdPantalla(unsigned int nId){
	nIdPantalla = nId;
}

unsigned int APP_DATAMANAGEMENT_getIdPantalla(void){
	return nIdPantalla;
}

void APP_DATAMANAGEMENT_setSensorData(int nIdSensor, float fValue){

}
DATAMANAGEMENT_SENSOR_DATA APP_DATAMANAGEMENT_getSensorData(int idSensor);

void APP_DATAMANAGEMENT_setDataToSend(int nIdSensor, float fValue);
DATAMANAGEMENT_SENSOR_DATA APP_DATAMANAGEMENT_getDataToSend(void);

void APP_DATAMANAGEMENT_setDataToEmergency(float nPulsaciones, GPS_DATA nValoresGPS);
DATAMANAGEMENT_SENSOR_DATA APP_DATAMANAGEMENT_getDataToEmergency(void);


/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/

