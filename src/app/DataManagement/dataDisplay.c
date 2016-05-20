/**
 * @file    dataDisplay.c
 * @brief   Fuente de las funciones para el manejo de datos entre tareas
 * @par		Descripci�n de funciones:
 * 			En este fichero se implementan las funciones para poder escribir y leer sobre variables privadas
 * 			al fichero que permiten comunicar las tareas del programa de CARELOJ: L�gica, Env�o y Pantalla
 * @version 1.6
 * @author  F. Dom�nguez
 * @date    17/05/2015
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "dataDisplay.h"

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

static unsigned int nIdPantalla = 0;

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

void APP_DATA_DISPLAY_setIdPantalla(unsigned int nId){
	nIdPantalla = nId;
}

unsigned int APP_DATA_DISPLAY_getIdPantalla(void){
	return nIdPantalla;
}

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/



