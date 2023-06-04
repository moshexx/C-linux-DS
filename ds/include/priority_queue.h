/******************************************************************************/
/*		Descriptions - Priority Queue API Functions							  */
/*		Date: 9.11.2020					    								  */
/*		Group: OL96						    								  */
/******************************************************************************/

#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

typedef	struct p_queue pq_t;

/* A compare function that returns the difference of one "minus" other */
typedef	int(*prior_func_t)(const void *one, const void *other);

/* returns 1 if the data matches the criteria, else returns 0 */
typedef	int(*is_criter_match_t)(const void *one, const void *other, size_t n);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
* Description: Create an empty p_queue.
* Return value: pq_t pointer to the new pq_t.
* Errors: Returns NULL if memory allocation failed.
* Undefined behavior: none.
*
* Complexity: O(1).
*/
pq_t *PQCreate(prior_func_t prior_func);

/*
* Description: Destroys the pq_t and frees all allocated memory.
* Return value: none.
* Errors: none.
* Undefined behavior: p_queue can't be NULL.
*
* Complexity: O(n).
*/
void PQDestroy(pq_t *p_queue);

/*
* Description: Checks if the pq_t is empty.
* Return value: 1 (TRUE) if empty or 0 (FALSE) else
* Errors: none.
* Undefined behavior: p_queue can't be NULL.
*
* Complexity: O(1).
*/
int PQIsEmpty(const pq_t *p_queue);

/*
* Description: Inserts new element to the pq_t.
* Return value: 0 (SUCCESS) if memory allocation didn't fail, 1 (FAILURE) else
* Errors: none.
* Undefined behavior: p_queue can't be NULL.
*
* Complexity: O(n) based on sorted_linked_list.
              O(log n) based on heap.
*/
int PQEnqueue(pq_t *p_queue, const void *data);

/*
* Description: Removes the front element in the pq_t.
* Return value: none.
* Errors: none.
* Undefined behavior: p_queue can't be NULL, the pq_t can't be empty.
*
* Complexity: O(1) based on sorted_linked_list.
              O(log n) based on heap.
*/
void PQDequeue(pq_t *p_queue);

/*
* Description: Gets data from the front element in the pq_t.
* Return value: pointer to the data.
* Errors: none.
* Undefined behavior: p_queue can't be NULL, the pq_t can't be empty.
*
* Complexity: O(1).
*/
void *PQPeek(const pq_t *p_queue);

/*
* Description: Counts number of elements in the pq_t.
* Return value: Returns the size of the pq_t.
* Errors: none.
* Undefined behavior: p_queue can't be NULL.
*
* Complexity: O(n).
*/
size_t PQSize(const pq_t *p_queue);

/*
* Description: Empties the pq_t from all elements
* Return value: none.
* Errors:
* Undefined behavior: p_queue can't be NULL, the pq_t can't be empty.
*
* Complexity: O(n)
*/
void PQFlush(pq_t *p_queue);

/*
* Description: Erases the first element whose data is identical to data.
* Return value: returns a pointer to the data if an element was found and
* removed, otherwise returns NULL
* Errors:
* Undefined behavior: p_queue can't be NULL
*
* Complexity: O(n)
*/
void *PQErase(pq_t *p_queue, is_criter_match_t is_criter_match, const void *data, size_t n);
#endif   /*__PRIORITY_QUEUE_H__*/
