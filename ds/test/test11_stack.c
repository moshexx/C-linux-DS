/*****************************************************************************
*																			 *
*	Worksheet: 	test_stack.c	 			 										 *
*	Author: 	Moshe Cohen 			    								 *
*	Reviewer: 					    									 *
*	Date: 		26th October 2020 											 *
*																			 *
*****************************************************************************/

#include <stdio.h>
#include <string.h> 
#include "stack.h"


#define GREEN_COLOR     "\x1b[0;32m"
#define RED_COLOR     "\x1b[0;31m"
#define DEFAULT_COLOR    "\x1b[0;0m"

#define RUN_TEST(result, name) {\
            printf("Test %s: ", name);\
            if (result)\
            {\
                printf(GREEN_COLOR);\
                printf("Success\n");\
                printf(DEFAULT_COLOR);\
            }\
            else\
            {\
                printf(RED_COLOR);\
                printf("Fail\n");\
                printf(DEFAULT_COLOR);\
            }\
        }

struct stack
{
    size_t top_index;
    size_t capacity;
    void **elements;
}; 

int main()
{
	stack_t *my_stack = StackCreate(50);
	stack_t *my_stack2 = StackCreate(50);
	int n = 542;
	char *s = "sfsf";
	char c = 'A';
	double arr[5] = { 2,4,6,8,10 };
	size_t tmp = 0;
	
	/* Create */
    RUN_TEST(50 == my_stack->capacity, "Create 1");
    printf("adress of my_stack: %p, adress of elements: %p\n",
    		 (void *)(my_stack),(void *)(my_stack->elements));
    
    /* Capacity */
    RUN_TEST(StackCapacity(my_stack) == my_stack->capacity, "Capacity 1");
    RUN_TEST(50 == StackCapacity(my_stack), "Capacity 2");
    		 
    /* Push */
    /* check if top index increase by 1 after every push */
    tmp = my_stack->top_index;
    StackPush(my_stack, &n);
    RUN_TEST(tmp + 1 == my_stack->top_index, "Push 1(int)");
    tmp = my_stack->top_index;
    StackPush(my_stack, &s);
    RUN_TEST(tmp + 1 == my_stack->top_index, "Push 2(char*)");
    tmp = my_stack->top_index;
    StackPush(my_stack, arr);
    RUN_TEST(tmp + 1 == my_stack->top_index, "Push 3(arr)");
    /* check if Push pushed the right element - last one is arr */
    /* the first member of arr is 2 */
  	RUN_TEST(2 == *(double*)(StackPeek(my_stack)), "Push 4");
  	
  	/* IsEmpty */
  	RUN_TEST(1 == StackIsEmpty(my_stack2), "IsEmpty 1(Empty1)");
  	RUN_TEST(0 == StackIsEmpty(my_stack), "IsEmpty 2(not Empty0)");
  	
  	/* pop check */
  	StackPush(my_stack, &c);
  	RUN_TEST('A' == *(char*)(StackPeek(my_stack)), "Pop 1");
	/*printf("%c\n", *(char*)(StackPeek(my_stack))); printf A
	printf("%lu\n", StackPeek(my_stack2));  הדפסה של מחסנית לא מאותחלת, 0 או זבל */
		
	/* Size */
	RUN_TEST((StackSize(my_stack) == 4), "Size 1"); /* number of elements = 4 */
	RUN_TEST((StackSize(my_stack2) == 0), "Size 2(empty stack)"); /* number of elements = 0 */

		
	/* Destroy */
	StackDestroy(my_stack);
	StackDestroy(my_stack2);
  	printf("Test Destroy: check vlg\n");
  	
 	return 0;
}

