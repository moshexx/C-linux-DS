/********************************************
*File name: ws6.c
Author: Moshe Cohen
Reviwer:  Roy Halperin
*******************************************/
#include <stdio.h>
#include "ws6.h"

#define CHAR_BITS  8  /* size of character */
#define INT_BITS  ( sizeof(int) * CHAR_BITS)

/* return from function:    x * (2 ^ y); */
long Pow2(unsigned int x, unsigned y)
{
	long ans;
	
	ans = x << y; 

	return ans;
}

/* Use to print the data in binary format */
void PrintInBinary(unsigned n)
{
	int i;
	
	for (i = (INT_BITS -1) ; i >= 0 ; --i)	
	{
	  (n & (1 << i))? printf("1"): printf("0");	
	}
	printf("\n");
}

/* Function to get number of '1' bits in binary 
   representation */
unsigned int Count(unsigned int n) 
{ 
    unsigned int count = 0;
     
    while (n) 
    { 
        count += n & 1; 
        n >>= 1; 
    } 
    
    return count; 
} 

/* count bits witout loop - until int 15 (2^4-1) */
unsigned int CountNoLoop(unsigned int n)
{
	unsigned int count = 0; 
	
	/* count = ((n >>3 ) & 1)+((n >> 2) & 1)+((n >> 1) & 1)+(n & 1); */
	/*
	n = (n & 0x5555555555555555) + ((n >> 1) & 0x5555555555555555); /*01010101..*/
    /*n = (n & 0x3333333333333333) + ((n >> 2) & 0x3333333333333333); /*00110011..*/
   /* n = (n & 0x0f0f0f0f0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f0f0f0f0f); /*00001111..*/
    /*n = (n & 0x00ff00ff00ff00ff) + ((n >> 8) & 0x00ff00ff00ff00ff); /*0000000011..*/
    /*n = (n & 0x0000ffff0000ffff) + ((n >> 16) & 0x0000ffff0000ffff);/*16*0 16*1*/
    */
	count = n - ((n >> 1) & 033333333333) - ((n >> 2) & 011111111111);
	return ((count + (count >> 3)) & 030707070707) % 63; 
    /* return __builtin_popcount(num); */

	return count; 
}

/* ex 2 - loop*/
int IsPow2(unsigned int n) 
{
	unsigned int count = Count(n);
	
	if (count == 1)
	{
		/* case n is power of 2 */
		return 1;	
	}
	/* case n is NOT power of 2 */
	return 0; 
}  			

/* ex 2 - No loop. HammingWeight */
int IsPow2NoLoop(unsigned int n)
{
	if (n && ( ! (n & (n - 1) ) ) )
	{
		return (1);
	}
	else
	{
		return (0);
	}
	
}

/* ex 3 - add 1 without using operators */
unsigned int Add1(unsigned int n)
{
	/* phase 1: num = not n
	   phase 2: -num  */
	return (-(~n));
}

/* ex4 print only the members with three '1' bits*/
int Print3BitsOn(unsigned int arr[] ,int size)
{
	int i = 0;
	
	for (i = 0 ;i < size ;++i)
	{
		if( 3 == Count(arr[i]) )
		printf("%d\n" ,arr[i]);
	}
	return 0;
}

/* ex5 - version 1: byte mirror ex. 10001110 to 01110001 */
unsigned int ByteMirror(unsigned int n)
{
    unsigned int count = (INT_BITS -1); 
    unsigned int tmp = n;          
	
	PrintInBinary(n);
	n >>= 1; 
    
	while(n)
	{
		tmp <<= 1;         
		tmp |= n & 1; 
		n >>= 1; 
		count--;
	}
    
    tmp <<= count; 
    PrintInBinary(tmp);
    return tmp;
}

/* ex5 - no loop */
unsigned int ByteMirrorNoLoop(unsigned int n)
{
	n = (((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1));
	n = (((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2));
	n = (((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4));
	n = (((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8));

	return((n >> 16) | (n << 16));
}

void Swap(int *num1 ,int *num2)
{
	 *num1 ^= *num2;
	 *num2 ^= *num1;
	 *num1 ^= *num2;
}

/* מספר שהוא כפולה של 16, הוא מספר ש4 הביטים הימניים שלו מאופסים */
unsigned int Closest(unsigned int num)
{
				/* 1111111.....0000 */
	unsigned int a = 0xfffffff0;
	
	a = a & num;
	
	return a;
}

/* This function return 1 only if the bits in 2 & 6 are both set 
 The counting start from 0! (char 'D'==70)*/
unsigned int NotIf1(unsigned char c)
{
	printf("Notice!\nThe function counts the locations of bits from 0(not 1)\n");
	if( (c & (1<<2)) && ((c & (1<<6))) )
	{
		return 1;
	}
	
	return 0;
}

/* This function return 1 only if the bits in 2 | 6 are set */
unsigned int NotIf2(unsigned char c)
{
	printf("Notice!\nThe function counts the locations of bits from 0(not 1)\n");
	if( (c & (1 << 2)) || ((c & (1 << 6))) )
	{
		return 1;
	}
	
	return 0;
}

unsigned int NotIf3(unsigned int n)
{
	unsigned int temp = 0;
	
	printf("Notice!\nThe function counts the locations of bits from 0(not 1)\n");
	temp = ((1 & (n >> 3)) ^ (1 & (n >> 5)));
	
	return (n ^ (temp << 3 | temp << 5));
}

void FloatAnalysis(float n)
{
	int i;
	int *f = NULL;
	f = (int *) &n;
	
	
	for (i = (INT_BITS - 1) ; i >= 0 ; --i)	
	{
	  (*f & (1 << i))? printf("1"): printf("0");	
	  if (31 == i || 23 == i)
	  printf(" .");
	}
	printf("\nsign bits .exponent bits .mantissa bits\n");
}
