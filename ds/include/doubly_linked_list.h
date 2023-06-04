/******************************************************************************/
/*		Descriptions - Doubly Linked List API Functions	- V-2				  */
/*		Date: 4.11.2020					    								  */
/*		Group: OL96						    								  */
/******************************************************************************/

#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

#include <stddef.h>/*size_t*/

/******************************************************************************/
typedef struct doubly_linked_list dl_t;
typedef struct node node_t;
typedef node_t* dl_iter_t;

typedef	int(*act_func_t)(void *data, void *params);
/*if they match returns true(1) else return false(0)*/
typedef	int(*is_match_t)(const void *one, const void *other, size_t n);
/******************************************************************************/

/*
* Description: Create a doubly linked list.
* Return value: Pointer of dl_t.
* Errors: Return NULL when fail allocate memory.
* Undefined behavior: none.
*
* Complexity: O(1).
*/
dl_t *DListCreate(void);

/*
* Description: Free all allocated memory.
* Return value: none.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(n).
*/
void DListDestroy(dl_t *dlist);

/*
* Description: Check if list is empty.
* Return value: 0 FALSE, 1 TRUE (list is empty).
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(1).
*/
int DListIsEmpty(const dl_t *dlist);

/*
* Description: Return number of elements in the list.
* Return value: Return number of elements in the list.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(n).
*/
size_t DListSize(const dl_t *dlist);

/*
* Description: Return the first valid iterator of list (if empty - tail).
* Return value: Iterator of iter_t.
* Errors: none
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(1).
*/
dl_iter_t DListBegin(const dl_t *dlist);

/*
* Description: Return the last iterator of list (tail - null itertor).
* Return value: Iterator of dl_iter_t.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(1).
*/
dl_iter_t DListEnd(const dl_t *dlist);

/*
* Description: Return the next iterator.
* Return value: iterator of dl_iter_t.
* Errors: none
* Undefined behavior: iterator cannot be the tail or NULL.
*
* Complexity: O(1).
*/
dl_iter_t DListNext(const dl_iter_t current);

/*
* Description: Return the previous iterator.
* Return value: iterator of dl_iter_t.
* Errors: none
* Undefined behavior: iterator cannot be the head or NULL.
*
* Complexity: O(1).
*/
dl_iter_t DListPrev(const dl_iter_t current);

/*
* Description: Compare between one iterator to other.
* Return value: 0 = FALSE, 1 = TRUE(same).
* Errors: none.
* Undefined behavior: none.
*
* Complexity: O(1).
*/
int DListIsSameIter(const dl_iter_t one, const dl_iter_t other);

/*
* Description: Get data from iterator.
* Return value: pointer to data.
* Errors: none.
* Undefined behavior: iterator cannot be tail or NULL.
*
* Complexity: O(1).
*/
void *DListGetData(const dl_iter_t iter);

/*
* Description: Set the data to iterator.
* Return value: none.
* Errors: none.
* Undefined behavior: iterator cannot be tail or NULL.
*
* Complexity: O(1).
*/
void DListSetData(dl_iter_t iter,const void *data);

/*
* Description: Insert new iterator before the iterator.
* Return value: 0 for success, 1 failure.
* Errors: fail to allocate memory.
* Undefined behavior: iter cannot be NULL.
*
* Complexity: O(1).
*/
int DListInsertBefore(dl_iter_t iter, const void *data);

/*
* Description: Remove the iterator, and	deallocate its memory.
* Return value: none.
* Errors: none.
* Undefined behavior: iterator can not be the tail, iter cannot be NULL.
*
* Complexity: O(1).
*/
void DListRemove(dl_iter_t iter);

/*
* Description: Create new element and push to the head of the list.
* Return value: 0 for success, 1 failure.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(1).
*/
int DListPushFront(dl_t *dlist, const void *new_data);

/*
* Description: Create new element and push to the end of the list.
* Return value: 0 for success, 1 failure.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(1).
*/
int DListPushBack(dl_t *dlist, const void *new_data);

/*
* Description: Pop the first element of the list.
* Return value: none.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL, List can't be epmty.
*
* Complexity: O(1).
*/
void DListPopFront(dl_t *dlist);

/*
* Description: Pop the last element of the list.
* Return value: none.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL, List can't be epmty.
*
* Complexity: O(1).
*/
void DListPopBack(dl_t *dlist);

/*
* Description: Find which elemnent in the list (start from iterator from)
* consist with the same data, n represent size of bytes to compare.
* Return value: The iterator that found, else return to.
* In case to before from returns tail.
* Errors: none.
* Undefined behavior: from and to cannot be NULL.
*
* Complexity: O(n).
*/
dl_iter_t DListFind(const dl_iter_t from, const dl_iter_t to,
							is_match_t is_match, const void *data, size_t n);

/*
* Description: Active function for each element between from and to iterators
* (the to iterator not include).
* Return value: 0 for success, 1 failure.
* Errors: none.
* Undefined behavior: from and to cannot be NULL.
*
* Complexity: O(n).
*/
int DListForEach(dl_iter_t from, const dl_iter_t to,
											act_func_t act_func, void *params);

/*
* Description: Cuts sublist between src_from and src_to(not included)
* and inserts it before dest_iter.
* Return value: none.
* Errors: none.
* Undefined behavior: from and to cannot be NULL.
*
* Complexity: O(1).
*/
void DListSplice(dl_iter_t dest_iter, dl_iter_t src_from,
													const dl_iter_t src_to);

/*
* Description: Recieves a list in which it duplicates the nodes that fit
* void* data nodes.
* Return value: 0 for success, 1 failure.
* Errors: none.
* Undefined behavior: list, to and from cannot be NULL.
*
* Complexity: O(n).
*/
int DListMultFind(const dl_iter_t from, const dl_iter_t to,
				is_match_t is_match, const void *data, size_t n, dl_t *dlist);

/*static int CreateNode(dl_iter_t iter, const void *data);*/
#endif   /*__DOUBLY_LINKED_LIST_H__*/
