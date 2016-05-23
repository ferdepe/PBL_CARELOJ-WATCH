/**
 * @file      Timer.h
 * @brief     Ficheros relacionados para inicializar y utilizar el timer TTC.
 * @par		  Descripción de la función:
 * 			  par1
 *            par2
 * @author    Mikel Etxebeste Larrea
 * @date      18/05/2016
 * @version   1.0
 * @todo      todo
 * @bug       bug
 */

#ifndef TIMER_H_
#define TIMER_H_

/*****************************************************
*                   MODULES USED                     *
*****************************************************/



/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

//defines

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*                 EXPORTED VARIABLES                 *
*****************************************************/

//variables externas si hay

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/
/**
 * @fn         HAL_initTTC1
 * @brief      Función que inicializa el timer TTC.
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @author     Mikel Etxebeste
 * @date       18/05/2016
 **/
void HAL_TIMER_TTC_initTimer();
/**
 * @fn         HAL_initTTC1
 * @brief      Función que obtiene el contador de la interrupción que interrumpe cada segundo.
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @author     Mikel Etxebeste
 * @date       18/05/2016
 **/
unsigned int HAL_TIMER_TTC_getCount();

/*****************************************************
*                        EOF                         *
*****************************************************/




#endif /* TIMER_H_ */
