/*******************************************************************************
------------------------------------------------------------------------------
*	file name: pthread_uid.c
*	author: Thanks to Yoni Ladijenski
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <stdlib.h>
#include <sys/types.h>/*pid_t*/
#include <time.h>/*time()*/
#include <unistd.h> /*getpid*/
#include <time.h> /*time(), size_t*/
#include <pthread.h> /* mutex */
#include <signal.h> /* sig_atomic_t */

#include "pthread_safe_uid.h"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define RED printf("\033[0;31m")
#define GREEN printf("\033[0;32m")
#define YELLOW printf("\033[01;33m")
#define BLUE printf("\033[0;34m")
#define LIGTH_BLUE printf("\033[01;36m")
#define RESET printf("\033[0m")
#define RUN_TEST(result, name) {\
			LIGTH_BLUE;\
            /*printf("Test %s: ", name);*/\
            RESET;\
            if (result)\
            {\
               /* GREEN;\
                printf("Success\n");\
                RESET;*/\
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

pthread_t tid[10] = {0};
pthread_mutex_t mtx1;
pthread_mutex_t mtx2;

size_t array[1000000] = {0};

void *treadcheck1(void *x);
void *treadcheck2(void *x);
/*****************************/

int TestThreads();

int main()
{
	size_t i = 0;
	for(;i < 100000; ++i)
	{
		RUN_TEST(TestThreads(), "TestThreads");
	}

	for(i = 1; i < 1000000; ++i)
	{
		if(array[i] != 1)
		{
			printf("i = %ld, array[i] = %ld\n", i, array[i]);
		}
	}


	return 0;
}

void *treadcheck1(void *x)
{
	ilrd_pthread_uid_t bad_uid = PThreadUIDGetBadUID();
	ilrd_pthread_uid_t my_uid;

	pthread_mutex_lock(&mtx1);

	my_uid = PThreadUIDCreate();

	*(int*)x += (0 == PThreadUIDIsSame(my_uid, bad_uid));

	++array[my_uid.counter];

	pthread_mutex_unlock(&mtx1);

	return NULL;
}

void *treadcheck2(void *x)
{
	ilrd_pthread_uid_t bad_uid = PThreadUIDGetBadUID();
	ilrd_pthread_uid_t my_uid;

	pthread_mutex_lock(&mtx2);

	my_uid = PThreadUIDCreate();

	*(int*)x += (0 == PThreadUIDIsSame(my_uid, bad_uid));

	/*printf("counter %ld\n", my_uid.counter);*/

	++array[my_uid.counter];

	pthread_mutex_unlock(&mtx2);

	return NULL;
}

int TestThreads()
{
	size_t i = 0;
	int x = 0;
	int y = 0;

	if (0 != pthread_mutex_init(&mtx1, NULL))
	{
		return 1;
	}

	if (0 != pthread_mutex_init(&mtx2, NULL))
	{
		return 1;
	}

	for(i = 0; i < 5; ++i)
	{
		pthread_create(&(tid[i]), NULL, &treadcheck1, &x);
	}

	for(i = 5; i < 10; ++i)
	{
		pthread_create(&(tid[i]), NULL, &treadcheck2, &y);
	}

	for(i = 0; i < 10; ++i)
	{
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(&mtx1);
	pthread_mutex_destroy(&mtx2);
	return (x + y == 10);
}
