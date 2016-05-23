/************************************************************************************
 * watch.c
 * Created on: xx/10/2015
 * Author: Javier Barragán
 * Version: 1.0
 ************************************************************************************/
/********************************************
 * Includes de modulos externos
 *******************************************/
#include <stdio.h>
#include "display.h"
#include "timer_scugic.h"

/********************************************
 * Includes de definiciones del modulo
 *******************************************/
#include "watch.h"

/********************************************
 * Variables internas/privadas del modulo(ENCAPSULAMIENTO)
 *******************************************/
static T_TIME actualTime;
static unsigned int countA = 0;
static unsigned int countB = 2;
int aux; //boton gmt

/********************************************
 * Funciones privadas del modulo(ENCAPSULAMIENTO)
 *******************************************/
void LIBS_WATCH_initTime();
int LIBS_WATCH_GMT();

/********************************************
 * Implementacion de funciones publicas
 *******************************************/
void LIBS_WATCH_setTime( T_TIME time )
{
	actualTime.hour=time.hour;
	actualTime.min=time.min;
	actualTime.seg=time.seg;
}
void LIBS_WATCH_updateTime()
{
	countA = HAL_TIMER_SCUGIC_getTimerCount();
	if (countB != countA)
	{
        displayMenu();
		actualTime.seg++;
		if (actualTime.seg >= 60)
		{
			actualTime.seg = 0;
			actualTime.min++;
		}
		if (actualTime.min >= 60)
		{
		    actualTime.min = 0;
		    actualTime.hour++;
		}
		if (actualTime.hour >= 24)
		{
			actualTime.hour = 0;
		}
		countB = countA;

	}

}
void LIBS_WATCH_displayTime()
{
	char str[20],str2[10];
	int hora;
	sprintf(str, "TIEMPO\0");
	HAL_DISPLAY_printString(str,'T');
	aux = LIBS_WATCH_GMT();
	if (aux==1)
	{
		if(actualTime.hour > 12)
		{
			hora=actualTime.hour-12;
			sprintf( str, "%2d::%2d::%2d", hora, actualTime.min, actualTime.seg);
			sprintf(str2, "PM\0");
		}
		else //(actualTime.hour<12)
		{
			sprintf( str, "%2d::%2d::%2d", actualTime.hour, actualTime.min, actualTime.seg);
			sprintf(str2, "AM\0");
		}
	}
	else
		{
			sprintf( str, "%2d::%2d::%2d", actualTime.hour, actualTime.min, actualTime.seg);
			sprintf(str2, "\0");
		}
	HAL_DISPLAY_printString(str,'V');
	HAL_DISPLAY_printString(str2,'U');
}

/********************************************
 * Implementacion de funciones privadas
 *******************************************/
void LIBS_WATCH_initTime()
{
	actualTime.hour=0;
	actualTime.min=0;
	actualTime.seg=0;
}
int LIBS_WATCH_GMT()
{
	int status;
	//status=HAL_HW_ABSTRACTION_readButton();
	return status;
}
