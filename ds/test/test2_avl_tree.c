/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_avl_tree.c
*	author: Yoni Ladijensky
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <stdlib.h>

#include "avl_tree.h"
#include "print_avl.h"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define RED printf("\033[0;31m")
#define GREEN printf("\033[0;32m")
#define YELLOW printf("\033[01;33m")
#define BLUE printf("\033[0;34m")
#define LIGTH_BLUE printf("\033[01;36m")
#define RESET printf("\033[0m")
#define RUN_TEST(result, name) {\
			LIGTH_BLUE;\
            printf("Test %s: ", name);\
            RESET;\
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



enum successful {SUCCEED, FAILED};
enum matching {NO, YES};

typedef struct point
{
	int x;
	int y;
} point_t;

int IsBeforeFuncInt(const void *one, const void *other);
int IsBeforeFuncStruct(const void *one, const void *other);
int PrintDataInit(void *data, void *params);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int TestAVLCreateandAVLIsEmpty();
int TestAVLInsert();
int TestSize();
int TestAVLForEach();
int TestAVLFind();
int TestAVLHeight();
int TestAVLRemove();
int TestRotate();
int Test();

int main()
{
	RUN_TEST(TestAVLCreateandAVLIsEmpty(), "TestAVLCreateandAVLIsEmpty");
	RUN_TEST(TestAVLInsert(), "TestAVLInsert");
	RUN_TEST(TestSize(), "TestSize");
	RUN_TEST(TestAVLForEach(), "TestAVLForEach");
	RUN_TEST(TestAVLFind(), "TestAVLFind");
	RUN_TEST(TestAVLHeight(), "TestAVLHeight");
	RUN_TEST(TestAVLRemove(), "TestAVLRemove");
	RUN_TEST(TestRotate(), "TestRotate");
	RUN_TEST(Test(), "Test");

	return 0;
}

int Test()
{
	int x = 0;
	int b = 33;
	int e = 13;
	int h = 53;
	int j = 61;
	int k = 9;
	int l = 21;
	int m = 11;
	int a = 8;
	int aa = 22;
	int aaa = 12;
	avl_t *tree1 = AVLCreate(IsBeforeFuncInt);

	x += (SUCCEED == AVLInsert(tree1, &b));
	printf("1\n");
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &e));
	printf("2\n");
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &h));
	printf("3\n");
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &j));
	printf("4\n");
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &l));
	printf("5\n");
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &m));
	printf("6\n");
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &a));
	printf("7\n");
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &k));
	printf("8\n");
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &aa));
	printf("9\n");
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &aaa));
	printf("10\n");
	print_ascii_tree(tree1);



	AVLDestroy(tree1);

	return(10 == x);
}

int TestRotate()
{
	int x = 0;
	int b = 2;
	int e = 5;
	int h = 8;
	int j = 10;
	int k = 11;
	int l = 12;
	int m = 13;
	int a = 100;
	int aa = 1000;
	avl_t *tree1 = AVLCreate(IsBeforeFuncInt);
	avl_t *tree2 = AVLCreate(IsBeforeFuncInt);

	x += (SUCCEED == AVLInsert(tree1, &j));
	x += (SUCCEED == AVLInsert(tree1, &e));
	x += (SUCCEED == AVLInsert(tree1, &l));
	x += (SUCCEED == AVLInsert(tree1, &b));
	x += (SUCCEED == AVLInsert(tree1, &m));
	x += (SUCCEED == AVLInsert(tree1, &h));
	x += (SUCCEED == AVLInsert(tree1, &k));
	x += (7 == AVLSize(tree1));
	printf("insert : 10, 5, 12, 2, 13, 8, 11");
	printf("\n");
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &a));
	printf("insert : 100\n");
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &aa));
	printf("insert : 1000\n");
	print_ascii_tree(tree1);
	x += (9 == AVLSize(tree1));
	x += (2 == *(int*)AVLRemove(tree1, &b));
	printf("remove 2 \n");
	print_ascii_tree(tree1);
	x += (8 == AVLSize(tree1));
	x += (8 == *(int*)AVLRemove(tree1, &h));
	printf("remove 8 \n");
	print_ascii_tree(tree1);
	x += (11 == *(int*)AVLRemove(tree1, &k));
	printf("remove 11\n");
	print_ascii_tree(tree1);
	x += (5 == *(int*)AVLRemove(tree1, &e));
	printf("remove 5\n");
	print_ascii_tree(tree1);
	x += (10 == *(int*)AVLRemove(tree1, &j));
	printf("remove 10\n");
	print_ascii_tree(tree1);


	j = 3;
	e = 6;
	l = 2;
	b = 1;
	m = 9;
	printf("Another Test\ninsert : 3, 6, 2 ,1 ,9\n");
	x += (SUCCEED == AVLInsert(tree2, &j));
	x += (SUCCEED == AVLInsert(tree2, &e));
	x += (SUCCEED == AVLInsert(tree2, &l));
	x += (SUCCEED == AVLInsert(tree2, &b));
	x += (SUCCEED == AVLInsert(tree2, &m));
	print_ascii_tree(tree2);
	x += (5 == AVLSize(tree2));
	x += (3 == *(int*)AVLRemove(tree2, &j));
	printf("after remove root\n");
	print_ascii_tree(tree2);
	x += (4 == AVLSize(tree2));

	AVLDestroy(tree1);
	AVLDestroy(tree2);

	return(25 == x);

}

int TestAVLRemove()
{
	int x = 0;
	int b = 2;
	int e = 5;
	int h = 8;
	int j = 10;
	int k = 11;
	int l = 12;
	int m = 13;
	avl_t *tree1 = AVLCreate(IsBeforeFuncInt);

	x += (SUCCEED == AVLInsert(tree1, &j));
	x += (SUCCEED == AVLInsert(tree1, &e));
	x += (NULL == AVLRemove(tree1, &l));
	x += (SUCCEED == AVLInsert(tree1, &l));
	x += (SUCCEED == AVLInsert(tree1, &b));
	x += (SUCCEED == AVLInsert(tree1, &m));
	x += (SUCCEED == AVLInsert(tree1, &h));
	x += (SUCCEED == AVLInsert(tree1, &k));
	x += (7 == AVLSize(tree1));
	printf("\n");
	print_ascii_tree(tree1);
	x += (2 == AVLHeight(tree1));
	x += (10 == *(int*)AVLRemove(tree1, &j));
	x += (2 == AVLHeight(tree1));
	printf("remove 10\n");
	print_ascii_tree(tree1);
	x += (6 == AVLSize(tree1));
	x += (5 == *(int*)AVLRemove(tree1, &e));
	x += (2 == AVLHeight(tree1));
	printf("remove 5\n");
	print_ascii_tree(tree1);
	x += (5 == AVLSize(tree1));
	x += (12 == *(int*)AVLRemove(tree1, &l));
	printf("remove 12\n");
	print_ascii_tree(tree1);
	x += (4 == AVLSize(tree1));
	x += (11 == *(int*)AVLRemove(tree1, &k));
	printf("remove 11\n");
	print_ascii_tree(tree1);
	x += (3 == AVLSize(tree1));
	x += (13 == *(int*)AVLRemove(tree1, &m));
	x += (1 == AVLHeight(tree1));
	printf("remove 13\n");
	print_ascii_tree(tree1);
	x += (2 == AVLSize(tree1));
	x += (8 == *(int*)AVLRemove(tree1, &h));
	x += (0 == AVLHeight(tree1));
	printf("remove 8\n");
	print_ascii_tree(tree1);
	x += (1 == AVLSize(tree1));
	x += (2 == *(int*)AVLRemove(tree1, &b));
	printf("remove 2\n");
	x += (-1 == AVLHeight(tree1));
	x += (0 == AVLSize(tree1));
	printf("height left is :%d\n" , AVLHeight(tree1));

	x += (NULL == AVLRemove(tree1, &j));
	AVLDestroy(tree1);

	return(30 == x);

}

int TestAVLHeight()
{
	int x = 0;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	int aa = -1;
	int aaa = -11;
	int aaaa = -121;
	avl_t *tree1 = AVLCreate(IsBeforeFuncInt);

	x += (SUCCEED == AVLInsert(tree1, &b));
	x += (SUCCEED == AVLInsert(tree1, &a));
	x += (1 == AVLHeight(tree1));
	printf("height is :%d\n" , AVLHeight(tree1));
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &c));
	x += (SUCCEED == AVLInsert(tree1, &d));
	x += (2 == AVLHeight(tree1));
	printf("height is :%d\n" , AVLHeight(tree1));
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &e));
	x += (2 == AVLHeight(tree1));
	printf("height is :%d\n" , AVLHeight(tree1));
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &aaaa));
	x += (SUCCEED == AVLInsert(tree1, &aaa));
	x += (2 == AVLHeight(tree1));
	printf("height is :%d\n" , AVLHeight(tree1));
	print_ascii_tree(tree1);
	x += (SUCCEED == AVLInsert(tree1, &aa));
	x += (3 == AVLHeight(tree1));
	printf("height is :%d\n" , AVLHeight(tree1));
	print_ascii_tree(tree1);

	AVLDestroy(tree1);

	return(13 == x);
}

int TestAVLFind()
{
	int x = 0;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	avl_t *tree1 = AVLCreate(IsBeforeFuncInt);

	x += (SUCCEED == AVLInsert(tree1, &a));
	x += (SUCCEED == AVLInsert(tree1, &b));
	x += (SUCCEED == AVLInsert(tree1, &c));
	x += (SUCCEED == AVLInsert(tree1, &d));
	x += (1 == *(int*)AVLFind(tree1, &a));
	x += (4 == *(int*)AVLFind(tree1, &d));

	AVLDestroy(tree1);

	return(6 == x);
}

int TestAVLForEach()
{
	int x = 0;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	avl_t *tree1 = AVLCreate(IsBeforeFuncInt);
	avl_t *tree2 = AVLCreate(IsBeforeFuncInt);

	x += (SUCCEED == AVLInsert(tree1, &a));
	x += (SUCCEED == AVLInsert(tree1, &b));
	x += (SUCCEED == AVLInsert(tree1, &c));
	x += (SUCCEED == AVLInsert(tree1, &d));
	printf("\n should be : 1,2,3,4\n");
	x += (SUCCEED == AVLForEach(tree1, PrintDataInit, 0, INORDER));
	printf("\nshould be : 1,2\n");
	x += (SUCCEED == AVLInsert(tree2, &a));
	x += (SUCCEED == AVLInsert(tree2, &b));
	x += (SUCCEED == AVLForEach(tree2, PrintDataInit, 0, PREORDER));
	printf("\n");

	AVLDestroy(tree1);
	AVLDestroy(tree2);

	return(8 == x);
}

int TestSize()
{
	int x = 0;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	avl_t *tree1 = AVLCreate(IsBeforeFuncInt);
	avl_t *tree2 = AVLCreate(IsBeforeFuncInt);

	x += (SUCCEED == AVLInsert(tree1, &b));
	x += (SUCCEED == AVLInsert(tree1, &d));
	x += (SUCCEED == AVLInsert(tree1, &a));
	x += (SUCCEED == AVLInsert(tree1, &c));
	x += (2 == AVLHeight(tree1));
	x += (4 == AVLSize(tree1));

	x += (SUCCEED == AVLInsert(tree2, &a));
	x += (SUCCEED == AVLInsert(tree2, &b));
	x += (1 == AVLHeight(tree2));
	x += (2 == AVLSize(tree2));

	AVLDestroy(tree1);
	AVLDestroy(tree2);

	return(10 == x);
}

int TestAVLInsert()
{
	int x = 0;
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	avl_t *tree1 = AVLCreate(IsBeforeFuncInt);

	x += (-1 == AVLHeight(tree1));
	x += (SUCCEED == AVLInsert(tree1, &b));
	x += (0 == AVLHeight(tree1));
	x += (SUCCEED == AVLInsert(tree1, &a));
	x += (1 == AVLHeight(tree1));
	x += (SUCCEED == AVLInsert(tree1, &c));
	x += (1 == AVLHeight(tree1));
	x += (NO == AVLIsEmpty(tree1));
	x += (3 == AVLSize(tree1));
	printf("should be 1,3,2 -->");
	x += (SUCCEED == AVLForEach(tree1, PrintDataInit, 0, POSTORDER));

	x += (SUCCEED == AVLInsert(tree1, &d));
	x += (2 == AVLHeight(tree1));
	x += (4 == AVLSize(tree1));

	AVLDestroy(tree1);

	return (13 == x);
}

int TestAVLCreateandAVLIsEmpty()
{
	int x = 0;
	avl_t *tree1 = AVLCreate(IsBeforeFuncInt);
	avl_t *tree2 = AVLCreate(IsBeforeFuncStruct);

	x += (NULL != tree1);
	x += (NULL != tree2);

	x += (YES == AVLIsEmpty(tree1));
	x += (YES == AVLIsEmpty(tree2));

	AVLDestroy(tree1);
	AVLDestroy(tree2);

	return(4 == x);
}



/***********************************************************************/
int IsBeforeFuncInt(const void *one, const void *other)
{
	if (*(int*)one < *(int*)other)
	{
		return 1;
	}

	return 0;
}

int IsBeforeFuncStruct(const void *one, const void *other)
{
	if (((point_t*)one)->x < ((point_t*)other)->x)
	{
		return 1;
	}

	return 0;
}

int PrintDataInit(void *data, void *params)
{
	printf(",%d",*(int*)data);

	(void)params;

	return 0;
}
