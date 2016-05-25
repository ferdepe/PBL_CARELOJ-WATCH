/**
 * @file      display.h
 * @brief     Cabecera de las funciones de display.
 * @par		  Descripci�n de la funci�n:
 *			  Cabecera con la definici�n de las funciones
 *			  generales p�blicas del display.
 * @author    Javier Barrag�n
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
 * @brief      Inicializaci�n del Display.
 * @par		   Descripci�n de la funci�n:
 *			   Funci�n encargada de inicializar
 *			   el display para la pantalla.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       17/10/2015
 */
void HAL_DISPLAY_init();

/**
 * @fn         HAL_DISPLAY_screen
 * @brief      Impresi�n de la pantalla en Display.
 * @par		   Descripci�n de la funci�n:
 * 			   Imprime las cadenas de caracteres str's.
 *             La letra indica la posici�n en pantalla dependiendo
 *             si es [T]ipo, [V]alor o [U]nidad.
 * @param[in]  str[],cadena de caracter de entrada a reproducir.
 * @param[in]  str1[],cadena de caracter de entrada a reproducir.
 * @param[in]  str2[],cadena de caracter de entrada a reproducir.
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       25/05/2016
 */
void HAL_DISPLAY_screen(char strT[], char strV[], char strU[]);

/**
 * @fn         HAL_DISPLAY_printString
 * @brief      Impresi�n de cadena de caracteres en Display.
 * @par		   Descripci�n de la funci�n:
 * 			   imprime la cadena de caracteres str.
 *             letra indica la posicion en pantalla dependiendo
 *             si es [T]ipo, [V]alor o [U]nidad.
 * @param[in]  str[] y letra.
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       17/10/2015
 */
void HAL_DISPLAY_printString(char str[], char letra);

/**
 * @fn         HAL_DISPLAY_menu
 * @brief      Imprime encuadrado el menu elegido.
 * @par		   Descripci�n de la funci�n:
 *
 * @param[in]  str[], cadena de caracteres.
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       17/10/2015
 */
void HAL_DISPLAY_menu( char str[]);

/**
 * @fn         HAL_DISPLAY_printData
 * @brief      Imprime un string por pantalla.
 * @par		   Descripci�n de la funci�n:
 *
 * @param[in]  str[], cadena de caracteres.
 * @param[in]  fRed, intensidad de rojo en valores de RGB.
 * @param[in]  fGreen, intensidad de verde en valores de RGB.
 * @param[in]  fBlue, intensidad de azul en valores de RGB.
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       17/10/2015
 */
void HAL_DISPLAY_printData(float str[], double fRed, double fGreen, double fBlue);

/**
 * @fn         HAL_DISPLAY_printData
 * @brief      Lee el valor ingresado por consola.
 * @par		   Descripci�n de la funci�n:
 *
 * @param[in]  void
 * @param[out] int devuelve un 0.
 * @author     Javier Barrag�n
 * @date       17/10/2015
 */
int HAL_DISPLAY_readInteger(void);

/**
 * @fn         HAL_DISPLAY_refresh
 * @brief      Actualiza el display.
 * @par		   Descripci�n de la funci�n:
 *			   Borra y el actualiza el buffer,
 *			   y limpia la pantalla.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barrag�n
 * @date       24/10/2015
 */
void HAL_DISPLAY_refresh(void);

#endif /* DISPLAY_H_ */
