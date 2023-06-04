/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_priority_queue.c
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <stdlib.h>
#include <string.h>

#include "priority_queue.h"

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

enum successful {SUCCEED, FAILED};

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int MemCmp(const void *one, const void *other);
int IsMatch(const void *one, const void *other, size_t n);
int main()
{
    pq_t *p_queue = PQCreate(MemCmp);
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9};

    RUN_TEST(NULL != p_queue, "PQCreate");
    RUN_TEST(1 == PQIsEmpty(p_queue), "PQIsEmpty(empty)");
    RUN_TEST(0 == PQSize(p_queue), "PQSize(empty)");
    RUN_TEST(SUCCEED == PQEnqueue(p_queue, arr + 1), "PQEnqueue 1");
    RUN_TEST(arr + 1 == PQPeek(p_queue), "PQPeek 1");
    RUN_TEST(SUCCEED == PQEnqueue(p_queue, arr + 2), "PQEnqueue 2");
    RUN_TEST(arr + 1 == PQPeek(p_queue), "PQPeek 2");
    RUN_TEST(SUCCEED == PQEnqueue(p_queue, arr + 3), "PQEnqueue 3");
    RUN_TEST(SUCCEED == PQEnqueue(p_queue, arr + 4), "PQEnqueue 4");
    RUN_TEST(SUCCEED == PQEnqueue(p_queue, arr + 5), "PQEnqueue 5");
    RUN_TEST(5 == PQSize(p_queue), "PQSize(not empty)");
    PQDequeue(p_queue);
    RUN_TEST(arr + 2 == PQPeek(p_queue), "PQDequeue");
    RUN_TEST(4 == PQSize(p_queue), "PQSize after PQDequeue");
    PQFlush(p_queue);
    RUN_TEST(1 == PQIsEmpty(p_queue), "PQFlush");

    RUN_TEST(SUCCEED == PQEnqueue(p_queue, arr + 5), "PQEnqueue 1");
    RUN_TEST(SUCCEED == PQEnqueue(p_queue, arr + 3), "PQEnqueue 2");
    RUN_TEST(SUCCEED == PQEnqueue(p_queue, arr + 1), "PQEnqueue 3");
    RUN_TEST(SUCCEED == PQEnqueue(p_queue, arr + 2), "PQEnqueue 4");
    RUN_TEST(SUCCEED == PQEnqueue(p_queue, arr + 6), "PQEnqueue 5");

    RUN_TEST(arr + 3 == PQErase(p_queue, IsMatch, arr + 3, sizeof(int)),
                                            "PQErase return value");
    RUN_TEST(4 == PQSize(p_queue), "PQSize after PQErase");
    RUN_TEST(arr + 1 == PQPeek(p_queue), "Check Priority ");

    printf("first member(1): %d\n", *(int *)(PQPeek(p_queue)));

    printf("vlg check :)\n");
    PQDestroy(p_queue);

	return 0;
}

int MemCmp(const void *one, const void *other)
{
	return (memcmp(one, other, sizeof(int)));
}

int IsMatch(const void *one, const void *other, size_t n)
{
	return (!memcmp(one, other, n));
}
