/**
 * @file    dataBuffersAux.c
 * @brief   Fuente de las funciones para operar sobre buffers auxiliares
 * @par		Descripción de funciones:
 * 			En este ficherose implementan las funciones para poder escribir y leer sobre buffers auxiliares.
 * 			En principio, buffers circulares y variables globales
 * @version 1.5
 * @author  F. Domínguez
 * @date    04/03/2015
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "dataManagement.h"
#include "config.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/
typedef struct{
	char id;
	float value;
	unsigned char units[UNITS_STRING];
}DATAMANAGEMENT_MEMORY;
/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

extern STATIC_CIRCULAR_BUFFER DATAMANAGEMENT_envioDatos;
extern STATIC_CIRCULAR_BUFFER DATAMANAGEMENT_envioEmergencia;
extern unsigned char DATAMANAGEMENT_idPantalla;
extern DATAMANAGEMENT_MEMORY DATAMANAGEMENT_SensorValues[MEMORY_SIZE];

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

void APP_DATAMANAGEMENT_initBuffers(){
	STATIC_CIRCULAR_BUFFER_init(&DATAMANAGEMENT_envioDatos);
	STATIC_CIRCULAR_BUFFER_init(&DATAMANAGEMENT_envioEmergencia);
}

unsigned int APP_DATAMANAGEMENT_send2Buffer(STATIC_CIRCULAR_BUFFER *obj, unsigned char *Data, unsigned int len){
	int ret = 0;

	ret = STATIC_CIRCULAR_BUFFER_insertChars(obj,Data,len);

	return ret;
}

unsigned int APP_DATAMANAGEMENT_readFromBuffer(STATIC_CIRCULAR_BUFFER * obj, unsigned char *str_read){
	int stringOK =0;

	stringOK = STATIC_CIRCULAR_BUFFER_existChar(obj,'$');

	if(stringOK){
		stringOK = STATIC_CIRCULAR_BUFFER_readChars(obj, str_read);
	}

	return stringOK;
}

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/

