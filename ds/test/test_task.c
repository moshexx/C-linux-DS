#include <stdio.h>
#include "task.h"

int test();

int main()
{
    task_t *t = TaskCreate(10, 5, test, NULL);

    printf("get time: 10 = %ld\n", TaskGetTimeToExecute(t));

    TaskRun(t);
    TaskReschedule(t);

    printf("get new time: 15 = %ld\n", TaskGetTimeToExecute(t));
    printf("get freq: 5 = %ld\n", TaskGetFrequency(t));

    printf("get uid counter: 1 = %ld\n", (TaskGetUID(t)).counter);
    printf("get uid time_stamp:  %ld\n", (TaskGetUID(t)).time_stamp);
    printf("get uid pid:  %d\n", (TaskGetUID(t)).pid);

    TaskDestroy(t);

    return 0;
}

int test()
{
    printf("test1\n");
    return 0;
}
