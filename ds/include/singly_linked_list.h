/******************************************************************************/
/*		Descriptions - Singly Linked List API Functions	ver4				  */
/*		Date: 28.10.2020													  */
/*		Group: OL96															  */
/******************************************************************************/

#ifndef __SINGLY_LINKED_LIST_H__
#define __SINGLY_LINKED_LIST_H__

#include <stddef.h>

typedef	struct singly_linked_list sl_t;
typedef	struct node node_t;
typedef node_t* sl_iter_t;

typedef	int(*act_func_t)(void *data, void *params);
typedef	int(*cmp_func_t)(const void *one, const void *other, size_t n);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
* Description: Create struct of singly linked list.
* Return value: Pointer of sl_t.
* Errors: Return NULL when fail allocate memory.
* Undefined behavior: none.
*
* Complexity: O(1).
*/
sl_t *SListCreate(void);

/*
* Description: Return the first iterator of list (head).
* Return value: Iterator of sl_iter_t.
* Errors: none
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(1).
*/
sl_iter_t SListBegin(const sl_t *list);

/*
* Description: Return the last iterator of list (tail - null itertor).
* Return value: Iterator of sl_iter_t.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(1).
*/
sl_iter_t SListEnd(const sl_t *list);

/*
* Description: Free all allocated memory.
* Return value: none.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(n).
*/
void SListDestroy(sl_t *list);

/*
* Description: Return number of elements in the list.
* Return value: Return number of elements in the list.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(n).
*/
size_t SListSize(const sl_t *list);

/*
* Description: Insert new iterator before the iterator.
* Return value: 0 for success, 1 failure.
* Errors: fail to allocate memory.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(1).
*/
int SListInsertBefore(sl_t *list ,sl_iter_t iter, const void *new_data);

/*
* Description: Remove the iterator, and	deallocate its memory.
* Return value: none.
* Errors: none.
* Undefined behavior: iterator can not be the tail, Pointer to list cannot be NULL.
*
* Complexity: O(1).
*/
void SListRemove(sl_t *list ,sl_iter_t iter);

/*
* Description: Check if list is empty.
* Return value: 0 FALSE, 1 TRUE (list is empty).
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(1).
*/
int SListIsEmpty(const sl_t *list);

/*
* Description: Return the next iterator.
* Return value: iterator of sl_iter_t.
* Errors:
* Undefined behavior: iterator cannot be the tail.
*
* Complexity: O(1).
*/
sl_iter_t SListNextIter(const sl_iter_t iter);

/*
* Description: Active function for each element between from and to iterators
* (to iterator not include).
* Return value: 0 for success, 1 failure.
* Errors: none.
* Undefined behavior: none.
*
* Complexity: O(n).
*/
int SListForEach(act_func_t act_func, void *params, sl_iter_t from, const sl_iter_t to);

/*
* Description: Find which elemnent in the list (start from iterator from)
* consist with the same data, n represent size of bytes to compare.
* Return value: The iterator that found, else return tail.
* Errors: none.
* Undefined behavior: none.
*
* Complexity: O(n).
*/

sl_iter_t SListFind(sl_iter_t from, cmp_func_t cmp_func, const void *data, size_t n);

/*
* Description: Set the data to iterator.
* Return value: none.
* Errors: none.
* Undefined behavior: iterator cannot be tail.
*
* Complexity: O(1).
*/
void SListSetData(sl_iter_t iter, const void *new_data);

/*
* Description: Get data from iterator.
* Return value: pointer to data.
* Errors: none.
* Undefined behavior: iterator cannot be tail.
*
* Complexity: O(1).
*/
void *SListGetData(const sl_iter_t iter);

/*
* Description: Create new element and push to the end of list.
* Return value: 0 for success, 1 failure.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(1).
*/
int SListPushBack(sl_t *list, const void *new_data);

/*
* Description: Pop the last element of the list.
* Return value: none.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL, List can't be epmty.
*
* Complexity: O(n).
*/
void SListPopBack(sl_t *list);

/*
* Description: Compare between one iterator to other.
* Return value: 0 = FALSE, 1 = TRUE(same).
* Errors: none.
* Undefined behavior: none.
*
* Complexity: O(1).
*/
int SListIsSameIter(const sl_iter_t one, const sl_iter_t other);

/*
* Description: append the front of src to back of dest. after, src will be empty list.
* Return value: none.
* Errors: none.
* Undefined behavior: Pointers to dest and src cannot be NULL.
*
* Complexity: O(1).
*/
void SListAppend(sl_t *dest, sl_t *src);

#endif /* __SINGLY_LINKED_LIST_H__ */
