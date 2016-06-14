/**
 * @file    tareaLogica.h
 * @brief   Cabecera con la declaraci�n de los estados, eventos, acciones y ejecuci�n del conjunto
 * @par		Estructura
 *			- Enumeraci�n de estados
 *			- Declaraci�n de eventos
 *			- Declaraci�n de acciones
 *			- Declaraci�n de la funci�n para la ejecuci�n de la m�quina de estados
 * @par		Diagrama m�quina de estados
 * @image	html stm_CARELOJ.jpg
 * @author  J. Barrag�n
 * @author  F. Dom�nguez
 * @author  M. Etxebeste
 * @date    19/02/2015
 * @version 1.0
 * @todo	Crear funcionalidad entry en MotorAutomatas.c
 */

#ifndef APP_LOGICA_TAREA_H_
#define APP_LOGICA_TAREA_H_

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "MotorAutomatas.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/
/**
 * @enum       estados
 * @brief      Estados que componen la m�quina de estados
 * @par		   Descripci�n:
 * 			   -IDLE
 * 			   -EMERGENCIA
 * 			   -MOSTRANDO DATOS
 * 			   -RECOGIENDO DATOS
 * @author     F. Dom�nguez
 * @date       26/02/2016
*/
typedef enum{
	IDLE,
	EMERGENCIA,
	MOSTRANDO_DATOS,
	RECOGIENDO_DATOS
}estados;

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*                 EXPORTED VARIABLES                 *
*****************************************************/

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/

/***                    EVENTOS                   ***/
BOOLEAN E_UsuarioSeCae(void);
BOOLEAN E_BotonEmergenciaPulsado(void);
BOOLEAN E_AvisoEnBuffer(void);
BOOLEAN E_BotonDisplayPulsado(void);
BOOLEAN E_after10secs(void);
BOOLEAN E_BotonRecogidaPulsado(void);
BOOLEAN E_FinRecogida(void);

//Evento falso para mantener el aut�mata activo
BOOLEAN E_nulo(void);

/***                   ACCIONES                   ***/
void A_displayData(void);
void A_displayReloj(void);
void A_displayGet(void);
void A_displayDataResult(void);
void A_displayEmergency(void);
void A_resetContador(void);

//Para los eventos sin acci�n
void A_nula(void);

/***                 DO ESTADOS                   ***/
void ESTADO_idle_do(void);
void ESTADO_emergencia_do(void);
void ESTADO_mostrando_datos_do(void);
void ESTADO_recogiendo_datos_do(void);

void APP_TAREALOGICA_ejecutaTarea(void);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* LOGICA_TAREA_H_ */
