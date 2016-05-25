/**
 * @file    dataEmergency.c
 * @brief   Fuente de las funciones para el manejo del env�o de datos de Emergencia.
 * @par		Descripci�n de funciones:
 * 			En este fichero se implementan las funciones para poder escribir y leer sobre
 * 			la variable privada en forma de estructura encargada de reunir todos los datos
 * 			necesarios a enviar durante el protocolo de Emergencia.
 * @version 1.0
 * @author  F. Dom�nguez
 * @date    24/05/2016
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "dataEmergency.h"

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
  * @var       DATAMANAGEMENT_EMERGENCY_SEND emergencyToSend
  * @brief     Variable privada usada para reunir todos los datos necesarios a enviar.
  * @author    F. Dom�nguez
  * @date      20/05/2016
  */
static DATAMANAGEMENT_EMERGENCY_SEND emergencyToSend = {.nIdUsuario = ID_DISP, .bDatoPendEnv = 0};

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
/**
 * @fn         void APP_DATA_EMERGENCY_setDataToEmergency()
 * @brief      Funci�n de tipo set.
 * @par		   Descripci�n de la funci�n:
 * 			   Coloca en la variable privada emergencyToSend los valores indicados
 * 			   por par�metro y el flag a uno que indica que a�n no se ha enviado.
 * @param[in]  float nPulsaciones
 * @param[in]  GPS_DATA nValoresGPS
 * @author     F. Dom�nguez
 * @date       20/05/2016
 */
void APP_DATA_EMERGENCY_setDataToEmergency(float nPulsaciones, GPS_DATA nValoresGPS){
	emergencyToSend.fValueBPM = nPulsaciones;
	emergencyToSend.valuesGPS = nValoresGPS;
	emergencyToSend.bDatoPendEnv = 1;
}

/**
 * @fn         DATAMANAGEMENT_EMERGENCY_SEND APP_DATA_EMERGENCY_getDataToEmergency()
 * @brief      Funci�n de tipo get.
 * @par		   Descripci�n de la funci�n:
 * 			   Obtiene de la variable privada emergencyToSend los valores introducidos
 * 			   para que sean enviados. Si procede seg�n valor de emergencyToSend.bDatoPendEnv.
 * @ret        emergencyToSend
 * @author     F. Dom�nguez
 * @date       20/05/2016
 */
DATAMANAGEMENT_EMERGENCY_SEND APP_DATA_EMERGENCY_getDataToEmergency(void){
	return emergencyToSend;
}

/**
 * @fn         int APP_DATA_EMERGENCY_dataReady()
 * @brief      Funci�n de tipo get.
 * @par		   Descripci�n de la funci�n:
 * 			   Obtiene el valor de emergencyToSend.bDatoPendEnv. Si es 1 los datos a�n no
 * 			   han sido enviados. Si es 0, ya han sido enviados
 * @ret        emergencyToSend.bDatoPendEnv
 * @author     F. Dom�nguez
 * @date       20/05/2016
 */
int APP_DATA_EMERGENCY_dataReady(void){
	return emergencyToSend.bDatoPendEnv;
}

/**
 * @fn         void APP_DATA_EMERGENCY_emergencySent()
 * @brief      Se pone el flag a 0.
 * @par		   Descripci�n de la funci�n:
 * 			   Se pone el flag a 0 cuando se ha enviado la estructura correctamente.
 * @ret        emergencyToSend.bDatoPendEnv
 * @author     F. Dom�nguez
 * @date       20/05/2016
 */
void APP_DATA_EMERGENCY_emergencySent(void){
	emergencyToSend.bDatoPendEnv = 0;
}

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/



