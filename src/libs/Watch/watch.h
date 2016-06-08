
/**
 * @file      watch.h
 * @brief     Cabecera de las funciones referida a la l�gica del reloj.
 * @par		  Descripci�n de la funci�n:
 *			  Funciones que se encargan de la l�gica del funcionamiento
 *			  de la hora, minutos y segundos del reloj.
 * @author    Javier Barrag�n
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
 * @par		   Descripci�n de la funci�n:
 * 			   Ubica los valores ingresados por el
 * 			   usuario en la estructura del reloj.
 * @param[in]  T_TIME time, estructura con el valor deseado del tiempo.
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       17/10/2015
 */
void LIBS_WATCH_setTime( T_TIME time );

/**
 * @fn         LIBS_WATCH_updateTime
 * @brief      Actualizaci�n del tiempo.
 * @par		   Descripci�n de la funci�n:
 * 			   Actualiza el valor del reloj.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       17/10/2015
 */
void LIBS_WATCH_updateTime();

/**
 * @fn         LIBS_WATCH_displayTime
 * @brief      Reproducci�n en pantalla del tiempo.
 * @par		   Descripci�n de la funci�n:
 * 			   Reproduce la hora del reloj en pantalla y
 * 			   controla la opci�n de 24/AM-PM.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       17/10/2015
 */
void LIBS_WATCH_displayTime();

/**
 * @fn         LIBS_WATCH_displayTime
 * @brief      Devoluci�n del tiempo.
 * @par		   Descripci�n de la funci�n:
 *			   Funci�n que devuelve la estructura con valores
 *			   del tiempo: hora, minutos y segundos.
 * @param[in]  void
 * @param[out] T_TIME actualtime, estructura de tiempo actual.
 * @author     Javier Barrag�n
 * @date       24/10/2016
 */
T_TIME LIBS_WATCH_getTime();

#endif /* WATCH_H_ */
