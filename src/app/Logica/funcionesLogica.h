/**
 * @file    funcionesLogica.h
 * @brief   Cabecera con la declaración de las funciones que realizarán la lógica general
 * @par		Descripción de la función:
 * 			En estos ficheros se recoge el conjunto de funciones que realizarán la lógica
 * 			interna de la máquina de estados correspondiente a las acciones, eventos y do.
 * @author  F. Domínguez
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

/***                LÓGICA ACCIONES               ***/
void APP_FUNCIONESLOGICA_A_displayPantalla(unsigned int nId);
void APP_FUNCIONESLOGICA_A_setContador(unsigned int *cont, unsigned char nOperacion);
/***                 LÓGICA ENTRY                 ***/
void APP_FUNCIONESLOGICA_ENT_getTimerCount();

/***                   LÓGICA DO                 ***/
void APP_FUNCIONESLOGICA_DO_protocoloEmergencia();
void APP_FUNCIONESLOGICA_DO_getData();

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* FUNCIONESLOGICA_H_ */
