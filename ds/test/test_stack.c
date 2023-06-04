#include<stdio.h>

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


int CheckPush(stack_t * s, void * val)
{
	StackPush(s , val);
	if( StackPeek(s) != val)
	{
		printf("fail on push with value %d \n", *(int*)(val));
		return 0;
	
	}
	return 1;

} 

        
int TestPush(stack_t * s)
{
	static int a = 1, b = 2 , c = 3, d = 4;
	int res =0;
	res += CheckPush(s ,&a);
	res += CheckPush(s ,&b);
	res += CheckPush(s ,&c);
	res += CheckPush(s ,&d);

	return(res == 4);
}        

int CheckPop(stack_t * s)
{
	int * val = (int *) *((s -> elements) + (s -> top_index) - 1);
	StackPop(s); 
	
	if( *((s -> elements) + (s -> top_index) - 1) == val)
	{
		printf("fail on pop with value %d \n", *val);
		return 0;
	
	}
	return 1;

} 

        
int TestPop(stack_t * s)
{
	int res =0;

	res += CheckPop(s );
	res += CheckPop(s);
	res += CheckPop(s);

	return(res == 3);
}      

int CheckPeek(stack_t * s)
{
	int  val = *(int *) StackPeek(s);
	if( 1  != val )
	{
		printf("fail on peek with value %d \n", val);
		return 0;
	
	}
	return 1;

} 

        
int TestPeek(stack_t * s)
{
	int res =0;
	res += CheckPeek(s);
	return(res == 1);
}      



        
int Testsize(stack_t * s, size_t size)
{
	return(StackSize(s) == size ? 1 : 0);
} 


int TestIsEmpty(stack_t * s)
{
	int res  = 0;
	
	res += ( 0 == StackIsEmpty(s));
	StackPop(s);
	res += ( 1 == StackIsEmpty(s));
	
	return(res == 2);
}   



int Testcapacity(stack_t * s, size_t capacity)
{
	return(StackCapacity(s) == capacity);
} 


        

int main()
{
	size_t capacity = 10;
	
	stack_t *stack = StackCreate(capacity);
	
	RUN_TEST(TestPush(stack), "StackPush" );
	RUN_TEST(Testsize(stack, 4), "StackSizeAfterPush"); 
	RUN_TEST(TestPop(stack), "StackPop"); 
	RUN_TEST(Testsize(stack, 1), "StackSizeAfter3Pop"); 
	RUN_TEST(TestPeek(stack), "StackPeek"); 
	RUN_TEST(Testsize(stack, 1), "StackSizeAfterPeek"); 
	RUN_TEST(TestIsEmpty(stack), "StackIsEmpty"); 
	RUN_TEST(Testcapacity(stack, capacity), "StackCapacity");
	
	
	StackDestroy(stack);
	
	return (0);

}
