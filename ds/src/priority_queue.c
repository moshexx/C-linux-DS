/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: priority_queue.c
*	author: Moshe Cohen
*	reviewer: Topaz

--------------------------------------------------------------------------------
*******************************************************************************/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert */

#include "priority_queue.h"

#define _PRIORITY_QUEUE_WITH_SORTED_LIST_

enum status{FALSE, TRUE};

#ifdef heap_based /* <--- compilation line: make EXTRA=-Dheap_based */
#include "heap.h"
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~ definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct p_queue
{
    heap_t *heap;
};

struct combination
{/* use for adapting 'is_match'(HeapRemove) function to 'is_criter_match' */
    size_t n;
    is_criter_match_t is_criter_match;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~ Static function declaration ~~~~~~~~~~~~~*/

static int IsMatchWrapper(const void *lhs, const void *rhs, void *params);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

pq_t *PQCreate(prior_func_t prior_func)
{
    pq_t *p_queue = NULL;

    assert(NULL != prior_func);

    p_queue = (pq_t *)malloc(sizeof(pq_t));
    if (NULL == p_queue)
    {
        return NULL;
    }

    p_queue->heap = HeapCreate(prior_func);
    if (NULL == p_queue->heap)
    {
        free (p_queue); p_queue = NULL;
        return NULL;
    }

    return p_queue;
}

void PQDestroy(pq_t *p_queue)
{
    assert(NULL != p_queue);

    HeapDestroy(p_queue->heap);
    free(p_queue); p_queue = NULL;
}

int PQIsEmpty(const pq_t *p_queue)
{
    assert(NULL != p_queue);

    return(HeapIsEmpty(p_queue->heap));
}

int PQEnqueue(pq_t *p_queue, const void *data)
{
    assert(NULL != p_queue);

    return(HeapPush(p_queue->heap, data));
}

void PQDequeue(pq_t *p_queue)
{
    assert(NULL != p_queue);
    assert(!PQIsEmpty(p_queue));

    HeapPop(p_queue->heap);
}

void *PQPeek(const pq_t *p_queue)
{
    assert(NULL != p_queue);
    assert(!PQIsEmpty(p_queue));

    return (HeapPeek(p_queue->heap));
}

size_t PQSize(const pq_t *p_queue)
{
    assert(NULL != p_queue);

    return (HeapSize(p_queue->heap));
}

void PQFlush(pq_t *p_queue)
{
    assert(NULL != p_queue);

    while (!PQIsEmpty(p_queue))
    {
        PQDequeue(p_queue);
    }
}

void *PQErase(pq_t *p_queue, is_criter_match_t is_criter_match,
                                    const void *data, size_t n)
{
    struct combination adapter;
    adapter.n = n;
    adapter.is_criter_match = is_criter_match;

    assert(NULL != p_queue);
    assert(NULL != data);
    assert(NULL != is_criter_match);

    return HeapRemove(p_queue->heap, (void *)data, IsMatchWrapper, &adapter);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Static Function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static int IsMatchWrapper(const void *lhs, const void *rhs, void *params)
{
    struct combination *tmp = (struct combination *)params;

    return (tmp->is_criter_match(lhs, rhs, tmp->n));
}

/*#endif*/ /* _PRIORITY_QUEUE_WITH_HEAP_ */


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#else /* default compilation */
#include "sorted_linked_list.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct p_queue
{
sol_t *solist;
};
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

pq_t *PQCreate(prior_func_t prior_func)
{
    pq_t *p_queue = NULL;

    assert(NULL != prior_func);

    p_queue = (pq_t *)malloc(sizeof(pq_t));
    if (NULL == p_queue)
    {
        printf("allocation faild\n");
        return NULL;
    }

    p_queue->solist = SortedListCreate(prior_func);
    if (NULL == p_queue->solist)
    {
        free (p_queue); p_queue = NULL;
        printf("allocation faild\n");
        return NULL;
    }

    return p_queue;
}

void PQDestroy(pq_t *p_queue)
{
    assert(NULL != p_queue);

    SortedListDestroy(p_queue->solist);
    free(p_queue); p_queue = NULL;
}

int PQIsEmpty(const pq_t *p_queue)
{
    assert(NULL != p_queue);

    return(SortedListIsEmpty(p_queue->solist));
}

int PQEnqueue(pq_t *p_queue, const void *data)
{
    assert(NULL != p_queue);

    return(SortedListInsert(p_queue->solist, data));
}

void PQDequeue(pq_t *p_queue)
{
    assert(NULL != p_queue);
    assert(!SortedListIsEmpty(p_queue->solist));

    SortedListPopFront(p_queue->solist);
}

void *PQPeek(const pq_t *p_queue)
{
    assert(NULL != p_queue);
    assert(!PQIsEmpty(p_queue));

    return SortedListGetData(SortedListBegin(p_queue->solist));
}

size_t PQSize(const pq_t *p_queue)
{
    assert(NULL != p_queue);

    return (SortedListSize(p_queue->solist));
}

void PQFlush(pq_t *p_queue)
{
    assert(NULL != p_queue);
    /*assert(!PQIsEmpty(p_queue));*/

    while (!PQIsEmpty(p_queue))
    {
        PQDequeue(p_queue);
    }
}

void *PQErase(pq_t *p_queue, is_criter_match_t is_criter_match, const void *data, size_t n)
{
    sol_iter_t tmp = NULL;
    void *cpy_data = NULL;

    tmp = SortedListFindIf(SortedListBegin(p_queue->solist),
                SortedListEnd(p_queue->solist), is_criter_match, data, n);

    if (FALSE == SortedListIsSameIter(SortedListEnd(p_queue->solist), tmp))
    {
        cpy_data = SortedListGetData(tmp);
        SortedListRemove(tmp);
    }

    return cpy_data;
}

#endif 
