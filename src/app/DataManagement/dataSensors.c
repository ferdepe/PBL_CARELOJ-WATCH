/**
 * @file    dataSensors.c
 * @brief   Fuente de las funciones para el manejo del envío de datos de los sensores.
 * @par		Descripción de funciones:
 * 			En este fichero se implementan las funciones para poder escribir y leer sobre
 * 			las variables privadas en forma de estructura encargadas de reunir los datos
 * 			relacionados con los sensores y su envío.
 * @version 1.0
 * @author  F. Domínguez
 * @date    24/05/2016
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
/**
 * @var       DATAMANAGEMENT_SENSOR_DATA sensorValues
 * @brief     Variable privada usada para reunir todos los datos de los sensores.
 *            Id y valor.
 * @author    F. Domínguez
 * @date      24/05/2016
 */
static DATAMANAGEMENT_SENSOR_DATA sensorValues[NUMBER_SENSORS];

/**
 * @var       DATAMANAGEMENT_DATA_SEND dataToSend
 * @brief     Variable privada usada para reunir todos los datos necesarios a enviar.
 *            Lo contenido en DATAMANAGEMENT_SENSOR_DATA sensorValues más el id del
 *            usuario y el número de sensores asociados al dispositivo.
 * @author    F. Domínguez
 * @date      24/05/2016
 */
static DATAMANAGEMENT_DATA_SEND dataToSend = {.nIdUsuario = ID_DISP ,.nNumSensores = NUMBER_SENSORS ,.bDatoPendEnv = 0};

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
/**
 * @fn         void APP_DATA_SENSORS_setSensorData()
 * @brief      Función de tipo set.
 * @par		   Descripción de la función:
 * 			   Coloca en las estructuras privadsa dataToSend y sensorValues
 * 			   los valores indicados por parámetro y el flag a uno, que indica
 * 			   que aún no se ha enviado.
 * @param[in]  int nIdSensor
 * @param[in]  float fValue
 * @author     F. Domínguez
 * @date       24/05/2016
 */
void APP_DATA_SENSORS_setSensorData(int nIdSensor, float fValue){
	dataToSend.valuesRegister[nIdSensor].nId = sensorValues[nIdSensor].nId = nIdSensor;
	dataToSend.valuesRegister[nIdSensor].value = sensorValues[nIdSensor].value = fValue;
	dataToSend.bDatoPendEnv = 1;
}

/**
 * @fn         DATAMANAGEMENT_EMERGENCY_SEND APP_DATA_EMERGENCY_getDataToEmergency()
 * @brief      Función de tipo get.
 * @par		   Descripción de la función:
 * 			   Obtiene de la variable privada sensorValues los valores de los sensores recogidos
 * 			   para que sean consultados. Si procede según valor de emergencyToSend.bDatoPendEnv.
 * @param[in]  int idSensor
 * @ret        sensorValues[idSensor]
 * @author     F. Domínguez
 * @date       24/05/2016
 */
DATAMANAGEMENT_SENSOR_DATA APP_DATA_SENSORS_getSensorData(int idSensor){
	return sensorValues[idSensor];
}

/**
 * @fn         DATAMANAGEMENT_DATA_SEND APP_DATA_SENSORS_getDataToSend()
 * @brief      Función de tipo get.
 * @par		   Descripción de la función:
 * 			   Obtiene de la variable privada dataToSend los valores de los sensores recogidos
 * 			   mas el id del dispositivo para que sean enviados. Si procede según valor de
 * 			   dataToSend.bDatoPendEnv.
 * @ret        dataToSend
 * @author     F. Domínguez
 * @date       24/05/2016
 */
DATAMANAGEMENT_DATA_SEND APP_DATA_SENSORS_getDataToSend(void){
	return dataToSend;
}

/**
 * @fn         int APP_DATA_SENSORS_dataReady()
 * @brief      Función de tipo get.
 * @par		   Descripción de la función:
 * 			   Obtiene el valor de dataToSend.bDatoPendEnv. Si es 1 los datos aún no
 * 			   han sido enviados. Si es 0, ya han sido enviados.
 * @ret        emergencyToSend.bDatoPendEnv
 * @author     F. Domínguez
 * @date       24/05/2016
 */
int APP_DATA_SENSORS_dataReady(void){
	return dataToSend.bDatoPendEnv;
}

/**
 * @fn         void APP_DATA_SENSORS_dataSent()
 * @brief      Se pone el flag a 0.
 * @par		   Descripción de la función:
 * 			   Se pone el flag a 0 cuando se ha enviado la estructura correctamente.
 * @ret        dataToSend.bDatoPendEnv
 * @author     F. Domínguez
 * @date       24/05/2016
 */
void APP_DATA_SENSORS_dataSent(void){
	dataToSend.bDatoPendEnv = 0;
}


/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/


