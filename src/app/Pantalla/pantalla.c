 /**
 * @file      pantalla.c
 * @brief     Short description.
 * @par		  Descripción de la función:
 * 			  par1
 *            par2
 * @author    author
 * @date      17/05/2016
 * @version   1.0
 * @todo      todo
 * @bug       bug
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/
#include <stdio.h>
#include "display.h"
#include "watch.h"
#include "dataDisplay.h"
#include "dataSensors.h"

#include "pantalla.h"
/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/
/**
 * @fn         APP_PANTALLA_screen0
 * @brief      Display del tiempo.
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/05/2016
 */
void APP_PANTALLA_screen0();

/**
 * @fn         APP_PANTALLA_screen1
 * @brief      Display del tiempo.
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/05/2016
 */
void APP_PANTALLA_screen1();

/**
 * @fn         APP_PANTALLA_screen2
 * @brief      Display de
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/05/2016
 */
void APP_PANTALLA_screen2();

/**
 * @fn         APP_PANTALLA_screen3
 * @brief      Display de
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/05/2016
 */
void APP_PANTALLA_screen3();

/**
 * @fn         APP_PANTALLA_screen40
 * @brief      Display de mensaje
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/05/2016
 */
void APP_PANTALLA_screen40();

/**
 * @fn         APP_PANTALLA_screen41
 * @brief      Display de
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/05/2016
 */
void APP_PANTALLA_screen41();

/**
 * @fn         APP_PANTALLA_screen42
 * @brief      Display de
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/05/2016
 */
void APP_PANTALLA_screen42();

/**
 * @fn         APP_PANTALLA_screen43
 * @brief      Display de
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/05/2016
 */
void APP_PANTALLA_screen43();
void APP_PANTALLA_printTipo(char[]);
void APP_PANTALLA_printValor(float);
void APP_PANTALLA_printUnidad(CONFIG_SENSORS);
void APP_PANTALLA_printMensaje(char[]);

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/
char str[];
/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

//variables globales, precedidas de static (privada)

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
void APP_PANTALLA_init()
{
    //inicializacion display
    HAL_DISPLAY_init();
    display_borrar_buffer();
    displayBackground();
    updateFrame();
}

void APP_PANTALLA_mostrar()
{
	switch(APP_DATA_DISPLAY_getIdPantalla())
	{
	case 0:
	    APP_PANTALLA_screen0();
	    break;
	case 1:
		APP_PANTALLA_screen1();
		break;
	case 2:
		APP_PANTALLA_screen2();
		break;
	case 3:
		APP_PANTALLA_screen3();
		break;
	case 40:
		APP_PANTALLA_screen40();
		break;
	case 41:
		APP_PANTALLA_screen41();
		break;
	case 42:
		APP_PANTALLA_screen42();
		break;
	case 43:
		APP_PANTALLA_screen43();
		break;
	}
}
/*****************************************************
*                  LOCAL FUNCTIONS                   *
************************************************
*****************************************************/
void APP_PANTALLA_screen0()
{
	LIBS_WATCH_displayTime();
}
void APP_PANTALLA_screen1()
{
	DATAMANAGEMENT_SENSOR_DATA PULSOMETRO;
	PULSOMETRO=APP_DATA_SENSORS_getSensorData(1);

	APP_PANTALLA_printTipo("PULSOMETRO");
	APP_PANTALLA_printValor(PULSOMETRO.value);
	APP_PANTALLA_printUnidad(PULSOMETRO.nId);
}

void APP_PANTALLA_screen2()
{
	APP_PANTALLA_printTipo("SENSOR 2");
	APP_PANTALLA_printValor(APP_DATA_SENSORS_getSensorData(2).value);
	APP_PANTALLA_printUnidad(APP_DATA_SENSORS_getSensorData(2).nId);
}
void APP_PANTALLA_screen3()
{
	APP_PANTALLA_printTipo("SENSOR 3");
	APP_PANTALLA_printValor(APP_DATA_SENSORS_getSensorData(3).value);
	APP_PANTALLA_printUnidad(APP_DATA_SENSORS_getSensorData(3).nId);
}
void APP_PANTALLA_screen40()
{
	APP_PANTALLA_printMensaje("Recogiendo Datos...");
}
void APP_PANTALLA_screen41()
{
	APP_PANTALLA_printMensaje("Enviando Datos...");
}
void APP_PANTALLA_screen42()
{
	APP_PANTALLA_printMensaje("Boton de panico ON");
}
void APP_PANTALLA_screen43()
{
	APP_PANTALLA_printMensaje("Datos Recogidos");
}
void APP_PANTALLA_printTipo(char str[])
{
	HAL_DISPLAY_printString(str,'T');
}
void APP_PANTALLA_printValor(float valor)
{
	sprintf(str,"%f\0",valor);
	HAL_DISPLAY_printString(str,'V');
}
void APP_PANTALLA_printUnidad(CONFIG_SENSORS Id)
{
	if(Id==PULSOMETRO) sprintf(str,"BPM");
	else if(Id==BASCULA) sprintf(str,"KG");
	HAL_DISPLAY_printString(str,'U');
}
void APP_PANTALLA_printMensaje(char str[])
{
	HAL_DISPLAY_printString(str,'V');
}
