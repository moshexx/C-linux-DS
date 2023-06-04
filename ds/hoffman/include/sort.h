#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h>

void BubbleSort(int *arr, size_t size);
void BubbleSortOptimized(int *arr, size_t size);
void InsertionSort(int *arr, size_t size);
void SelectionSort(int *arr, size_t size);
int CountingSort(int *arr, size_t size);
int *RowCountingSort(int *arr, size_t size, int min, int max,
                                int *arr_copy, int *histogram);
int RadixSort(unsigned int *arr, size_t size, size_t nbits);
unsigned int *RowRadixSort(unsigned int *arr ,size_t size,size_t nbits,
            unsigned int *arr_copy, unsigned int *histogram, size_t his_size);

int *BinarySearchIterative(int *arr, int length, int num);
int *BinarySearchRecur(int *arr, int length, int num);
int MergeSort(int *arr, size_t num_of_elements);
/*base == arr
nmeb == number of elements
size == sizeof(int)*/
void QSort(void *base, size_t nmemb, size_t size,
                              int (*compare)(const void *lhs, const void *rhs));



#endif   /*__SORT_H__*/
