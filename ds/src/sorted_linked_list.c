/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: sorted_linked_list.c
*	author: Moshe Cohen
*	reviewer: Adi Cohen

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> /* assert */

#include "sorted_linked_list.h"
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

sol_t *SortedListCreate(cmp_func_t cmp_func)
{
    sol_t *solist = NULL;

    assert(NULL != cmp_func);

    solist = (sol_t *)malloc(sizeof(sol_t));
    if(NULL == solist)
    {
        printf("Memory allocation failured(solist)\n");
        return NULL;
    }

    solist->cmp_func = cmp_func;
    solist->dlist = DListCreate();
    if(NULL == solist->dlist)
    {
        free (solist); solist = NULL;
        printf("Memory allocation failured(dlist)\n");
        return NULL;
    }

    return solist;
}
/******************************************************************************/
void SortedListDestroy(sol_t *solist)
{
    assert(NULL != solist);

    DListDestroy(solist->dlist); solist->dlist = NULL;
    free(solist); solist = NULL;
}
/******************************************************************************/
int SortedListIsEmpty(const sol_t *solist)
{
    assert(NULL != solist);

    return (DListIsEmpty(solist->dlist));
}
/******************************************************************************/
size_t SortedListSize(const sol_t *solist)
{
    assert(NULL != solist);

    return DListSize((void *)solist->dlist);
}
/******************************************************************************/
sol_iter_t SortedListBegin(const sol_t *solist)
{
    assert(NULL != solist);

    return(DListBegin(solist->dlist));
}
/******************************************************************************/
sol_iter_t SortedListEnd(const sol_t *solist)
{
    assert(NULL != solist);

    return (DListEnd(solist->dlist));
}
/******************************************************************************/
sol_iter_t SortedListNext(const sol_iter_t current)
{
    assert(NULL != current);

    return(DListNext(current));
}
/******************************************************************************/
sol_iter_t SortedListPrev(const sol_iter_t current)
{
    assert(NULL != current->prev); /* head */

    return (DListPrev(current));
}
/******************************************************************************/
int SortedListIsSameIter(const sol_iter_t one, const sol_iter_t other)
{
    assert(NULL != one);
    assert(NULL != other);

    return (one == other);
}
/******************************************************************************/
void *SortedListGetData(const sol_iter_t iter)
{
    assert(NULL != iter);
    assert(NULL != DListNext(iter));

    return(DListGetData(iter));
}
/*******insert = o(n) in sorted (unlike regular list = o(1))*******************/
int SortedListInsert(sol_t *solist, const void *data)
{
    sol_iter_t runner = NULL;

    assert(NULL != solist);

    runner = SortedListBegin(solist);
    while (SortedListEnd(solist) != runner)
    {
        if (0 < solist->cmp_func(DListGetData(runner), data)) /* data < runner */
        {
            break;
        }
        runner = SortedListNext(runner);
    }

    return DListInsertBefore(runner, data);
}
/******************************************************************************/
void SortedListRemove(sol_iter_t iter)
{
    assert(NULL != iter);
    assert(NULL != iter->next); /* tail */
    assert(NULL != iter->prev); /* head */

    DListRemove(iter);
}
/******************************************************************************/
void SortedListPopFront(sol_t *solist)
{
    assert(NULL != solist);
    assert(!SortedListIsEmpty(solist));

    SortedListRemove(SortedListBegin(solist));
}
/******************************************************************************/
void SortedListPopBack(sol_t *solist)
{
    assert(NULL != solist);
    assert(!SortedListIsEmpty(solist));

    DListPopBack(solist->dlist);
}
/******************************************************************************/
int SortedListForEach(sol_iter_t from, const sol_iter_t to,
						oper_func_t oper_func, void *params)
{
    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != oper_func);

    return (DListForEach(from, to, oper_func, params));
}
/******************************************************************************/
sol_iter_t SortedListFind(sol_t *solist, const sol_iter_t from,
                        const sol_iter_t to, const void *data)
{
    sol_iter_t runner = NULL;

    assert(NULL != solist);
    assert(NULL != from);
    assert(NULL != to);

    runner = from;
    while (SortedListEnd(solist) != runner
                        && to != runner &&
                        0 >= solist->cmp_func(SortedListGetData(runner), data))
    {
        if (0 == solist->cmp_func(SortedListGetData(runner), data))
        {
            break;
        }
        runner = SortedListNext(runner);
    }

    return runner;
}
/******************************************************************************/
sol_iter_t SortedListFindIf(const sol_iter_t from, const sol_iter_t to,
			 criter_match_t criter_match, const void *params, size_t n)
{
    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != criter_match);

    return (DListFind(from, to, criter_match, params, n));
}
/******************************************************************************/
void SortedListMerge(sol_t *dest, sol_t *src)
{
    sol_iter_t dest_runner = NULL;

    assert(NULL != src);
    assert(NULL != dest);
    assert(src != dest);
    assert(dest->cmp_func == src->cmp_func);

    dest_runner = SortedListBegin(dest);

    while (!SortedListIsEmpty(src) && SortedListEnd(dest) != dest_runner)
    {
        if (0 < dest->cmp_func(DListGetData(dest_runner),
                            DListGetData(SortedListBegin(src))))
        {
            DListSplice(dest_runner, (SortedListBegin(src)),
                        SortedListNext(SortedListBegin(src)));
        }
        else
        {
            dest_runner = SortedListNext(dest_runner);
        }
    }
    /* Adding up the rest of src (if existing) */
    DListSplice(SortedListEnd(dest), SortedListBegin(src), SortedListEnd(src));
}
/******************************************************************************/
