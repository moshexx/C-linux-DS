/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: task.c
*	author: Moshe Cohen
*	reviewer: Yarden Natovich

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> /* assert */

#include "task.h"
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

enum status_t{FALSE = 0, TRUE = 1};

struct task
{
    time_t time_to_execute;
    time_t frequency;
    ilrd_uid_t uid;
    void *params;
    oper_func_t oper_func;
};
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

task_t *TaskCreate(time_t time_to_execute, time_t frequency,
						oper_func_t oper_func, void *params)
{
    task_t *task = NULL;

    assert (NULL != oper_func);

    if (frequency < 0)
    {
        frequency = -frequency;
    }
    task = (task_t *)malloc(sizeof(task_t));
    if (NULL == task)
    {
        printf("allocation FAILURE\n");
        return NULL;
    }

    task->time_to_execute = time_to_execute;
    task->frequency = frequency;
    task->uid = UIDCreate();
    task->params = params;
    task->oper_func = oper_func;
    if (TRUE == UIDIsSame(TaskGetUID(task), UIDGetBadUID()))
    {
        printf("UID is bad\n");
        return NULL;
    }

    return task;
}

void TaskDestroy(task_t *task)
{
    free (task); task = NULL;
}

int TaskRun(const task_t *task)
{
    assert (NULL != task);

    return(task->oper_func(task->params));
}

void TaskReschedule(task_t *task)
{

    assert (NULL != task);
    assert (0 < task->frequency);

    task->time_to_execute += task->frequency;

}

ilrd_uid_t TaskGetUID(const task_t *task)
{
    assert (NULL != task);

    return(task->uid);
}

time_t TaskGetTimeToExecute(const task_t *task)
{
    assert (NULL != task);

    return(task->time_to_execute);
}

time_t TaskGetFrequency(const task_t *task)
{
    assert (NULL != task);

    return(task->frequency);
}
