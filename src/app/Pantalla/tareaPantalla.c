/*
 * tareaPantalla.c
 *
 *  Created on: 20/05/2016
 *      Author: Javo
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "tareaPantalla.h"
#include "pantalla.h"


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

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
/**
 * @fn      void APP_PANTALLA_ejecutaTarea(void)
 * @brief   Función que llama a la ejecución de la tarea referida a la visualización en pantalla.
 * @par		Descripción de la función:
 * 			Esta función llama a la lógica encargada de reproducir sobre la pantalla los posibles estados.
 * 			A través de consultar el idPantalla y los datos, reproduce una pantalla particular.
 * @param   void
 * @return  void
*/
void APP_TAREAPANTALLA_ejecutaTarea(void){

	APP_PANTALLA_mostrar();
}

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/



