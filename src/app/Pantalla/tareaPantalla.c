 /**
 * @file      tareaPantalla.c
 * @brief     Fichero con las funciones externas de la tarea encargada de manejar la pantalla.
 * @par		  Descripci�n de la funci�n:
* 			  Conjunto de funciones externas para que la logica general de la aplicaci�n
* 			  pueda manipular la tarea de impresi�n en pantalla.
  * @author   Javier Barrag�n
 * @date      24/05/2016
 * @version   1.0
 * @todo
 * @bug
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
 * @brief   Funci�n que llama a la ejecuci�n de la tarea referida a la visualizaci�n en pantalla.
 * @par		Descripci�n de la funci�n:
 * 			Esta funci�n llama a la l�gica encargada de reproducir sobre la pantalla los posibles estados.
 * 			A trav�s de consultar el idPantalla y los datos, reproduce una pantalla particular.
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



