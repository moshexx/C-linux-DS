#include "heap.h"
#include <stdio.h>


#include "dynamic_vector.h"


struct heap
{
	cmp_t cmp;
	dvector_t *dvector;
};


#define SIZE 12
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


int data[SIZE] = {0,2,11,66,8,44,200,5,6,150,162,3};


void PrintVector(dvector_t *dvector)
{
    size_t i = 1;

    printf("~~~~~~~~~DVector~~~~~~~~~:\n\n");
    for (i = 0; i < DVectorSize(dvector); i++)
    {
        printf("ARR[%lu] = %d\n", i,*(int *)*(void **)DVectorAccessElement(dvector, i));
    }
    printf("\n\n");
}

int CmpIntMax(const void *lhs, const void *rhs)
{
    return *(int *)rhs - *(int *)lhs;

}
int CmpIntMin(const void *lhs, const void *rhs)
{
    return *(int *)lhs - *(int *)rhs;

}

int TestPush(heap_t *heap)
{
    size_t i;
    size_t res = 0;

    res += HeapIsEmpty(heap) == 1;
    for (i = 0; i < SIZE ; ++i)
    {
	HeapPush(heap,data + i);
	res += HeapSize(heap) == i + 1;
    }
    res += *(int *)HeapPeek(heap) == 200;

	/*PrintVector(heap->dvector);*/

    return res == SIZE + 2;
}


int TestPop(heap_t *heap)
{
    size_t res = 0;
    HeapPop(heap);
    res += *(int *)HeapPeek(heap) == 162;
    HeapPop(heap);
    res += *(int *)HeapPeek(heap) == 150;
    HeapPop(heap);
    res += *(int *)HeapPeek(heap) == 66;
    HeapPop(heap);
    res += *(int *)HeapPeek(heap) == 44;
    HeapPop(heap);
    res += *(int *)HeapPeek(heap) == 11;

    res += HeapSize(heap) == 7;
		/*PrintVector(heap->dvector);*/
    return res == 6;
}


int Match(const void* lhs, const void *rhs, void *params)
{
	(void)params;
    return *(int *)lhs == *(int *)rhs;
}





int TestInt2()
{
    heap_t *heap = HeapCreate(CmpIntMax);
    int x = 0;
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    size_t i = 0;


    x += (1 == HeapIsEmpty(heap));
    x += (0 == HeapSize(heap));

    for (i = 0; i < 20; ++i)
    {
        x += (0 == HeapPush(heap, &arr[i]));
    }
    x += (5 == *(int*)HeapRemove(heap, &arr[4], Match, NULL));

    x += (11 == *(int*)HeapRemove(heap, &arr[10], Match, NULL));

    while (1 != HeapIsEmpty(heap))
    {
        HeapPop(heap);
    }

    HeapDestroy(heap);
    return (24 == x);
}




int TestRemove(heap_t *heap)
{
    size_t res = 0;
    int params =10;
    int a2 = 2;
    int a100 = 100;
    int a11 = 11;
    int a8 = 8;
    void * data = HeapRemove(heap,&a2,Match,&params);

    res += *(int *)data == 2;

    data = HeapRemove(heap,&a100,Match,&params);
    res += data == NULL;

    data = HeapRemove(heap,&a11,Match,&params);

    res += *(int *)data == 11;

    data = HeapRemove(heap,&a8,Match,&params);

    res += *(int *)data == 8;

    res += *(int *)HeapPeek(heap) == 6;
printf("data: %d\n", *(int *)HeapPeek(heap));
PrintVector(heap->dvector);
    return res == 5;

}




int main()
{
    heap_t *heap = HeapCreate(CmpIntMax);
    RUN_TEST(TestPush(heap),"TestPush");
    RUN_TEST(TestPop(heap),"TestPop");
    RUN_TEST(TestRemove(heap),"TestRemove");
    HeapDestroy(heap);
    RUN_TEST(TestInt2(),"Testint2");

    return 0;
}
