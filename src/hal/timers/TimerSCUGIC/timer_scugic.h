/**
 * @file    timer.h
 * @brief   Declaraciones para manejar un �nico timer
 * @par		Descripci�n del fichero:
 *          Las funciones aqu� declaradas permiten implementar
 *          un timer que provocar� una interrupci�n cada
 *          x msecs indicados
 * @author  F. Dom�nguez
 * @date    04/03/2016
 * @version 1.0
 */

#ifndef TIMER_SCUGIC_H_
#define TIMER_SCUGIC_H_

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
void HAL_TIMER_SCUGIC_initTimer(unsigned int msecs);
unsigned int HAL_TIMER_SCUGIC_getTimerCount();

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* TIMER_H_ */
