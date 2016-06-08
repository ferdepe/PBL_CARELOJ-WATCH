
/**
 * @file      watch.h
 * @brief     Cabecera de las funciones referida a la lógica del reloj.
 * @par		  Descripción de la función:
 *			  Funciones que se encargan de la lógica del funcionamiento
 *			  de la hora, minutos y segundos del reloj.
 * @author    Javier Barragán
 * @date      24/05/2016
 * @version   1.0
 * @todo
 * @bug
 */
#ifndef WATCH_H_
#define WATCH_H_

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/
typedef struct t_time
{
	unsigned char hour;
	unsigned char min;
	unsigned char seg;
} T_TIME;

/*****************************************************
*                 EXPORTED VARIABLES                 *
*****************************************************/

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/

/**
 * @fn         LIBS_WATCH_setTime
 * @brief      Seteo del tiempo.
 * @par		   Descripción de la función:
 * 			   Ubica los valores ingresados por el
 * 			   usuario en la estructura del reloj.
 * @param[in]  T_TIME time, estructura con el valor deseado del tiempo.
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/10/2015
 */
void LIBS_WATCH_setTime( T_TIME time );

/**
 * @fn         LIBS_WATCH_updateTime
 * @brief      Actualización del tiempo.
 * @par		   Descripción de la función:
 * 			   Actualiza el valor del reloj.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/10/2015
 */
void LIBS_WATCH_updateTime();

/**
 * @fn         LIBS_WATCH_displayTime
 * @brief      Reproducción en pantalla del tiempo.
 * @par		   Descripción de la función:
 * 			   Reproduce la hora del reloj en pantalla y
 * 			   controla la opción de 24/AM-PM.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/10/2015
 */
void LIBS_WATCH_displayTime();

/**
 * @fn         LIBS_WATCH_displayTime
 * @brief      Devolución del tiempo.
 * @par		   Descripción de la función:
 *			   Función que devuelve la estructura con valores
 *			   del tiempo: hora, minutos y segundos.
 * @param[in]  void
 * @param[out] T_TIME actualtime, estructura de tiempo actual.
 * @author     Javier Barragán
 * @date       24/10/2016
 */
T_TIME LIBS_WATCH_getTime();

#endif /* WATCH_H_ */
