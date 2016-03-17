/**
 * @file    MotorAutomatas.c
 * @brief   Source con las funciones para implementar un motor de m�quina de estados.
 * @par		Descripci�n del fichero:
 *          En este fichero se implementan las funciones para la ejecuci�n del aut�mata con
 *          la m�quina de estados. En EjecutaAutomata se procesa la m�quina de estados y llama
 *          a EjecutaEstado con el estado correspondiente para que eval�e si ocurren ciertos
 *          eventos y ejecutar sus posibles acciones.
 * @author  F. Dom�nguez
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
 * @brief      Lanza la ejecuci�n del aut�mata asociado a una m�quina de estados
 * @par        Descripci�n funci�n:
 *             Se recorre el array de estados hasta que se encuentre el estado activo en ese momento. Posteriormente,
 *             con el id del estado se llama a EjecutaEstado.
 * @param[in]  TS_AUTOMATA *elAutomata
 * @author     F. Dom�nguez
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
 * @brief      Ejecuta el estado que corresponda seg�n a donde apunte el callback
 * @par        Descripci�n funci�n:
 *             Se comprueban si son ciertos los eventos del estado cuyo id ha sido introducido
 *             por par�metro. En caso de que un evento se cumpla, ejecuta su acci�n asociada (si tiene) 
 *             Por �ltimo, si esa transici�n conduce a un estado distinto. Se le indica al aut�mata cu�l
 *             es el estado activado. Es importante comprender bien las estructuras TS_EVEACC, TS_ESTADO
 *             , TS_AUTOMATA.
 * @param[in]  TS_ESTADO *elEstado
 * @param[in]  TS_AUTOMATA *elAutomata
 * @author     F. Dom�nguez
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
		//Si hay un evento y lleva asociada una acci�n, la ejecuta
		if (Indx->evento() == TRUE)
		{
			if (Indx->accion != NULL)
			{
				Indx->accion();
			}

			//Asigna nuevo estado si la transici�n es hacia otro
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


