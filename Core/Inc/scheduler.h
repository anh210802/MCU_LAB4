/*
 * scheduler.h
 *
 *  Created on: Dec 7, 2023
 *      Author: anhxa
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>

typedef struct {
	void (*pTask)(void);
	uint32_t	Delay;
	uint32_t	Period;
	uint8_t		RunMe;

	uint32_t	TaskID;
}sTasks;

#define SCH_MAX_TASKS 40
#define CYCLES_TIMER 10

void SCH_Init(void);

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);

void SCH_Delete(uint32_t ID);

#endif /* SCHEDULER_H_ */
