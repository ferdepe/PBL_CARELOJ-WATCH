/*****************************************************
* FILE NAME: comunicacion.h                          *
*                                                    *
* PURPOSE: Conjunto de funciones públicas para       *
*          enviar y recibir paquetes de datos entre  *
*          varias tareas.                            *
*                                                    *
* AUTHOR: Fernando Domínguez                         *
*                                                    *
* DATE: 24/12/2015     VERSION: 1.2                  *
*                                                    *
*****************************************************/

#ifndef DATAMANAGEMENT_H_
#define DATAMANAGEMENT_H_

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "staticCircularBuffer.h"

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

void APP_DATAMANAGEMENT_initBuffers();
unsigned int APP_DATAMANAGEMENT_send2Buffer(STATIC_CIRCULAR_BUFFER *obj, unsigned char *Data, unsigned int len);
unsigned int APP_DATAMANAGEMENT_readFromBuffer(STATIC_CIRCULAR_BUFFER *obj, unsigned char *str_read);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* DATAMANAGEMENT_H_ */
