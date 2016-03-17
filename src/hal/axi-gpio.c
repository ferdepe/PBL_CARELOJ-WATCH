/*
 * HAL_axi_gpio.c
 *
 *  Created on: 19 Feb, 2016
 *      Author: Fernando
 */

#include "axi-gpio.h"

/*************************************************//**
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

