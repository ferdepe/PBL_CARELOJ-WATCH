/**
 * @file    staticCircularBuffer.c
 * @brief   Conjunto de funciones para crear e implementar un buffer circular
 * @author  F. Domínguez
 * @date    17/11/2015
 * @version 1.5
*/

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

/**
 * @fn         void STATIC_CIRCULAR_BUFFER_init(STATIC_CIRCULAR_BUFFER *obj)
 * @brief      Inicializar el Buffer
 * @param[in]  STATIC_CIRCULAR_BUFFER *obj
 * @author     F. Domínguez
 * @date       17/11/2015
 * @version    1.0
*/
void STATIC_CIRCULAR_BUFFER_init(STATIC_CIRCULAR_BUFFER *obj) {
	obj->head = 0;
	obj->tail = 0;
	obj->empty = 1;
	obj->writing = 0;
}
/**
 * @fn         unsigned int STATIC_CIRCULAR_BUFFER_insertChar(STATIC_CIRCULAR_BUFFER *obj, unsigned char data)
 * @brief      Escribe un caracter
 * @param[in]  STATIC_CIRCULAR_BUFFER *obj
 * @param[in]  unsigned char data
 * @return     ret
 * @author     F. Domínguez
 * @date       17/11/2015
 * @version    1.0
*/
unsigned int STATIC_CIRCULAR_BUFFER_insertChar(STATIC_CIRCULAR_BUFFER *obj,
		unsigned char data) {

	int freeDataCount, ret;

	freeDataCount = STATIC_CIRCULAR_BUFFER_freeDataCount(obj);

	if (freeDataCount > 0) {
		obj->Buffer[obj->head] = data;
		obj->head++;
		if (obj->head == MAX_BUFFER) {
			obj->head = 0;
		}
		obj->empty = 0;
		ret = 1;
	} else {
		ret = 0;
	}

	return ret;

}
/**
 * @fn         unsigned int STATIC_CIRCULAR_BUFFER_insertChars(STATIC_CIRCULAR_BUFFER *obj, unsigned char *data, unsigned int len)
 * @brief      Inserta una cadena de caracteres
 * @par		   Descripción de la función
 * @param[in]  STATIC_CIRCULAR_BUFFER *obj
 * @param[in]  unsigned char data
 * @return     ret
 * @author     F. Domínguez
 * @date       17/11/2015
 * @version    1.0
*/
unsigned int STATIC_CIRCULAR_BUFFER_insertChars(STATIC_CIRCULAR_BUFFER *obj,
		unsigned char *data, unsigned int len) {

	int i, freeDataCount, ret;
	freeDataCount = STATIC_CIRCULAR_BUFFER_freeDataCount(obj);

	if (freeDataCount > 0) {
		if (len > freeDataCount) {
			len = freeDataCount;
			//Sobrescribiría a la cola??
		}
		for (i = 0; i < len; i++) {
			obj->Buffer[obj->head] = data[i];
			obj->head++;
			if (obj->head == MAX_BUFFER) {
				obj->head = 0;
			}
		}
		obj->empty = 0;
		ret = len;
	} else {
		ret = 0;
	}

	return ret;
}
/**
 * @fn         unsigned char STATIC_CIRCULAR_BUFFER_readChar(STATIC_CIRCULAR_BUFFER *obj)
 * @brief      Lee un caracter
 * @param[in]  STATIC_CIRCULAR_BUFFER *obj
 * @return     ret
 * @author     F. Domínguez
 * @date       17/11/2015
 * @version    1.0
*/
unsigned char STATIC_CIRCULAR_BUFFER_readChar(STATIC_CIRCULAR_BUFFER *obj) {

	unsigned char ret;

	if (obj->empty) {
		return 0;
	} else {
		ret = obj->Buffer[obj->tail];
		obj->tail++;
		if (obj->tail == MAX_BUFFER) {
			obj->tail = 0;
		}
		if (obj->tail == obj->head) {
			obj->empty = 1;
		}
	}
	return ret;
}
/**
 * @fn         unsigned char STATIC_CIRCULAR_BUFFER_readChar(STATIC_CIRCULAR_BUFFER *obj)
 * @brief      Lee un caracter
 * @param[in]  STATIC_CIRCULAR_BUFFER *obj
 * @return     ret
 * @author     F. Domínguez
 * @date       17/11/2015
 * @version    1.0
*/
unsigned int STATIC_CIRCULAR_BUFFER_readChars(STATIC_CIRCULAR_BUFFER *obj,
		unsigned char *data) {

	unsigned int ret;
	unsigned int i = 0;

	if (obj->empty) {
		ret = 0;
	}
	else {
		while(obj->tail != obj->head){
			if (i == MAX_BUFFER){
				obj->tail = 0;
			}

			data[i] = obj->Buffer[obj->tail];

			obj->tail++;
			if (obj->tail == MAX_BUFFER){
				obj->tail = 0;
			}
			i++;
		}
		obj->empty = 1;
		ret = 1;
	}

	return ret;
}
/**
 * @fn         unsigned int STATIC_CIRCULAR_BUFFER_freeDataCount(STATIC_CIRCULAR_BUFFER *obj)
 * @brief      Número libre de caracteres
 * @param[in]  STATIC_CIRCULAR_BUFFER *obj
 * @return     ret
 * @author     F. Domínguez
 * @date       17/11/2015
 * @version    1.0
*/
unsigned int STATIC_CIRCULAR_BUFFER_freeDataCount(STATIC_CIRCULAR_BUFFER *obj) {

	unsigned int ret = 0;

	//Si la posición de la  cola es mayor que la de la cabeza...
	if (obj->tail > obj->head) {
		ret = obj->tail - obj->head;
	} else {
		//Si son iguales, puede ser que el buffer esté vacío o lleno
		if (obj->empty) {
			ret = MAX_BUFFER;
		} else {
			if (obj->head == obj->tail) {
				ret = 0;
			} else {
				ret = MAX_BUFFER - (obj->head - obj->tail);
			}
		}
	}

	return ret;
}
/**
 * @fn         unsigned int STATIC_CIRCULAR_BUFFER_dataCount(STATIC_CIRCULAR_BUFFER *obj)
 * @brief      Devuelve el número de caracteres
 * @param[in]  STATIC_CIRCULAR_BUFFER *obj
 * @return     ret
 * @author     F. Domínguez
 * @date       17/11/2015
 * @version    1.0
*/
unsigned int STATIC_CIRCULAR_BUFFER_dataCount(STATIC_CIRCULAR_BUFFER *obj) {

	unsigned int ret = 0;

	if (obj->tail > obj->head) {
		ret = (obj->head + MAX_BUFFER) - obj->tail;
	} else {
		if (obj->empty) {
			ret = 0;
		} else {
			if (obj->head == obj->tail) {
				ret = MAX_BUFFER;
			} else {
				ret = obj->head - obj->tail;
			}
		}
	}

	return ret;
}
/**
 * @fn         unsigned int STATIC_CIRCULAR_BUFFER_existChar(STATIC_CIRCULAR_BUFFER *obj, char data)
 * @brief      Devuelve si existe un char
 * @par		   Descripción de la función
 * @param[in]  STATIC_CIRCULAR_BUFFER *obj
 * @param[in]  char data
 * @return     ret
 * @author     F. Domínguez
 * @date       17/11/2015
 * @version    1.0
*/
unsigned int STATIC_CIRCULAR_BUFFER_existChar(STATIC_CIRCULAR_BUFFER *obj, char data) {
	int i = 0;
	int encontrado = 0;
	int cont = 0;
	int ret = 0;
	int len;

	i = obj->tail;
	len = STATIC_CIRCULAR_BUFFER_dataCount(obj);

	while ((cont < len) && !(encontrado)){
		if (obj->Buffer[i] == data)
			encontrado = 1;
		cont++;
		i++;
		if (i == MAX_BUFFER)
			i = 0;
	}

	if(encontrado)
		ret = (obj->tail) + cont;
	return ret;
}

/*****************************************************
 *                EXPORTED VARIABLES                  *
 *****************************************************/

/*****************************************************
 *                  LOCAL FUNCTIONS                   *
 *****************************************************/

