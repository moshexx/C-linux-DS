/******************************************************************************/
/*		Descriptions - Task API Functions								  	  */
/*		Date: 11.11.2020					     						   	  */
/*		Group: OL96						      								  */
/******************************************************************************/

#ifndef __TASK_H__
#define __TASK_H__

#include <time.h> /* time_t */

#include "uid.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef	struct task task_t;
typedef	int(*oper_func_t)(void *params);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* 
* Description: creates a new task
* Return value: pointer to the task
* Errors: NULL if memory allocation or UID is beduid
* Undefined behavior: oper_func can't be NULL
*	      			
* Complexity: O(1).
*/
task_t *TaskCreate(time_t time_to_execute, time_t frequency,
						oper_func_t oper_func, void *params);

/* 
* Description: frees memory allocated for the task
* Return value: none
* Errors: none.
* Undefined behavior: 
*	      			
* Complexity: O(1).
*/
void TaskDestroy(task_t *task);

/* 
* Description: executes the function given to the task
* Return value: returns 0 if function execution succeeded or 1 if failed
* Errors: none.
* Undefined behavior: task can't be NULL
*
* Complexity: O(1) (in practice, same as the task function's complexity)
*/
int TaskRun(const task_t *task);

/* 
* Description: resets the time_to_execute of task
* Return value: none.
* Errors: task's frequency is 0
* Undefined behavior: task can't be NULL 
*
* Complexity: O(1)
*/
void TaskReschedule(task_t *task);

/*
* Description: gets the uid of task
* Return value: task's uid
* Errors: none.
* Undefined behavior: task can't be NULL
*	      			
* Complexity: O(1).
*/
ilrd_uid_t TaskGetUID(const task_t *task);

/*
* Description: gets the time_to_execute of task
* Return value: time_to_execute
* Errors: none.
* Undefined behavior: task can't be NULL
*	      			
* Complexity: O(1).
*/
time_t TaskGetTimeToExecute(const task_t *task);

/*
* Description: gets the task's frequency
* Return value: task's frequency
* Errors: none.
* Undefined behavior: task can't be NULL
*	      			
* Complexity: O(1).
*/
time_t TaskGetFrequency(const task_t *task);

#endif   /*__TASK_H__*/
