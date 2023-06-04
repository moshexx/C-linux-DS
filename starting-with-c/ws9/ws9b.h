/*****************************************************************************
*																			 *
*	Worksheet: 	ws9.h	 			 										 *
*	Author: 		Moshe Cohen 			    							 *
*	Reviewer: 	Adi Cohen		    										 *
*	Date: 		20th October 2020 											 *
*																			 *
*****************************************************************************/
#ifndef __WS9B_H__
#define __WS9B_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* for both ws9b.c and test_ws9b.c */
#define IS_LITTLE_ENDIAN() (*(short*)"\x0001\0000" == 1)

/* convert int to string */
char *Itoa(int value, char *str);

/* convert string to int */
int Atoi(const char *str);

/* convert int type decimal number to base 0-9 (int) */
int DecimalToLowBase(int decimal_num ,int base);


/* convert int type decimal number to base 11-36 (string) */
char *DecimalToHighBase(int decimal_num, char *str, int base);

/* convert int decimal number to any base number as a string */
char *ItoaAnyBase(int value, char *str, int base);

/* convert string type number from any base to decimal (int) */
int AtoiAnyBase(const char *any_base_num, int base);

/* print the chars which appear in both arr1 and arr2 but don't appear in arr3 */
void ThreeArray(char *arr1, char *arr2, char *arr3,
		 size_t first, size_t sec, size_t third);

/* If you want to know if your computer is Indian use this */
int IsLittleEndian();


#endif /* __WS9B_H__ */



