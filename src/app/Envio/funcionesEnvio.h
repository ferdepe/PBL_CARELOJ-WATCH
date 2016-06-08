/**
 * @file    funcionesEnvio.h
 * @brief   Declaración de las funciones que para realizar las tareas de comunicación
 * @par		Objetivo:
 *			Este header se enfoca a la portabilidad del código. Los nombres de las funciones
 *			y su funcionalidad serán siempre las mismas independientemente del protocolo.
 * @author  F. Domínguez
 * @date    17/03/2015
 * @version 1.0
 */

#ifndef FUNCIONESENVIO_H_
#define FUNCIONESENVIO_H_

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
void APP_FUNCIONESENVIO_initChannel(void);
void APP_FUNCIONESENVIO_send(char * str_id, int len);
void APP_FUNCIONESENVIO_refresh(void);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* FUNCIONESENVIO_H_ */
