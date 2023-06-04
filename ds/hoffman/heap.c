/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: heap.c
*	author: Moshe Cohen
*	reviewer: Roy Chen

--------------------------------------------------------------------------------
*******************************************************************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert */

#include "heap.h"
#include "dynamic_vector.h"

#define CAPACITY 100
#define ARR(index) ((void **)DVectorAccessElement(heap->dvector, index))
#define PARENT(index) (ARR((index - 1) / 2))
#define CHILD_L(index) (ARR(index * 2 + 1))
#define CHILD_R(index) (ARR(index * 2 + 2))
#define I_LEFT(index) (2 * index + 1)
#define I_RIGHT(index) (2 * index + 2)
#define PARENT_INDEX(index) ((index - 1) / 2)
#define LAST_INDEX (DVectorSize(heap->dvector) - 1)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct heap
{
	cmp_t cmp;
	dvector_t *dvector;
};

enum successful {SUCCESS, FAILURE};
enum status_t {FALSE = 0, TRUE = 1};
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Helper functions declerations ~~~~~~~~~~~~~~~~~*/

static void SwapPtr(void **first, void **second);
static void HeapifyUp(heap_t *heap, size_t index);
static void HeapifyDown(heap_t *heap, size_t index);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ API functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

heap_t *HeapCreate(cmp_t cmp)
{
    heap_t *heap = NULL;

    assert(NULL != cmp);

    heap = (heap_t *)malloc(sizeof(heap_t));
    if (NULL == heap)
    {
        return NULL;
    }

    heap->cmp = cmp;
    heap->dvector = DVectorCreate(CAPACITY, sizeof(void **));
    if (NULL == heap->dvector)
    {
		free(heap); heap = NULL;
        return NULL;
    }

    return heap;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void HeapDestroy(heap_t *heap)
{
    assert(NULL != heap);

    DVectorDestroy(heap->dvector);
    free(heap); heap = NULL;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int HeapPush(heap_t *heap, const void *data)
{
	dvector_t *backup_for_dvector = NULL;

    assert(NULL != heap);
    assert(NULL != data);

	/* recapacity may occur. recapacity can fail */
	backup_for_dvector = heap->dvector;
	heap->dvector = DVectorPushBack(heap->dvector, (void *)&data);
    if (NULL == heap->dvector)
    {
		heap->dvector = backup_for_dvector;
        return FAILURE;
    }
					/* index = size - 1 */
	HeapifyUp(heap, LAST_INDEX);

    return SUCCESS;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void HeapPop(heap_t *heap)
{
	dvector_t *backup_for_dvector = NULL;

    assert(NULL != heap);

	/* Swap root with the last element in dvector */
	SwapPtr(ARR(0), ARR(LAST_INDEX));

	backup_for_dvector = heap->dvector;
	/* Pop the 'old root' - which stored now in the last place of dvector */
	heap->dvector = DVectorPopBack(heap->dvector);
	if (NULL == heap->dvector)
    {
		heap->dvector = backup_for_dvector;
    }

	if (!HeapIsEmpty(heap))
	{
		HeapifyDown(heap, 0);
	}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void *HeapPeek(const heap_t *heap)
{
    assert(NULL != heap);

    return (*(void **)DVectorAccessElement(heap->dvector, 0));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

size_t HeapSize(const heap_t *heap)
{
    assert(NULL != heap);

    return (DVectorSize(heap->dvector));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int HeapIsEmpty(const heap_t *heap)
{
    assert(NULL != heap);

    return (0 == DVectorSize(heap->dvector));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void *HeapRemove(heap_t *heap, void *data,
                int (*is_match)(const void* lhs, const void *rhs, void *params),
                void *params)
{
	void *data_to_return = NULL;
	size_t i = 0;

    assert(NULL != heap);
    assert(NULL != data);
    assert(NULL != is_match);

	for (i = 0; i < HeapSize(heap); ++i)
	{
		if (TRUE == is_match(*ARR(i), data, params))
		{
			dvector_t *backup_for_dvector = heap->dvector;

			data_to_return = *ARR(i);
			SwapPtr(ARR(i), ARR(LAST_INDEX));
			heap->dvector = DVectorPopBack(heap->dvector);
			if (NULL == heap->dvector)
		    {
				heap->dvector = backup_for_dvector;
		    }

			/* if the element to remove is the last element */
			if (i == HeapSize(heap))
			{
				break;
			}

			HeapifyUp(heap, i);
			HeapifyDown(heap, i);
			break;
		}
	}

    return data_to_return;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Helper functions ~~~~~~~~~~~~~~~~~~*/

static void SwapPtr(void **first, void **second)
{
	void *tmp = *first;
	*first = *second;
	*second = tmp;
}

/* Swap child with parent while he is 'smaller' then him */
static void HeapifyUp(heap_t *heap, size_t index)
{
	while (index > 0 && heap->cmp(*ARR(index), *PARENT(index)) < 0)
	{
		SwapPtr(ARR(index), PARENT(index));
		index = PARENT_INDEX(index);
	}
}

static void HeapifyDown(heap_t *heap, size_t index)
{
	/* base case - no children */
	if (I_LEFT(index) > LAST_INDEX)
	{
		return;
	}
	else if (I_RIGHT(index) <= LAST_INDEX)
	{/* has 2 children */
		size_t smaller = heap->cmp(*CHILD_L(index), *CHILD_R(index)) <= 0 ?
											I_LEFT(index) : I_RIGHT(index);
		if (heap->cmp(*ARR(index), *ARR(smaller)) > 0)
		{
			SwapPtr(ARR(index), ARR(smaller));
			HeapifyDown(heap, smaller);
		}
	}
	else
	{/* has left child only */
		if (heap->cmp(*ARR(index), *CHILD_L(index)) >= 0)
		{
			SwapPtr(ARR(index), CHILD_L(index));
			HeapifyDown(heap, I_LEFT(index));
		}
	}
}
