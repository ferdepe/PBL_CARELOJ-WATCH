
/**
 * @file      Adc.c
 * @brief     Implementación de la logica de inicializacion y recogida de datos del ADC.
 * @par		  Descripción de la función:
 * 			  par1
 *            par2
 * @author    Mikel Etxebeste
 * @date      18/05/2016
 * @version   1.0
 * @todo      todo
 * @bug       bug
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/
#include <stdio.h>
//#include "platform.h"
#include "xsysmon.h"
#include "xil_types.h"
#include "xil_exception.h"
#include "timer_ttc.h"
#include "Adc.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/
#define SYSMON_DEVICE_ID XPAR_SYSMON_0_DEVICE_ID //ID of xadc_wiz_0
#define XSysMon_RawToExtVoltage(AdcData) \
	((((float)(AdcData))*(1.0f))/65536.0f)

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/

//Declaración funciones privadas

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/
 /**
 * @var       SysMonInst
 * @brief     Instancia del XADC.
 * @author    Mikel Etxebeste
 * @date      18/05/2016
*/
static XSysMon SysMonInst;
/**
* @var       SysMonInstPtr
* @brief     Puntero a la Instancia del XADC.
* @author    Mikel Etxebeste
* @date      18/05/2016
*/
XSysMon *SysMonInstPtr = &SysMonInst;


/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

void HAL_ADC_Init(){

	XSysMon_Config *SysMonConfigPtr;
	int xStatus;
	//----------------------------------------------------------------------- SysMon Hasieratu
	SysMonConfigPtr = XSysMon_LookupConfig(SYSMON_DEVICE_ID);
	if(SysMonConfigPtr == NULL) printf("LookupConfig FAILURE\n\r");

	xStatus = XSysMon_CfgInitialize(SysMonInstPtr, SysMonConfigPtr,SysMonConfigPtr->BaseAddress);
	if(XST_SUCCESS != xStatus) printf("CfgInitialize FAILED\r\n");
		//-----------------------------------------------------------------------------------------
	XSysMon_GetStatus(SysMonInstPtr); // status zaharra garbitu

}

float HAL_ADC_ObtenerDato(){
	u32 TempRawData,VccIntRawData,ExtVolRawData,i;
	float TempData,VccIntData,ExtVolData,NewExtVolData = 0, Old = 0, New;
	float MAX = 0, MIN = 100;
	float  x;

	while ((XSysMon_GetStatus(SysMonInstPtr) & XSM_SR_EOS_MASK) != XSM_SR_EOS_MASK);//wait until EOS activated

	ExtVolRawData = XSysMon_GetAdcData(SysMonInstPtr,XSM_CH_AUX_MAX); // 15 kanaleko sarrera auxiliarra irakurri
	ExtVolData = XSysMon_RawToExtVoltage(ExtVolRawData);

	return ExtVolData;

}


/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/

//Funciones privadas





