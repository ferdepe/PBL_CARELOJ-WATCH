/**
 * @file    MotorAutomatas.h
 * @brief   Header con las declaraciones para implementar un motor de máquina de estados.
 * @par		Descripción del fichero:
 *          En el fichero se definen nuevos tipos de variable como BOOLEAN, BYTE y callbacks para apuntar a los
 *			eventos y acciones a ejecutar según corresponda. La máquina de estados se define a través de macros del
 *          preprocesador. Se crean tres tipos de estructuras: \link TS_EVEACC \endlink, \link TS_ESTADO \endlink 
 *          y \link TS_AUTOMATA \endlink. Por último se definen las funciones para ejecutar el autómata y el estado que 
 *          corresponda en cada momento.
 * @author  F. Domínguez
 * @date    25/02/2016 
*/

#ifndef MOTORAUTOMATAS_H_
#define MOTORAUTOMATAS_H_

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

#define NULL 0
#define TRUE 1
#define FALSE 0

/**
 * @typedef    BOOLEAN
 * @brief      Valor booleano
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
typedef unsigned char BOOLEAN;
/**
 * @typedef    BYTE
 * @brief      Valor de ocho bits
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
typedef unsigned char BYTE;

/**
 * @typedef    (*TPFN_ACC)(void)
 * @brief      Puntero a al array de acciones que devuelve void
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
typedef void        (*TPFN_ACC)(void); /* Puntero a una función acción */
/**
 * @typedef    (*TPFN_EVE)(void)
 * @brief      Puntero a al array de eventos que devuelve BOOLEAN
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
typedef BOOLEAN     (*TPFN_EVE)(void); /* Puntero a una función evento */

/**
 * @def        ITEM_EAC(ident,event,acci)
 * @brief      Definición transición a partir de un evento (event) que ejecuta una acción (acci)
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
#define ITEM_EAC(ident,event,acci) { ident, #event, event, acci }
/**
 * @def        ESTADO(nombre)
 * @brief      Definición de un estado dentro del array, cada uno con un array de transiciones
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
#define ESTADO(nombre)                             \
        const TS_EVEACC x##nombre[] = {
/**
 * @def        FIN_ESTADO(nombre, ident, control)
 * @brief      Definición del fin del estado con callback al do del propio estado
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
#define FIN_ESTADO(nombre, ident, control)         \
	,{0,NULL,NULL,NULL} };                     \
       const TS_ESTADO nombre =            \
      {ident, #ident, control, (TS_EVEACC *) x##nombre};

/**
 * @def        AUTOMATA(nombre)
 * @brief      Definición de un autómata que ejecutará una máquina de estados
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
#define AUTOMATA(nombre)                           \
	const TS_ESTADO * const (x##nombre[]) = {

/**
 * @def        FIN_AUTOMATA(nombre,ident, StopC)
 * @brief      Definición del fin un autómata que ejecutará una máquina de estados con su array.
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
#define FIN_AUTOMATA(nombre,ident, StopC)          \
	   ,NULL };                                \
	 const TS_AUTOMATA nombre =          \
      {ident, 0 ,#nombre, StopC, (TS_ESTADO **) x##nombre};

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*ESTRUCTURA DE UN EVENTO-ACCIÓN*/
/**
 * @struct     TS_EVEACC
 * @brief      Estructura con los valores asociados a un evento-acción
 * @par        Descripción:
 *             - Callback a evento.
 *             - Callback a acción.
 *             - Identificador de estado de destino
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
typedef struct {
	  BYTE          id;                /* Identificador del estado destino */
	  char        * nombre;            /* Nombre identificativo de depuración */
	  TPFN_EVE      evento;            /* Puntero a la función evento */
	  TPFN_ACC      accion;            /* Puntero a la función acción */
} TS_EVEACC;

/*
 *   TPFN_EVE : Puntero a función que devuelve BOOLEAN (unsigned char) que indica si el evento ha ocurrido o no.
 *   TPFN_ACC : Puntero a función que devuelve vacío (void) y que ordena la ejecución de una acción al ocurrir un evento.
 */

/*ESTRUCTURA DE UN ESTADO*/
/**
 * @struct     TS_ESTADO
 * @brief      Estructura con los valores asociados a un estado
 * @par        Descripción:
 *             - Callback a DO.
 *             - Callback a la estructura \link TS_EVEACC \endlink correspondiente a cada estado.
 *             - Identificador de estado
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
typedef struct {
	  BYTE          id;                /* Identificador del estado */
	  char        * nombre;            /* Nombre identificativo de depuraci¢n */
	  TPFN_ACC      controles;         /* Función de control del estado (DO) de la máquina de estados */
	  //void (*entry) (void);
	  TS_EVEACC   * funcion;           /* Puntero (array de transiciones) de las funciones del estado */
} TS_ESTADO;

/*ESTRUCTURA DEL MOTOR*/
/**
 * @struct     TS_AUTOMATA
 * @brief      Estructura para ejecutar la máquina de estados desde el autómata
 * @par        Descripción:
 *             - Callback a un puntero (array) de todos los estados
 *             - Condición necesaria para ejecución. Se pondrá a 1 para que esté siempre en ejecución.
 *             - Identificador de estado de destino
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
typedef struct {
	  BYTE          id;                /* Identificador del automata */
	  BYTE 			id_estado_actual;  /* Identificador del estado actual del autómata */
	  char        * nombre;            /* Nombre identificativo de depuraci¢n */
	  TPFN_EVE      StopCond;          /* Condici¢n necesaria para la ejecuci¢n */
	  TS_ESTADO   **estado;            /* Matriz de punteros a los ESTADOS (Puntero a un puntero (array) que devuelve TS_ESTADO*/
} TS_AUTOMATA;

/*****************************************************
*                 EXPORTED VARIABLES                 *
*****************************************************/

/*****************************************************
*                  EXPORTED FUNCTIONS                *
*****************************************************/
void EjecutaAutomata( TS_AUTOMATA *elAutomata);

void EjecutaEstado( TS_ESTADO   *elEstado , TS_AUTOMATA *elAutomata);

/*****************************************************
*                        EOF                         *
*****************************************************/

#endif /* MOTORAUTOMATAS_H_ */

