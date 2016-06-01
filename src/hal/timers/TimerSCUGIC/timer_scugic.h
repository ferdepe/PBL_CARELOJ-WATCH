/**
 * @file      timer_scugic.h
 * @brief     Short description.
 * @par		  Descripción de la función:
 * 			  par1
 *            par2
 * @author    F. Domínguez
 * @date      dd/mm/yyyy
 * @version   1.0
 */

#ifndef TIMER_SCUGIC_H_
#define TIMER_SCUGIC_H_

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "xscutimer.h"
#include "gic_arm.h"

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

int HAL_TIMER_SCUGIC_TimerSetup(int nHz);
int HAL_TIMER_SCUGIC_GetTimerCount(void);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* TIMER_SCUGIC_H_ */
