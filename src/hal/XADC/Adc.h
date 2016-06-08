
/**
 * @file      Adc.h
 * @brief     Funciones relacionadas con la obtención de datos del ADC.
 * @par		  Descripción de la función:
 * 			  par1
 *            par2
 * @author    Mikel Etxebeste
 * @date      18/05/2016
 * @version   1.0
 * @todo      todo
 * @bug       bug
 */
#ifndef LOGICA_ADC_H_
#define LOGICA_ADC_H_



/*****************************************************
*                   MODULES USED                     *
*****************************************************/

//includes

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
 * @fn         HAL_ADCInit
 * @brief      Función para inicializar el ADC.
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @author     Mikel Etxebeste
 * @date       18/05/2016
 **/
void HAL_ADC_Init();
/**
 * @fn         HAL_ADCInit
 * @brief      Funciónque obtiene el dato procesado del ADC.
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @author     Mikel Etxebeste
 * @date       18/05/2016
 **/
float HAL_ADC_ObtenerDato();

/*****************************************************
*                        EOF                         *
*****************************************************/



#endif /* LOGICA_ADC_H_ */
