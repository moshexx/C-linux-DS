/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_sorted_linked_list.c
*	author: Moshe Cohen
*	reviewer: Adi Cohen

--------------------------------------------------------------------------------
*******************************************************************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <stdlib.h>
#include <string.h> /* memcpy */

#include "sorted_linked_list.h"

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
enum matching {NO, YES};

struct sorted_list /* sol_t */
{
cmp_func_t cmp_func;
dl_t *dlist;
};

struct node
{
void *data;
node_t *next;
node_t *prev;
};
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Aid Functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int MemCmp(const void *one, const void *other);
int PrintNode(void *data, void *params);
void PrintAll(dl_t *dl);
int AddNum(void *data, void *params);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~main~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main()
{
    int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 12, 5, 4, 3, 2, 1, 0};
    int n = 1;
    int n2 = -1;
    sol_t *solist = NULL;
    sol_t *solist2 = NULL;
    dl_iter_t iter = NULL;
    dl_iter_t iter2 = NULL;
    dl_iter_t from = NULL;
    dl_iter_t to = NULL;
    size_t i = 0;

    solist = SortedListCreate(MemCmp);
    RUN_TEST(NULL != solist, "Create SortedList");

    RUN_TEST(1 == SortedListIsEmpty(solist), "Is empty (empty list)");
	RUN_TEST(0 == SortedListSize(solist), "Size (empty list)");
    RUN_TEST(0 == SortedListInsert(solist, data + 2), "First insert");
    RUN_TEST(1 == SortedListSize(solist), "Size after first insert");
    RUN_TEST(0 == SortedListInsert(solist, data + 5), "Second insert");
    RUN_TEST(2 == SortedListSize(solist), "Size after second insert");

    iter = SortedListBegin(solist);
    RUN_TEST(data + 2 == SortedListGetData(iter), "Get data of Begin");
    iter2 = SortedListEnd(solist);
    iter2 = SortedListPrev(iter2);
    RUN_TEST(data + 5 == SortedListGetData(iter2), "Get data of Prev(End)");
    RUN_TEST(0 == SortedListIsSameIter(iter, iter2), "(Not) same iter");
    SortedListInsert(solist, data + 1);
    printf("After Insert:\n1 -> 2 -> 5 -> NULL:(original)\n");
    PrintAll(solist->dlist); /* 1 -> 2 ->5 -> NULL*/
    SortedListPopBack(solist);
    printf("After PopBac:\n1 -> 2 -> NULL:(original\n");
    PrintAll(solist->dlist); /* 1 -> 2 -> NULL*/
    SortedListPopFront(solist);
    printf("After PopFront:\n2 -> NULL:(original\n");
    PrintAll(solist->dlist); /* 2 -> NULL*/
    RUN_TEST(0 == SortedListIsEmpty(solist), "Is empty (not empty)");
    iter = SortedListBegin(solist);
	SortedListRemove(iter);
    RUN_TEST(1 == SortedListIsEmpty(solist), "Remove");

    for (i = 9; i > 0; --i)
	{
		SortedListInsert(solist, data + i);
	}
    iter = SortedListBegin(solist);
	iter = SortedListNext(iter);
	iter = SortedListNext(iter);
	RUN_TEST(data + 3 == SortedListGetData(iter), "Get Data");
    PrintAll(solist->dlist); /* 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> NULL */

    from = SortedListBegin(solist);
    to = SortedListEnd(solist);
    RUN_TEST(0 == SortedListForEach(from, to, AddNum, &n), "For Each");
    printf("After SortedListForEach + 1:\n");
    PrintAll(solist->dlist); /* 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> NULL */

    SortedListDestroy(solist);

    solist = SortedListCreate(MemCmp);
    for (i = 9; i > 0; --i)
	{
		SortedListInsert(solist, data + i);
	}
    printf("After reCreate:\n"); /* 2 -> 3 -> 4 -> 5... */
    PrintAll(solist->dlist);
    from = SortedListBegin(solist);
    to = SortedListEnd(solist);
    RUN_TEST(0 == SortedListForEach(from, to, AddNum, &n2), "For Each2");
    printf("After SortedListForEach - 1:\n"); /* 1 -> 2 -> 3 -> 4 -> 5... */
    PrintAll(solist->dlist);

    iter = SortedListFind(solist, from, to, data + 4);
    printf("data + 4 = %d\n", data[4]);
    PrintNode(SortedListGetData(iter), NULL);
    RUN_TEST(data + 4 == SortedListGetData(iter), "Find (regular)1");

    from = SortedListBegin(solist);
    to = SortedListEnd(solist);
    iter2 = SortedListFind(solist, from, to, data + 12); /* not find */
    RUN_TEST(iter2 == SortedListEnd(solist), "Find (no match)2");

    solist2 = SortedListCreate(MemCmp);
    for (i = 15; i > 7; --i)
	{
		SortedListInsert(solist2, data + i);
	}
    printf("\ndest before Merge: \n");
    PrintAll(solist->dlist);
    printf("\nsrc before Merge: \n");
    PrintAll(solist2->dlist);

    SortedListMerge(solist, solist2);

    printf("\ndest after Merge:\n");
    PrintAll(solist->dlist);

    printf("\nsrc after Merge:\n");
    PrintAll(solist2->dlist);

    SortedListDestroy(solist);
    SortedListDestroy(solist2);
    return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Aid Functions Implementaion~~~~~~~~~~~~~~~~~~~*/
int MemCmp(const void *one, const void *other)
{
	return (memcmp(one, other, sizeof(int)));
}

int PrintNode(void *data, void *params)
{
    (void)params;
    printf("%d -> ", *(int *)data);
    return 0;
}

void PrintAll(dl_t *dl)
{
    dl_iter_t begin = DListBegin(dl);
    dl_iter_t end = DListEnd(dl);

    DListForEach(begin, end, PrintNode, NULL);

    printf("NULL\n");
}

int AddNum(void *data, void *params)
{
    *((int *)data) += *((int *)params);

    return 0;
}

/*
void SortedListMerge(sol_t *dest, sol_t *src)
{
    sol_iter_t current = NULL;

    assert(NULL != src);
    assert(NULL != dest);

    while (!SortedListIsEmpty(src))
    {
        current = SortedListBegin(src);
        SortedListInsert(dest, SortedListGetData(current));
        SortedListRemove(current);
    }
}
*/
