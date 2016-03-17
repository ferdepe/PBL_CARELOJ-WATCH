/**
 * @file    tareaLogica.c
 * @brief   Fuente de la tarea que realiza el control de la lógica de la aplicación
 * @par		Logica
 *			- Estado 1
 *			- Estado 2
 *			- Estado 3
 * @par		Flujo
 * @image	html diagrama.genral.jpg
 * @author  F. Domínguez
 * @date    19/02/2015
 * @version 1.0
 * @todo aplicar entry a la máquina de estados
 * @todo platform.h como simulación
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "tareaLogica.h"
#include "funcionesLogica.h"
#include "axi-gpio.h"
//Simulación
#include "platform.h"
#include <stdio.h>

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/
ESTADO(idle)
	ITEM_EAC(EMERGENCIA, E_UsuarioSeCae, NULL),
	ITEM_EAC(EMERGENCIA, E_BotonEmergenciaPulsado, NULL),
	ITEM_EAC(MOSTRANDO_DATOS, E_BotonDisplayPulsado, A_displayData),
	ITEM_EAC(RECOGIENDO_DATOS, E_BotonRecogidaPulsado, A_displayGet)
FIN_ESTADO(idle,IDLE, ESTADO_idle_do)

ESTADO(emergencia)
	ITEM_EAC(IDLE, E_AvisoEnBuffer, NULL)
FIN_ESTADO(emergencia,EMERGENCIA,ESTADO_emergencia_do)

ESTADO(mostrando_datos)
	ITEM_EAC(IDLE, E_after10secs, A_displayReloj),
	ITEM_EAC(RECOGIENDO_DATOS, E_BotonRecogidaPulsado, A_displayGet),
	ITEM_EAC(MOSTRANDO_DATOS, E_BotonDisplayPulsado, A_displayData),
	ITEM_EAC(EMERGENCIA, E_UsuarioSeCae, A_resetContador),
	ITEM_EAC(EMERGENCIA, E_BotonEmergenciaPulsado, A_resetContador)
FIN_ESTADO(mostrando_datos,MOSTRANDO_DATOS,ESTADO_mostrando_datos_do)

ESTADO(recogiendo_datos)
	ITEM_EAC(MOSTRANDO_DATOS, E_FinRecogida, A_displayDataResult),
	ITEM_EAC(EMERGENCIA, E_UsuarioSeCae, NULL),
	ITEM_EAC(EMERGENCIA, E_BotonEmergenciaPulsado, NULL)
FIN_ESTADO(recogiendo_datos,RECOGIENDO_DATOS,ESTADO_recogiendo_datos_do)

AUTOMATA(careloj)
	& idle,
	& emergencia,
	& mostrando_datos,
	& recogiendo_datos
FIN_AUTOMATA(careloj, 1, E_nulo)

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/
static unsigned int contPantallaMedida = 0;

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

/**
 * @fn      BOOLEAN E_UsuarioSeCae
 * @brief   Evento de la caída del usuario.
 * @par     Descripción de la función:
 *          Evento que se produce al caerse el usuario detectado por el acelerómetro.
 * @return  ret
 * @date    16/02/2016
 */
BOOLEAN E_UsuarioSeCae(void){
	BOOLEAN ret;

	ret = APP_FUNCIONESLOGICA_E_readAcelerometer();

	return ret;
}

/**
 * @fn      BOOLEAN E_BotonEmergenciaPulsado
 * @brief   Evento de Botón de Emergencia pulsado
 * @par     Descripción de la función:
 *          Evento que se produce al pulsar el usuario el botón de Emergencia para pedir auxilio.
 * @return  ret
 * @date     16/02/2016
 */
BOOLEAN E_BotonEmergenciaPulsado(void){
	BOOLEAN ret;

	ret = APP_FUNCIONESLOGICA_E_readRedButton();

	return ret;
}

/**
 * @fn      BOOLEAN E_BotonDisplayPulsado
 * @brief   Evento de botón de cambio de pantalla pulsado
 * @par     Descripción de la función:
 *          Evento que indica que el usuario quiere cambiar el dato que quiere visualizar en pantalla entre las
 *          distintas pantallas disponibles
 * @return  ret
 * @date    16/02/2016
 */
BOOLEAN E_BotonDisplayPulsado(void){
	BOOLEAN ret;

	ret = APP_FUNCIONESLOGICA_E_readBlackButton();

	return ret;
}

/**
 * @fn      BOOLEAN E_BotonRecogidaPulsado
 * @brief   Evento de botón de recogida de datos de los sensores
 * @par     Descripción de la función:
 *          Evento que indica que el usuario va a recoger las medidas para ser enviadas posteriormente
 * @return  ret
 * @date    16/02/2016
 */
BOOLEAN E_BotonRecogidaPulsado(void){
	BOOLEAN ret;

		ret = APP_FUNCIONESLOGICA_E_readGreenButton();

		return ret;
	}

/**
 * @fn      BOOLEAN E_AvisoEnBuffer
 * @brief   Evento que indica que el dato está en el buffer de envío
 * @par     Descripción de la función:
 *          Evento producido cuando se escriben los datos de petición de socorro en el buffer de envío, desde
 *          el cual la tarea de envío va a enviar eses datos
 * @return  ret
 * @date    16/02/2016
 */
BOOLEAN E_AvisoEnBuffer(void){
	BOOLEAN ret = FALSE;
	unsigned int data;

	data = APP_FUNCIONESLOGICA_E_avisoEnBuffer();
	if (data >= 1 )
		ret = TRUE;
	return ret;
}

/**
 * @fn      BOOLEAN E_after10secs
 * @brief   Evento que indica que han pasado 10 segundos
 * @par     Descripción de la función:
 *          Evento para volver al estado IDLE si tras 10 segundos no se ha pulsado ningún botón de cambio de pantalla
 *          distintas pantallas disponibles
 * @return  ret
 * @date    16/02/2016
 */
BOOLEAN E_after10secs(void){
	BOOLEAN ret = FALSE;
	unsigned int data;

	data = APP_FUNCIONESLOGICA_E_after10s();
	if (data >= 1 )
		ret = TRUE;
	return ret;
}

/**
 * @fn      BOOLEAN E_FinRecogida
 * @brief   Evento que indica el fin de recogida de los datos de los sensores
 * @par     Descripción de la función:
 *          Evento que indica que los datos de los sensores han sido recogidos y puestos en el buffer para envío o bien
 *          que ha sido imposible realizar la medición
 * @return  ret
 * @date    16/02/2016
 */
BOOLEAN E_FinRecogida(void){
	BOOLEAN ret = FALSE;
	unsigned int data;

	data = APP_FUNCIONESLOGICA_E_endGetData();
	if (data == 1 )
		ret = TRUE;
	return ret;
}
/**
 * @fn         BOOLEAN E_nulo(void)
 * @brief      Evento nulo para no salir de la máquina de estado.
 * @par		   Descripción de la función:
 *             Evento que siempre devuelve un valor FALSE para el correcto funcionamiento del motor
 *             de la máquina de estados y que esta se ejecute tipo while(1)
 * @return     ret = FALSE
 * @date       26/02/2016
*/
BOOLEAN E_nulo(void){
	BOOLEAN ret = FALSE;
	return ret;
}

/**
 * @brief   Declaración de las acciones de la máquina de estados
 * @par		Nombre acción:
 *			- A_semaforoRojo
 * @param   void
 * @return  void
*/

void A_displayData(void){
	APP_FUNCIONESLOGICA_ENT_getTimerCount();
	APP_FUNCIONESLOGICA_A_setContador(&contPantallaMedida, SUMA);
	printf("Pantalla: %i \n\r", contPantallaMedida);
}
void A_displayReloj(void){
	APP_FUNCIONESLOGICA_A_setContador(&contPantallaMedida, RESET);
	printf("Pantalla: %i \n\r", contPantallaMedida);
	/*
	 * Insertar función displayPantalla con ID = 0
	 */
}
void A_displayGet(void){
	/*
	 * Insertar función displayPantalla con ID
	 */
	printf("Pantalla: Recogiendo datos... \r\n");
}
void A_displayDataResult(void){
	APP_FUNCIONESLOGICA_ENT_getTimerCount();
	APP_FUNCIONESLOGICA_A_setContador(&contPantallaMedida, RESTA);
	/*
	 * Insertar función displayPantalla con ID
	 */
	printf("Pantalla: Datos Recogidos \r\n");
}

void A_resetContador(void){
	APP_FUNCIONESLOGICA_A_setContador(&contPantallaMedida, RESET);
}

/**
 * @brief   Declaración de los DO a realizar en el estado que lo requiera
 * @par		Nombre DO:
 *			- ESTADO_verde_do
 * @param   void
 * @return  void
*/

void ESTADO_idle_do(void){
	HAL_AXI_GPIO_writeAxiLedPin(0,1);

}

void ESTADO_emergencia_do(void){
	HAL_AXI_GPIO_writeAxiLedPin(1,1);
	APP_FUNCIONESLOGICA_DO_protocoloEmergencia();
}

void ESTADO_mostrando_datos_do(void){
	HAL_AXI_GPIO_writeAxiLedPin(2,1);
}

void ESTADO_recogiendo_datos_do(void){
	HAL_AXI_GPIO_writeAxiLedPin(3,1);
	APP_FUNCIONESLOGICA_DO_getData();
}

void ESTADO_accion_nula(void){
	//VACÍO
}

/**
 * @brief   Función que llama a la ejecución de la máquina de estados
 * @par		La función llama a un autómata que implementa en su interior
            una máquina de estados:
 * @param   void
 * @return  void
*/

void APP_TAREALOGICA_ejecutaTarea(void){
	EjecutaAutomata(&careloj);
}

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/
