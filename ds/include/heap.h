/*******************************************************************************
*		Descriptions - Heap API Functions V2	                                   *
*		Date: 15.12.2020						                               *
*		Group: OL96							                                   *
*******************************************************************************/

#ifndef __HEAP_H__
#define __HEAP_H__
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stddef.h> /* size_t */

typedef struct heap heap_t;

/* The cmp function  return  an  integer less than, equal to, or greater than
zero if @lhs is, respectively, before , match, or after @rhs.
*/
typedef int(*cmp_t)(const void *lhs, const void *rhs);

/* in src file
#include "dynamic_vector.h"

struct heap
{
	cmp_t cmp;
	dvector_t *dvector;
};
end of src file */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
* Description: Create heap.
* Return value: Pointer to heap.
* Errors: Return NULL when fail allocate memory.
* Undefined behavior: Function pointer is NULL.
* Complexity: O(1).
*/
heap_t *HeapCreate(cmp_t cmp);

/*
* Description: free the heap.
* Return value: none.
* Errors: None
* Undefined behavior: @heap is NULL.
*
* Complexity: O(1).
*/
void HeapDestroy(heap_t *heap);

/*
* Description: insret @data to heap.
* Return value: 0 for success, 1 for failure.
* Errors: allocation failure.
* Undefined behavior: @heap is NULL, @data can not be NULL.
*
* Complexity: amortized O(log(n)), worst O(n).
*/
int HeapPush(heap_t *heap, const void *data);

/*
* Description: removes the first element from heap.
* Return value: None.
* Errors: None.
* Undefined behavior: @heap is NULL.
*
* Complexity: amortized O(log(n)), worst O(n).
*/
void HeapPop(heap_t *heap);

/*
* Description: returns the data of the first element in heap.
* Return value: data of the first element in heap, if heap is empty returns NULL.
* Errors: None
* Undefined behavior: @heap is NULL.
*
* Complexity: O(1).
*/
void *HeapPeek(const heap_t *heap);

/*
* Description: returns number of elements in the heap.
* Return value: number of elements in heap.
* Errors: None
* Undefined behavior: @heap is NULL.
*
* Complexity: O(1).
*/
size_t HeapSize(const heap_t *heap);

/*
* Description: Checks if heap is empty.
* Return value: 1 if empty, 0 if not empty.
* Errors: None.
* Undefined behavior: @heap is NULL.
*
* Complexity: O(1).
*/
int HeapIsEmpty(const heap_t *heap);

/*
* Description: Remove the element whose data is identical to @data.
* Return value: the removed data or NULL if @data not found.
* Errors: None.
* Undefined behavior: @heap is NULL, @data is NULL.
*
* Complexity: O(n).
*/
void *HeapRemove(heap_t *heap, void *data,
                int (*is_match)(const void* lhs, const void *rhs, void *params),
                void *params);

#endif   /*__HEAP_H___*/
