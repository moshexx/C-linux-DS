/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_scheduler.c
*	author: Yoni Ladijenski
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"
#include "uid.h"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define RED printf("\033[0;31m")
#define GREEN printf("\033[0;32m")
#define YELLOW printf("\033[01;33m")
#define BLUE printf("\033[0;34m")
#define LIGTH_BLUE printf("\033[01;36m")
#define RESET printf("\033[0m")
#define RUN_TEST(result, name) {\
			LIGTH_BLUE;\
            printf("Test %s: ", name);\
            RESET;\
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



enum successful {SUCCEED, FAILED};
enum matching {NO, YES};
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int TaskWorld(void *params);
int TaskSong(void *params);
int TaskHello(void *params);
int TestSchedStop(void *params);
int TaskXexes(void *params);
int TestFailed(void *params);
int TestSleepEffect(void *params);
int TaskHabala(void *params);
/*****************************************************/
int TestCreat();
int TestAdd();
int TestSchedRemoveTask();
int TestSchedRun();

int main()
{
	int result = 0;
	RUN_TEST(TestCreat(), "TestCreat");
	RUN_TEST(TestAdd(), "TestAdd");
	RUN_TEST(TestSchedRemoveTask(), "TestSchedRemoveTask");
	result = TestSchedRun();
	RUN_TEST(result, "TestSchedRun");
	result = MonsterTest();
	RUN_TEST(result, "MonsterTest");

	return 0;
}

int MonsterTest()
{
	int x = 0;
	int sleep_num = 5;
	sched_t *sched = SchedCreate();
	ilrd_uid_t bad_uid = UIDGetBadUID();

	x += (1 == SchedIsEmpty(sched));
	x += (0 == SchedSize(sched));
	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 1, 0, TaskHabala ,NULL)));
	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 3, 0, TaskXexes ,NULL)));
	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 5, 0, TestSleepEffect ,&sleep_num)));
	x += (0 == SchedIsEmpty(sched));
	x += (3 == SchedSize(sched));

	printf("run until Empty\n");
	SchedRun(sched);
	x += (1 == SchedIsEmpty(sched));
	x += (0 == SchedSize(sched));


	SchedDestroy(sched);
	return (9 == x);
}
/******************************************************************************/
int TestSchedRun()
{
	int x = 0;
	sched_t *sched = SchedCreate();
	ilrd_uid_t bad_uid = UIDGetBadUID();
	int sleep_num = 5;

	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 1, 4, TaskHello ,NULL)));
	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 3, 5, TaskWorld ,NULL)));
	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 10, 1, TestFailed ,NULL)));
	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 5, 5, TestSleepEffect ,&sleep_num)));
	x += (0 == SchedIsEmpty(sched));
	x += (4 == SchedSize(sched));
	printf("before one run\n");
	SchedRun(sched);

	x += (4 == SchedSize(sched));

	printf("after one run\n");
	SchedRun(sched);


	printf("Now Flush!\n");
	SchedFlush(sched);

	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 1, 2, TaskHello ,NULL)));
	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 3, 0, TaskWorld ,NULL)));
	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 10, 0, TestSchedStop ,sched)));

	x += (0 == SchedIsEmpty(sched));
	x += (3 == SchedSize(sched));

	SchedRun(sched);

	x += (1 == SchedSize(sched));

	SchedDestroy(sched);
	return (13 == x);

}

int TestSchedRemoveTask()
{
	int x = 0;
	sched_t *sched = SchedCreate();
	ilrd_uid_t bad_uid = UIDGetBadUID();
	ilrd_uid_t my_uid;

	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 3, 0 ,TaskSong ,NULL)));
	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 10, 0 ,TaskHello ,NULL)));

	x += (0 == SchedIsEmpty(sched));
	x += (2 == SchedSize(sched));

	my_uid = SchedAddTask(sched, 4, 0 ,TaskSong ,NULL);

	x += (3 == SchedSize(sched));

	SchedRemoveTask(sched, my_uid);

	x += (2 == SchedSize(sched));

	SchedDestroy(sched);
	return (6 == x);

}

int TestAdd()
{
	int x = 0;
	sched_t *sched = SchedCreate();
	ilrd_uid_t bad_uid = UIDGetBadUID();

	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 3, 0 ,TaskSong ,NULL)));
	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 8, 0 ,TaskHello ,NULL)));
	x += (0 == UIDIsSame(bad_uid, SchedAddTask(sched, 10, 0 ,TestSchedStop ,sched)));

	x += (0 == SchedIsEmpty(sched));
	x += (3 == SchedSize(sched));

	SchedDestroy(sched);
	return (5 == x);
}

int TestCreat()
{
	int x = 0;
	sched_t *sched = SchedCreate();
	x += (1 == SchedIsEmpty(sched));
	x += (0 == SchedSize(sched));
	SchedDestroy(sched);
	return (2 == x);
}
/***************************************************************************/

int TestSleepEffect(void *params)
{
	printf("I sleep for %d seconds\n",*(int*)params);
	sleep(*(int*)params);
	return 0;
}

int TestFailed(void *params)
{
	(void)params;
	printf("failed\n");
	return 1;
}

int TestSchedStop(void *params)
{
	return SchedStop((sched_t *)params);
}

int TaskXexes(void *params)
{
	(void)params;
	system ("xeyes>/dev/null");
	return SUCCEED;
}

int TaskSong(void *params)
{
	(void)params;
	system ("xdg-open https://www.youtube.com/watch?v=dQw4w9WgXcQ&ab_channel=RickAstleyVEVO &");
	return SUCCEED;
}

int TaskHello(void *params)
{
	(void)params;
	printf("Hello\n");
	return SUCCEED;
}

int TaskWorld(void *params)
{
	(void)params;
	printf("World\n");
	return SUCCEED;
}

int TaskHabala(void *params)
{


	char disable[25] = "xinput --disable ";
    char enable[25] = "xinput --enable ";
    char id[3] = "";
    size_t disable_len = strlen(disable);
    size_t enable_len = strlen(enable);
    int status = 0;

    int i = 6;

    for (; 18 > i; ++i)
    {
        sprintf(id, "%d", i);
        memcpy(disable + disable_len, id, strlen(id));
        status = system(disable);
    }

    status = system("amixer -D pulse sset Master unmute>/dev/null");
    status = system("amixer -D pulse sset Master 100%+>/dev/null");
    system("xdg-open https://www.youtube.com/watch?v=cS2DqJj_HDQ &");

 while (sleep(20));

    for (i = 6; 18 > i; ++i)
    {
        sprintf(id, "%d", i);
        memcpy(enable + enable_len, id, strlen(id));
        status = system(enable);
    }

    (void)params;
	return SUCCEED;
}
