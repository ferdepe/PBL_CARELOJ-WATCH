/**
 * @file    tareaLogica.c
 * @brief   Fuente de la tarea que realiza el control de la l�gica de la aplicaci�n
 * @par		Logica
 *			- Estado 1
 *			- Estado 2
 *			- Estado 3
 * @par		Flujo
 * @image	html diagrama.genral.jpg
 * @author  F. Dom�nguez
 * @date    19/02/2015
 * @version 1.0
 * @todo aplicar entry a la m�quina de estados
 * @todo platform.h como simulaci�n
 * @todo leds en estados s�lo para pruebas
 * @todo llamar a la funci�n \link funcionesLogica.c\APP_FUNCIONESLOGICA_A_displayPantalla \endlink
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "tareaLogica.h"
#include "funcionesLogica.h"
#include "axi-gpio.h"
//Simulaci�n
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
/**
 * @var       static unsigned int contPantallaMedida
 * @brief     Variable global que lleva el valor del identificador de las pantallas relacionadas con los sensores.
 * @author    Fernando Dom�nguez
 * @date      24/03/2016
*/
static unsigned int contPantallaMedida = 0;

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

/***                    EVENTOS                   ***/
/**
 * @fn      BOOLEAN E_UsuarioSeCae
 * @brief   Evento de la ca�da del usuario.
 * @par     Descripci�n de la funci�n:
 *          Evento que se produce al caerse el usuario detectado por el aceler�metro.
 * @return  ret
 * @author  F. Dom�nguez
 * @date    16/02/2016
 */
BOOLEAN E_UsuarioSeCae(void){
	BOOLEAN ret;

	ret = APP_FUNCIONESLOGICA_E_readAcelerometer();

	return ret;
}

/**
 * @fn      BOOLEAN E_BotonEmergenciaPulsado
 * @brief   Evento de Bot�n de Emergencia pulsado.
 * @par     Descripci�n de la funci�n:
 *          Evento que se produce al pulsar el usuario el bot�n de Emergencia para pedir auxilio.
 * @return  ret
 * @author  F. Dom�nguez
 * @date     16/02/2016
 */
BOOLEAN E_BotonEmergenciaPulsado(void){
	BOOLEAN ret;

	ret = APP_FUNCIONESLOGICA_E_readRedButton();

	return ret;
}

/**
 * @fn      BOOLEAN E_BotonDisplayPulsado
 * @brief   Evento de bot�n de cambio de pantalla pulsado.
 * @par     Descripci�n de la funci�n:
 *          Evento que indica que el usuario quiere cambiar el dato que quiere visualizar en pantalla entre las
 *          distintas pantallas disponibles
 * @return  ret
 * @author  F. Dom�nguez
 * @date    16/02/2016
 */
BOOLEAN E_BotonDisplayPulsado(void){
	BOOLEAN ret;

	ret = APP_FUNCIONESLOGICA_E_readBlackButton();

	return ret;
}

/**
 * @fn      BOOLEAN E_BotonRecogidaPulsado
 * @brief   Evento de bot�n de recogida de datos de los sensores.
 * @par     Descripci�n de la funci�n:
 *          Evento que indica que el usuario va a recoger las medidas para ser enviadas posteriormente
 * @return  ret
 * @author  F. Dom�nguez
 * @date    16/02/2016
 */
BOOLEAN E_BotonRecogidaPulsado(void){
	BOOLEAN ret;

		ret = APP_FUNCIONESLOGICA_E_readGreenButton();

		return ret;
	}

/**
 * @fn      BOOLEAN E_AvisoEnBuffer
 * @brief   Evento que indica que el dato est� en el buffer de env�o.
 * @par     Descripci�n de la funci�n:
 *          Evento producido cuando se escriben los datos de petici�n de socorro en el buffer de env�o, desde
 *          el cual la tarea de env�o va a enviar eses datos
 * @return  ret
 * @author  F. Dom�nguez
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
 * @brief   Evento que indica que han pasado 10 segundos.
 * @par     Descripci�n de la funci�n:
 *          Evento para volver al estado IDLE si tras 10 segundos no se ha pulsado ning�n bot�n de cambio de pantalla
 *          distintas pantallas disponibles
 * @return  ret
 * @author  F. Dom�nguez
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
 * @brief   Evento que indica el fin de recogida de los datos de los sensores.
 * @par     Descripci�n de la funci�n:
 *          Evento que indica que los datos de los sensores han sido recogidos y puestos en el buffer para env�o o bien
 *          que ha sido imposible realizar la medici�n
 * @return  ret
 * @author  F. Dom�nguez
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
 * @fn      BOOLEAN E_nulo(void)
 * @brief   Evento nulo para no salir de la m�quina de estado.
 * @par		Descripci�n de la funci�n:
 *          Evento que siempre devuelve un valor FALSE para el correcto funcionamiento del motor
 *          de la m�quina de estados y que esta se ejecute tipo while(1)
 * @return  ret = FALSE
 * @author  F. Dom�nguez
 * @date    26/02/2016
*/
BOOLEAN E_nulo(void){
	BOOLEAN ret = FALSE;
	return ret;
}

/***                   ACCIONES                   ***/
/**
 * @fn      A_displayData(void)
 * @brief   Acci�n que llama a mostrar pantalla seg�n un contador de pantalla \link contPantallaMedida \endlink.
 * @par		Descripci�n de la funci�n:
 *          Con \link APP_FUNCIONESLOGICA_A_setContador \endlink operamos sobre el contador de pantalla, en este
 *          caso SUMA. Cada vez que se pulsa el bot�n avanza a la siguiente pantalla (a la inicial si est� en la �ltima).
 * @author  F. Dom�nguez
 * @date    26/02/2016
*/
void A_displayData(void){
	APP_FUNCIONESLOGICA_ENT_getTimerCount();
	APP_FUNCIONESLOGICA_A_setContador(&contPantallaMedida, SUMA);
	APP_FUNCIONESLOGICA_A_displayPantalla(contPantallaMedida);
	printf("Pantalla: %i \n\r", contPantallaMedida);
}

/**
 * @fn      A_displayReloj(void)
 * @brief   Acci�n que llama a mostrar pantalla la pantalla del reloj con su id fijo.
 * @par		Descripci�n de la funci�n:
 *          Con \link APP_FUNCIONESLOGICA_A_setContador \endlink operamos sobre el contador de pantalla, en este
 *          caso RESET debido a que reloj es la pantalla inicial y se le asocia un 0 a su identificador.
 * @author  F. Dom�nguez
 * @date    26/02/2016
*/
void A_displayReloj(void){
	APP_FUNCIONESLOGICA_A_setContador(&contPantallaMedida, RESET);
	APP_FUNCIONESLOGICA_A_displayPantalla(contPantallaMedida);
	printf("Pantalla: %i \n\r", contPantallaMedida);
	/*
	 * Insertar funci�n displayPantalla con ID = 0
	 */
}

/**
 * @fn      A_displayGet(void)
 * @brief   Acci�n que llama a mostrar por pantalla la pantalla de que el dispositivo est� recogiendo datos.
 * @par		Descripci�n de la funci�n:
 *          Con \link APP_FUNCIONESLOGICA_A_setContador \endlink operamos sobre el contador de pantalla, en este
 *          caso RESET debido a que reloj es la pantalla inicial y se le asocia un 0 a su identificador.
 * @author  F. Dom�nguez
 * @date    26/02/2016
*/
void A_displayGet(void){
	/*
	 * Insertar funci�n displayPantalla con ID
	 */
	APP_FUNCIONESLOGICA_A_displayPantalla(40);
	printf("Pantalla: Recogiendo datos... \r\n");
}

/**
 * @fn      A_displayDataResult(void)
 * @brief   Acci�n que llama a mostrar por pantalla que el dispositivo ha acabado de recoger datos.
 * @par		Descripci�n de la funci�n:
 *          Con \link APP_FUNCIONESLOGICA_A_setContador \endlink operamos sobre el contador de pantalla, en este
 *          caso RESET debido a que reloj es la pantalla inicial y se le asocia un 0 a su identificador.
 * @author  F. Dom�nguez
 * @date    26/02/2016
*/
void A_displayDataResult(void){
	APP_FUNCIONESLOGICA_ENT_getTimerCount();
	APP_FUNCIONESLOGICA_A_setContador(&contPantallaMedida, RESTA);
	/*
	 * Insertar funci�n displayPantalla con ID 43
	 */
	printf("Pantalla: Datos Recogidos \r\n");
}

/**
 * @fn      A_resetContador(void)
 * @brief   Acci�n que resetea \link contPantallaMedida \endlink.
 * @par		Descripci�n de la funci�n:
 *          Con \link APP_FUNCIONESLOGICA_A_setContador \endlink operamos sobre el contador de pantalla, en este
 *          caso RESET. Al entrar en el estado de EMERGENCIA dede MOSTRANDO_DATOS resetea el contador.
 * @author  F. Dom�nguez
 * @date    17/03/2016
*/
void A_resetContador(void){
	APP_FUNCIONESLOGICA_A_setContador(&contPantallaMedida, RESET);
}

/***                 DO ESTADOS                   ***/
/**
 * @fn      ESTADO_idle_do(void)
 * @brief   Do del estado IDLE con led indicador de que est� en ese estado. SIMULACI�N
 * @author  Fernando Dom�nguez
 * @date    17/03/2016
*/
void ESTADO_idle_do(void){
	HAL_AXI_GPIO_writeAxiLedPin(0,1);

}

/**
 * @fn      ESTADO_emergencia_do(void)
 * @brief   Do del estado EMERGENCIA.
 * @par     Descripci�n de la funci�n:
 *          - Escribe en el led 1 para simulaci�n
 *          - Llama a la funci�n de protocolo de emergencia. Recogida de datos y colgarlos en buffer env�o \link DATAMANAGEMENT_envioEmergencia \endlink.
 * @author  Fernando Dom�nguez
 * @date    17/03/2016
*/
void ESTADO_emergencia_do(void){
	HAL_AXI_GPIO_writeAxiLedPin(1,1);
	APP_FUNCIONESLOGICA_DO_protocoloEmergencia();
}

/**
 * @fn      ESTADO_mostrando_datos_do(void)
 * @brief   Do del estado MOSTRANDO_DATOS con led indicador de que est� en ese estado. SIMULACI�N
 * @author  Fernando Dom�nguez
 * @date    17/03/2016
*/
void ESTADO_mostrando_datos_do(void){
	HAL_AXI_GPIO_writeAxiLedPin(2,1);
}

/**
 * @fn      ESTADO_recogiendo_datos_do(void)
 * @brief   Do del estado RECOGIENDO_DATOS.
 * @par     Descripci�n de la funci�n:
 *          - Escribe en el led 3 para simulaci�n
 *          - Llama a la funci�n para recogida de datos y colgarlos en buffer env�o \link DATAMANAGEMENT_envioDatos \endlink.
 * @author  Fernando Dom�nguez
 * @date    17/03/2016
*/
void ESTADO_recogiendo_datos_do(void){
	HAL_AXI_GPIO_writeAxiLedPin(3,1);
	APP_FUNCIONESLOGICA_DO_getData();
}

/**
 * @fn      APP_TAREALOGICA_ejecutaTarea(void)
 * @brief   Funci�n que llama a la ejecuci�n de la m�quina de estados
 * @par		Descripci�n de la funci�n:
 *          La funci�n llama a un aut�mata que implementa en su interior
 *          la m�quina de estados definida.
 * @author  Fernando Dom�nguez
 * @date    17/03/2016
*/

void APP_TAREALOGICA_ejecutaTarea(void){
	EjecutaAutomata(&careloj);
}

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/
