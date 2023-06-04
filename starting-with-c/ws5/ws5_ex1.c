/********************************************
*File name: ws5_ex1.c
Author: Moshe Cohen
Reviwer:  Yoni
*******************************************/

#include <stdio.h>   /*for printf*/
#define SIZE 10

typedef struct print_me
{
	int x;
	void (*print)(int);
} print_me_t;

void InitializArr(print_me_t arr[] ,size_t size);
void Print(int num);
void PrintArr(print_me_t arr[] ,size_t size);
	
int main()
{
	print_me_t arr[SIZE]; 
	
	InitializArr(arr ,SIZE);
	PrintArr(arr ,SIZE);
	
	return 0;
}

void InitializArr(print_me_t arr[] ,size_t size)
{
	size_t i;
	
	for (i=0 ; i<size ; ++i)
	{
		arr[i].x = i;
		arr[i].print = Print;
	}
}
void Print(int num)
{
	printf("%d\n" ,num);
}

void PrintArr(print_me_t arr[] ,size_t size)
{
	size_t i;
	
	for (i=0 ; i<size ; ++i)
	{
		arr[i].print(arr[i].x);
	}
}
