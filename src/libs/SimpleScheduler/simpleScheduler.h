/*****************************************************
 * FILE NAME: staticCircularBuffer.h                  *
 *                                                    *
 * PURPOSE: Declaración de funciones públicas para    *
 *          crear y operar un Scheduler               *
 *                                                    *
 * AUTHOR: Fernando Domínguez                         *
 *                                                    *
 * DATE: 11/12/2015     VERSION: 1.0                  *
 *                                                    *
 *****************************************************/

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
