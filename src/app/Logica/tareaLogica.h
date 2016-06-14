/**
 * @file    tareaLogica.h
 * @brief   Cabecera con la declaración de los estados, eventos, acciones y ejecución del conjunto
 * @par		Estructura
 *			- Enumeración de estados
 *			- Declaración de eventos
 *			- Declaración de acciones
 *			- Declaración de la función para la ejecución de la máquina de estados
 * @par		Diagrama máquina de estados
 * @image	html stm_CARELOJ.jpg
 * @author  J. Barragán
 * @author  F. Domínguez
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
 * @brief      Estados que componen la máquina de estados
 * @par		   Descripción:
 * 			   -IDLE
 * 			   -EMERGENCIA
 * 			   -MOSTRANDO DATOS
 * 			   -RECOGIENDO DATOS
 * @author     F. Domínguez
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

//Evento falso para mantener el autómata activo
BOOLEAN E_nulo(void);

/***                   ACCIONES                   ***/
void A_displayData(void);
void A_displayReloj(void);
void A_displayGet(void);
void A_displayDataResult(void);
void A_displayEmergency(void);
void A_resetContador(void);

//Para los eventos sin acción
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
