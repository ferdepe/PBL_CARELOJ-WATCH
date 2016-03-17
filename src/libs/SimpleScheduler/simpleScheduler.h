/**
 * @file    simpleScheduler.h
 * @brief   Header de un pequeño y sencillo scheduler para la gestión de tareas
 * @author  F. Domínguez
 * @date    11/12/2015 
*/

#ifndef SIMPLESCHEDULER_H_
#define SIMPLESCHEDULER_H_

/*****************************************************
 *                   MODULES USED                     *
 *****************************************************/

/*****************************************************
 *               DEFINITIONS AND MACROS               *
 *****************************************************/

#define SCHEDULE_TASK_MAX 5

/*****************************************************
 *              TYPEDEFS AND STRUCTURES               *
 *****************************************************/
/**
 * @struct     STASK
 * @brief      Estructura con las propiedades que posee una tarea
 * @par        Descripción:
 *             - Callback a que realizar
 *             - Delay
 *             - Periodo
 *             - Booleano que indica si se ha de ejecutar o no
 * @author     F. Domínguez
 * @date       27/02/2016 
*/
typedef struct {
	void (*pFunction)(void);
	int Delay;
	int Period;
	unsigned char RunMe;
} STASK;

/*****************************************************
 *                 EXPORTED VARIABLES                 *
 *****************************************************/

/*****************************************************
 *                  EXPORTED FUNCTIONS                *
 *****************************************************/

void SIMPLE_SCHEDULER_init();
void SIMPLE_SCHEDULER_schedule();
//void SIMPLE_SCHEDULER_backgroundTask();
void SIMPLE_SCHEDULER_addTask(void (*pFunction)(void), int period, int delay);
void SIMPLE_SCHEDULER_update();

/*****************************************************
 *                        EOF                         *
 *****************************************************/

#endif /* SIMPLESCHEDULER_H_ */
