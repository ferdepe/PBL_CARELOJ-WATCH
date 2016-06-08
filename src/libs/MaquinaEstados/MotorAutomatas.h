/**
 * @file    MotorAutomatas.h
 * @brief   Header con las declaraciones para implementar un motor de m�quina de estados.
 * @par		Descripci�n del fichero:
 *          En el fichero se definen nuevos tipos de variable como BOOLEAN, BYTE y callbacks para apuntar a los
 *			eventos y acciones a ejecutar seg�n corresponda. La m�quina de estados se define a trav�s de macros del
 *          preprocesador. Se crean tres tipos de estructuras: \link TS_EVEACC \endlink, \link TS_ESTADO \endlink 
 *          y \link TS_AUTOMATA \endlink. Por �ltimo se definen las funciones para ejecutar el aut�mata y el estado que 
 *          corresponda en cada momento.
 * @author  F. Dom�nguez
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
 * @author     F. Dom�nguez
 * @date       25/02/2016 
*/
typedef unsigned char BOOLEAN;
/**
 * @typedef    BYTE
 * @brief      Valor de ocho bits
 * @author     F. Dom�nguez
 * @date       25/02/2016 
*/
typedef unsigned char BYTE;

/**
 * @typedef    (*TPFN_ACC)(void)
 * @brief      Puntero a al array de acciones que devuelve void
 * @author     F. Dom�nguez
 * @date       25/02/2016 
*/
typedef void        (*TPFN_ACC)(void); /* Puntero a una funci�n acci�n */
/**
 * @typedef    (*TPFN_EVE)(void)
 * @brief      Puntero a al array de eventos que devuelve BOOLEAN
 * @author     F. Dom�nguez
 * @date       25/02/2016 
*/
typedef BOOLEAN     (*TPFN_EVE)(void); /* Puntero a una funci�n evento */

/**
 * @def        ITEM_EAC(ident,event,acci)
 * @brief      Definici�n transici�n a partir de un evento (event) que ejecuta una acci�n (acci)
 * @author     F. Dom�nguez
 * @date       25/02/2016 
*/
#define ITEM_EAC(ident,event,acci) { ident, #event, event, acci }
/**
 * @def        ESTADO(nombre)
 * @brief      Definici�n de un estado dentro del array, cada uno con un array de transiciones
 * @author     F. Dom�nguez
 * @date       25/02/2016 
*/
#define ESTADO(nombre)                             \
        const TS_EVEACC x##nombre[] = {
/**
 * @def        FIN_ESTADO(nombre, ident, control)
 * @brief      Definici�n del fin del estado con callback al do del propio estado
 * @author     F. Dom�nguez
 * @date       25/02/2016 
*/
#define FIN_ESTADO(nombre, ident, control)         \
	,{0,NULL,NULL,NULL} };                     \
       const TS_ESTADO nombre =            \
      {ident, #ident, control, (TS_EVEACC *) x##nombre};

/**
 * @def        AUTOMATA(nombre)
 * @brief      Definici�n de un aut�mata que ejecutar� una m�quina de estados
 * @author     F. Dom�nguez
 * @date       25/02/2016 
*/
#define AUTOMATA(nombre)                           \
	const TS_ESTADO * const (x##nombre[]) = {

/**
 * @def        FIN_AUTOMATA(nombre,ident, StopC)
 * @brief      Definici�n del fin un aut�mata que ejecutar� una m�quina de estados con su array.
 * @author     F. Dom�nguez
 * @date       25/02/2016 
*/
#define FIN_AUTOMATA(nombre,ident, StopC)          \
	   ,NULL };                                \
	 const TS_AUTOMATA nombre =          \
      {ident, 0 ,#nombre, StopC, (TS_ESTADO **) x##nombre};

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*ESTRUCTURA DE UN EVENTO-ACCI�N*/
/**
 * @struct     TS_EVEACC
 * @brief      Estructura con los valores asociados a un evento-acci�n
 * @par        Descripci�n:
 *             - Callback a evento.
 *             - Callback a acci�n.
 *             - Identificador de estado de destino
 * @author     F. Dom�nguez
 * @date       25/02/2016 
*/
typedef struct {
	  BYTE          id;                /* Identificador del estado destino */
	  char        * nombre;            /* Nombre identificativo de depuraci�n */
	  TPFN_EVE      evento;            /* Puntero a la funci�n evento */
	  TPFN_ACC      accion;            /* Puntero a la funci�n acci�n */
} TS_EVEACC;

/*
 *   TPFN_EVE : Puntero a funci�n que devuelve BOOLEAN (unsigned char) que indica si el evento ha ocurrido o no.
 *   TPFN_ACC : Puntero a funci�n que devuelve vac�o (void) y que ordena la ejecuci�n de una acci�n al ocurrir un evento.
 */

/*ESTRUCTURA DE UN ESTADO*/
/**
 * @struct     TS_ESTADO
 * @brief      Estructura con los valores asociados a un estado
 * @par        Descripci�n:
 *             - Callback a DO.
 *             - Callback a la estructura \link TS_EVEACC \endlink correspondiente a cada estado.
 *             - Identificador de estado
 * @author     F. Dom�nguez
 * @date       25/02/2016 
*/
typedef struct {
	  BYTE          id;                /* Identificador del estado */
	  char        * nombre;            /* Nombre identificativo de depuraci�n */
	  TPFN_ACC      controles;         /* Funci�n de control del estado (DO) de la m�quina de estados */
	  //void (*entry) (void);
	  TS_EVEACC   * funcion;           /* Puntero (array de transiciones) de las funciones del estado */
} TS_ESTADO;

/*ESTRUCTURA DEL MOTOR*/
/**
 * @struct     TS_AUTOMATA
 * @brief      Estructura para ejecutar la m�quina de estados desde el aut�mata
 * @par        Descripci�n:
 *             - Callback a un puntero (array) de todos los estados
 *             - Condici�n necesaria para ejecuci�n. Se pondr� a 1 para que est� siempre en ejecuci�n.
 *             - Identificador de estado de destino
 * @author     F. Dom�nguez
 * @date       25/02/2016 
*/
typedef struct {
	  BYTE          id;                /* Identificador del automata */
	  BYTE 			id_estado_actual;  /* Identificador del estado actual del aut�mata */
	  char        * nombre;            /* Nombre identificativo de depuraci�n */
	  TPFN_EVE      StopCond;          /* Condici�n necesaria para la ejecuci�n */
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

