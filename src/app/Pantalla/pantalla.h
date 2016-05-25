/**
 * @file      pantalla.h
 * @brief     Header de las funciones utilizadas por la tareaPantalla.
 * @par		  Descripción:
 * 			  Conjunto de funciones que utiliza la tareaPantalla para
 * 			  comunicarse con el HAL para realizar al impresion en pantalla.
 * @author    Javier Barragán
 * @date      24/05/2016
 * @version   1.0
 * @todo
 * @bug
 */
 #ifndef PANTALLA_H_
#define PANTALLA_H_

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

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/
/**
 * @fn         APP_PANTALLA_init
 * @brief      Inicialización de la pantalla.
 * @par		   Descripción de la función:
 * 			   Función encargada de llamar a funciones
 * 			   en el HAL que inicializan el Display.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/05/2016
 */
void APP_PANTALLA_init(void);

/**
 * @fn         APP_PANTALLA_mostrar
 * @brief      Proceso para mostrar en pantalla.
 * @par		   Descripción de la función:
 *			   Función que llama a la función
 *			   APP_DATAMANAGEMENT_getIdPantalla para
 *			   procesar que pantalla debe imprimir en el
 *			   Display.
 * @param[in]  void
 * @param[out] void
 * @author     Javier Barragán
 * @date       17/05/2016
 */
void APP_PANTALLA_mostrar(void);
/*****************************************************
*                        EOF                         *
*****************************************************/
#endif /* PANTALLA_H_ */
