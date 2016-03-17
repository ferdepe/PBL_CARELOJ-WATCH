/*****************************************************
* FILE NAME: MotorAutomatas                          *
*                                                    *
* PURPOSE: Declaración de funciones públicas, macros *
*          y estructuras para la gestión lógica de   *
*          máquinas de estado no jerárquicas         *
*                                                    *
* AUTHOR: Fernando Domínguez                         *
*                                                    *
* DATE: 22/12/2015     VERSION: 1.0                  *
*                                                    *
*****************************************************/

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

typedef unsigned char BOOLEAN;
typedef unsigned char BYTE;


typedef void        (*TPFN_ACC)(void); /* Puntero a una función acción */
typedef BOOLEAN     (*TPFN_EVE)(void); /* Puntero a una función evento */

#define ITEM_EAC(ident,event,acci) { ident, #event, event, acci }

#define ESTADO(nombre)                             \
        const TS_EVEACC x##nombre[] = {

#define FIN_ESTADO(nombre, ident, control)         \
	,{0,NULL,NULL,NULL} };                     \
       const TS_ESTADO nombre =            \
      {ident, #ident, control, (TS_EVEACC *) x##nombre};


#define AUTOMATA(nombre)                           \
	const TS_ESTADO * const (x##nombre[]) = {

#define FIN_AUTOMATA(nombre,ident, StopC)          \
	   ,NULL };                                \
	 const TS_AUTOMATA nombre =          \
      {ident, 0 ,#nombre, StopC, (TS_ESTADO **) x##nombre};

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*ESTRUCTURA DE UN EVENTO-ACCIÓN*/
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
typedef struct {
	  BYTE          id;                /* Identificador del estado */
	  char        * nombre;            /* Nombre identificativo de depuraci¢n */
	  TPFN_ACC      controles;         /* Función de control del estado (DO) de la máquina de estados */
	  TS_EVEACC   * funcion;           /* Puntero (array de transiciones) de las funciones del estado */
} TS_ESTADO;

/*ESTRUCTURA DEL MOTOR*/
typedef struct {
	  BYTE          id;                /* Identificador del automata */
	  BYTE 			id_estado_actual;  /* Identificador del estado actual del autómata */
	  char        * nombre;            /* Nombre identificativo de depuraci¢n */
	  TPFN_EVE      StopCond;          /* Condici¢n necesaria para la ejecuci¢n */
	  TS_ESTADO   **estado;            /* Matriz de punteros a los ESTADOS */
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

