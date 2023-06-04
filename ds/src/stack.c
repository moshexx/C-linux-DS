/*****************************************************************************
*																			 *
*	Worksheet: 	stack.c	 			 										 *
*	Author: 	Moshe Cohen 			    								 *
*	Reviewer: Yoni Ladijensky					    										 *
*	Date: 		26th October 2020 											 *
*																			 *
*****************************************************************************/
#include <stdlib.h> /* malloc, free, size_t */
#include <assert.h>

#include "stack.h"

struct stack
{
    size_t top_index;
    size_t capacity;
    void **elements;
};

stack_t *StackCreate(size_t capacity)
{
	stack_t *stack = NULL;

	assert(capacity > 0);

	stack = (stack_t *)malloc(sizeof(stack_t) + capacity * sizeof(void **));
	if (NULL == stack)
	{
		return NULL;
	}

	stack->capacity = capacity;
	stack->top_index = 0;
	stack->elements = (void **)((char *)stack + sizeof(stack_t)); /* pointer arithmetics */

	return stack;
}

void StackPush(stack_t *stack, void *element)
{
	assert(stack);
	assert((stack->top_index) != stack->capacity); /* stack not full */

	stack->elements[++(stack->top_index)] = element;
}

int StackIsEmpty(const stack_t *stack)
{
	if (stack->top_index == 0)
	{
	    return 1;
	}

	return 0;
}

void StackDestroy(stack_t *stack)
{
  assert(stack);

  free(stack); stack = NULL;
}

void *StackPeek(const stack_t *stack)
{
	assert(stack);
	assert(0 != (stack->top_index));

	/*	returns the *element in index [top_index] of **elements	*/
	return (stack->elements[stack->top_index]);
}

size_t StackCapacity(const stack_t *stack)
{
	return (stack->capacity);
}

void StackPop(stack_t *stack)
{
	assert(stack);
	assert(0 != (stack->top_index)); /* stack not empty */

	--(stack->top_index);
}

size_t StackSize(const stack_t *stack)
{
	assert(stack);

	return (stack->top_index);
}
