
/**
 * @file      Adc.h
 * @brief     Funciones relacionadas con la obtenci�n de datos del ADC.
 * @par		  Descripci�n de la funci�n:
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
 * @brief      Funci�n para inicializar el ADC.
 * @par		   Descripci�n de la funci�n:
 * 			   par1
 *             par2
 * @author     Mikel Etxebeste
 * @date       18/05/2016
 **/
void HAL_ADC_Init();
/**
 * @fn         HAL_ADCInit
 * @brief      Funci�nque obtiene el dato procesado del ADC.
 * @par		   Descripci�n de la funci�n:
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
