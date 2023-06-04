/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_binary_sorted_tree.c
*	author: Nir Shaulian
*	reviewer: Lia Borisover

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */

#include "binary_sorted_tree.h"

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

enum status
{
	SUCCESS,
	FAILURE
};
enum matching
{
	NO,
	YES
};

typedef struct int_and_char
{
    int num;
    char ch;
}int_and_char_t;

    /*~~~~~~~~~~~~~~~~~~~~ static functions declerations ~~~~~~~~~~~~~~~~~~~~~*/
static int IsBeforeStructWrap(const void *lhs, const void *rhs);
static int IsBeforeStruct(const int_and_char_t *lhs, const int_and_char_t *rhs);
static int PrintNum(void *data, void *params);
static int PrintTree(bst_t *bst);


static int TestBst();
static bst_t *TestCreate();
static int TestInsert(bst_t *bst, int_and_char_t *arr, int *int_arr);
static int TestIfSorted(void *f_data , void *int_arr_sorted);
static int TestPrev(bst_t *bst, int *int_arr_sorted);
static int TestFind(bst_t *bst, int *int_arr_sorted);
static int TestRemove(bst_t *bst, size_t size, int *int_arr);


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- main -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
int main()
{
    TestBst();


	return 0;
}

    /*~~~~~~~~~~~~~~~~~~~~~~~~ static functions ~~~~~~~~~~~~~~~~~~~~~~~~*/
static int IsBeforeStruct(const int_and_char_t *lhs, const int_and_char_t *rhs)
{
    return (lhs->num < rhs->num);
}


static int IsBeforeStructWrap(const void *lhs, const void *rhs)
{
    return IsBeforeStruct(lhs, rhs);
}

static int PrintNum(void *data, void *params)
{
    (void)params;
    printf("%d ", ((int_and_char_t *)data)->num);

    return SUCCESS;
}

static int PrintTree(bst_t *bst)
{
    return BSTForEach(bst, PrintNum, bst);
}

static int TestBst()
{
    int_and_char_t arr[SIZE_OF_ARR];

    int int_arr[SIZE_OF_ARR] =
                            {30, 20, 40, 10, 25, 22, 50, 60, 55, 57, 52, 23, 0};
    int int_arr_sorted[SIZE_OF_ARR] =
                            {0, 10, 20, 22, 23, 25, 30, 40, 50, 52, 55, 57, 60};
    bst_t *bst = NULL;

    bst = TestCreate();
    if (NULL == bst)
    {
        printf("create failed\n");
        return FAILURE;
    }
    TestInsert(bst, arr, int_arr);
    PrintTree(bst);
    printf("\n");
    BSTForEach(bst, TestIfSorted, int_arr_sorted);
    TestPrev(bst, int_arr_sorted);
    TestFind(bst, int_arr_sorted);
    TestRemove(bst, BSTSize(bst), int_arr);

    BSTDestroy(bst);
    return SUCCESS;
}


static bst_t *TestCreate()
{
    bst_t *bst = BSTCreate(IsBeforeStructWrap);
    if (NULL == bst)
    {
        printf("create failed\n");
        return NULL;
    }

    RUN_TEST(YES == BSTIsEmpty(bst), "create & IsEmpty");
    RUN_TEST(0 == BSTSize(bst), "create & Size");

    return bst;
}

static int TestInsert(bst_t *bst, int_and_char_t *arr, int *int_arr)
{
    size_t i = 0;
    char c = 'a';

    for (i = 0; i < SIZE_OF_ARR; ++i)
    {
        arr[i].num = int_arr[i];
        arr[i].ch = c;

        if (YES == BSTIsSameIter(BSTEnd(bst), BSTInsert(bst, arr + i)))
        {
            printf("Insert failed\n");
            return FAILURE;
        }
        RUN_TEST(i + 1 == BSTSize(bst), "insert & size");
    }

    return SUCCESS;
}

static int TestIfSorted(void *f_data , void *int_arr_sorted)
{
    static size_t i = 0;
    int_and_char_t *data = f_data;
    int num = ((int *)(int_arr_sorted))[i];

    RUN_TEST(num == data->num, "Insert & GetData & ForEach");

    ++i;

    return SUCCESS;
}

static int TestPrev(bst_t *bst, int *int_arr_sorted)
{
    size_t i = 0;
    bst_iter_t iter = BSTEnd(bst);
    int_and_char_t *data = NULL;

    for (iter = BSTPrev(iter); NO == BSTIsSameIter(iter, BSTBegin(bst));
                                                    ++i, iter = BSTPrev(iter))
    {
        int_and_char_t *data = BSTGetData(iter);
        RUN_TEST((int_arr_sorted[SIZE_OF_ARR - 1 - i] == data->num),
                                                                "Prev & data");
    }

    data = BSTGetData(iter);
    RUN_TEST((int_arr_sorted[SIZE_OF_ARR - 1 - i] == data->num),
                                                            "Prev & data");

    return SUCCESS;
}

static int TestFind(bst_t *bst, int *int_arr_sorted)
{
    size_t i = 0;
    bst_iter_t iter = BSTEnd(bst);
    int_and_char_t *data = NULL;

    for (i = 0; i < SIZE_OF_ARR; ++i)
    {
        iter = BSTFind(bst, int_arr_sorted + i);
        data = BSTGetData(iter);
        RUN_TEST(int_arr_sorted[i] == data->num, "Find");
    }

    return SUCCESS;
}

static int TestRemove(bst_t *bst, size_t size, int *int_arr)
{
    size_t i = 0;
    bst_iter_t iter =NULL;

    for (i = 0; i < SIZE_OF_ARR; ++i)
    {
        iter = BSTFind(bst, int_arr + i);
        BSTRemove(iter);
        RUN_TEST(size - 1 -i == BSTSize(bst), "Remove & size");
        PrintTree(bst);
    }

    return SUCCESS;
}
