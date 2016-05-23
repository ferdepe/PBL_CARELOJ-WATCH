/************************************************************************************
 * watch.h
 * Created on: xx/10/2015
 * Author: Javier Barragán
 * Version: 1.0
 ************************************************************************************/

#ifndef WATCH_H_
#define WATCH_H_

/********************************************
 * Macros Públicas
 *******************************************/

/********************************************
 * Types definition
 *******************************************/
typedef struct t_time
{
	unsigned char hour;
	unsigned char min;
	unsigned char seg;
} T_TIME;
/********************************************
 * Variables Públicas
 *******************************************/

/********************************************
 * Funciones Públicas
 *******************************************/

/********************************************
 * LIBS_WATCH_setTime
 *
 * Ubica los valores ingresados por el
 * usuario en la estructura del reloj
 * @In@ time
 * @Out@
 *******************************************/
void LIBS_WATCH_setTime( T_TIME time );

/********************************************
 * LIBS_WATCH_updateTime
 *
 * Actualiza el valor del reloj
 * @In@ time, estructura de "tiempo"
 * @Out@
 *******************************************/
void LIBS_WATCH_updateTime();

/********************************************
 * LIBS_WATCH_displayTime
 *
 * Reproduce la hora del reloj en pantalla y
 * controla la opción de 24/AM-PM
 * @In@
 * @Out@
 *******************************************/
void LIBS_WATCH_displayTime();


#endif /* WATCH_H_ */
