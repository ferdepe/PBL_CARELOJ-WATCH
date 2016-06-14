 /**
 * @file      watch.c
 * @brief     Fichero con las funciones referida a la lógica del reloj.
 * @par		  Descripción de la función:
 *			  Funciones que se encargan de la lógica del funcionamiento
 *			  de la hora, minutos y segundos del reloj.
 * @author    Javier Barragán
 * @date      24/05/2016
 * @version   1.0
 * @todo
 * @bug       No se utiliza LIBS_WATCH_GMT().
 */
/*****************************************************
*                   MODULES USED                     *
*****************************************************/
#include <stdio.h>
#include "display.h"
#include "timer_ttc.h"

#include "watch.h"
/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/

void LIBS_WATCH_initTime();
int LIBS_WATCH_GMT();

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

static T_TIME actualTime;
static unsigned int countA = 0;
static unsigned int countB = 2;
int aux; //boton gmt

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

void LIBS_WATCH_setTime( T_TIME time )
{
	actualTime.hour=time.hour;
	actualTime.min=time.min;
	actualTime.seg=time.seg;
}

void LIBS_WATCH_updateTime()
{
	countA = HAL_TIMER_TTC_GetTimerCount();
	if (countB != countA)
	{
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
	char strT[5], strV[10], strU[3];
	int hora;
	sprintf(strT, "TIEMPO\n");
	aux = LIBS_WATCH_GMT();
	if (aux==1)
	{
		if(actualTime.hour > 12)
		{
			hora=actualTime.hour-12;
			sprintf( strV, "%2d:%2d:%2d", hora, actualTime.min, actualTime.seg);
			sprintf(strU, "PM");
		}
		else //(actualTime.hour<12)
		{
			sprintf( strV, "%2d:%2d:%2d", actualTime.hour, actualTime.min, actualTime.seg);
			sprintf(strU, "AM");
		}
	}
	else
		{
			sprintf( strV, "%2d:%2d:%2d", actualTime.hour, actualTime.min, actualTime.seg);
			sprintf(strU, "\0");
		}
	//HAL_DISPLAY_screen(strT,strV,strU);
}

T_TIME LIBS_WATCH_getTime()
{
	return actualTime;
}
/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/
/**
 * @fn         LIBS_WATCH_initTime
 * @brief      Inicialización del tiempo.
 * @par		   Descripción de la función:
 *			   Inicializa a 0 todas las variables de la
 *			   estructura tiempo: hora, minutos y segundos.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/10/2015
 */
void LIBS_WATCH_initTime()
{
	actualTime.hour=0;
	actualTime.min=0;
	actualTime.seg=0;
}

/**
 * @fn         LIBS_WATCH_GMT
 * @brief      Cambio de formato de reloj.
 * @par		   Descripción de la función:
 * 			   Leyendo botón permite seleccionar el formato
 * 			   del tipo de reloj AM/PM o 24hs.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/10/2015
 */
int LIBS_WATCH_GMT()
{
	int status;
	//status=HAL_HW_ABSTRACTION_readButton();
	return status;
}
