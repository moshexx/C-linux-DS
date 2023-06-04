/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_sort.c
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    #include <stdio.h> /* printf */
    #include <stdlib.h> /* srand, malloc, free */
    #include <time.h> /* clock */

    #include "../include/sort.h"

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
#define ARR_SIZE 666

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions declarations~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int TestPartOne(void);
int TestBinarySearch(void);
int TestMergeSort(void);
int TestQuickSort(void);
void PrintArray(int *arr, size_t size);
int IntCmp(const void *low, const void *high); /* for QSort */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~main~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main(int argc ,char *argv[])
{
    TestPartOne();
    TestBinarySearch();
    TestMergeSort();
    TestQuickSort();

    (void)argc;
    (void)argv;
	return 0;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int TestPartOne(void)
{
    int arr[] = {95, 84, 22, 3, 5, 21, 25};
    int arr2[] = {95, 84, 22, 3, 5, 21, 25};
    int arr3[] = {95, 84, 22, 3, 5, 21, 25};
    int arr4[] = {3, 22, 84, 95, 5};
    int arr5[] = {95, 84, 22, 3, 5, 21, 25};
    int arr6[] = {3, 22, 84, 95, 5};

    int arr_count[] = {20, 555, 5, 50, 23, 4, 2};
    size_t size_count = sizeof(arr_count)/sizeof(arr_count[0]);

    unsigned int arr_radix[] = {25, 12, 7, 7, 8};
    size_t size_radix = sizeof(arr_radix)/sizeof(arr_count[0]);


    size_t size = sizeof(arr)/sizeof(arr[0]);
    size_t size4 = sizeof(arr4)/sizeof(arr4[0]);
    size_t size6 = sizeof(arr6)/sizeof(arr6[0]);

    printf("array: \n");
    PrintArray(arr, size);

    printf("\nBubbleSort: \n");
    BubbleSort(arr, size);
    PrintArray(arr, size);

    printf("\nBubbleSortOptimized: \n");
    BubbleSortOptimized(arr2, size);
    PrintArray(arr2, size);

    printf("\nInsertionSort: \n");
    InsertionSort(arr4, size4);
    PrintArray(arr4, size4);
    InsertionSort(arr3, size);
    PrintArray(arr3, size);

    printf("\nSelectionSort: \n");
    SelectionSort(arr6, size6);
    PrintArray(arr6, size6);
    SelectionSort(arr5, size);
    PrintArray(arr5, size);
    printf("\n\n");



    printf("\nCountingSort: \n");
    CountingSort(arr_count, size_count);
    PrintArray(arr_count, size_count);

    PrintArray((int *)arr_radix, size_radix);
    printf("\nRadixSort:  \n");
    RadixSort(arr_radix, size_radix, 2);
    PrintArray((int *)arr_radix, size_radix);


    /*RadixSort(unsigned int *arr, size, nbits)*/
    return 0;
}

int TestBinarySearch(void)
{
    size_t i = 0;
    int status = SUCCESS;
    int arr[ARR_SIZE] = { 0 };


    /* create sorted array */
    for (i = 0; i < ARR_SIZE; ++i)
    {
        arr[i] = i;
    }

    /* search through -  BinarySearchIterative*/
    for (i = 0; i < ARR_SIZE && SUCCESS == status; ++i)
    {
        status = !(arr[i] == *BinarySearchIterative(arr, ARR_SIZE, i));
        /*printf("%d\n", *BinarySearchIterative(arr, ARR_SIZE, i));*/
    }
    RUN_TEST(SUCCESS == status, "Binary Search Iterative");

    /* search through -  BinarySearchBinarySearchRecur*/
    for (i = 0; i < ARR_SIZE && SUCCESS == status; ++i)
    {
        status = !(arr[i] == *BinarySearchRecur(arr, ARR_SIZE, i));
        /*printf("%d\n", *BinarySearchRecur(arr, ARR_SIZE, i));*/
    }
    RUN_TEST(SUCCESS == status, "Binary Search Recurtion");

    return SUCCESS;
}

int TestMergeSort(void)
{
    size_t i = 0;
    int arr[ARR_SIZE] = { 0 };

    /* create shuffled array */
    srand((unsigned)time(NULL));
    for (i = 0; i < ARR_SIZE; ++i)
    {
       arr[i] = rand() % 1000;
    }
/*    PrintArray(arr, ARR_SIZE);
*/
    MergeSort(arr, ARR_SIZE);
    printf("MergeSort:\n");
    PrintArray(arr, ARR_SIZE);

    return SUCCESS;
}

int TestQuickSort(void)
{
    size_t i = 0;
    int arr[ARR_SIZE] = { 0 };

    /* create shuffled array */
    srand((unsigned)time(NULL));
    for (i = 0; i < ARR_SIZE; ++i)
    {
       arr[i] = rand() % 1000;
    }
/*    PrintArray(arr, ARR_SIZE);
*/
    QSort(arr, ARR_SIZE, sizeof(int), IntCmp);
    printf("QSort:\n");
    PrintArray(arr, ARR_SIZE);

    return SUCCESS;
}
void PrintArray(int *arr, size_t size)
{
    size_t i;

    for (i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int IntCmp(const void *low, const void *high)
{
    return (*(int *)low < *(int *)high) ? -1 : (*(int *)high < *(int *)low);
}
