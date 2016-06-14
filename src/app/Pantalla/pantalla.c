 /**
 * @file      pantalla.c
 * @brief     Fichero de las funciones utilizadas por la tareaPantalla.
 * @par		  Descripción de la función:
 * 			  Conjunto de funciones que utiliza la tareaPantalla para
 * 			  comunicarse con el HAL para realizar al impresion en pantalla.
 * @author    Javier Barragán
 * @date      24/05/2016
 * @version   1.0
 * @todo
 * @bug
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

void APP_PANTALLA_screenClock(void);

void APP_PANTALLA_screenSensor(unsigned int Id);

void APP_PANTALLA_screenBanner(unsigned int Id);

void APP_PANTALLA_printTipo(CONFIG_SENSORS Id);

void APP_PANTALLA_printValor(float valor);

void APP_PANTALLA_printUnidad(CONFIG_SENSORS Id);

void APP_PANTALLA_printMensaje(char str[],char str1[]);

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/
char strT[10], strV[6], strU[3];
char str[];
/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
void APP_PANTALLA_init()
{
    //inicializacion display
    HAL_DISPLAY_init();
    //HAL_DISPLAY_refresh();
}

void APP_PANTALLA_mostrar()
{
	unsigned int Id;
	Id=APP_DATA_DISPLAY_getIdPantalla();
	if(Id==0) APP_PANTALLA_screenClock();
	else if(Id<10) APP_PANTALLA_screenSensor(Id);
	else if(Id>10) APP_PANTALLA_screenBanner(Id);
	else APP_PANTALLA_printMensaje("","Error");
}
/*****************************************************
*                  LOCAL FUNCTIONS                   *
************************************************
*****************************************************/
/**
 * @fn         APP_PANTALLA_screenClock
 * @brief      Display del tiempo.
 * @par		   Descripción de la función:
 * 			   Función que empieza con el llamado para
 * 			   imprimir el reloj en pantalla.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/05/2016
 */
void APP_PANTALLA_screenClock()
{
	T_TIME tiempo;
	tiempo=LIBS_WATCH_getTime();
	sprintf(strT, "TIEMPO\n");
	sprintf(strV, "%d:%i:%i", tiempo.hour, tiempo.min, tiempo.seg);
	sprintf(strU, "\0");
	HAL_DISPLAY_screen(strT,strV,strU);
}

/**
 * @fn         APP_PANTALLA_screenSensor
 * @brief      Display del sensor.
 * @par		   Descripción de la función:
 * 			   Función que empieza con el llamado para
 * 			   imprimir el tipo, valor y unidad de un sensor en pantalla.
 * @param[in]  unsigned int ID, identificador del sensor.
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/05/2016
 */
void APP_PANTALLA_screenSensor(unsigned int Id)
{
	DATAMANAGEMENT_SENSOR_DATA SENSOR;

	SENSOR=APP_DATA_SENSORS_getSensorData(Id);
	APP_PANTALLA_printTipo(Id);
	APP_PANTALLA_printValor(SENSOR.value);
	APP_PANTALLA_printUnidad(Id);
	HAL_DISPLAY_screen(strT,strV,strU);
}

/**
 * @fn         APP_PANTALLA_screenBanner
 * @brief      Display de mensajes fijos.
 * @par		   Descripción de la función:
 * 			   Función encargada de reproducir en el
 * 			   display los mensajes fijos sin valores.
 * @param[in]  unsigned int Id, Identificador del mensaje.
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/05/2016
 */
void APP_PANTALLA_screenBanner(unsigned int Id)
{
	if(Id==40)	APP_PANTALLA_printMensaje("Recogiendo","Datos...");
	else if(Id==41) APP_PANTALLA_printMensaje("Enviando","Datos...");
	else if(Id==42) APP_PANTALLA_printMensaje("Boton de","Panico ON");
	else if(Id==43) APP_PANTALLA_printMensaje("Datos","Recogidos");
	else APP_PANTALLA_printMensaje("","Error");
}

/**
 * @fn         APP_PANTALLA_printTipo
 * @brief      Función para imprimir el Tipo de sensor.
 * @par		   Descripción de la función:
 * 			   Función encargada de reproducir en el
 * 			   display el tipo de sensor seleccionado y que
 * 			   se reproducirá sus datos en pantalla.
 * @param[in]  CONFIG_SENSORS Id, Identificador de la estructura del sensor.
 * @param[out] void
 * @author     Javier Barragán
 * @date       24/05/2016
 */
void APP_PANTALLA_printTipo(CONFIG_SENSORS Id)
{
	if(Id==PULSOMETRO) sprintf(strT,"PULSOMETRO");
	else if(Id==BASCULA) sprintf(strT,"BASCULA");
	//else if(Id==GPS) sprintf(str,"GPS");
}

/**
 * @fn         APP_PANTALLA_printValor
 * @brief      Función para imprimir el Valor del sensor.
 * @par		   Descripción de la función:
 * 			   Función encargada de reproducir en el
 * 			   display el valor de sensor seleccionado y que
 * 			   se reproducirá sus datos en pantalla.
 * @param[in]  float valor, valor del sensor.
 * @param[out] void
 * @author     Javier Barragán
 * @date       24/05/2016
 */
void APP_PANTALLA_printValor(float valor)
{
	sprintf(strV,"%.2f",valor);
}

/**
 * @fn         APP_PANTALLA_printUnidad
 * @brief      Función para imprimir la Unidad del sensor.
 * @par		   Descripción de la función:
 * 			   Función encargada de reproducir en el
 * 			   display la unidad del sensor seleccionado y que
 * 			   se reproducirá sus datos en pantalla.
 * @param[in]  CONFIG_SENSORS Id, Identificador del sensor.
 * @param[out] void
 * @author     Javier Barragán
 * @date       24/05/2016
 */
void APP_PANTALLA_printUnidad(CONFIG_SENSORS Id)
{
	if(Id==PULSOMETRO) sprintf(strU,"BPM");
	else if(Id==BASCULA) sprintf(strU,"KG");
}

/**
 * @fn         APP_PANTALLA_printMensaje
 * @brief      Función para imprimir mensajes en pantalla.
 * @par		   Descripción de la función:
 * 			   Función encargada de reproducir en el
 * 			   display mensajes y que se reproducirá en pantalla.
 * @param[in]  char str[], cadena de caracteres del primer renglón del mensaje.
 * @param[in]  char str1[], cadena de caracteres del segundo renglón del mensaje.
 * @param[out] void
 * @author     Javier Barragán
 * @date       24/05/2016
 */
void APP_PANTALLA_printMensaje(char str[],char str1[])
{
	HAL_DISPLAY_screen(str,str1,"");
}
