 /**
 * @file      acelerometro.c
 * @brief     Fichero de las funciones utilizadas por el acelerometro ADXL345.
 * @par		  Descripción de la función:
 *            Fichero con las funciones para comunicarse con el
 *            Hardware del acelerometro ADXL345.
 * @author    Javier Barragán
 * @date      02/06/2016
 * @version   1.0
 * @todo	  modularizar mas la librería.
 * @bug
 */

/*****************************************************
*                   MODULES USED                     *
*****************************************************/
#include "xspips.h"
#include "xgpiops.h"
#include "acelerometro.h"
/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/
void HAL_ACELEROMETRO_masterConfig(void);
void HAL_ACELEROMETRO_slaveConfig(void);
unsigned int HAL_ACELEROMETRO_ReadInterrupt(unsigned int);
void HAL_ACELEROMETRO_WriteSPI(unsigned char,unsigned char);
void HAL_ACELEROMETRO_ReadSPI(unsigned char);

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/
XSpiPs Spi;
XSpiPs_Config *SpiConfig;

XGpioPs Gpio;//MIO
XGpioPs_Config *ConfigPtr;

unsigned char buff_tx[8]; //buffer de transmisión en SPI
unsigned char buff_rx[8]; //buffer de recepción en SPI

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/

void HAL_ACELEROMETRO_init(void)
{
	HAL_ACELEROMETRO_masterConfig();
	HAL_ACELEROMETRO_slaveConfig();
}

unsigned int HAL_ACELEROMETRO_getEstadoCaida(void)
{
	return HAL_ACELEROMETRO_ReadInterrupt(2);
}

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/
/**
 * @fn         HAL_ACELEROMETRO_masterConfig
 * @brief      Configuración del maestro en SPI (Zybo).
 * @par		   Descripción de la función:
 *			   Se realizan los pasos de configuración
 *			   a nivel de SPI y de las MIOs que leeran
 *			   las interrupciones.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       02/06/2016
 */
void HAL_ACELEROMETRO_masterConfig(void)
{

	//Configuración de MIO para lectura de interrupción (MIO 0)
	ConfigPtr = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
	XGpioPs_CfgInitialize(&Gpio, ConfigPtr, ConfigPtr->BaseAddr);
	//XGpioPs_SetDirectionPin(&Gpio,7,1); //led
	//XGpioPs_SetOutputEnablePin(&Gpio,7,1);//led
	XGpioPs_SetDirectionPin(&Gpio,0,0); //int2 del acelerometro

	//Initialize the SPI device.
	SpiConfig = XSpiPs_LookupConfig(XPAR_PS7_SPI_1_DEVICE_ID); //defino SPI1 (MIO)
	XSpiPs_CfgInitialize(&Spi, SpiConfig, SpiConfig->BaseAddress);

	//Perform a self-test to check hardware build.
	XSpiPs_SelfTest(&Spi);

	//Configuración de ZyboSPI como maestro y config Pol1 Pha1
	XSpiPs_SetOptions(&Spi, XSPIPS_MASTER_OPTION|XSPIPS_CLK_ACTIVE_LOW_OPTION|XSPIPS_CLK_PHASE_1_OPTION);

	//COnfiguracion del clk
	XSpiPs_SetClkPrescaler(&Spi, XSPIPS_CLK_PRESCALE_128);
}

/**
 * @fn         HAL_ACELEROMETRO_slaveConfig
 * @brief      Configura el esclavo en SPI (Acelerometro).
 * @par		   Descripción de la función:
 *			   Realiza la configuración de los registros
 *			   del acelerometro con los valores deseados
 *			   que funcione el acelerometro.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       02/06/2016
 */
void HAL_ACELEROMETRO_slaveConfig(void)
{
	/*
	 * Configuración de Registros del acelerometro
	 */
	HAL_ACELEROMETRO_WriteSPI(0x31,0x0B);//tipo de ACL: 13bit
	///////////FREEFALL CONFIG//////////////
	HAL_ACELEROMETRO_WriteSPI(0x2F,0x04);//FREEFALL en INT2
	HAL_ACELEROMETRO_WriteSPI(0x28,0x0C);//THRESH_FF  FREEFALL
	HAL_ACELEROMETRO_WriteSPI(0x29,0x06);//TIME_FF FREEFALL/
	///////////TAP CONFIG//////////////
	HAL_ACELEROMETRO_WriteSPI(0x2A,0x07);//TAP AXES Enables
	HAL_ACELEROMETRO_WriteSPI(0x21,0x15);//DUR
	HAL_ACELEROMETRO_WriteSPI(0x22,0x15);//LATENT
	HAL_ACELEROMETRO_WriteSPI(0x23,0x45);//WINDOW
	HAL_ACELEROMETRO_WriteSPI(0x1D,0x35);//THRESH_TAP
	//////////////////////////////////
	HAL_ACELEROMETRO_WriteSPI(0x2D,0x08);//Measure Enable
	HAL_ACELEROMETRO_WriteSPI(0x2E,0x04);//habilita INTERRUPCIONES: FREEFALL(bit2),SINGLETAP(bit6),DOBLETAP(bit5)
}

/**
 * @fn         HAL_ACELEROMETRO_ReadInterrupt
 * @brief      Lee los pines de interrupción del acelerometro.
 * @par		   Descripción de la función:
 *			   Las interrupciones del acelerometro están conectados
 *			   en pines MIOs de la Zybo. Se lee el estado del pin
 *			   deseado.
 * @param[in]  unsigned int numInt, indica que interrupción se lee.
 * @param[out] unsigned int, devuelve el estado de la interrupción.
 * @author     Javier Barragán
 * @date       02/06/2016
 */
unsigned int HAL_ACELEROMETRO_ReadInterrupt(unsigned int numInt)
{
	HAL_ACELEROMETRO_ReadSPI(0x30);
	switch(numInt)
	{
	case 1:
		return XGpioPs_ReadPin(&Gpio,9);//Lee MIO9, donde se conecta la INT1 del acelerometro
	case 2:
		return XGpioPs_ReadPin(&Gpio,0);//Lee MIO0, donde se conecta la INT2 del acelerometro
	}
    return 0;
}

/**
 * @fn         HAL_ACELEROMETRO_WriteSPI
 * @brief      Escritura de un registro del acelerometro por SPI.
 * @par		   Descripción de la función:
 *			   Función que escribe el registro deseado con el valor
 *			   ingresado.
 * @param[in]  unsigned char registro, registro deseado a escribir.
 * @param[in]  unsigned char valor, valor deseado a escribir.
 * @param[out] void
 * @author     Javier Barragán
 * @date       02/06/2016
 */
void HAL_ACELEROMETRO_WriteSPI(unsigned char registro,unsigned char valor)
{
	buff_tx[0]=registro;
    buff_tx[1]=valor;
	XSpiPs_PolledTransfer(&Spi, buff_tx,buff_rx, 2);
}

/**
 * @fn         HAL_ACELEROMETRO_ReadSPI
 * @brief      Lectura de un registro del acelerometro por SPI.
 * @par		   Descripción de la función:
 *			   Función que lee el registro deseado y devuelve su
 *			   lectura en la petición siguiente de SPI.
 * @param[in]  unsigned char registro, registro deseado a leer.
 * @param[out] void
 * @author     Javier Barragán
 * @date       02/06/2016
 */
void HAL_ACELEROMETRO_ReadSPI(unsigned char registro)
{
	buff_tx[0]=0x80|registro; //registro de fuentes de interrupciones
    buff_tx[1]=0x00;
	XSpiPs_PolledTransfer(&Spi, buff_tx,buff_rx, 2);
}
