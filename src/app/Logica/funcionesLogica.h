/**
 * @file    funcionesLogica.h
 * @brief   Cabecera con la declaraci�n de las funciones que realizar�n la l�gica general
 * @par		Descripci�n de la funci�n:
 * 			En estos ficheros se recoge el conjunto de funciones que realizar�n la l�gica
 * 			interna de la m�quina de estados correspondiente a las acciones, eventos y do.
 * @author  F. Dom�nguez
 * @date    04/03/2015
 * @version 1.0
 * @todo
 */

#ifndef FUNCIONESLOGICA_H_
#define FUNCIONESLOGICA_H_

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/
#define RESET 0
#define SUMA 1
#define RESTA 2

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/
typedef unsigned char BOOLEAN;

/*****************************************************
*                 EXPORTED VARIABLES                 *
*****************************************************/

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/
/***                 LOGICA EVENTOS               ***/
BOOLEAN APP_FUNCIONESLOGICA_E_readRedButton();
BOOLEAN APP_FUNCIONESLOGICA_E_readGreenButton();
BOOLEAN APP_FUNCIONESLOGICA_E_readBlackButton();
BOOLEAN APP_FUNCIONESLOGICA_E_readAcelerometer();
BOOLEAN APP_FUNCIONESLOGICA_E_after10s();
BOOLEAN APP_FUNCIONESLOGICA_E_endGetData();
BOOLEAN APP_FUNCIONESLOGICA_E_avisoEnBuffer();

/***                L�GICA ACCIONES               ***/
void APP_FUNCIONESLOGICA_A_displayPantalla(unsigned int nId);
void APP_FUNCIONESLOGICA_A_setContador(unsigned int *cont, unsigned char nOperacion);
/***                 L�GICA ENTRY                 ***/
void APP_FUNCIONESLOGICA_ENT_getTimerCount();

/***                   L�GICA DO                 ***/
void APP_FUNCIONESLOGICA_DO_protocoloEmergencia();
void APP_FUNCIONESLOGICA_DO_getData();

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* FUNCIONESLOGICA_H_ */
