 /**
 * @file      display.c
 * @brief     Fichero de las funciones utilizadas por el display.
 * @par		  Descripción de la función:
 *            Fichero con las funciones para comunicarse con el
 *            Hardware del display a utilizar.
 * @author    Javier Barragán
 * @date      24/05/2016
 * @version   1.0
 * @todo
 * @bug       no se utiliza HAL_DISPLAY_menu().
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
	//displayBackground();
	//display_borrar_buffer();
	//borrarFrameBuffer();
	//displayMenu();
	copiarFrameBuffer();
	updateFrame();
}
void HAL_DISPLAY_screen(char strT[], char strV[], char strU[])
{
	borrarFrameBuffer();
	displayBackground();
	HAL_DISPLAY_printString(strT, 'T');
	HAL_DISPLAY_printString(strV, 'V');
	HAL_DISPLAY_printString(strU, 'U');
	copiarFrameBuffer();
	updateFrame();
}
void HAL_DISPLAY_printString(char str[], char tipo)
{
	int	 i, y, x0;
	if (tipo=='T' ) y = 440;//titulo
	if (tipo=='V' ) y = 480;//valor
	if (tipo=='U' ) y = 520;//unidad
//	if (tipo=='T' ) y = 230;//titulo
//	if (tipo=='V' ) y = 240;//valor
//	if (tipo=='U' ) y = 250;//unidad
	x0=((strlen(str))/2);
	for( i=0; i<strlen(str); i++)
	{
		displayChar((x0-i)*16, y , str[i]);
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

void HAL_DISPLAY_refresh(void)
{
    display_borrar_buffer();
    borrarFrameBuffer();
    displayBackground();
    copiarFrameBuffer();
    updateFrame();
}
/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/

//Funciones privadas


