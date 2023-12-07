/*
 * scheduler.c
 *
 *  Created on: Dec 7, 2023
 *      Author: anhxa
 */


#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];

uint8_t current_index_task = 0;

void SCH_Init(void){
	current_index_task = 0;
}

void SCH_Add_Task (void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	if(current_index_task < SCH_MAX_TASKS){
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY / CYCLES_TIMER;
		SCH_tasks_G[current_index_task].Period = PERIOD / CYCLES_TIMER;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;

		current_index_task++;
	}
}

void SCH_Update(void){
	for(int i = 0; i < current_index_task; i++){
		if (SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay--;
		}else{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe += 1;
		}
	}
}

void SCH_Dispatch_Tasks(void){
	for(int i = 0; i < current_index_task; i++){
		if(SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();
		}
	}
}

void SCH_Delete(uint32_t taskID){
	int i = taskID;
	for(;i < current_index_task;i++){
		SCH_tasks_G[i].pTask = SCH_tasks_G[i+1].pTask ;
		SCH_tasks_G[i].Delay = SCH_tasks_G[i +1].Delay ;
		SCH_tasks_G[i].Period = SCH_tasks_G[i+1].Period ;
		SCH_tasks_G[i].RunMe = SCH_tasks_G[i+1].RunMe ;
		SCH_tasks_G[i].TaskID = SCH_tasks_G[i +1].TaskID ;
	}
		SCH_tasks_G[i].pTask =0x0000;
		SCH_tasks_G[i].Delay =0;
		SCH_tasks_G[i].Period =0;
		SCH_tasks_G[i].RunMe =0;
}
