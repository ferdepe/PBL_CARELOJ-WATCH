/**
 * @file    timer.h
 * @brief   Declaraciones para manejar un único timer
 * @par		Descripción del fichero:
 *          Las funciones aquí declaradas permiten implementar
 *          un timer que provocará una interrupción cada
 *          x msecs indicados
 * @author  F. Domínguez
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
