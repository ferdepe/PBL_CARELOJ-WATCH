/**
 * @file      acelerometro.h
 * @brief     Cabecera de las funciones del acelerometro.
 * @par		  Descripci�n de la funci�n:
 *			  Cabecera con la definici�n de las funciones
 *			  generales p�blicas del acelerometro.
 * @author    Javier Barrag�n
 * @date      02/06/2016
 * @version   1.0
 * @todo
 * @bug
 */
#ifndef ACELEROMETRO_H_
#define ACELEROMETRO_H_



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

/**
 * @fn         HAL_ACELEROMETRO_init
 * @brief      Inicializaci�n del Acelerometro.
 * @par		   Descripci�n de la funci�n:
 *			   Funci�n encargada de inicializar
 *			   el acelerometro.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       02/06/2016
 */
void HAL_ACELEROMETRO_init();

/**
 * @fn         HAL_DISPLAY_getEstadoCaida
 * @brief      Devuelve el Estado si ha ocurrido una ca�da.
 * @par		   Descripci�n de la funci�n:
 * 			   Funci�n encargada de devolver a la l�gica si ha
 * 			   ocurrido o no una ca�da de la persona.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       02/06/2016
 */
unsigned int HAL_ACELEROMETRO_getEstadoCaida(void);



#endif /* ACELEROMETRO_H_ */
