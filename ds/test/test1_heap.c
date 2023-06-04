/*#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "priority_queue.h"

#define GREEN_COLOR     "\x1b[0;32m"
#define RED_COLOR     "\x1b[0;31m"
#define DEFAULT_COLOR    "\x1b[0;0m"

#define RUN_TEST(result, name) {\
            printf("Test %s: ", name);\
            if (result)\
            {\
                printf(GREEN_COLOR);\
                printf("Success\n");\
                printf(DEFAULT_COLOR);\
            }\
            else\
            {\
                printf(RED_COLOR);\
                printf("Fail\n");\
                printf(DEFAULT_COLOR);\
            }\
        }

int CmpFuncInt(const void *one, const void *other)
{
    return (*(int*)other - *(int*)one);

}

int CmpFuncIntMin(const void *one, const void *other)
{
    return (*(int*)one - *(int*)other);

}

int MachFuncInt(const void *one, const void *other, void *params)
{
    (void)params;
    return (*(int*)other == *(int*)one);
}

int TestBase()
{
	int a =1, b = 2, c = 3, d = 4, e = 6;
	heap_t *heap = HeapCreate(CmpFuncInt);
	int res = 0;

	res += (1 == HeapIsEmpty(heap));
	res += (0 == HeapPush(heap , &a));
	res += (a == *(int*)HeapPeek(heap));
	res += (0 == HeapPush(heap , &b));
	res += (b == *(int*)HeapPeek(heap));
	res += (0 == HeapPush(heap , &c));
	res += (c == *(int*)HeapPeek(heap));
	res += (0 == HeapPush(heap , &d));
	res += (d == *(int*)HeapPeek(heap));
	res += (HeapSize(heap) == 4);
	res += (b == *(int*)HeapRemove(heap, &b, MachFuncInt, NULL));
	res += (NULL == HeapRemove(heap, &e, MachFuncInt, NULL));
	res += (HeapSize(heap) == 3);
	printf("out \n");
	while(!HeapIsEmpty(heap))
	{
		printf("%d \n",*(int*)HeapPeek(heap));
		HeapPop(heap);
	}
	res += (HeapSize(heap) == 0);
	HeapDestroy(heap);
	return (res == 14);
	 
}

int TestMinHeap()
{
	int a =1, b = 2, c = 3, d = 4, e = 6;
	heap_t *heap = HeapCreate(CmpFuncIntMin);
	int res = 0;
	
	res += (1 == HeapIsEmpty(heap));
	res += (0 == HeapPush(heap , &a));
	res += (a == *(int*)HeapPeek(heap));
	res += (0 == HeapPush(heap , &b));
	res += (a == *(int*)HeapPeek(heap));
	res += (0 == HeapPush(heap , &c));
	res += (a == *(int*)HeapPeek(heap));
	res += (0 == HeapPush(heap , &d));
	res += (a == *(int*)HeapPeek(heap));
	res += (HeapSize(heap) == 4);
	res += (b == *(int*)HeapRemove(heap, &b, MachFuncInt, NULL));
	res += (NULL == HeapRemove(heap, &e, MachFuncInt, NULL));
	res += (HeapSize(heap) == 3);
	printf("out \n");
	while(!HeapIsEmpty(heap))
	{
		printf("%d \n",*(int*)HeapPeek(heap));
		HeapPop(heap);
	}
	res += (HeapSize(heap) == 0);
	HeapDestroy(heap);
	return (res == 14);
}

int TestAll()
{
	heap_t *heap = HeapCreate(CmpFuncIntMin);
	heap_t *heap2 = HeapCreate(CmpFuncIntMin);
	pq_t * q = PQCreate(CmpFuncIntMin);
	int res = 0;
	int arr [200];
	size_t i = 0;

	for(i =0; i<200; ++i)
	{
		arr[i]= rand () % 10000;
		PQEnqueue(q,&arr[i]);
	}
	for(i =0; i<200 ; ++i)
	{
		res += (0 == HeapPush(heap , &arr[i]));
		res += (0 == HeapPush(heap2 , &arr[i]));
	}

	res += (HeapSize(heap) == 200);

	for(i =0; i<200; ++i)
	{	
		res += (*(int*)HeapPeek(heap) == *(int*)PQPeek(q));
		PQDequeue(q);
		HeapPop(heap);
		res += (arr[i] == *(int*)HeapRemove(heap2, &arr[i], MachFuncInt, NULL));
		
	}

	res += (HeapSize(heap) == 0);
	res += (1 == HeapIsEmpty(heap));
	
	PQDestroy(q);
	HeapDestroy(heap);
	HeapDestroy(heap2);

	return (res == 803);
}


int main()
{
	RUN_TEST(TestBase(), "max base");
	RUN_TEST(TestMinHeap(), "min base");
	RUN_TEST(TestAll(), "test random values");
	return 0;
}*/
/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_heap_sort.c
*	author: Yoni Ladijensky
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <stdlib.h>

#include "heap.h"
#include "priority_queue.h"

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
        
#define SIZE 173   

enum successful {SUCCEED, FAILED};
enum matching {NO, YES};
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	
typedef struct point
{
	long x;
	long y;
} point_t;
	
int CmpFuncInt(const void *one, const void *other);
int MachFuncInt(const void *one, const void *other, void *params);

int CmpFuncStruct(const void *one, const void *other);
int MachFuncStructY(const void *one, const void *other, void *params);

int TestInt();
int TestStruct();


int main()
{
	RUN_TEST(TestInt(), "TestInt");
	RUN_TEST(TestStruct(), "TestStruct");

	return 0;
}

int TestStruct()
{
	heap_t *heap = HeapCreate(CmpFuncStruct);
	int x = 0;
	point_t a = {1,1};
	point_t b = {2,2};
	point_t c = {3,3};
	point_t d = {4,4};
	point_t big = {100,100};
	point_t bigger = {1000,1000}; 
	
	x += (NULL != heap);
	
	x += (YES == HeapIsEmpty(heap));
	x += (0 == HeapSize(heap));
	
	x += (0 == HeapPush(heap, &a));
	x += (0 == HeapPush(heap, &b));
	x += (0 == HeapPush(heap, &c));
	x += (0 == HeapPush(heap, &d));
	
	x += (0 == HeapIsEmpty(heap));
	x += (4 == HeapSize(heap));
	
	x += (2 == (*(point_t*)HeapRemove(heap, &b, MachFuncStructY, NULL)).y);
	
	x += (0 == HeapPush(heap, &bigger));
	x += (0 == HeapPush(heap, &big));
	
	x += (NO == HeapIsEmpty(heap));
	x += (5 == HeapSize(heap));
	
	x += (1000 == (*(point_t*)HeapRemove(heap, &bigger, MachFuncStructY, NULL)).y);
	
	x += (NULL == HeapRemove(heap, &bigger, MachFuncStructY, NULL));
	
	while (YES != HeapIsEmpty(heap))
	{
		printf("x = %ld, y = %ld\n", (*(point_t*)HeapPeek(heap)).x,
												(*(point_t*)HeapPeek(heap)).y);
		HeapPop(heap);
	}
	
	HeapDestroy(heap);
	return (16 == x);
}

int TestInt()
{
	heap_t *heap = HeapCreate(CmpFuncInt);
	int x = 0;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int big = 100;
	int bigger = 1000; 
	
	x += (NULL != heap);
	
	x += (YES == HeapIsEmpty(heap));
	x += (0 == HeapSize(heap));
	
	x += (0 == HeapPush(heap, &a));
	x += (0 == HeapPush(heap, &b));
	x += (0 == HeapPush(heap, &c));
	x += (0 == HeapPush(heap, &d));
	
	x += (0 == HeapIsEmpty(heap));
	x += (4 == HeapSize(heap));
	
	x += (2 == *(int*)HeapRemove(heap, &b, MachFuncInt, NULL));
	
	x += (0 == HeapPush(heap, &bigger));
	x += (0 == HeapPush(heap, &big));
	
	x += (NO == HeapIsEmpty(heap));
	x += (5 == HeapSize(heap));
	
	x += (1000 == *(int*)HeapRemove(heap, &bigger, MachFuncInt, NULL));
	
	x += (NULL == HeapRemove(heap, &bigger, MachFuncInt, NULL));
	
	while (YES != HeapIsEmpty(heap))
	{
		printf("%d\n", *(int*)HeapPeek(heap));
		HeapPop(heap);
	}
	
	HeapDestroy(heap);
	return (16 == x);
}

/******************************************************************************/

int CmpFuncStruct(const void *one, const void *other)
{
	point_t *test = (point_t *)one;
	point_t *test2 = (point_t *)other;
	return (test2->x - test->x);
}

int MachFuncStructY(const void *one, const void *other, void *params)
{
	point_t *test = (point_t *)one;
	point_t *test2 = (point_t *)other;

	(void)params;
	return (test2->y == test->y);
}


int MachFuncStruct(const void *one, const void *other, void *params)
{
	(void)params;
	return (*(int*)other == *(int*)one);
}

int CmpFuncInt(const void *one, const void *other)
{
	return (*(int*)other - *(int*)one);

}

int MachFuncInt(const void *one, const void *other, void *params)
{
	(void)params;
	return (*(int*)other == *(int*)one);
}

/*****************************************************************************/


