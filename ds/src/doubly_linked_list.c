/*******************************************************************************
*
*	Worksheet:    doubly_linked_list.c
*
*	Author:       Moshe Cohen
*	Reviewer:     Lidor Cohen
*	Date:         5.11.2020
*   Did you know? printf allocate 1024 Bytes and free them !!!  2^10
*******************************************************************************/
#include <stdlib.h> /* size_t, malloc, free */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */

#include "doubly_linked_list.h"
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Admin~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

enum result_t{ FALSE = 0, TRUE = 1 };
enum status_t{ SUCCESS = 0, FAILURE = 1};

struct node
{
    void *data;
    node_t *next;
    node_t *prev;
};

struct doubly_linked_list
{
    node_t head;
    node_t tail;
};
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Help Functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static int DlCreatIter(dl_iter_t next, dl_iter_t prev, const void *data);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

dl_t *DListCreate(void)
{
    dl_t *dlist = (dl_t *)malloc(sizeof(dl_t));
    if(NULL == dlist)
    {
        printf("Memory allocation failured\n");
        return NULL;
    }

    dlist->tail.data = NULL;
    dlist->tail.next = NULL;
    dlist->tail.prev = &dlist->head;

    dlist->head.data = NULL;
    dlist->head.prev = NULL;
    dlist->head.next = &dlist->tail;

    return dlist;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void DListDestroy(dl_t *dlist)
{
    assert(NULL != dlist);

    while (!DListIsEmpty(dlist))
    {
        DListRemove(DListBegin(dlist));
    }

    free(dlist);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int DListIsEmpty(const dl_t *dlist)
{
    assert(NULL != dlist);

    return (DListBegin(dlist) == DListEnd(dlist));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* next time- use foreach */
size_t DListSize(const dl_t *dlist)
{
    size_t count = 0;
    dl_iter_t runner = NULL;

    assert(NULL != dlist);

    runner = DListBegin(dlist);
    while (runner->next != NULL)
    {
        runner = runner->next;
        ++count;
    }

    return count;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
dl_iter_t DListBegin(const dl_t *dlist)
{
    assert(NULL != dlist);

    return(dlist->head.next);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
dl_iter_t DListEnd(const dl_t *dlist)
{
    assert(NULL != dlist);

    return ((dl_iter_t)&dlist->tail);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
dl_iter_t DListNext(const dl_iter_t current)
{
    assert(NULL != current);
    assert(NULL != current->next); /* tail */


    return(current->next);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
dl_iter_t DListPrev(const dl_iter_t current)
{
    assert(NULL != current);
    assert(NULL != current->prev); /* head */

    return(current->prev);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int DListIsSameIter(const dl_iter_t one, const dl_iter_t other)
{
    return (one == other);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void *DListGetData(const dl_iter_t iter)
{
    assert(NULL != iter);
    assert(NULL != iter->next); /* tail */
    assert(NULL != iter->prev); /* head */

    return(iter->data);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void DListSetData(dl_iter_t iter,const void *data)
{
    assert(NULL != iter);
    assert(NULL != iter->next); /* tail */
    assert(NULL != iter->prev); /* head */

    iter->data = (void *)data;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static int DlCreatIter(dl_iter_t next, dl_iter_t prev, const void *data)
{
    dl_iter_t iter = (dl_iter_t)malloc(sizeof(node_t));
    if(NULL == iter)
    {
        printf("Memory allocation failured\n");
        return FAILURE;
    }
    iter->data = (void *)data;
    iter->next = next;
    iter->prev = prev;
    next->prev = iter;
    prev->next = iter;

    return SUCCESS;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int DListInsertBefore(dl_iter_t iter, const void *data)
{
    assert(NULL != iter);

    return(DlCreatIter(iter, iter->prev, data));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void DListRemove(dl_iter_t iter)
{
    assert(NULL != iter);
    assert(NULL != iter->next); /* tail */
    assert(NULL != iter->prev); /* head */

    iter->prev->next = iter->next;
    iter->next->prev = iter->prev;

    free(iter); iter = NULL;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int DListPushFront(dl_t *dlist, const void *new_data)
{
    assert(NULL != dlist);

    return(DListInsertBefore(DListBegin(dlist), new_data));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int DListPushBack(dl_t *dlist, const void *new_data)
{
    assert(NULL != dlist);

    return(DListInsertBefore(DListEnd(dlist), new_data));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void DListPopFront(dl_t *dlist)
{
    assert(NULL != dlist);
    assert(!DListIsEmpty(dlist));

    DListRemove(DListBegin(dlist));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void DListPopBack(dl_t *dlist)
{
    assert(NULL != dlist);
    assert(!DListIsEmpty(dlist));

    DListRemove(DListEnd(dlist)->prev);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
dl_iter_t DListFind(const dl_iter_t from, const dl_iter_t to,
							is_match_t is_match, const void *data, size_t n)
{
    dl_iter_t runner = NULL;

    assert(NULL != to);
    assert(NULL != from);

    runner = from;
    while (runner != to && TRUE != is_match(runner->data, data, n))
    {
        runner = runner->next;
    }
    /* if didn't find - return 'to' */
    return runner;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int DListForEach(dl_iter_t from, const dl_iter_t to,
											act_func_t act_func, void *params)
{
    int status = 0;

    assert(NULL != to);
    assert(NULL != from);

    while (from != to && from->next != NULL)
    {
        status = act_func((void *)from->data, params);
        if(FAILURE == status)
        {
            printf("act_func failed \n");
            return FAILURE;
        }
        from = from->next;
    }

    return SUCCESS;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* To do InsertBefore dest_iter to the new list */
void DListSplice(dl_iter_t dest_iter, dl_iter_t src_from,
													const dl_iter_t src_to)
{
    dl_iter_t src_from_prev = NULL;

    assert(NULL != dest_iter);
    assert(NULL != src_from);
    assert(NULL != src_to);

    if (src_from == src_to)
    {
        return;
    }

    /*comments can't help - go the whiteboard. right upper corner */
    src_from_prev = src_from->prev;

    src_from->prev = dest_iter->prev;
    dest_iter->prev->next = src_from;

    src_to->prev->next = dest_iter;
    dest_iter->prev = src_to->prev;

    src_from_prev->next = src_to;
    src_to->prev = src_from_prev;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int DListMultFind(const dl_iter_t from, const dl_iter_t to,
				is_match_t is_match, const void *data, size_t n, dl_t *dlist)
{
    int fstop = 0;
    dl_iter_t runner = NULL;

    assert(NULL != dlist);
    assert(NULL != to);
    assert(NULL != from);

    for (runner = from; runner != to && !fstop; runner = runner->next)
    {
        if (TRUE == is_match(runner->data, data, n))
        {
            fstop = DListPushBack(dlist, runner->data);
        }
    }
    /* SUCCESS or FAILURE */
    return fstop;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
