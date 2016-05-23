/**
 * @file      pantalla.h
 * @brief     Short description.
 * @par		  Descripción de la función:
 * 			  par1
 *            par2
 * @author    Javier Barragán
 * @date      17/05/2016
 * @version   1.0
 * @todo      todo
 * @bug       bug
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
void APP_PANTALLA_init();

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
void APP_PANTALLA_mostrar();
/*****************************************************
*                        EOF                         *
*****************************************************/
#endif /* PANTALLA_H_ */
