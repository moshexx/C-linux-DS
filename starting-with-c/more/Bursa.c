/****************************************************************************
*															 *
*	Worksheet: 		 			 						 *
*	Author: 		Moshe Cohen 			    						 *
*	Reviewer: 				    						 *
*	Date: 		20th October 2020 								 *
*															 *
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int arr[] = { 5 ,7 ,8 ,2 ,3 };
	int min = arr[0];
	int max = arr[0];
	int profit;
	size_t i ,j ,max_index = 1 ,min_index = 0;
	size_t size = sizeof(arr)/sizeof(arr[0]);
	
	for (i = 0 ,j=1 ;j < size ; ++i ,++j )
	{
		if(arr[i] < min &&  max_index > min_index)
		{
			min_index = i;
			min = arr[i];
		}
		if(arr[j] > max)
		{
			max = arr[j];
			max_index = j;
		}
	}
 
 	profit = max - min;
 	
 	printf("the buy index is [%lu]\nthe sell index is [%lu]\nthe profit is %d.\n" ,min_index ,max_index ,profit);
    return 0;
}
