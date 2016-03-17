/*****************************************************
* FILE NAME: MotorAutomatas.c                        *
*                                                    *
* PURPOSE: Conjunto de funciones públicas, macros    *
*          y estructuras para la gestión lógica de   *
*          máquinas de estado no jerárquicas         *
*                                                    *
* AUTHOR: Fernando Domínguez                         *
*                                                    *
* DATE: 22/12/2015     VERSION: 1.0                  *
*                                                    *
*****************************************************/

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

void EjecutaAutomata(TS_AUTOMATA *elAutomata)
{
	TS_ESTADO **Indx;    /* Valor indice rastreador */

	if (elAutomata->StopCond())  return;

	for (Indx = elAutomata->estado; *Indx != NULL; ++Indx)
	{
	    if (elAutomata->id_estado_actual == (*Indx)->id)
	    {
			EjecutaEstado(*Indx , elAutomata);
			return;
	    }
	}
}

void EjecutaEstado(TS_ESTADO *elEstado , TS_AUTOMATA *elAutomata)
{
	TS_EVEACC *Indx;   /* Indice de rastreo */

	(*elEstado->controles)();

	for (Indx = elEstado->funcion; Indx->evento != NULL; ++Indx)
	{
		if (Indx->evento() == TRUE)
		{
			if (Indx->accion != NULL)
			{
				Indx->accion();
			}
			if (Indx->id != elAutomata->id_estado_actual)
			{
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


