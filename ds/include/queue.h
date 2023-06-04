/******************************************************************************/
/*		Descriptions - Queue API Functions	ver1		      				  */
/*		Date: 02.11.2020					     						   	  */
/*		Group: OL96						      								  */
/******************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */

typedef	struct queue queue_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* 
* Description: Create empty queue.
* Return value: Pointer of queue_t.
* Errors: Return NULL when fail allocate memory.
* Undefined behavior: none.
*	      			
* Complexity: O(1).
*/
queue_t *QCreate(void);

/* 
* Description: Destroy queue and free allocated memory.
* Return value: none.
* Errors: none.
* Undefined behavior: Pointer to queue cannot be NULL.
*	      			
* Complexity: O(n).
*/
void QDestroy(queue_t *queue);

/* 
* Description: Check if queue is empty.
* Return value: 0 = FALSE, 1 = TRUE(empty).
* Errors: none.
* Undefined behavior: Pointer to queue_t cannot be NULL.
*	      			
* Complexity: O(1).
*/
int QIsEmpty(const queue_t *queue);

/* 
* Description: Insert new element to queue.
* Return value: 0 = Success, 1 = Failure(memory allocation).
* Errors: none.
* Undefined behavior: Pointer to queue cannot be NULL.
*	      			
* Complexity: O(1).
*/
int QEnqueue(queue_t *queue,const void *data);

/* 
* Description: Remove the front element in queue.
* Return value: none.
* Errors: none.
* Undefined behavior: Pointer to queue cannot be NULL, Queue cannot be empty.
*	      			
* Complexity: O(1).
*/
void QDequeue(queue_t *queue);

/*
* Description: Get data from the front element in queue.
* Return value: point to data.
* Errors: none.
* Undefined behavior: Pointer to queue cannot be NULL, Queue cannot be empty.
*	      			
* Complexity: O(1).
*/
void *QPeek(const queue_t *queue);

/* 
* Description: append the front of src to back of dest. after, src will be empty queue.
* Return value: none.
* Errors: none.
* Undefined behavior: Pointers to dest and src cannot be NULL.
*	      			
* Complexity: O(1).
*/
void QAppend(queue_t *dest, queue_t *src);

/* 
* Description: Return the size of the Queue.
* Return value: Return the number of elements in the Queue.
* Errors: none.
* Undefined behavior: Pointer to queue cannot be NULL.
*	      			
* Complexity: O(n).
*/
size_t QSize(const queue_t *queue);

#endif /* __QUEUE_H__ */
