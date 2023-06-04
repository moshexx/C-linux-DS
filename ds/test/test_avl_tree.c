/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_avl_tree.c
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <stdlib.h>

#include "../include/avl_tree.h"
#include "../include/print_avl.h"


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
#define SIZE_OF_ARR 13

enum successful {SUCCESS, FAILURE};
enum matching {NO, YES};


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int BasicTest(void);
avl_t *TestCreate(void);
void TestInsert(avl_t *tree, int arr[], size_t size_of_arr);
int TestRemove(avl_t *tree);
static int IsBefore(const void *lhs, const void *rhs);
static int PrintData(void *data, void *params);


int main()
{
    int arr[] = {30, 20, 40, 10, 25, 22, 50, 60, 55, 57, 52, 23, 0};
    size_t size_of_arr = sizeof(arr) / sizeof(arr[0]);
    avl_t *tree = NULL;

    RUN_TEST(SUCCESS == BasicTest(), "BasicTest");
    printf("\n");

    tree = TestCreate();
    if (NULL == tree)
    {
        printf("Create Failed\n");
        return FAILURE;
    }
    TestInsert(tree, arr, size_of_arr);
    printf("Big tree after Inserts:\n");
    print_ascii_tree(tree);
    AVLForEach(tree, PrintData, NULL, INORDER);
    printf("\n");

    printf("Big tree after Removes:\n");
    TestRemove(tree);

    printf("\n");
    AVLDestroy(tree);

	return 0;
}

int BasicTest()
{
    avl_t *tree2 = NULL;
    int n1 = 0;
    int n2 = 42;
    int n3 = 88;
    int n4 = 110;
    int n5 = 555;
    int n6 = 666;
    int n7 = 90;
    int n8 = 99;
    int nn = 110;
    int *p1 = &n1;
    int *p2 = &n2;
    int *p3 = &n3;
    int *p4 = &n4;
    int *p5 = &n5;
    int *p6 = &n6;
    int *p7 = &n7;
    int *tmp = NULL;
    int *tmp2 = NULL;

    printf("~~~~~~~~~~~~~~~~~~Test - BasicTest~~~~~~~~~~~~~~~~~~\n");

    tree2 = AVLCreate(IsBefore);
    if (NULL == tree2)
    {
        printf("Create tree2 Failed\n");
        return 1;
    }
    RUN_TEST(YES == AVLIsEmpty(tree2), "Create & IsEmpty");
    RUN_TEST(0 == AVLSize(tree2), "Create & Size");

    AVLInsert(tree2, p1);
    AVLInsert(tree2, p3);
    AVLInsert(tree2, p2);
    AVLInsert(tree2, p4);
    AVLInsert(tree2, p5);
    AVLInsert(tree2, p7);
    AVLInsert(tree2, &n8);

    printf("\n");
    print_ascii_tree(tree2);
    AVLForEach(tree2, PrintData, NULL, INORDER); printf("\n");

    tmp = (int *)AVLFind(tree2, p2);
    tmp2 = (int *)AVLFind(tree2, p6);
    RUN_TEST(*p2 == *tmp, "Find");
    RUN_TEST(NULL == tmp2, "Find When does not exist");
    tmp = (int *)AVLFind(tree2, &nn);
    RUN_TEST(*p4 == *tmp, "Find with the same data - but in another variable");
    AVLRemove(tree2, &n2);
    print_ascii_tree(tree2);

    AVLDestroy(tree2);

    return SUCCESS;
}
avl_t *TestCreate()
{
    avl_t *tree = AVLCreate(IsBefore);

    printf("~~~~~~~~~~~~~~~~~~Test - TestCreate~~~~~~~~~~~~~~~~~~\n");

    if (NULL == tree)
    {
        printf("Create tree Failed\n");
        return NULL;
    }

    RUN_TEST(YES == AVLIsEmpty(tree), "Create & IsEmpty");
    RUN_TEST(0 == AVLSize(tree), "Create & Size");

    return tree;
}

void TestInsert(avl_t *tree, int arr[], size_t size_of_arr)
{

    int fail = 0;
    size_t i = 0;
    printf("~~~~~~~~~~~~~~~~~~Test - TestInsert~~~~~~~~~~~~~~~~~~\n");

    for (i = 0; i < size_of_arr && !fail; ++i)
    {
        fail = AVLInsert(tree, (arr + i));
    }
    RUN_TEST(NO == AVLIsEmpty(tree), "IsEmpty after Insert");
    RUN_TEST(size_of_arr == AVLSize(tree), "Size after Insert");

    /* print tree now*/
}

int TestRemove(avl_t *tree)
{ /*  index:      0   1   2   3  4   5   6   7   8   9   10  11  12*/
    int arr[] = {30, 20, 40, 10, 25, 22, 50, 60, 55, 57, 52, 23, 0};
    size_t size_of_arr = sizeof(arr) / sizeof(arr[0]);

    size_t i = 0;
    printf("~~~~~~~~~~~~~~~~~~Test - TestRemove~~~~~~~~~~~~~~~~~~\n");
    /*AVLRemove(tree, (arr + 12));
    print_ascii_tree(tree);
    AVLRemove(tree, (arr + 11));
    print_ascii_tree(tree);
    AVLRemove(tree, (arr + 10));
    print_ascii_tree(tree);
    AVLRemove(tree, (arr + 9));
    print_ascii_tree(tree);
    AVLRemove(tree, (arr + 4));
    print_ascii_tree(tree);
    AVLRemove(tree, (arr + 5));
    print_ascii_tree(tree);
    AVLRemove(tree, (arr + 6));
    print_ascii_tree(tree);
    AVLRemove(tree, (arr + 7));*/
for (i = 0; i < size_of_arr-1; ++i)
   {
       printf("\nremove %d:\n", arr[i]);
       AVLRemove(tree, (arr + i));
       print_ascii_tree(tree);
       AVLForEach(tree, PrintData, NULL, INORDER);
       printf("\n");
       RUN_TEST(size_of_arr - 1 -i == AVLSize(tree), "Size after Remove");
 }
 AVLRemove(tree, (arr + size_of_arr - 1));
 RUN_TEST(0 == AVLSize(tree), "Size after Last Remove(Empty)");
 RUN_TEST(1 == AVLIsEmpty(tree), "IsEmpty after Last Remove(Empty)");

return SUCCESS;
}
/*****************************************************************************/
static int IsBefore(const void *lhs, const void *rhs)
{
    return (*(int *)lhs < *(int *)rhs);
}

static int PrintData(void *data, void *params)
{
    printf("%d--> ",*(int *)data);
    (void)params;
    return 0;
}
