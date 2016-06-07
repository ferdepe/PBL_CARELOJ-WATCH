/**
 * @file    funcionesLogica.c
 * @brief   Source con la implementaci�n de las funciones que realizar�n la l�gica general.
 * @par		Descripci�n de la funci�n:
 * 			En estos ficheros se recoge el conjunto de funciones que realizar�n la l�gica
 * 			interna de la m�quina de estados correspondiente a las acciones, eventos y do.
 * @author  F. Dom�nguez
 * @date    04/03/2015
 * @version 1.0
 * @todo    Funci�n entry del getTimerCount
 * @todo    Contador timer a 2 segundos, cambiarlo a 10 como en esquema
 * @bug     Variables globales avisoEnBuffer y endGetData no se resetean.
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/
#include "funcionesLogica.h"
#include "axi-gpio.h"
#include "timer_ttc.h"
#include "dataSensors.h"

#include "dataEmergency.h"
#include "dataDisplay.h"
#include "Pulsometro.h"
#include "acelerometro.h"
#include "config.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

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
 * @var       static unsigned int contadorTimer
 * @brief     Variable global que lleva el valor inicial del timer a la entrada del estado MOSTRANDO DATOS
 * @author    Fernando Dom�nguez
 * @date      24/03/2016
*/
static unsigned int contadorTimer = 0;
/**
 * @var       static unsigned int avisoEnBuffer
 * @brief     Variable global que indica si el aviso de emergencia est� en el buffer o no
 * @author    Fernando Dom�nguez
 * @date      24/03/2016
*/
static unsigned int avisoEnBuffer = 0;
/**
 * @var       static unsigned int endGetData
 * @brief     Variable global que indica si se ha acabado de recoger datos (con o sin �xito)
 * @author    Fernando Dom�nguez
 * @date      24/03/2016
*/
static unsigned int endGetData = 0;

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

/***                 LOGICA EVENTOS               ***/
/**
 * @fn        APP_FUNCIONESLOGICA_E_readAcelerometer(void)
 * @brief     Funci�n llamada en el evento que lee si el aceler�metro ha detectado una ca�da.
 * @par		  Simulada por bot�n!
 * @author    Fernando Dom�nguez
 * @date      24/03/2016
*/
BOOLEAN APP_FUNCIONESLOGICA_E_readAcelerometer(){
	static unsigned int pinAnterior = 0;
	unsigned int pinActual = 0;
	BOOLEAN ret;

	pinActual = HAL_ACELEROMETRO_getEstadoCaida();

	if(pinActual && !pinAnterior)
		ret = 1;
	else
		ret = 0;

	pinAnterior = pinActual;
	return ret;
}

/**
 * @fn        APP_FUNCIONESLOGICA_E_readRedButton(void)
 * @brief     Funci�n llamada en el evento que lee si el usuario pulsa o no el bot�n ROJO relacionado con la solicitud de emergencia.
 * @par		  �Simulada por bot�n!
 * @return    ret
 * @author    Fernando Dom�nguez
 * @date      24/03/2016
*/
BOOLEAN APP_FUNCIONESLOGICA_E_readRedButton(){
	static unsigned int pinAnterior = 0;
	unsigned int pinActual;
	BOOLEAN ret;

	pinActual = HAL_AXI_GPIO_readAxiButtonPin(1);

	if(pinActual && !pinAnterior)
		ret = 1;
	else
		ret = 0;

	pinAnterior = pinActual;
	return ret;
}

/**
 * @fn        APP_FUNCIONESLOGICA_E_readBlackButton(void)
 * @brief     Funci�n llamada en el evento que lee si el usuario pulsa o no el bot�n NEGRO relacionado con el display.
 * @par		  Simulada por bot�n!
 * @return    ret
 * @author    Fernando Dom�nguez
 * @date      24/03/2016
*/
BOOLEAN APP_FUNCIONESLOGICA_E_readBlackButton(){
	static unsigned int pinAnterior = 0;
	unsigned int pinActual;
	BOOLEAN ret;

	pinActual = HAL_AXI_GPIO_readAxiButtonPin(2);

	if(pinActual && !pinAnterior)
		ret = 1;
	else
		ret = 0;

	pinAnterior = pinActual;
	return ret;
}

/**
 * @fn        APP_FUNCIONESLOGICA_E_readGreenButton(void)
 * @brief     Funci�n llamada en el evento que lee si el usuario pulsa o no el bot�n VERDE relacionado con la recogida de datos.
 * @par		  Simulada por bot�n!
 * @return    ret
 * @author    Fernando Dom�nguez
 * @date      24/03/2016
*/
BOOLEAN APP_FUNCIONESLOGICA_E_readGreenButton(){
	static unsigned int pinAnterior = 0;
	unsigned int pinActual;
	BOOLEAN ret;

	pinActual = HAL_AXI_GPIO_readAxiButtonPin(3);

	if(pinActual && !pinAnterior)
		ret = 1;
	else
		ret = 0;

	pinAnterior = pinActual;
	return ret;
}

/**
 * @fn        APP_FUNCIONESLOGICA_E_after10s(void)
 * @brief     Funci�n llamada en el evento que comprueba si han pasado los 10 segundos para pasar a IDLE sin actividad.
 * @par		  Descripci�n de la funci�n:
 *            Se comprueba el timer desde el valor de su contador en el cu�l se ha entrado (o reentrado)
 *            al estado. El valor inicial se guarda en \link contadorTimer \endlink en la funci�n
 *            \link APP_FUNCIONESLOGICA_ENT_getTimerCount \endlink. Cuando la diferencia supera a 10 segundos
 *            devuleve un 1 o TRUE.
 * @return    1
 * @return    0
 * @author    Fernando Dom�nguez
 * @date      24/03/2016
*/
BOOLEAN APP_FUNCIONESLOGICA_E_after10s(){
	unsigned int cont = 0;

	cont = HAL_TIMER_TTC_GetTimerCount();
	if ((cont - contadorTimer) >= 20)
		return 1;
	else
		return 0;
}

/**
 * @fn         APP_FUNCIONESLOGICA_E_endGetData(void)
 * @brief      Funci�n llamada en el evento que devuelve si se ha acabado de leer los datos y colgarlos en el buffer \link DATAMANAGEMENT_envioDatos \endlink.
 * @par		   Descripci�n de la funci�n:
 *             La funci�n \link APP_FUNCIONESLOGICA_DO_getData \endlink realiza la recogida y preparaci�n de la trama de env�o que coloca
 *             en \link DATAMANAGEMENT_envioDatos \endlink para su posterior env�o en \link tareaEnvio.c \endlink; cuando acaba de realizar
 *             esta operaci�n, sea correcta o no, pone la variable global endGetData a 1.
 * @var        static unsigned int endGetData
 * @brief      Variable global.
 * @return     endGetData
 * @author     Fernando Dom�nguez
 * @date       24/03/2016
*/
BOOLEAN APP_FUNCIONESLOGICA_E_endGetData(){
	return endGetData;
}

/**
 * @fn         APP_FUNCIONESLOGICA_E_avisoEnBuffer(void)
 * @brief      Funci�n llamada en el evento que devuelve si los datos de emergencia han sido puestos en el buffer \link DATAMANAGEMENT_envioEmergencia \endlink para
 *             su posterior env�o.
 * @par		   Descripci�n de la funci�n:
 *             La funci�n \link APP_FUNCIONESLOGICA_DO_protocoloEmergencia \endlink llama a la recogida de los datos necesarios a transmitir
 *             en caso de una emergencia del usuario, y coloca esa trama en el buffer \link DATAMANAGEMENT_envioEmergencia \endlink para su
 *             posterior env�o en \link tareaEnvio.c \endlink; cuando los datos de emergencia est�n colgados en el buffer, la variable global
 *             devuleve un 1 o TRUE.
 * @var        static unsigned int avisoEnBuffer
 * @brief      Variable global
 * @return     avisoEnBuffer
 * @author     Fernando Dom�nguez
 * @date       24/03/2016
*/
BOOLEAN APP_FUNCIONESLOGICA_E_avisoEnBuffer(){

	return avisoEnBuffer;
}

/***                L�GICA ACCIONES               ***/
/**
 * @fn         APP_FUNCIONESLOGICA_A_displayPantalla(nId)
 * @brief      Funci�n llamada en la acci�n que llama a mostrar una pantalla en el display seg�n el id que corresponda.
 * @par		   Descripci�n de la funci�n:
 *             Cada pantalla posible que se muestra por la pantalla, estar� configurada previamente y asociada a una estructura que contendr� el
 *             identificador que le corresponda, con su valor y sus unidades (en caso de que sea una pantalla asociada a una medida de un sensor).
 *             �nicamente se pasa el id por par�metro, con ese id se llama a otra funci�n para que muestre la pantalla asociada.
 * @param[in]  unsigned int nId
 * @author     Fernando Dom�nguez
 * @date       24/03/2016
*/
void APP_FUNCIONESLOGICA_A_displayPantalla(unsigned int nId){
	APP_DATA_DISPLAY_setIdPantalla(nId);
}

/**
 * @fn         APP_FUNCIONESLOGICA_A_displayPantalla(unsigned int *cont, unsigned char nOperacion)
 * @brief      Funci�n llamada en la acci�n que opera sobre el contador del id de pantalla \link contPantallaMedida \endlink declarado como global en \link tareaLogica.c \endlink.
 * @par		   Descripci�n de la funci�n:
 *             En funci�n de la operaci�n introducida por par�metro en nOperacion (SUMA, RESTA o RESET) se modifica el contador. Todas son para manejar el cambio
 *             entre pantallas que muestran valores le�dos de sensores y almacenados en memoria.
 * @param[in]  unsigned int *cont
 * @param[in]  unsigned char nOperacion
 * @param[out] unsigned int *cont
 * @author     Fernando Dom�nguez
 * @date       24/03/2016
*/
void APP_FUNCIONESLOGICA_A_setContador(unsigned int *cont, unsigned char nOperacion){
	int operador = *cont;

	switch(nOperacion){
	case RESET :
		operador = 0;
		break;
	case SUMA :
		operador = (operador+1) % (NUMBER_SENSORS+1);
		break;
	case RESTA :
		if(*cont > 0)
		operador = operador - 1;
		break;

	}

	*cont = operador;
}

/***                 L�GICA ENTRY                 ***/
/**
 * @fn         APP_FUNCIONESLOGICA_ENT_getTimerCount(void)
 * @brief      Funci�n llamada en el entry del estado mostrando datos que asigna a \link contadorTimer \endlink un valor de referencia inicial en MOSTRANDO_DATOS
 * @par		   Descripci�n de la funci�n:
 *             El valor de referencia del timer, configurado al inicializar el programa, se coge al entrar en el estado para que el evento
 *             \link APP_FUNCIONESLOGICA_E_after10s \endlink pueda comprobar que han pasado los 10 segundos desde la entrada al estado para
 *             retornar a IDLE si no se ha pulsado ning�n bot�n.
 * @author     Fernando Dom�nguez
 * @date       24/03/2016
*/
void APP_FUNCIONESLOGICA_ENT_getTimerCount(){
	contadorTimer = HAL_TIMER_TTC_GetTimerCount();
}

/**
 * @fn         APP_FUNCIONESLOGICA_DO_protocoloEmergencia(void)
 * @brief      Funci�n llamada en el do de EMERGENCIA
 * @par		   Descripci�n de la funci�n:
 *             Aqu� se llama a la funci�n para recoger los datos de los sensores que devuelve una trama a enviar, esa trama se cuelga posteriormente
 *             en el buffer \link DATAMANAGEMENT_envioEmergencia \endlink en la funci�n \link APP_DATAMANAGEMENT_send2Buffer \endlink.
 * @author     Fernando Dom�nguez
 * @date       24/03/2016
*/
/***                  L�GICA DO                   ***/
void APP_FUNCIONESLOGICA_DO_protocoloEmergencia(){

	/*
	 * INSERTAR AQU� FUNCI�N QUE LLAMA A RECOGER DATOS EMERGENCIA
	 */
	GPS_DATA gpsValues = {30,45,23.0,12,33,30.2};
	unsigned int BPM;
	BPM = LIBS_PULSOMETRO_GetBPM();

	APP_DATA_EMERGENCY_setDataToEmergency(BPM, gpsValues);
	avisoEnBuffer = APP_DATA_EMERGENCY_dataReady();
}

/**
 * @fn         APP_FUNCIONESLOGICA_DO_getData(void)
 * @brief      Funci�n llamada en el do de RECOGIENDO DATOS
 * @par		   Descripci�n de la funci�n:
 *             Aqu� se llama a la funci�n para recoger los datos de los sensores que devuelve una trama a enviar, esa trama se cuelga posteriormente
 *             en el buffer \link DATAMANAGEMENT_envioDatos \endlink en la funci�n \link APP_DATAMANAGEMENT_send2Buffer \endlink.
 * @author     Fernando Dom�nguez
 * @date       24/03/2016
*/
void APP_FUNCIONESLOGICA_DO_getData(){
	/*
	 * INSERTAR AQU� FUNCI�N DE REGOGIDA DE DATOS
	 */
	unsigned int BPM;
	BPM = LIBS_PULSOMETRO_GetBPM();


	APP_DATA_SENSORS_setSensorData(PULSOMETRO, /*130.0*/ BPM);
	
	APP_DATA_SENSORS_setSensorData(BASCULA, 75);
	
	
	endGetData = APP_DATA_SENSORS_dataReady();
}
/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/

