/**
 * @file    funcionesEnvioUART.c
 * @brief   Source con la implementación para mandar y recibir información por UART
 * @par		Objetivo:
 *			Se enfoca a la portabilidad del código. Los nombres de las funciones y su
 *			funcionalidad serán siempre las mismas independientemente del protocolo.
 *			En este caso se emplea el protocolo UART.
 * @author  F. Domínguez
 * @date    17/03/2015
 * @version 1.0
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/
#include "funcionesEnvio.h"

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
void APP_FUNCIONESENVIO_initChannel(void){

}

void APP_FUNCIONESENVIO_send(char * str_id, char * data){

	xil_printf(str_id);
	xil_printf(": ");
	xil_printf(data);
	xil_printf("\r\n");
}
void APP_FUNCIONESENVIO_receive(char * data){

}

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/
