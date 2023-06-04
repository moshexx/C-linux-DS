/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_heap.c
*	author: Moshe Cohen
*	reviewer: Roy Chen

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <stdlib.h>

#include "heap.h"
#include "dynamic_vector.h"

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

struct heap
{
	cmp_t cmp;
	dvector_t *dvector;
};

enum successful {SUCCESS, FAILURE};
enum matching {NO, YES};
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ functions declerations ~~~~~~~~~~~~~~~~~*/

int BasicTest(void);
void PrintVector(dvector_t *dvector);
int IntCmp(const void *low, const void *high); /* for HeapCreate */
int IsMatchInt(const void *lhs, const void *rhs, void *params);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main()
{
    RUN_TEST(SUCCESS == BasicTest(), "BasicTest");


	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int BasicTest(void)
{
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    int f = 6;
    int g = 7;
    int moshe = 5;
    int cohen;

    heap_t *heap = HeapCreate(IntCmp);
    if (NULL == heap)
    {
        return FAILURE;
    }
    printf("\n");
    RUN_TEST(0 == HeapSize(heap), "Size(empty)");
    RUN_TEST(1 == HeapIsEmpty(heap), "IsEmpty(empty)");


    HeapPush(heap, &a);
    HeapPush(heap, &b);
    HeapPush(heap, &c);
    HeapPush(heap, &d);
    HeapPush(heap, &e);
    HeapPush(heap, &f);
    HeapPush(heap, &g);
    PrintVector(heap->dvector);

    HeapPop(heap);
    HeapPop(heap);
    HeapPop(heap);
    PrintVector(heap->dvector);

    HeapPush(heap, &f);
    HeapPush(heap, &e);
    HeapPush(heap, &d);
    HeapPush(heap, &a);
    HeapPush(heap, &b);
    HeapPush(heap, &c);
    HeapPush(heap, &d);
    HeapPop(heap);
    HeapPop(heap);
    HeapPush(heap, &e);
    HeapPush(heap, &f);
    HeapPush(heap, &g);
    HeapPop(heap);
    HeapPop(heap);
    HeapPop(heap);
    HeapPush(heap, &g);
    PrintVector(heap->dvector);
    RUN_TEST(10 == HeapSize(heap), "Size");
    RUN_TEST(0 == HeapIsEmpty(heap), "IsEmpty(Not empty)");

    RUN_TEST(4 == *(int *)HeapPeek(heap), "HeapPeek");

    cohen = *(int *)HeapRemove(heap, &moshe,IsMatchInt, NULL);
    RUN_TEST(cohen == moshe, "return value HeapRemove");


    RUN_TEST(9 == HeapSize(heap), "Size after HeapRemove");
    PrintVector(heap->dvector);


    HeapDestroy(heap);
    (void)moshe;

    return SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Helper functions ~~~~~~~~~~~~~~~~~~*/

/* for data = int** */
void PrintVector(dvector_t *dvector)
{
    size_t i = 1;

    printf("~~~~~~~~~DVector~~~~~~~~~:\n\n");
    for (i = 0; i < DVectorSize(dvector); i++)
    {
        printf("ARR[%lu] = %d\n", i, **(int **)DVectorAccessElement(dvector, i));
    }
    printf("\n\n");
}

int IntCmp(const void *low, const void *high)
{
    /*return (*(int *)low - *(int *)high);*/
    return (*(int *)low < *(int *)high) ? -1 : (*(int *)high < *(int *)low);
}

int IsMatchInt(const void* lhs, const void *rhs, void *params)
{
    (void)params;
    return (*(int *)lhs - *(int *)rhs == 0);
}
