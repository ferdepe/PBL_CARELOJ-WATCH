/************************************************************************************
 * watch.h
 * Created on: xx/10/2015
 * Author: Javier Barrag�n
 * Version: 1.0
 ************************************************************************************/

#ifndef WATCH_H_
#define WATCH_H_

/********************************************
 * Macros P�blicas
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
 * Variables P�blicas
 *******************************************/

/********************************************
 * Funciones P�blicas
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
 * controla la opci�n de 24/AM-PM
 * @In@
 * @Out@
 *******************************************/
void LIBS_WATCH_displayTime();


#endif /* WATCH_H_ */
