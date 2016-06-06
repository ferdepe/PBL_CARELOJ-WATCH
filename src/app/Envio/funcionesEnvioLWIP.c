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
#include "timer_scugic.h"
#include "lwip_tcp.h"

#include "netif/xadapter.h"

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
struct netif host_netif;
struct netif *time_netif;

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
void APP_FUNCIONESENVIO_initChannel(void){
	HAL_TIMER_SCUGIC_TimerSetup();
	HAL_LWIP_TCP_init();

	}

void APP_FUNCIONESENVIO_send(char * str_id, int len){
	HAL_LWIP_TCP_setBuffEnvio(str_id,len);
	HAL_LWIP_TCP_launchClient();
}

void APP_FUNCIONESENVIO_refresh(void){
	HAL_LWIP_TCP_refreshIO();
}


/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/
