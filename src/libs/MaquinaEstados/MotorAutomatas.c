/**
 * @file    MotorAutomatas.c
 * @brief   Source con las funciones para implementar un motor de máquina de estados.
 * @par		Descripción del fichero:
 *          En este fichero se implementan las funciones para la ejecución del autómata con
 *          la máquina de estados. En EjecutaAutomata se procesa la máquina de estados y llama
 *          a EjecutaEstado con el estado correspondiente para que evalúe si ocurren ciertos
 *          eventos y ejecutar sus posibles acciones.
 * @author  F. Domínguez
 * @date    25/02/2016 
 * @todo    Implementar funcionalidad de entry
*/

/*****************************************************
*                   MODULES USED                     *
*****************************************************/

#include "MotorAutomatas.h"

/*****************************************************
*               DEFINITIONS AND MACROS               *
*****************************************************/

/*****************************************************
*              TYPEDEFS AND STRUCTURES               *
*****************************************************/

/*****************************************************
*           PROTOTYPES OF LOCAL FUNCTIONS            *
*****************************************************/

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  GLOBAL VARIABLES                  *
*****************************************************/

/*****************************************************
*                EXPORTED FUNCTIONS                  *
*****************************************************/
/**
 * @fn         void EjecutaAutomata(TS_AUTOMATA *elAutomata)
 * @brief      Lanza la ejecución del autómata asociado a una máquina de estados
 * @par        Descripción función:
 *             Se recorre el array de estados hasta que se encuentre el estado activo en ese momento. Posteriormente,
 *             con el id del estado se llama a EjecutaEstado.
 * @param[in]  TS_AUTOMATA *elAutomata
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
void EjecutaAutomata(TS_AUTOMATA *elAutomata)
{
	TS_ESTADO **Indx;    /* Valor indice rastreador */

	if (elAutomata->StopCond())  return;

	//Lee el array de estados
	for (Indx = elAutomata->estado; *Indx != NULL; ++Indx)
	{
		//Si encuentra el estado actual (==*Indx->id)...
	    if (elAutomata->id_estado_actual == (*Indx)->id)
	    {
			EjecutaEstado(*Indx , elAutomata);
			return;
	    }
	}
}

/**
 * @fn         void EjecutaEstado(TS_ESTADO *elEstado , TS_AUTOMATA *elAutomata)
 * @brief      Ejecuta el estado que corresponda según a donde apunte el callback
 * @par        Descripción función:
 *             Se comprueban si son ciertos los eventos del estado cuyo id ha sido introducido
 *             por parámetro. En caso de que un evento se cumpla, ejecuta su acción asociada (si tiene) 
 *             Por último, si esa transición conduce a un estado distinto. Se le indica al autómata cuál
 *             es el estado activado. Es importante comprender bien las estructuras TS_EVEACC, TS_ESTADO
 *             , TS_AUTOMATA.
 * @param[in]  TS_ESTADO *elEstado
 * @param[in]  TS_AUTOMATA *elAutomata
 * @author     F. Domínguez
 * @date       25/02/2016 
*/
void EjecutaEstado(TS_ESTADO *elEstado , TS_AUTOMATA *elAutomata)
{
	TS_EVEACC *Indx;   /* Indice de rastreo */

	//DO del estado
	(*elEstado->controles)();

	//Lee el array de transiciones
	for (Indx = elEstado->funcion; Indx->evento != NULL; ++Indx)
	{
		//Si hay un evento y lleva asociada una acción, la ejecuta
		if (Indx->evento() == TRUE)
		{
			if (Indx->accion != NULL)
			{
				Indx->accion();
			}

			//Asigna nuevo estado si la transición es hacia otro
			if (Indx->id != elAutomata->id_estado_actual)
			{
				//Indx->entry();
				elAutomata->id_estado_actual = Indx->id;


				return;
			}
		}
	}
}

/*****************************************************
*                EXPORTED VARIABLES                  *
*****************************************************/

/*****************************************************
*                  LOCAL FUNCTIONS                   *
*****************************************************/


