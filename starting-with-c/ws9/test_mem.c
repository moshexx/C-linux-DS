/****************************************************************************
*															 *
*	Worksheet: 	ws8.c	 			 						 *
*	Author: 		Moshe Cohen 			    						 *
*	Reviewer: 	Roy Chen				    						 *
*	Date: 		19th October 2020 								 *
*															 *
*****************************************************************************/
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>


int MemSetTest();
int MemCpyTest();
int MemMoveTest();

int main()
{
	MemSetTest();
	MemCpyTest();
	MemMoveTest();

	printf("\033[1;31m");
	printf("\nThe tests are over :) \n");
	printf("\033[0m;");

    return 0;
}

int MemSetTest()
{
	char *str = (char *)malloc(sizeof(char) * 10);
	char *str2 = (char *)malloc(sizeof(char) * 10);
	
	MemSet(str, 'a', 4);
	memset(str2, 'a', 4);
 	
 	if(0 != memcmp(str, str2, 4))
 	{
 		printf("EROR: MemSetTest\n");
 	}
 	
 	free(str);
 	free(str2);  
 	 
	return 0;
	
}

int MemCpyTest()
{
	char *str = (void *)malloc(sizeof(size_t) * 20);
	char *str2 = (void *)malloc(sizeof(size_t) * 20);
	char str3[] = "HelloHelloHello";
	
	MemCpy(str ,str3 ,12);
 	if(0 != memcmp(str, str3, 12))
 	{
 		printf("EROR: MemCpyTest\n");
 	}
 	
 	free(str);
 	free(str2);  
 	  
	return 0;
}

int MemMoveTest()
{
	
	char *str = (void *)malloc(sizeof(size_t) * 20);
	char *str2 = (void *)malloc(sizeof(size_t) * 20);
	char str3[] = "HelloHelloHello";
	
	char src[100] = "MosheCoh"; 
	char src2[100] = "MosheCoh";
	
	MemMove(src + 5, src, strlen(src) + 1); 
	memmove(src2 + 5, src2, strlen(src2) + 1);

	if(0 != memcmp(src, src2, 4))
 	{
 		printf("EROR: MemMoveTest1\n");
 	}
	
	MemMove(str ,str3 ,12);
	memmove(str2 ,str3 ,12);
 	if(0 != memcmp(str ,str2 ,12))
 	{
 		printf("EROR: MemMoveTest2\n");
 	}
 	
 	free(str);
 	free(str2); 
 	
	return 0;
}

