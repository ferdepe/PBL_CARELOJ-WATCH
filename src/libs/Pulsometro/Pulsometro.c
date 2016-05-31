
/**
 * @file      name.c
 * @brief     Short description.
 * @par		  Descripción de la función:
 * 			  par1
 *            par2
 * @author    author
 * @date      dd/mm/yyyy
 * @version   1.0
 * @todo      todo
 * @bug       bug
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include <stdio.h>
#include "Adc.h"
#include "Timer_TTC.h"
#include "Pulsometro.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/
/**
 * @fn         PULSOMETRO_ContadorDePulsos
 * @brief      Es la función que se ocupa de contar de contar cuantos pulsos ha habiado.
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @author     Mikel Etxebeste
 * @date       18/05/2016
 **/
void PULSOMETRO_ContadorDePulsos();
/**
 * @fn         PULSOMETRO_ContadorDePulsos
 * @brief      Es la función que se ocupa de calcular las pulsaciones por minuto.
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @author     Mikel Etxebeste
 * @date       18/05/2016
 **/
void PULSOMETRO_CalculoXMinuto();
/**
 * @fn         PULSOMETRO_SysMonFractionToInt
 * @brief      Función para obtener mas decimales..
 * @par		   Descripción de la función:
 * 			   par1
 *             par2
 * @param[1]   float numero
 * @author     Mikel Etxebeste
 * @date       18/05/2016
 **/
//static int PULSOMETRO_SysMonFractionToInt(float FloatNum);

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/
/**
* @var       pulse
* @brief     Variable para contar pulsos.
* @author    Mikel Etxebeste
* @date      18/05/2016
*/
static int pulse, pulse1;
/**
* @var       BPM
* @brief     Variable que indica las pulsaciones por minuto..
* @author    Mikel Etxebeste
* @date      18/05/2016
*/
unsigned int BPM;

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

unsigned int LIBS_PULSOMETRO_GetBPM(){
	static int cnt = 0, cnt1 = 0, resta;

	cnt = HAL_TIMER_TTC_getCount();

	while(resta < 10){
		cnt1 = HAL_TIMER_TTC_getCount();
		resta = cnt1 - cnt;
		PULSOMETRO_ContadorDePulsos();
	}

	/*
while(cnt==cnt1){
	cnt1 = HAL_TIMER_TTC_getCount();
	PULSOMETRO_ContadorDePulsos();
}
	cnt = cnt1;*/
	resta = 0;
	cnt = cnt +10;
	PULSOMETRO_CalculoXMinuto();

	return BPM;
}

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/

void PULSOMETRO_ContadorDePulsos(){
	//u32 TempRawData,VccIntRawData,ExtVolRawData,i;
	//float TempData;
	//float VccIntData;
	float ExtVolData;
	float New;
	static float Old = 0;
 	static float MAX = 0, MIN = 100;
	float  x;

	ExtVolData = HAL_ADC_ObtenerDato();

	New = ExtVolData;
		if(New > Old){
		if(New > MAX){
			MAX = New;
					  	  }
			if(New < MIN){
				MIN = New;
					  	  }
				  }
			if(New < Old){
				x = MAX-MIN;

			if((x >= 0.13) && (x <= 0.3)){
				  MAX = 0;
				  MIN = 100;
				  pulse++;
				  pulse1 = pulse;
				  		  //printf("%d\n", pulse1);
				  	  }

				  }
				  Old = New;


				//printf("Vaux15: %0d.%03d Volt. \r\n", (int)(ExtVolData), SysMonFractionToInt(ExtVolData));

				//printf("\r\n%0d.%03d,%0d.%03d",(int)(VccIntData), SysMonFractionToInt(VccIntData),(int)(ExtVolData), SysMonFractionToInt(ExtVolData));
}

void PULSOMETRO_CalculoXMinuto(){

		BPM = 6*(pulse1);

		//BPM = 3;
		//printf("BPM: %d \n\r", BPM);
		pulse = 0;

}

/*
int PULSOMETRO_SysMonFractionToInt(float FloatNum){
	float Temp;
	Temp = FloatNum;
	if (FloatNum < 0) {
	Temp = -(FloatNum);
	}
	return( ((int)((Temp -(float)((int)Temp)) * (1000.0f))));
}
*/
