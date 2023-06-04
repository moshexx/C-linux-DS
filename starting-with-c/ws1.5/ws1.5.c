/*
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	

	return 0;	
}
*/

/* #exercise 1 */
#include <stdio.h>

void swapInt(int *a ,int *b )
{
	int temp = *a;
	*a = *b;
	*b = temp;
}



int main()
{	
	int a=2, b=5;
	
	printf("a=%d\nb=%d\n",a,b);
	
	swapInt(&a, &b);
	printf("a=%d\nb=%d\n",a,b);
	
	return 0;	
}


#/* #exercise 2 */
#include <stdio.h>

void copyArray(int arr[] , int size , int *arr_copy)
{
	int i;
	
	for (i=0 ; i<size ; i++)
	{
		arr_copy[i]=arr[i];
	}
}

int main()
{
	int arr[5]={1,2,3,4,5}, int arr2[5]={0};
	int i;
	
	copyArray(arr,sizeof(arr)/sizeof(arr[0]),arr2);
	
	for(i=0 ; i<sizeof(arr)/sizeof(arr[0]) ; i++)
	{
		printf("arr: %d ",arr[i]);
	}
	
	printf("\n");
	
	for(i=0 ; i<sizeof(arr)/sizeof(arr[0]) ; i++)
	{
		printf("arr2: %d ",arr2[i]);
	}
	
	return 0;	
}


/* #exercise 3 */
#include <stdio.h>
#include <stdlib.h>

f(ptr)
{
	&ptr;
}
	
int main()
{
	static int s_i = 7;
	int i = 7;
	int *ptr = &i;
	int *ptr2 = (int *)malloc(sizeof(int));
	
	f(ptr);
	
	
	
	printf("\n &static int s_i = %p", &s_i);
	printf("\n &int i = %p", &i);
	printf("\n &ptr = %p", &ptr);	
	printf("\n &ptr2 = %p", &ptr2);
	printf("\n &f = %p", &f);
	printf("\n");
	
	free(ptr2);
	
	return 0;	
}
/* 
##
 &static int s_i = 0x5615e8c9f010
 &int i = 0x7ffd394602c4
 &ptr = 0x7ffd394602c8
 &ptr2 = 0x7ffd394602d0
 &f = 0x5615e8c9c1c9
אחסון בheap - הקצאה דינאמית- פונקציה f שנמצאת בזיכרון שהקצה לה הmalloc.
אחסון בdata section - משתנה סטאטי. The data section is used for declaring initialized data or constants. This data does not change at runtime. 
אחסון בstack - כל השאר. משתנים מקומיים, פוינטרים.
###################
*/

/* #exercise 4 - swap two pointers & two integers */ 

#include <stdio.h>
#include <stdlib.h>

void SwapPtr(int **a ,int **b ,int *z, int *y)
{
	int temp2 = *z;
	int *temp1 = *a;
	
	*a = *b;
	*b = temp1;
		
	*z = *y;
	*y = temp2;
}
	
int main()
{
	int y = 1 ,z = 2;
	int x = 5;
	int *a = NULL;
	int *b = &x;
	
	printf("The value of the pointers are:");
	printf("\na=%p\nb=%p\n",a,b);
	
	SwapPtr(&a ,&b ,&z ,&y);
	
	printf("After SwapPtr the value of the pointers are:");
	printf("\na=%p\nb=%p\n",a ,b);
	
	printf("The value of integers:");
	printf("\ny=%d\nz=%d\n",y ,z);
	
	return 0;	
}

/* question 6 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
	unsigned int *ip = 0; 
	float f = 3;
	float *fp = &f;
	ip = (unsigned int *) fp;
	printf("%u\n", *ip); // adress of f
	
	return 0;	
}

/* question 7 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *p = (int*)17;
	printf("\n%d\n" , (int)(long)(p));
	printf("%d\n", (int)(long)(p + 4)); //17+4*4=33
	
	return 0;	
}

/* question 8 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
	size_t i = 3; //משתנה מסוג size_t בשם i
	size_t array[] = {0, 1 ,2 ,33 ,4 ,5}; 
	printf("%lu\n", i[array]); //print 33
	
	return 0;
}


/* Questions - strings */

/* 1 - StrLen */
#include <stdio.h>
#include <string.h>
#include <assert.h>

int StrLen (char *str1)
{
	size_t lenth = 0;
	
	while (*str1 != '\0')
	{
		str1++;
		lenth++;
	}
	
	 assert('\0' == *str1);
	 assert(6 == lenth);

	return lenth;
}

int main()
{
	int len=0;
	char str1[]="hello!";
	
	len = StrLen(str1);
	printf("%d\n",len);
	
	return 0;
}

/* Note that the strlen() function doesn't count the null character \0 while calculating the length. */


/* 2 - StrCmp */
#include <stdio.h>
#include <string.h>
#include <assert.h>

int StrCmp(const char *str1 ,const char *str2)
{
	while (*str1 == *str2)
	{
		if ('\0' == *str1) /*אם 2 המחרוזות הגיעו ל\0 אזי שהן נגמרו והן שוות*/
			return 0;
		*str1++;
		*str2++;
	}
	
	if (*str1 < *str2) /*ערך האסקי קטן יותר*/
	{
		return -1;
	}
	return 1;
	
}

int main()
{
	int cmp;
	char str1[]="hello ";
	char str2[]="World!";
	
	cmp = StrCmp(str1, str2);
	printf("%d\n",cmp);
	
	return 0;
}

/* advanced - exercise 13 */
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
	const char * str1 = NULL; 
	char const * str2; 
	char * const str3 = NULL; /*read only variable*/ 
	char* str4 = NULL;
	char* const str5;         /*read only variable*/
	
	/*all above are compile*/
	
	str1 = str2;
	str2 = str3;
	str4 = str3;
	/* str3 = str4; >>> str3 is read only variable. */
	str2 = str4;
	/* str4 = str2; >>> assignment discards ‘const’ qualifier from pointer target type < ניסיון השמה זה מפר את ההבטחה הקודמת שערך מחרוזת זו ישאר קבוע
	   str5 = str4; >>> str5 is read only variable.  */
	
	return 0;
}





