/**
 * @file    funcionesLogica.c
 * @brief   Source con la implementación de las funciones que realizarán la lógica general
 * @par		Descripción de la función:
 * 			En estos ficheros se recoge el conjunto de funciones que realizarán la lógica
 * 			interna de la máquina de estados correspondiente a las acciones, eventos y do.
 * @author  F. Domínguez
 * @date    04/03/2015
 * @version 1.0
 * @todo
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/
#include "funcionesLogica.h"
#include "axi-gpio.h"
#include "timer.h"
#include "staticCircularBuffer.h"
#include "dataManagement.h"
#include "config.h"

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
STATIC_CIRCULAR_BUFFER DATAMANAGEMENT_envioEmergencia;
STATIC_CIRCULAR_BUFFER DATAMANAGEMENT_envioDatos;
unsigned char DATAMANAGEMENT_idPantalla;

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/
static unsigned int contadorTimer = 0;
static unsigned int avisoEnBuffer = 0;
static unsigned int endGetData = 0;

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
/***                 LOGICA EVENTOS               ***/
BOOLEAN APP_FUNCIONESLOGICA_E_readAcelerometer(){
	static unsigned int pinAnterior = 0;
	unsigned int pinActual;
	BOOLEAN ret;

	pinActual = HAL_AXI_GPIO_readAxiButtonPin(0);

	if(pinActual && !pinAnterior)
		ret = 1;
	else
		ret = 0;

	pinAnterior = pinActual;
	return ret;
}

BOOLEAN APP_FUNCIONESLOGICA_E_readRedButton(){
	static unsigned int pinAnterior = 0;
	unsigned int pinActual;
	BOOLEAN ret;

	pinActual = HAL_AXI_GPIO_readAxiButtonPin(1);

	if(pinActual && !pinAnterior)
		ret = 1;
	else
		ret = 0;

	pinAnterior = pinActual;
	return ret;
}
BOOLEAN APP_FUNCIONESLOGICA_E_readBlackButton(){
	static unsigned int pinAnterior = 0;
	unsigned int pinActual;
	BOOLEAN ret;

	pinActual = HAL_AXI_GPIO_readAxiButtonPin(2);

	if(pinActual && !pinAnterior)
		ret = 1;
	else
		ret = 0;

	pinAnterior = pinActual;
	return ret;
}
BOOLEAN APP_FUNCIONESLOGICA_E_readGreenButton(){
	static unsigned int pinAnterior = 0;
	unsigned int pinActual;
	BOOLEAN ret;

	pinActual = HAL_AXI_GPIO_readAxiButtonPin(3);

	if(pinActual && !pinAnterior)
		ret = 1;
	else
		ret = 0;

	pinAnterior = pinActual;
	return ret;
}


BOOLEAN APP_FUNCIONESLOGICA_E_after10s(){
	static int cont = 0;

	cont = HAL_TIMER_getTimerCount();
	if ((cont + contadorTimer) >= 1000)
		return 1;
	else
		return 0;
}

BOOLEAN APP_FUNCIONESLOGICA_E_endGetData(){
	return endGetData;
}
BOOLEAN APP_FUNCIONESLOGICA_E_avisoEnBuffer(){
	return avisoEnBuffer;
}

/***                LÓGICA ACCIONES               ***/
void APP_FUNCIONESLOGICA_A_displayPantalla(unsigned int nId){
	/*
	 * Insertar función displayPantalla con ID
	 */
}
unsigned char APP_FUNCIONESLOGICA_A_setContador(unsigned char cont, unsigned char nOperacion){
	switch(nOperacion){
	case RESET :
		cont = 0;
		break;
	case SUMA :
		cont = (cont%NUMBER_SENSORS) +1;
		break;
	case RESTA :
		if(cont > 0)
		cont = cont - 1;
		break;

	}

	return cont;
}

/***                 LÓGICA ENTRY                 ***/
void APP_FUNCIONESLOGICA_ENT_getTimerCount(){
	contadorTimer = HAL_TIMER_getTimerCount();
}

/***                  LÓGICA DO                   ***/
void APP_FUNCIONESLOGICA_DO_protocoloEmergencia(){

	/*
	 * INSERTAR AQUÍ FUNCIÓN QUE LLAMA A RECOGER DATOS EMERGENCIA
	 */

	static unsigned char str[] = "7121238ID_20g30m40sN_10g30m21sO_100b$";

	avisoEnBuffer = APP_DATAMANAGEMENT_send2Buffer(&DATAMANAGEMENT_envioEmergencia, str, 37);
}
void APP_FUNCIONESLOGICA_DO_getData(){
	/*
	 * INSERTAR AQUÍ FUNCIÓN DE REGOGIDA DE DATOS
	 */
	static unsigned char str[] = "7121238ID_pl100b_ps75kg$";

	APP_DATAMANAGEMENT_send2Buffer(&DATAMANAGEMENT_envioDatos, str, 24);

	endGetData = 1;
}
/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/

