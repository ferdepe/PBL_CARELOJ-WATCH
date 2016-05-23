
/**
 * @file      display.h
 * @brief     Short description.
 * @par		  Descripción de la función:
 * 			  par1
 *            par2
 * @author    Javier Barragán
 * @date      17/10/2015
 * @version   1.0
 * @todo      terminar HAL_DISPLAY_readInteger();
 * @bug
 */
#ifndef DISPLAY_H_
#define DISPLAY_H_

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

/**
 * @fn         HAL_DISPLAY_init
 * @brief      Inicialización del Display.
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/10/2015
 */
void HAL_DISPLAY_init();
/**
 * @fn         HAL_DISPLAY_printTipo
 * @brief      Impresión de cadena de caracteres en Display.
 * @par		   Descripción de la función:
 * 			   imprime la cadena de caracteres str.
 *             letra indica la posicion en pantalla dependiendo
 *             si es [T]ipo, [V]alor o [U]nidad.
 * @param[in]  str[] y letra.
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/10/2015
 */
void HAL_DISPLAY_printString(char str[], char letra);
/**
 * @fn         HAL_DISPLAY_printString
 * @brief      Impresión de cadena de caracteres en Display.
 * @par		   Descripción de la función:
 * 			   imprime la cadena de caracteres str.
 *             letra indica la posicion en pantalla dependiendo
 *             si es [T]ipo, [V]alor o [U]nidad.
 * @param[in]  str[] y letra.
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/10/2015
 */
void HAL_DISPLAY_printString(char str[], char letra);

/**
 * @fn         HAL_DISPLAY_menu
 * @brief      Imprime encuadrado el menu elegido.
 * @par		   Descripción de la función:
 *
 * @param[in]  str[], cadena de caracteres.
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/10/2015
 */
void HAL_DISPLAY_menu( char str[]);

/**
 * @fn         HAL_DISPLAY_printData
 * @brief      Imprime un string por pantalla.
 * @par		   Descripción de la función:
 *
 * @param[in]  str[], cadena de caracteres. fRed,fGreen y fBlue valores RGB.
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/10/2015
 */
void HAL_DISPLAY_printData(float str[], double fRed, double fGreen, double fBlue);

/**
 * @fn         HAL_DISPLAY_printData
 * @brief      Lee el valor ingresado por consola.
 * @par		   Descripción de la función:
 *
 * @param[in]
 * @param[out] devuelve un 0.
 * @author     Javier Barragán
 * @date       17/10/2015
 */
int HAL_DISPLAY_readInteger();

#endif /* DISPLAY_H_ */
