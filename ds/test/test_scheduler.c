/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_scheduler.c
*	author: Moshe Cohen
*	reviewer: Yarden Natovich

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <stdlib.h>

#include "task.h"
#include "scheduler.h"


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define RED printf("\033[0;31m")
#define GREEN printf("\033[0;32m")
#define YELLOW printf("\033[01;33m")
#define BLUE printf("\033[0;34m")
#define RESET printf("\033[0m")
#define RUN_TEST(result, name) {\
            printf("Test %s: ", name);\
            if (result)\
            {\
                GREEN;\
                printf("Success\n");\
                RESET;\
            }\
            else\
            {\
                RED;\
                printf("Failed\n");\
                RESET;\
            }\
        }

enum successful {SUCCESS, FAILURE};
enum matching {NO, YES};

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~aid functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    int test1();
    int test2();
    int test3();
    int test4();
    int test5();
    int StopWrapper(void *params);
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~main test~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    int main()
    {
        sched_t *sched = SchedCreate();
        ilrd_uid_t uid_task1;
        ilrd_uid_t uid_task2;
        ilrd_uid_t uid_task3;
        ilrd_uid_t uid_task4;
        ilrd_uid_t uid_task5;
        ilrd_uid_t uid_stop;

        static int x = 5;

        RUN_TEST(1 == SchedIsEmpty(sched), "SchedIsEmpty(empty)");
        RUN_TEST(0 == SchedSize(sched), "SchedSize(empty)");

        uid_task1 = SchedAddTask(sched, 4, 0, test2, &x);

        RUN_TEST(0 == SchedIsEmpty(sched), "SchedIsEmpty(not empty)");
        RUN_TEST(1 == SchedSize(sched), "SchedSize(1 task)");

        uid_task2 = SchedAddTask(sched, 3, 4, test1, &x);
        uid_task3 = SchedAddTask(sched, 6, 0, test3, &x);
        uid_stop = SchedAddTask(sched, 10, 0, StopWrapper, (void *)sched);

        printf("\nFirst RUN:\n");
        SchedRun(sched);

        SchedRemoveTask(sched, uid_task1);
        SchedRemoveTask(sched, uid_task2);
        SchedRemoveTask(sched, uid_task3);
        SchedRemoveTask(sched, uid_stop);

        RUN_TEST(1 == SchedIsEmpty(sched), "after Remove - SchedIsEmpty(empty)");
        RUN_TEST(0 == SchedSize(sched), "after Remove - SchedSize(empty)");

        uid_task1 = SchedAddTask(sched, 4, 0, test2, &x);
        uid_task2 = SchedAddTask(sched, 3, 4, test1, &x);
        uid_task3 = SchedAddTask(sched, 6, 0, test3, &x);
        uid_task4 = SchedAddTask(sched, 7, 0, test4, &x);
        uid_task5 = SchedAddTask(sched, 10, 0, test5, &x);

        uid_stop = SchedAddTask(sched, 5, 0, StopWrapper, (void *)sched);

        printf("\nSecond RUN:\n");
        SchedRun(sched);

        SchedRemoveTask(sched, uid_task2);
        SchedRemoveTask(sched, uid_stop);

        printf("\nLast RUN:\n");
        SchedRun(sched);


        SchedDestroy(sched);
        printf("Check valgrind\n");

        (void) uid_task4;
        (void) uid_task5;
        return 0;
    }
/*************************Help Function****************************************/
    int StopWrapper(void *params)
    {
        SchedStop((sched_t *)params);

        return SUCCESS;
    }

    int test1()
    {
        printf("run check: printf test1\n");
        return 0;
    }

    int test2()
    {
        printf("run check: printf test2\n");
        return 0;
    }

    int test3()
    {
        printf("Yarden Natovich - Welcome\n");
        return 0;
    }

    int test4()
    {
        system("firefox https://youtu.be/onGX_Q0okcQ?t=14");
        return 0;
    }

    int test5()
    {
        system("echo Hello world");
        /*system("telnet towel.blinkenlights.nl");*/
        return 0;
    }
