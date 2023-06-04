/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_recursion.c
*	author: Moshe Cohen
*	reviewer: none

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <stdlib.h>
#include <string.h>

#include "../include/recursion.h"
#include "../include/stack.h"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define RED printf("\033[0;31m")
#define GREEN printf("\033[0;32m")
#define YELLOW printf("\033[01;33m")
#define BLUE printf("\033[0;34m")
#define RESET printf("\033[0m")
#define RUN_TEST(result, name) {\
            printf("Test %s: ", name);\
            if (result)\
            {\
                GREEN;\
                printf("Success\n");\
                RESET;\
            }\
            else\
            {\
                RED;\
                printf("Failed\n");\
                RESET;\
            }\
        }

enum successful {SUCCESS, FAILURE};
enum matching {NO, YES};

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int TestFiboIter();
int TestFiboRecur();
void PrintList(node_t *node);
int TestFlipNode();

void TestStrLen();
void TestStrCmp();
void TestStrCpy();
void TestStrCat();
void TestStrStr();

int TestSortStack();
void PrintStack(stack_t *stack);

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~main~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main()
{
    TestFiboIter();
    TestFiboRecur();
    TestFlipNode();

    TestStrLen();
    TestStrCmp();
    TestStrCpy();
    TestStrCat();
    TestStrStr();

    TestSortStack();

	return 0;
}

/*********************** tests *****************************************/

int TestFiboIter()
{
    unsigned int fib_ser[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233,
                    377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657};
    unsigned int n_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                                                                        15, 16};
    size_t i = 0;
    size_t n_arr_size = sizeof(n_arr)/sizeof(n_arr[0]);

    YELLOW;
    printf("---Test Fibonacci Iter ---\n");
    RESET;
    for (i = 0; i < n_arr_size; ++i)
    {
        printf("[%lu]: ", i);
        RUN_TEST(fib_ser[i] == FiboIter(i), "FiboIter");
        printf("--------------------\n");
    }

    return SUCCESS;
}


int TestFiboRecur()
{
    unsigned int fib_ser[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233,
                    377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657};
    unsigned int n_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                                                                        15, 16};
    size_t i = 0;
    size_t n_arr_size = sizeof(n_arr)/sizeof(n_arr[0]);

    YELLOW;
    printf("---Test Fibonacci Recursion ---\n");
    RESET;
    for (i = 0; i < n_arr_size; ++i)
    {
        printf("[%lu]: ", i);
        RUN_TEST(fib_ser[i] == FiboRecur(i), ("Test FiboRecur"));
        printf("--------------------\n");
    }

    return SUCCESS;
}

int TestFlipNode()
{
    node_t *one = (node_t *)malloc(sizeof(node_t));
    node_t*two = (node_t *)malloc(sizeof(node_t));
    node_t*three = (node_t *)malloc(sizeof(node_t));
    node_t*four = (node_t *)malloc(sizeof(node_t));
    node_t*five = (node_t *)malloc(sizeof(node_t));
    node_t *new_head = NULL;
    node_t *head = one;

    int n1 = 111;
    int n2 = 222;
    int n3 = 333;
    int n4 = 444;
    int n5 = 555;
    int *p1 = &n1;
    int *p2 = &n2;
    int *p3 = &n3;
    int *p4 = &n4;
    int *p5 = &n5;

    one->data = p1;
    two->data = p2;
    three->data = p3;
    four->data = p4;
    five->data = p5;
    one->next = two;
    two->next = three;
    three->next = four;
    four->next = five;
    five->next = NULL;

    YELLOW;
    printf("Attention Visual Test for FlipList:\n");
    RESET;
    BLUE;
    printf("Original List:\n");
    RESET;
    PrintList(head);
    new_head = FlipList(one);
    BLUE;
    printf("List After Flip:\n");
    RESET;
    PrintList(new_head);
    RUN_TEST(new_head == five, "return value FlipList");

    free(one); one = NULL;
    free(two); two = NULL;
    free(three); three = NULL;
    free(four); four = NULL;
    free(five); five = NULL;

    return SUCCESS;
}

/***********************strings tests **************************************/

void TestStrLen()
{
    const char *str_arr[] = {"Hello world", "msodfsaofmksadfs", "moshe",
                                                "skdfksdf", "sfd", "2"};
    size_t i = 0;

    YELLOW;
    printf("\n---Test Strings ---\n");
    RESET;

    for (i = 0; i < 6; ++i)
    {
        RUN_TEST(strlen(str_arr[i]) == StrLen(str_arr[i]), "StrLen");
/*        printf("%lu\n",StrLen(str_arr[i])); */
   }
}
void TestStrCmp()
{
	char str1[10] = "Hello";
	char str2[10] = " World!";
	char str3[10] = "Hello";
	int res1 ,res2 ,res3;

	printf("\nStrCmp test:\n");

	res1 = StrCmp(str1 ,str2);
	res2 = StrCmp(str1 ,str3);
	res3 = StrCmp(str3 ,str1);

	printf("my StrCmp:\n");
	printf("str1 - str2 = %d\n" ,res1);
	printf("str1 - str3 = %d\n" ,res2);
	printf("str3 - str1 = %d\n" ,res3);

	printf("The original strcmp:\n");
	printf("str1 - str2 = %d\n" ,strcmp(str1 ,str2));
	printf("str1 - str3 = %d\n" ,strcmp(str1 ,str3));
	printf("str3 - str1 = %d\n" ,strcmp(str3 ,str1));
}

void TestStrCpy()
{
	char src[] = "Hello World!";
	char dest[20];
	char *str = NULL;

	printf("\nStrCpy test:\n");

	str = StrCpy(dest, src);
	printf("My StrCpy: %s\n", str);
	str = strcpy(dest, src);
	printf("Original strcpy: %s\n", str);
}

void TestStrCat()
{
	char str1[20] = "Hello ";
	const char str2[] = "World!\n";

    char str3[20] = "Hello ";
	const char str4[] = "World!\n";

	printf("\nmy StrCat:\n");
	StrCat(str1 ,str2);
	printf("%s", str1);

    printf("\noriginal strcat:\n");
	StrCat(str3 ,str4);
	printf("%s", str3);
}

void TestStrStr()
{
	const char *str = "Hello World!";
	const char *sub_str = "World";
	char *ptr;

	printf("\nMy StrStr:\n");
	ptr = StrStr(str ,sub_str);
	printf("First occurrence of string '%s' in '%s' is '%s'", sub_str, str, ptr);
 	printf("\nThe sub string of |%s| is |%s|. \nIn adress |%p|.\n", str ,ptr ,ptr);
}

/*********************** Sort Stack tests *************************************/

int TestSortStack()
{
    stack_t *stack = StackCreate(5 * sizeof(int *));
    stack_t *stack_tmp = StackCreate(5 * sizeof(int *));

    int n1 = 111;
    int n2 = 222;
    int n3 = 333;
    int n4 = 444;
    int n5 = 555;
    int *p1 = &n1;
    int *p2 = &n2;
    int *p3 = &n3;
    int *p4 = &n4;
    int *p5 = &n5;

    YELLOW;
    printf("\n---Test Stack Sort ---\n");
    RESET;

    StackPush(stack, p2);
    StackPush(stack, p1);
    StackPush(stack, p4);
    StackPush(stack, p5);
    StackPush(stack, p3);
    BLUE;
    printf("Original Stack\n");
    RESET;
    PrintStack(stack);
    stack_tmp = SortStack(&stack);
    BLUE;
    printf("Stack after sort\n");
    RESET;
    PrintStack(stack);
    PrintStack(stack_tmp); /* check return value */
    StackDestroy(stack);

    return SUCCESS;
}

/***********************helper functions **************************************/

void PrintList(node_t *node)
{
    while (NULL != node)
    {
        printf("%d ->", *(int *)(node->data));
        node = node->next;
    }
    printf("\n");
}

void  PrintStack(stack_t *stack)
{
    stack_t *stack_tmp = StackCreate(StackCapacity(stack));

    printf("Stack:\n");
    while (!StackIsEmpty(stack))
    {
        printf("%d-> ", *(int *)StackPeek(stack));
        StackPush(stack_tmp, StackPeek(stack));
        StackPop(stack);
    }
    printf("\n");

    while (!StackIsEmpty(stack_tmp))
    {
        StackPush(stack, StackPeek(stack_tmp));
        StackPop(stack_tmp);
    }

    StackDestroy(stack_tmp);
}
