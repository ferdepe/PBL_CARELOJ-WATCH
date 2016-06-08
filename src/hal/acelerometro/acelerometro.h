/**
 * @file      acelerometro.h
 * @brief     Cabecera de las funciones del acelerometro.
 * @par		  Descripción de la función:
 *			  Cabecera con la definición de las funciones
 *			  generales públicas del acelerometro.
 * @author    Javier Barragán
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
 * @brief      Inicialización del Acelerometro.
 * @par		   Descripción de la función:
 *			   Función encargada de inicializar
 *			   el acelerometro.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       02/06/2016
 */
void HAL_ACELEROMETRO_init();

/**
 * @fn         HAL_DISPLAY_getEstadoCaida
 * @brief      Devuelve el Estado si ha ocurrido una caída.
 * @par		   Descripción de la función:
 * 			   Función encargada de devolver a la lógica si ha
 * 			   ocurrido o no una caída de la persona.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       02/06/2016
 */
unsigned int HAL_ACELEROMETRO_getEstadoCaida(void);



#endif /* ACELEROMETRO_H_ */
