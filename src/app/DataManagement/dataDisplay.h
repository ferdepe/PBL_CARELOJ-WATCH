/**
 * @file    dataDisplay.h
 * @brief   Header de las funciones para el manejo de la pantalla
 * @par		Descripci�n de funciones:
 * 			En este fichero se declaran las funciones para poder escribir y leer sobre
 * 			la variable privada que permiten comunicar las tareas de L�gica y Pantalla.
 * @version 1.0
 * @author  F. Dom�nguez
 * @date    20/05/2015
 */

#ifndef DATADISPLAY_H_
#define DATADISPLAY_H_

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*                 EXPORTED VARIABLES                 *
*****************************************************/

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/

void APP_DATA_DISPLAY_setIdPantalla(unsigned int nId);
unsigned int APP_DATA_DISPLAY_getIdPantalla(void);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* DATADISPLAY_H_ */
