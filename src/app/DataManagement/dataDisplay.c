/**
 * @file    dataDisplay.c
 * @brief   Fuente de las funciones para el manejo de la pantalla
 * @par		Descripci�n de funciones:
 * 			En este fichero se implementan las funciones para poder escribir y leer sobre
 * 			la variable privada que permiten comunicar las tareas de L�gica y Pantalla.
 * @version 1.0
 * @author  F. Dom�nguez
 * @date    20/05/2016
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
 /**
 * @var       static unsigned int nIdPantalla
 * @brief     Variable privada usada como memoria para conectar las tareas L�gica y Pantalla.
 * @author    F. Dom�nguez
 * @date      20/05/2016
 */
static unsigned int nIdPantalla = 0;

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
/**
 * @fn         void APP_DATA_DISPLAY_setIdPantalla()
 * @brief      Funci�n de tipo set.
 * @par		   Descripci�n de la funci�n:
 * 			   Coloca en la variable privada nIdPantalla el valor deseado del id de la pantalla a mostrar.
 * @param[in]  unsigned int nId
 * @author     F. Dom�nguez
 * @date       20/05/2016
 */
void APP_DATA_DISPLAY_setIdPantalla(unsigned int nId){
	nIdPantalla = nId;
}

/**
 * @fn         unsigned int APP_DATA_DISPLAY_getIdPantalla()
 * @brief      Funci�n de tipo get.
 * @par		   Descripci�n de la funci�n:
 * 			   Obtiene de la privada nIdPantalla el valor deseado del id de la pantalla a mostrar.
 * @param[in]  unsigned int nId
 * @author     F. Dom�nguez
 * @date       20/05/2016
 */
unsigned int APP_DATA_DISPLAY_getIdPantalla(void){
	return nIdPantalla;
}

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/



