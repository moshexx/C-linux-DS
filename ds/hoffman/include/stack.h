/******************************************************************************/
/*		Descriptions - Stack API Functions			    					  */
/*		Date: 26.10.2020					    							  */
/*		Group: OL96						    								  */
/******************************************************************************/

#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>

typedef struct stack stack_t;


stack_t *StackCreate(size_t capacity);
/* 
* Description: allocate memory for stack.
* Return value: Pointer to strack_t.
* Errors: capacity must be higher than 0.
* Complexity: O(1).
*/

void StackDestroy(stack_t *stack);
/* 
* Description: free stack allocation.
* Return value: none.
* Errors: stack pointer can not be null.
* Complexity: O(1).
*/

void StackPop(stack_t *stack);
/* 
* Description: decrease size of stack by one.
* Return value: none.
* Errors: stack pointer can not be null, stack can not be empty.
* Complexity: O(1).
*/

void StackPush(stack_t *stack, void *element);
/* 
* Description: increase size of stack by one and add an element.
* Return value: none.
* Errors: stack pointer can not be null, stack can not be full.
* Complexity: O(1).
*/

void *StackPeek(const stack_t *stack);
/* 
* Description: return the element from top.
* Return value: void pointer to element.
* Errors: stack pointer can not be null, stack can not be empty.
* Complexity: O(1).
*/

size_t StackSize(const stack_t *stack);
/* 
* Description: return the current size of the stack.
* Return value: size_t number.
* Errors: stack pointer can not be null.
* Complexity: O(1).
*/

int StackIsEmpty(const stack_t *stack);
/* 
* Description: check if the stack is empty.
* Return value: 1 - for empty stack, 0 - otherwise.
* Errors: stack pointer can not be null.
* Complexity: O(1).
*/

size_t StackCapacity(const stack_t *stack);
/* 
* Description: return the capacity of the stack.
* Return value: size_t number.
* Errors: stack pointer can not be null.
* Complexity: O(1).
*/


#endif /* __STACK_H__ */



