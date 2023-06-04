/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: scheduler.c
*	author: Moshe Cohen
*	reviewer: Yarden Natovich

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free, size_t */
#include <assert.h> /* assert */
#include <unistd.h> /* sleep */

#include "scheduler.h"
#include "priority_queue.h"
#include "task.h"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

enum status_t{SUCCESS, FAILURE};
enum running_t{STOP_RUNNING, RUN};

struct scheduler
{
    pq_t *p_queue;
    task_t *curr_task;
    int is_running;
};
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~helper functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int PriorFunc(const void *one, const void *other)
{
    return (0 <= TaskGetTimeToExecute((task_t*)one) -
                 TaskGetTimeToExecute((task_t*)other));
}

int IsMatchUid(const void *task, const void *uid, size_t n)
{
    (void) n;
    return (UIDIsSame(*(ilrd_uid_t *)uid, TaskGetUID((task_t *)task)));
}
/*
int StopWrapper(void *params)
{
    SchedStop((sched_t *)params);

    return SUCCESS;
}*/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

sched_t *SchedCreate(void)
{
    sched_t *sched = (sched_t *)malloc(sizeof(sched_t ));
    if (NULL == sched)
    {
        printf("allocation failed\n");
        return NULL;
    }

    sched->p_queue = PQCreate(PriorFunc);
    if (NULL == sched->p_queue)
    {
    	free(sched); sched = NULL;
    	return NULL;
    }
    sched->curr_task = NULL;
    sched->is_running = 0;

    return sched;
}

void SchedDestroy(sched_t *sched)
{
    assert (NULL != sched);

    SchedFlush(sched);
    PQDestroy(sched->p_queue);
    free(sched); sched = NULL;
}

ilrd_uid_t SchedAddTask(sched_t *sched, time_t time_to_execute, time_t frequency
						, int(*oper_func)(void *params), void *params)
{
    task_t *task = NULL;

    assert (NULL != sched);
    assert (0 <= frequency);
    assert (0 <= time_to_execute);

    task = TaskCreate(time_to_execute, frequency, oper_func, params);
    if (NULL == task)
    {
        printf("TaskCreate Allocation failed\n");
        return UIDGetBadUID();
    }

    if (FAILURE == PQEnqueue(sched->p_queue, task))
    {
        printf("PQEnqueue Allocation failed\n");
        TaskDestroy(task);
        return UIDGetBadUID();
    }

    return(TaskGetUID(task));
}

void SchedRemoveTask(sched_t *sched, ilrd_uid_t uid)
{
    task_t *task = NULL;

    assert (NULL != sched);

    task = PQErase(sched->p_queue, IsMatchUid, &uid, 1);
    TaskDestroy(task);
}

void SchedFlush(sched_t *sched)
{
    assert (NULL != sched);

    while (!PQIsEmpty(sched->p_queue))
    {
        TaskDestroy(PQPeek(sched->p_queue));
        PQDequeue(sched->p_queue);
    }
}

int SchedRun(sched_t* sched)
{
    time_t run_time = time(NULL);
    time_t current_time = time(NULL);
    time_t sleep_time = 0;

    assert (NULL != sched);

    sched->is_running = RUN;

    /* if(SchedIsEmpty) / SchedStop / task FAILURE --> is_running = STOP_RUNNING */
    while (RUN == sched->is_running && !SchedIsEmpty(sched))
    {
        sched->curr_task = PQPeek(sched->p_queue);
        current_time = time(NULL);
        sleep_time = TaskGetTimeToExecute(sched->curr_task) - (difftime(current_time, run_time));
        if (sleep_time > 0)
        {
            sleep(sleep_time);
        }

        /* pop the current task from the queue */
        PQDequeue(sched->p_queue);

        if (FAILURE == TaskRun(sched->curr_task))
        {
            sched->is_running = STOP_RUNNING;
            /* return the task to the queue before sending the FAILURE */
            if (FAILURE == PQEnqueue(sched->p_queue, sched->curr_task))
            {
                printf("PQEnqueue Allocation failed\n");
                /* return FAILURE anyway */
            }
            return FAILURE;
        }

        /* If the current task is repetitive */
        if (0 < TaskGetFrequency(sched->curr_task))
        {
            TaskReschedule(sched->curr_task);
            if (FAILURE == PQEnqueue(sched->p_queue, sched->curr_task))
            {
                printf("PQEnqueue Allocation failed\n");
                sched->is_running = STOP_RUNNING;
                return FAILURE;
            }
        }
        else
        {
            TaskDestroy(sched->curr_task); sched->curr_task = NULL;
        }
    }

    sched->is_running = STOP_RUNNING;
    return SUCCESS;
}

int SchedStop(sched_t *sched)
{
    assert (NULL != sched);

    sched->is_running = STOP_RUNNING;

    return SUCCESS;
}

int SchedIsEmpty(sched_t* sched)
{
    assert (NULL != sched);

    return PQIsEmpty(sched->p_queue);
}

size_t SchedSize(sched_t* sched)
{
    assert (NULL != sched);

    return PQSize(sched->p_queue);
}
