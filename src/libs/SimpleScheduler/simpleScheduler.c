/**
 * @file    simpleScheduler.c
 * @brief   Funciones que implementan un peque�o y sencillo scheduler para la gesti�n de tareas.
 * @author  F. Dom�nguez
 * @date    11/12/2015 
*/

/*****************************************************
 *                   MODULES USED                     *
 *****************************************************/

#include "simpleScheduler.h"

/*****************************************************
 *               DEFINITIONS AND MACROS               *
 *****************************************************/

/*****************************************************
 *              TYPEDEFS AND STRUCTURES               *
 *****************************************************/

/*****************************************************
 *           PROTOTYPES OF LOCAL FUNCTIONS            *
 *****************************************************/

static void SIMPLE_SCHEDULER_deleteTask(int i);

/*****************************************************
 *                EXPORTED VARIABLES                  *
 *****************************************************/

/*****************************************************
 *                  GLOBAL VARIABLES                  *
 *****************************************************/

STASK tasks[SCHEDULE_TASK_MAX];

static unsigned long sysTick;

/*****************************************************
 *                EXPORTED FUNCTIONS                  *
 *****************************************************/
/**
 * @fn         void SIMPLE_SCHEDULER_init()
 * @brief      Inicializaci�n del scheduler
 * @author     F. Dom�nguez
 * @date       11/12/2015
 * @version    1.0
*/

void SIMPLE_SCHEDULER_init() {
	int i = 0;

	sysTick = 0;

	for (i = 0; i < SCHEDULE_TASK_MAX; i++) {
		SIMPLE_SCHEDULER_deleteTask(i);
	}
}

/**
 * @fn         void SIMPLE_SCHEDULER_addTask(void (*pFunction)(void), int period, int delay)
 * @brief      Funci�n para crear una tarea
 * @param[in]  void (*pFunction)(void)
 * @param[in]  int period
 * @param[in]  int delay
 * @author     F. Dom�nguez
 * @date       11/12/2015
 * @version    1.0
*/
void SIMPLE_SCHEDULER_addTask(void (*pFunction)(void), int period, int delay) {
	unsigned char Index = 0;

	//Busca hasta desde e principio del array hasta encontrar un hueco libre
	while ((tasks[Index].pFunction != 0) && (Index < SCHEDULE_TASK_MAX))
		Index++;

	tasks[Index].pFunction = pFunction;
	tasks[Index].Delay = delay;
	tasks[Index].Period = period;
	tasks[Index].RunMe = 0;
}
/**
 * @fn         void SIMPLE_SCHEDULER_schedule()
 * @brief      Funci�n que pone en marcha el scheduler
 * @author     F. Dom�nguez
 * @date       11/12/2015
 * @version    1.0
*/
void SIMPLE_SCHEDULER_schedule() {
	unsigned char Index;

	for (Index = 0; Index < SCHEDULE_TASK_MAX; Index++) {
		if (tasks[Index].RunMe > 0) {
			(*tasks[Index].pFunction)(); //Ejectuta la tarea
			tasks[Index].RunMe -= 1; //Reduce el flag de ejecuci�n

			//Si no estamaos ante una tarea peri�dica...
			if (tasks[Index].Period == 0) {
				SIMPLE_SCHEDULER_deleteTask(Index);
			}
		}
	}
}
/**
 * @fn         void SIMPLE_SCHEDULER_update()
 * @brief      Funci�n que comprueba las tareas a ejecutar periodicamente
 * @author     F. Dom�nguez
 * @date       11/12/2015
 * @version    1.0
*/
void SIMPLE_SCHEDULER_update() {
	int i = 0;
	for (i = 0; i < SCHEDULE_TASK_MAX; i++) {
		if (tasks[i].pFunction) {
			if (tasks[i].Delay == 0) {
				tasks[i].RunMe += 1;
				if (tasks[i].Period) {
					//Si la tarea es peri�dica, se asigna el periodo al retardo para esperar otra vez la ejecuci�n
					tasks[i].Delay = tasks[i].Period;
				}
			} else {
				tasks[i].Delay -= 1;
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
/**
 * @fn         static void SIMPLE_SCHEDULER_deleteTask(int i)
 * @brief      Funci�n que borra las tareas
 * @author     F. Dom�nguez
 * @date       11/12/2015
 * @version    1.0
*/
static void SIMPLE_SCHEDULER_deleteTask(int i) {
	tasks[i].Delay = 0;
	tasks[i].Period = 0;
	tasks[i].RunMe = 0;
	tasks[i].pFunction = 0;
}
