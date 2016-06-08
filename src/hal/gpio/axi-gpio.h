/**
 * @file    axi_gpio.h
 * @brief   Declaraciones para manejar diversas GPIO por el bus AXI
 * @par		Descripci�n del fichero:
 *          Las funciones aqu� declaradas permiten operar con los
 *          diversos perif�ricos AXI como botones, switches y leds
 *          de la placa ZYBO. Pueden devolver los valores como 4 bits
 *          o 1 �nico bit.
 * @author  F. Dom�nguez
 * @date    26/02/2016
 */

#ifndef HAL_AXIGPIO_H_
#define HAL_AXIGPIO_H_

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*                 EXPORTED VARIABLES                 *
*****************************************************/

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/
unsigned int HAL_AXI_GPIO_readAxiButtons();
unsigned int HAL_AXI_GPIO_readAxiSwitches();
unsigned int HAL_AXI_GPIO_readAxiButtonPin(unsigned int nPin);
unsigned int HAL_AXI_GPIO_readAxiSwitchPin(unsigned int nPin);
void HAL_AXI_GPIO_writeAxiLedPin (unsigned int nPin, unsigned int nValue);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* HAL_AXIGPIO_H_ */
