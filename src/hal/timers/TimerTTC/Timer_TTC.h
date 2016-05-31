/**
 * @file      timer_ttc.h
 * @brief     Short description.
 * @par		  Descripción de la función:
 * 			  par1
 *            par2
 * @author    author
 * @date      dd/mm/yyyy
 * @version   1.0
 */

#ifndef TIMER_TTC_H_
#define TIMER_TTC_H_

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "xttcps.h"
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

int HAL_TIMER_TTC_TimerSetup(unsigned int nHz);
int HAL_TIMER_TTC_GetTimerCount(void);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* TIMER_TTC_H_ */
