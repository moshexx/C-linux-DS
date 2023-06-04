/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: sort.c
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free, rand */
#include <assert.h> /* assert */
#include <string.h> /* memcpy,  */
#include <time.h>   /* time */

#include "../include/sort.h"

#define TOTAL_BITS 32 /* u int*/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

enum successful_t
{    ALLOCATION_FAILURE = -1,
     SUCCESS = 0,
     FAILURE = 1
 };
enum status_t {FALSE = 0, TRUE =1};

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~helper functions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Swap(int *a ,int *b);
void print(int *arr, size_t size);
static void minMax(int *arr, size_t size, int* min, int* max);
static int *BSearchRecur(int *arr, int l, int r, int num);
static int Merge(int *arr, int num_of_elements, int middle);
static void SwapVoid(void *first, void *second, size_t nmemb);
/*static int IntCmp(void *low, void *high); in test file*/
static size_t Partition(void *base, size_t nmemb, size_t size,
                    int(*compare)(const void *lhs, const void *rhs));

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void BubbleSort(int *arr, size_t size)
{
    size_t j = 0;
    int tmp = 0;
    /* O(n^2) */
    for (; 0 < size; --size)
    {
        /* j < size - 1 --> so j+1 cant be null */
        for (j = 0; j < size - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                /*Swap(&arr[j], &arr[j + 1]);*/
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void BubbleSortOptimized(int *arr, size_t size)
{
    size_t j;
    int tmp = 0;
    short fsorted = 0;

    for (j = 0; 0 < size && !fsorted; ++j, --size)
    {
        fsorted = 1;
        for (j = 0; j < size - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                fsorted = 0;
            }
        }
    }
}

void InsertionSort(int *arr, size_t size)
{
    size_t i;

    for (i = 1; i < size; ++i)
    {
        int curr = arr[i];
        int prev_i = i - 1;

        while (curr < arr[prev_i] && 0 <= prev_i)
        {
            /* swap and step back */
            arr[prev_i + 1] = arr[prev_i];
            --prev_i;
        }
        arr[prev_i + 1] = curr;
    }
}

void SelectionSort(int *arr, size_t size)
{
    size_t i = 0;
    size_t j = 0;
    size_t min_i = 0;
    int tmp;

    for (j = 0; j < size; min_i = j + 1, ++j)
    {
        /* find min elem in range j to the end */
        for(i = j; i < size; ++i)
        {
            if (arr[i] < arr[min_i])
            {
                min_i = i;
            }
        }
        /* SWAP arr[j] with arr[min_i] */
        tmp = arr[min_i];
        arr[min_i] = arr[j];
        arr[j] = tmp;
    }
}

int CountingSort(int *arr, size_t size)
{
    int *histogram = NULL;
    int *arr_copy = NULL;
    int min = arr[0];
    int max = arr[0];

    minMax(arr, size, &min, &max);

    histogram = (int *)calloc((max - min + 1), sizeof(int));
    /* the algorithm is stable only with arr_copy */
    arr_copy = (int *)calloc(size, sizeof(int));
    if (NULL == arr_copy || NULL == histogram)
    {
        printf("Allocation Failure\n");
        return FAILURE;
    }

    RowCountingSort(arr ,size, min, max, arr_copy, histogram);

    free(histogram); histogram = NULL;
    free(arr_copy); arr_copy = NULL;

    return SUCCESS;
}

int *RowCountingSort(int *arr, size_t size, int min, int max,
                                int *arr_copy, int *histogram)
{
    size_t i = 0;
    size_t his_i = 0;
    size_t jump_index = 0;
    int tmp = 0;
    int prev_tmp = 0;
    size_t his_size = max - min + 1;

    /* Initialize a histogram with the number of presence of each number */
    for (i = 0; i < size; ++i)
    {
        his_i = arr[i] - min; /* min is the offset */
        ++histogram[his_i];
    }

    /* convert histogram from num of presences to starting indexes of each num */
    prev_tmp = histogram[0];
    histogram[0] = 0;
    for (i = 1; i < his_size; ++i)
    {
        tmp = histogram[i];
        histogram[i] = prev_tmp + histogram[i - 1];
        prev_tmp = tmp;
    }

    /* copy the numbers in a sorted way to arr_cpy according to the histogram */
    for (i = 0; i < size; ++i)
    {
        his_i = arr[i] - min;
        jump_index = histogram[his_i];
        arr_copy[jump_index] = arr[i];
        ++histogram[his_i];
    }
    /* arr = arr_cpy */
    memcpy(arr, arr_copy, size * sizeof(int));

    return arr_copy;
}

int RadixSort(unsigned int *arr, size_t size, size_t nbits)
{
    size_t his_size = 1 << nbits; /* 2^nbits */
    unsigned int *arr_copy = (unsigned int *)calloc(size, sizeof(int));
    unsigned int *histogram = (unsigned int *)calloc((his_size), sizeof(unsigned int));
    if (NULL == arr_copy || NULL == histogram)
    {
        printf("Allocation Failure\n");
        return FAILURE;
    }

    RowRadixSort(arr ,size, nbits, arr_copy, histogram, his_size);

    free(histogram); histogram = NULL;
    free(arr_copy); arr_copy = NULL;

    return SUCCESS;
}

unsigned int *RowRadixSort(unsigned int *arr ,size_t size, size_t nbits,
            unsigned int *arr_copy, unsigned int *histogram, size_t his_size)
{
    size_t i = 0;
    size_t j = 0;
    unsigned int his_i = 0;
    size_t mask = his_size - 1; /* 2^nbits - 1 */
    unsigned int tmp = 0;
    unsigned int prev_tmp = 0;
    unsigned int jump_index = 0;

    for (j = 0; j <= TOTAL_BITS ; j += nbits)
    {

        /* Initialize a histogram with the number of presence of each number */
        for (i = 0; i < size; ++i)
        {
            his_i = arr[i];
            his_i &= mask; /* take only the nbits */
            his_i >>= j; /* create an offset - min num will be in index 0 */
            ++histogram[his_i]; /* increment the representetive index */
        }

        /* convert histogram from 'num of presences' to 'starting indexes' of each num */
        prev_tmp = histogram[0];
        histogram[0] = 0;
        for (i = 1; i < his_size; ++i)
        {
            tmp = histogram[i];
            histogram[i] = prev_tmp + histogram[i - 1];
            prev_tmp = tmp;
        }

        /* copy the numbers in a sorted way to arr_cpy according to the histogram */
        for (i = 0; i < size; ++i)
        {
            his_i = arr[i];
            his_i &= mask;
            his_i >>= (j);
            jump_index = histogram[his_i];
            arr_copy[jump_index] = arr[i];
            ++histogram[his_i];
        }

        memcpy(arr, arr_copy, size * sizeof(int));
        memset(histogram, 0, his_size * sizeof(unsigned int));
        mask <<= nbits;
    }

    return arr_copy;
}


int *BinarySearchIterative(int *arr, int length, int num)
{
    int left = 0;
    int right = length - 1;

    while (left <= right)
    {
        int middle = (left + right) / 2;

        if (num == arr[middle])
        {
            return (&arr[middle]);
        }

        else if (arr[middle] < num)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return NULL;
}

int *BinarySearchRecur(int *arr, int length, int num)
{
    int left = 0;
    int  right = length - 1;

    return BSearchRecur(arr, left, right, num);
}


int MergeSort(int *arr, size_t num_of_elements)
{
    int middle = num_of_elements / 2;

    /* base case - done sorting*/
    if (num_of_elements <= 1)
    {
        return SUCCESS;
    }

    /* devide arr to arr_left & arr_right */
    MergeSort(arr, middle);
    MergeSort(arr + middle, num_of_elements - middle);

    /* Remerge arr_left & arr_right sortedly */
    return Merge(arr, num_of_elements, middle);
}

void QSort(void *base, size_t nmemb, size_t size,
                              int(*compare)(const void *lhs, const void *rhs))
{
    int pivot_i = 0;

    if (nmemb < 2)
    {
        return;
    }

    pivot_i = Partition(base, nmemb, size, compare);
    QSort(base, pivot_i++, size, compare);
    QSort((char *)base + (pivot_i * size) ,nmemb - pivot_i, size, compare);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~helper functions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Swap(int *a ,int *b)
{
int tmp = *a;

*a = *b;
*b = tmp;
}

void print(int *arr, size_t size)
{
size_t i;

for (i = 0; i < size; ++i)
{
    printf("%d ", arr[i]);
}
printf("\n");
}

static void minMax(int *arr, size_t size, int* min, int* max)
{
    size_t i;
    *min = *max = arr[0];
    for (i = 0; i < size; i++)
    {
        if (arr[i] < *min)
            *min = arr[i];
        if (arr[i] > * max)
            *max = arr[i];
    }
}

static int *BSearchRecur(int *arr, int l, int r, int num)
{
    int middle = 0;

    /*base case FAILURE*/
    if ( r < l)
    {
        return NULL;
    }

    middle = (l + r) / 2;
    /* base case SUCCESS */
    if (num == arr[middle])
    {
        return (&arr[middle]);
    }

    if (num < arr[middle])
    { /* replace r with middle - 1 */
        return BSearchRecur(arr, l, middle - 1, num);
    }
    else /* arr[middle] < num */
    {/* replace l with middle + 1 */
        return BSearchRecur(arr, middle + 1, r, num);
    }
}

/* divide the "chunk" array and (cunqure!) remerge it sortedly */
static int Merge(int *arr, int num_of_elements, int middle)
{
    int l = 0;
    int i = 0;
    int j = 0;
    int size_left_arr = middle;
    int size_right_arr = num_of_elements - middle;
    int *left_arr = NULL;
    int *right_arr = NULL;

    left_arr = (int *)malloc(size_left_arr * sizeof(int));
    if (NULL == left_arr)
    {
        return ALLOCATION_FAILURE;
    }
    right_arr = (int *)malloc(size_right_arr * sizeof(int));
    if (NULL == right_arr)
    {
        free(left_arr);
        return ALLOCATION_FAILURE;
    }

    /* Divide */
    /* copy the left half of arr to left_arr */
    memcpy(left_arr, arr, size_left_arr * sizeof(int));
    /* copy the right half of arr to right_arr */
    memcpy(right_arr, arr + middle, size_right_arr * sizeof(int));

    /* Cunqure */
    /* Remerge the left_arr & right_arr into the arr */
    for (l = 0, i = 0, j = 0; i < size_left_arr && j < size_right_arr; ++l)
    {
        if (left_arr[i] <= right_arr[j])
        {
            arr[l] = left_arr[i];
            ++i;
        }
        else
        {
            arr[l] = right_arr[j];
            ++j;
        }
    }

    /* add the remaining elements to arr (if needed) */
    memcpy(arr + l,left_arr + i, sizeof(int) * (size_left_arr - i));
    memcpy(arr + l,right_arr + j, sizeof(int) * (size_right_arr - j));
    /* same as:
    while (i < size_left_arr)
    {
        arr[l] = left_arr[i];
        ++i;
        ++l;
    }

    while (j < size_right_arr)
    {
        arr[l] = right_arr[j];
        ++j;
        ++l;
    }*/

    free(left_arr);
    free(right_arr);

    return SUCCESS;
}

static void SwapVoid(void *first, void *second, size_t nmemb)
{
    unsigned char *first_ptr = (unsigned char *)first;
    unsigned char *second_ptr = (unsigned char *)second;
    unsigned char tmp;
    size_t i = 0;

    for (i = 0; i < nmemb; ++i)
    {
        tmp = first_ptr[i];
        first_ptr[i] = second_ptr[i];
        second_ptr[i] = tmp;
    }
}

/*static int IntCmp(void *low, void *high)
{
    return (*(int *)high < *(int *)low) ? -1 : (*(int *)low < *(int *)high);
}*/

                           /* arr          len */
static size_t Partition(void *base, size_t nmemb, size_t size,
                    int(*compare)(const void *lhs, const void *rhs))
{
    int pivot_i = 0;
    char *base_runner = (char *)base;
    char *last_element = base_runner + ((nmemb -1) * size);

    /* swap the pivot with the last element in base */
    SwapVoid(base_runner + ((rand() % nmemb) * size), last_element, size);

    /* run from 0 to last - 1. swap with pivot if needed. */
    for ( ;base_runner < last_element; base_runner += size)
    {
        if (compare(base_runner, last_element) < 0)
        {
            SwapVoid(base_runner, (char *)base + (size * pivot_i++), size);
        }
    }

    /* swap pivot with last element */
    SwapVoid((char *)base + (pivot_i * size), last_element, size);

    return pivot_i;
}
