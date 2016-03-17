/*****************************************************
 * FILE NAME: staticCircularBuffer.h                  *
 *                                                    *
 * PURPOSE: Declaración de funciones públicas para    *
 *          crear y operar un Buffer circular         *
 *                                                    *
 * AUTHOR: Fernando Domínguez                         *
 *                                                    *
 * DATE: 26/11/2015     VERSION: 1.0                  *
 *                                                    *
 *****************************************************/

#ifndef STATICCIRCULARBUFFER_H_
#define STATICCIRCULARBUFFER_H_

/*****************************************************
 *                   MODULES USED                     *
 *****************************************************/

/*****************************************************
 *               DEFINITIONS AND MACROS               *
 *****************************************************/

#define MAX_BUFFER 1024

/*****************************************************
 *              TYPEDEFS AND STRUCTURES               *
 *****************************************************/

typedef struct {
	unsigned char Buffer[MAX_BUFFER];
	unsigned int tail;
	unsigned int head;
	unsigned int len;
	unsigned char empty;
	unsigned char writing; //Como token, para saber si alguien escribe o no en el buffer (OPCIONAL)
} STATIC_CIRCULAR_BUFFER;

/*****************************************************
 *                 EXPORTED VARIABLES                 *
 *****************************************************/

/*****************************************************
 *                  EXPORTED FUNCTIONS                *
 *****************************************************/

void STATIC_CIRCULAR_BUFFER_init(STATIC_CIRCULAR_BUFFER *obj);
unsigned int STATIC_CIRCULAR_BUFFER_insertChar(STATIC_CIRCULAR_BUFFER *obj,
		unsigned char data);
unsigned int STATIC_CIRCULAR_BUFFER_insertChars(STATIC_CIRCULAR_BUFFER *obj,
		unsigned char *data, unsigned int len);
unsigned char STATIC_CIRCULAR_BUFFER_readChar(STATIC_CIRCULAR_BUFFER *obj);
unsigned int STATIC_CIRCULAR_BUFFER_readChars(STATIC_CIRCULAR_BUFFER *obj,
		unsigned char *data);
unsigned int STATIC_CIRCULAR_BUFFER_freeDataCount(STATIC_CIRCULAR_BUFFER *obj);
unsigned int STATIC_CIRCULAR_BUFFER_dataCount(STATIC_CIRCULAR_BUFFER *obj);
unsigned int STATIC_CIRCULAR_BUFFER_existChar(STATIC_CIRCULAR_BUFFER *obj,
		char data);

/*****************************************************
 *                        EOF                         *
 *****************************************************/

#endif /* STATICCIRCULARBUFFER_H_ */
