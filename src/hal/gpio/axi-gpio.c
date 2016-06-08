/**
 * @file        axi-gpio.c
 * @brief       Fuente para operar con los periféricos GPIO de la ZYNQ.
 * @par		    Descripción de funciones:
 * 			    Aquí se implementan las distintas funciones para operar con los periféricos GPIO implementados
 * 			    en la placa ZYBO, como botones, switches y leds.
 * @version     2.0
 * @author      F. Domínguez
 * @date        01/03/2015
*/

#include "axi-gpio.h"

/******************************************************
 *                    INCLUDES                        *
 *****************************************************/

#ifdef ZYNQ_7000
#include "xil_printf.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "xparameters.h"
#endif
#ifdef AXI_GPIO
#include "xgpio.h"
#endif

#ifdef AXI_GPIO
#define GPIO_DEVICE_ID_BUTTONS      XPAR_BTNS_4BITS_DEVICE_ID
#define GPIO_DEVICE_ID_SWITCHES     XPAR_SWS_4BITS_DEVICE_ID
#define GPIO_DEVICE_ID_LEDS         XPAR_LEDS_4BITS_DEVICE_ID
#define AXI_CHANNEL         1
#endif

#ifdef AXI_GPIO
	static XGpio Gpio_AXI;
#endif

/**
 * @fn         HAL_AXI_GPIO_readAxiButtons(void)
 * @brief      Función que lee el array de cuatro botones de la ZYBO y lo devuelve en cuatro bits concatenados.
 * @ret        Data
 * @author     Fernando Domínguez
 * @date       24/03/2016
*/
unsigned int HAL_AXI_GPIO_readAxiButtons() {
#if defined(ZYNQ_7000) &&  defined(AXI_GPIO)
	unsigned int Data;

	XGpio_Initialize(&Gpio_AXI, GPIO_DEVICE_ID_BUTTONS);

	XGpio_SetDataDirection(&Gpio_AXI, AXI_CHANNEL, 0x0F);
	Data = XGpio_DiscreteRead(&Gpio_AXI, AXI_CHANNEL);

	return Data;
#else
	return 0;
#endif
}

/**
 * @fn         HAL_AXI_GPIO_readAxiSwitches(void)
 * @brief      Función que lee el array de cuatro switches de la ZYBO y lo devuelve en cuatro bits concatenados.
 * @ret        Data
 * @author     Fernando Domínguez
 * @date       24/03/2016
*/
unsigned int HAL_AXI_GPIO_readAxiSwitches() {
#if defined(ZYNQ_7000) &&  defined(AXI_GPIO)
	unsigned int Data;

	XGpio_Initialize(&Gpio_AXI, XPAR_SWS_4BITS_DEVICE_ID);

	XGpio_SetDataDirection(&Gpio_AXI, AXI_CHANNEL, 0x0F);
	Data = XGpio_DiscreteRead(&Gpio_AXI, AXI_CHANNEL);

	return Data;
#else
	return 0;
#endif
}

/**
 * @fn         HAL_AXI_GPIO_readAxiButtonPin(unsigned int nPin)
 * @brief      Función que lee el pin del boton de la ZYBO indicado por parámetro.
 * @param[in]  unsigned int nPin
 * @author     Fernando Domínguez
 * @date       24/03/2016
*/
unsigned int HAL_AXI_GPIO_readAxiButtonPin(unsigned int nPin) {
#if defined(ZYNQ_7000) &&  defined(AXI_GPIO)
	unsigned int Data;

	XGpio_Initialize(&Gpio_AXI, GPIO_DEVICE_ID_BUTTONS);

	XGpio_SetDataDirection(&Gpio_AXI, AXI_CHANNEL, 0x0F);
	Data = XGpio_DiscreteRead(&Gpio_AXI, AXI_CHANNEL);

	Data = Data & (1 << nPin);
	Data = Data >> nPin;

	return Data;
#else
	return 0;
#endif
}

/**
 * @fn         HAL_AXI_GPIO_readAxiSwitchPin(unsigned int nPin)
 * @brief      Función que lee el pin del boton de la ZYBO indicado por parámetro.
 * @param[in]  unsigned int nPin
 * @author     Fernando Domínguez
 * @date       24/03/2016
*/
unsigned int HAL_AXI_GPIO_readAxiSwitchPin(unsigned int nPin) {
#if defined(ZYNQ_7000) &&  defined(AXI_GPIO)
	unsigned int Data;

	XGpio_Initialize(&Gpio_AXI, XPAR_SWS_4BITS_DEVICE_ID);

	XGpio_SetDataDirection(&Gpio_AXI, AXI_CHANNEL, 0x0F);
	Data = XGpio_DiscreteRead(&Gpio_AXI, AXI_CHANNEL);

	Data = Data & (1 << nPin);
	Data = Data >> nPin;

	return Data;
#else
	return 0;
#endif
}

/**
 * @fn         HAL_AXI_GPIO_readAxiSwitchPin(unsigned int nPin, unsigned int nValue)
 * @brief      Función que escribe en el pin del led de la ZYBO indicado por parámetro.
 * @param[in]  unsigned int nPin
 * @param[in]  unsigned int nValue
 * @author     Fernando Domínguez
 * @date       24/03/2016
*/
void HAL_AXI_GPIO_writeAxiLedPin(unsigned int nPin, unsigned int nValue) {
#if defined(ZYNQ_7000) &&  defined(AXI_GPIO)
	unsigned int nMask = 0x00;

	XGpio_Initialize(&Gpio_AXI, GPIO_DEVICE_ID_LEDS);

	if (nValue > 1)
		nValue = 1;

	nMask = nMask | (nValue << nPin);

	XGpio_SetDataDirection(&Gpio_AXI, AXI_CHANNEL, 0x00);
	XGpio_DiscreteWrite(&Gpio_AXI,AXI_CHANNEL, nMask);

#endif
}

