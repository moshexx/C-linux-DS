/*------------------------------------------------------------------------------
*	file name: avl_tree.c
*	author: Benj Ronen
*	reviewer:
------------------------------------------------------------------------------*/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <stdlib.h>
#include <assert.h>

#include "avl_tree.h"
#include "print_avl.h"
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[01;33m"
#define RESET 	"\033[0m"
#define BLUE "\033[0;34m"
#define RUN_TEST(result, name) {\
            printf(YELLOW"Test %s: "RESET, name);\
            if (result)\
            {\
                printf(GREEN"Success\n"RESET);\
            }\
            else\
            {\
                printf(RED"Failed\n"RESET); \
            }\
        }

#define SIZE (20)

enum successful {SUCCESS, FAILURE};
enum matching {NO, YES};
enum insertion_order {SEQUENTIAL, RANDOM};

/* functions needed to operate the tree: */
static int IsBefore(const void *lhs, const void *rhs)
{
	assert(NULL != lhs);
	assert(NULL != rhs);
	return (*(int *)lhs < *(int *)rhs);
}

int PrintEach(void *data, void *params)
{
	(void)params;
	printf("%d,", *(int *)data);
	return 0;
}



/*
	What a randomly inserted, unbalanced tree should look like:
		________________ 10 ________________
	   |									|
  ____ 2 ____						   ____ 15 ____
 |           |                        |            |
 1        __ 4 __                  __ 14           16 __
	     |       |                |                     |
	     3       5 _            _ 12 _                _ 18 _
	                | 	       |      |              |      |
	              _ 7 _        11     13             17     19
	             |     |                                     \
 	             6     9                                     20
	                  /
	                 8
*/

/*~~~~~~~~~~~~~~~~~~~~~~~~ Test Functions Declarations ~~~~~~~~~~~~~~~~~~~~~~~*/
void SimpleTestIs(void);
int TestIsEmpty(void);
int TestSize(void);
int TestHeight(void);
void TestForEach(void);
int TestFind(void);
int TestRemoveAndFind(void);

int MonsterTest(void);

void TestAll()
{
	RUN_TEST(TestRemoveAndFind(), "TestRemoveAndFind");
	RUN_TEST(TestIsEmpty(), "TestIsEmpty");
	RUN_TEST(TestHeight(), "TestHeight");
	RUN_TEST(TestFind(), "TestFind");
	RUN_TEST(TestSize(), "TestSize");
	printf(YELLOW"TestForEach:\n"RESET);
	TestForEach();

	RUN_TEST(MonsterTest(), "MonsterTest");
}

/*~~~~~~~~~~~~~~~~~~~~ Auxiliary Functions Declarations ~~~~~~~~~~~~~~~~~~~~~~*/
static void InitSequential(avl_t *tree, size_t elems_num);
static avl_t *CreateAndInit(size_t elems_num, int order);
static void InitRandom(avl_t *tree, size_t elems_num);

/* global variables to use in the tests: */
static int arr_seq[SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
static int arr_rand[SIZE] = {10,15,2,14,4,1,16,5,12,7,9,18,3,11,6,13,19,17,20,8};

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~Main~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main()
{
	TestAll();

	return 0;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Test Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int MonsterTest(void)
{
	avl_t *tree = NULL;
	int monst_array[SIZE] = {100,150,21,140,40,210,160,50,120,70,
						  90,180,30,110,60,130,190,170,200,80};
	size_t i = 0;
	int result = 0;

			 /*printf("\n"); print_ascii_tree(tree); printf("\n");*/

	tree = CreateAndInit(0, SEQUENTIAL);

	/* Hight, IsEmpty & Size on empty tree */
	result += (-1 == AVLHeight(tree));
	result += (1 == AVLIsEmpty(tree));
	result += (0 == AVLSize(tree));

	InitSequential(tree, SIZE);
    printf("\n"); print_ascii_tree(tree); printf("\n");
	/* Hight, IsEmpty & Size on non-empty tree */
	result += (4 == AVLHeight(tree));
	result += (0 == AVLIsEmpty(tree));
	result += (SIZE == AVLSize(tree));

	/* Checking balance using height: */
	for (i = 0; i < 12; ++i)
	{
		AVLInsert(tree, &monst_array[i]);
	}
	result += (5 == AVLHeight(tree));

	/* Find and Remove leaf */
	result += (120 == *(int *)AVLFind(tree, &monst_array[8]));
	result += (120 == *(int *)AVLRemove(tree, &monst_array[8]));
	result += (NULL == AVLFind(tree, &monst_array[8]));

	/* Find and Remove one-childed node */
	result += (100 == *(int *)AVLFind(tree, &monst_array[0]));
	result += (100 == *(int *)AVLRemove(tree, &monst_array[0]));
	result += (NULL == AVLFind(tree, &monst_array[0]));

	/* Find and Remove two-childed node */
	result += (140 == *(int *)AVLFind(tree, &monst_array[3]));
	result += (140 == *(int *)AVLRemove(tree, &monst_array[3]));
	result += (NULL == AVLFind(tree, &monst_array[3]));

	/* Find and Remove root node */
	result += (16 == *(int *)AVLFind(tree, &arr_seq[15]));
	result += (16 == *(int *)AVLRemove(tree, &arr_seq[15]));
	result += (NULL == AVLFind(tree, &arr_seq[15]));

	/* Find and Remove root node */
	AVLInsert(tree, &monst_array[8]);
	AVLInsert(tree, &monst_array[0]);
	AVLInsert(tree, &monst_array[3]);
	AVLInsert(tree, &arr_seq[15]);
	result += (SIZE + 12 == AVLSize(tree));
	result += (5 == AVLHeight(tree));
	AVLDestroy(tree);

	return (result == 21);
}

int TestIsEmpty(void)
{
	avl_t *tree1 = NULL;
	avl_t *tree2 = NULL;
	size_t arr[] = {0, 1, 11, SIZE};
	size_t i = 0;
	int result = 0;

	for (i = 0; i < 4; ++i)
	{
		tree1 = CreateAndInit(arr[i], RANDOM);
		tree2 = CreateAndInit(arr[i], SEQUENTIAL);
		if (arr[i] == 0)
		{
			result += (YES == AVLIsEmpty(tree1));
			result += (YES == AVLIsEmpty(tree2));
		}
		else
		{
			result += (NO == AVLIsEmpty(tree1));
			result += (NO == AVLIsEmpty(tree2));
		}
		AVLDestroy(tree1);
		AVLDestroy(tree2);
	}

	return (8 == result);
}

int TestSize(void)
{
	avl_t *tree1 = NULL;
	avl_t *tree2 = NULL;
	size_t arr[] = {0, 1, 11, SIZE};
	size_t i = 0;
	int result = 0;

	for (i = 0; i < 4; ++i)
	{
		tree1 = CreateAndInit(arr[i], RANDOM);
		tree2 = CreateAndInit(arr[i], SEQUENTIAL);

		result += (arr[i] == AVLSize(tree1));
		result += (arr[i] == AVLSize(tree2));

		AVLDestroy(tree1);
		AVLDestroy(tree2);
	}

	return (8 == result);
}

int TestHeight(void)
{
	avl_t *tree = NULL;
	size_t arr[] = {0, 1, 11};
	int result = 0;

	tree = CreateAndInit(arr[0], SEQUENTIAL);
	result += (-1 == AVLHeight(tree));
	AVLDestroy(tree);

	tree = CreateAndInit(arr[1], SEQUENTIAL);
	result += (0 == AVLHeight(tree));
	AVLDestroy(tree);

	tree = CreateAndInit(4, SEQUENTIAL);
	result += (2 == AVLHeight(tree));
	AVLDestroy(tree);

	tree = CreateAndInit(SIZE, RANDOM);
	result += (4 == AVLHeight(tree));
	AVLDestroy(tree);

	return (4 == result);
}

void TestForEach(void)
{
	avl_t *tree = NULL;
	tree = CreateAndInit(SIZE, RANDOM);
	print_ascii_tree(tree);
	printf(BLUE"Pre-Order:\n"RESET);
	AVLForEach(tree, PrintEach, NULL, PREORDER);
	printf("\n");
	AVLDestroy(tree);

	tree = CreateAndInit(SIZE, RANDOM);
	printf(BLUE"Post-Order:\n"RESET);
	AVLForEach(tree, PrintEach, NULL, POSTORDER);
	printf("\n");
	AVLDestroy(tree);

	tree = CreateAndInit(SIZE, RANDOM);
	printf(BLUE"In-Order:\n"RESET);
	AVLForEach(tree, PrintEach, NULL, INORDER);
	printf("\n");
	AVLDestroy(tree);
}

int TestFind(void)
{
	avl_t *tree = NULL;
	int result = 0;
	int thirty = 30;

	tree = CreateAndInit(0, RANDOM);
	result += (NULL == AVLFind(tree, &arr_seq[5]));
	InitRandom(tree, SIZE);
	result += (&arr_rand[0] == AVLFind(tree, &arr_seq[9]));
	result += (NULL == AVLFind(tree, &thirty));
	AVLDestroy(tree);

	return (3 == result);
}

/*
static int arr_seq[SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
static int arr_rand[SIZE] = {10,15,2,14,4,1,16,5,12,7,9,18,3,11,6,13,19,17,20,8};
*/

int TestRemoveAndFind(void)
{
	avl_t *tree = NULL;
	int result = 0;

	printf("\n");

	tree = CreateAndInit(SIZE, RANDOM);
	print_ascii_tree(tree);

	result += (10 == *(int *)AVLRemove(tree, &arr_seq[9]));
	print_ascii_tree(tree);
	result += (NULL == AVLFind(tree, &arr_seq[9]));

	result += (15 == *(int *)AVLRemove(tree, &arr_seq[14]));
	print_ascii_tree(tree);
	result += (NULL == AVLFind(tree, &arr_seq[14]));

	result += (11 == *(int *)AVLRemove(tree, &arr_seq[10]));
	print_ascii_tree(tree);
	result += (NULL == AVLFind(tree, &arr_seq[10]));

	result += (2 == *(int *)AVLRemove(tree, &arr_seq[1]));
	print_ascii_tree(tree);
	result += (NULL == AVLFind(tree, &arr_seq[1]));

	AVLDestroy(tree);

	return (8 == result);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Auxiliary Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* two Inits - insert nodes per request */
static void InitSequential(avl_t *tree, size_t elems_num)
{
	size_t i = 0;
	assert(elems_num <= SIZE);

	for (i = 0; i < elems_num; ++i)
	{
		AVLInsert(tree, &arr_seq[i]);
	}
}

static void InitRandom(avl_t *tree, size_t elems_num)
{
	size_t i = 0;
	assert(elems_num <= SIZE);

	for (i = 0; i < elems_num; ++i)
	{
		AVLInsert(tree, &arr_rand[i]);
	}
}

/* creates the tree */
static avl_t *CreateAndInit(size_t elems_num, int order)
{
	avl_t *tree = AVLCreate(IsBefore);

	if (NULL ==  tree)
	{
		printf("allocation failed\n");
		return NULL;
	}

	if (order == RANDOM)
	{
		InitRandom(tree, elems_num);
	}
	else
	{
		InitSequential(tree, elems_num);
	}

	return tree;
}
/* END */
