/******************************************************************************/
/*		Descriptions - Sorted List API Functions							  */
/*		Date: 8.11.2020					    								  */
/*		Group: OL96						    								  */
/******************************************************************************/

#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include "doubly_linked_list.h"

typedef struct sorted_list sol_t;
typedef dl_iter_t sol_iter_t;

typedef	int(*oper_func_t)(void *data, void *params);
typedef	int(*cmp_func_t)(const void *one, const void *other);
typedef	int(*criter_match_t)(const void *one, const void *other, size_t n);

/*
* Description: Creates sorted linked list
* Return value: Pointer to the list
* Errors: returns NULL if allocation failed
* Undefined behavior: cmp_func can't bu NULL
*
* Complexity: O(1).
*/
sol_t *SortedListCreate(cmp_func_t cmp_func);

/*
* Description: frees all allocated memory
* Return value: none
* Errors:
* Undefined behavior: pointer to list can't be NULL
*
* Complexity: O(n).
*/
void SortedListDestroy(sol_t *solist);

/*
* Description: Check if list is empty.
* Return value: 0 FALSE, 1 TRUE (list is empty).
* Errors: none.
* Undefined behavior: pointer to list can't be NULL
*
* Complexity: O(1).
*/
int SortedListIsEmpty(const sol_t *solist);

/*
* Description: returns number of elements in the list.
* Return value: number of elements in the list.
* Errors: none.
* Undefined behavior: pointer to list cannot be NULL.
*
* Complexity: O(n).
*/
size_t SortedListSize(const sol_t *solist);

/*
* Description: Return the first valid iterator of list (if empty - tail).
* Return value: Iterator of iter_t.
* Errors: none
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(1).
*/
sol_iter_t SortedListBegin(const sol_t *solist);

/*
* Description: Return the last iterator of list (tail - null itertor).
* Return value: Iterator of sol_iter_t.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(1).
*/
sol_iter_t SortedListEnd(const sol_t *solist);

/*
* Description: Return the next iterator.
* Return value: iterator of sol_iter_t.
* Errors: none
* Undefined behavior: iterator cannot be the tail.
*
* Complexity: O(1).
*/
sol_iter_t SortedListNext(const sol_iter_t current);

/*
* Description: Return the previous iterator.
* Return value: iterator of sol_iter_t.
* Errors: none
* Undefined behavior: iterator can't be the head
*
* Complexity: O(1).
*/
sol_iter_t SortedListPrev(const sol_iter_t current);

/*
* Description: Compare between one iterator to other.
* Return value: 0 = FALSE, 1 = TRUE(same).
* Errors: none.
* Undefined behavior: none.
*
* Complexity: O(1).
*/
int SortedListIsSameIter(const sol_iter_t one, const sol_iter_t other);

/*
* Description: Get data from iterator.
* Return value: pointer to data.
* Errors: none.
* Undefined behavior: iterator cannot be tail.
*
* Complexity: O(1).
*/
void *SortedListGetData(const sol_iter_t iter);

/*
* Description: Inserts new iterator with the data.
* Return value: 0 for success, 1 failure of memory allocation.
* Errors: fail to allocate memory.
* Undefined behavior: Pointer to list cannot be NULL.
*
* Complexity: O(n).
*/
int SortedListInsert(sol_t *solist, const void *data);

/*
* Description: Removes the iterator, and deallocates its memory.
* Return value: none.
* Errors: none.
* Undefined behavior: iterator can not be the tail.
*
* Complexity: O(1).
*/
void SortedListRemove(sol_iter_t iter);

/*
* Description: Pops the first element of the list.
* Return value: none.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL, List can't be epmty.
*
* Complexity: O(1).
*/
void SortedListPopFront(sol_t *solist);

/*
* Description: Pops the last element of the list.
* Return value: none.
* Errors: none.
* Undefined behavior: Pointer to list cannot be NULL, List can't be epmty.
*
* Complexity: O(1).
*/
void SortedListPopBack(sol_t *solist);

/*
* Description: Active function for each element between from and to iterators
* (the to iterator not include).
* Return value: 0 for success, 1 failure.
* Errors: none.
* Undefined behavior: oper_func, from and to can't be NULL. Changes that affect
* the sorting order are undefined behavior.
*
* Complexity: O(n).
*/
int SortedListForEach(sol_iter_t from, const sol_iter_t to,
						oper_func_t oper_func, void *params);

/*
* Description: Finds first iterator between from and to whose data is identical
* Return value: The iterator that found, else return to.
* In case to before from returns tail.
* Errors: none.
* Undefined behavior: pointer to list, from and to can't be NULL.
*
* Complexity: O(n).
*/
sol_iter_t SortedListFind(sol_t *solist, const sol_iter_t from, const
	 												   sol_iter_t to, const void *data);

/*
* Description: Finds first iterator between from and to (not including) whose
* data meets the criteria. n represent size of bytes to compare.
* Return value: The iterator that found, else return to.
* In case to before from returns tail.
* Errors: none.
* Undefined behavior: pointer to list, from and to can't be NULL.
*
* Complexity: O(n).
*/
sol_iter_t SortedListFindIf(const sol_iter_t from, const sol_iter_t to,
					 criter_match_t criter_match, const void *params, size_t n);

/*
* Description: Merges src into dest. Leaves src empty.
* Return value: none
* Errors: none.
* Undefined behavior: dest and src must have identical cmp_func
*
* Complexity: O(n).
*/
void SortedListMerge(sol_t *dest, sol_t *src);


#endif   /*__SORTED_LIST_H__*/
