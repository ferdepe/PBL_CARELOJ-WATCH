/**
 * @file      pantalla.c
 * @brief     Short description.
 * @par		  Descripción de la función:
 * 			  par1
 *            par2
 * @author    author
 * @date      17/10/2015
 * @version   1.0
 * @todo	  HAL_DISPLAY_menu sin uso
 * @bug
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/
#include <stdio.h>
#include "display_vga.h"

#include "display.h"
/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/

// funciones privadas

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

//variables globales, precedidas de static (privada)

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

void HAL_DISPLAY_init()
{
	displayInit();
	display_borrar_buffer();
}

void HAL_DISPLAY_printString(char str[], char tipo)
{
	int	 i, y,x0;
	if (tipo=='T' ) y = 230;//titulo
	if (tipo=='V' ) y = 240;//valor
	if (tipo=='U' ) y = 250;//unidad
	x0=((strlen(str))/2)*10;
	for( i=0; i<strlen(str); i++)
	{
		displayChar(x0-10*i, y , str[i]);
	}
}

void HAL_DISPLAY_printData(float str[], double fRed, double fGreen, double fBlue)
{
	int i;
	 for (i = 0 ; i < 80; i++)
	 {
	     dibujar_linea_2_pto( 5*i,  240-100*str[i] , 5*(i+1), 240-100*str[i+1], fRed, fGreen, fBlue );
	 }
	updateFrame();
}

int HAL_DISPLAY_readInteger()
{
	return 0;
}

void HAL_DISPLAY_menu( char str[])
{

}

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/

//Funciones privadas


