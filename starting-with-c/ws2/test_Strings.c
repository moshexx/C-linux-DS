#include <stdio.h>
#include "Strings.h"
#include <assert.h>
#include <string.h>
#include <strings.h>            /* for strcasecmp & strncasecmp */
#include <ctype.h>
#include <stdlib.h>
/*#include "Strings.c" Do not write this line !*/


void TestStrCpy();
void TestStrNCmp();
void TestStrCaseCmp();
void TestStrChr();
void TestStrCat();
void TestStrNCat();
void TestStrStr();
void TestStrDup();
void TestStrSpn();

int main()
{    
	TestStrCpy();
	TestStrNCmp();
	TestStrCaseCmp();
	TestStrChr();
	TestStrCat();
	TestStrNCat();
	TestStrStr();
	TestStrDup();
	TestStrSpn();
	
	return 0;    
}

void TestStrCpy()
{    
	char src[] = "Hello World!";
	char dest[20];
	char *str = NULL;

	printf("\nStrCpy test:\n");
		    
	str = StrCpy(dest, src);
	printf("My StrCpy: %s\n", str);
	str = strcpy(dest, src);
	printf("Original strcpy: %s\n", str);
}

void TestStrNCmp()
{
	char str1[10] = "Hello";
	char str2[10] = " World!";
	char str3[10] = "Hello";
	int res1 ,res2 ,res3;
	
	printf("\nStrNCmp test:\n");
	
	res1 = StrNCmp(str1 ,str2 ,4);
	res2 = StrNCmp(str1 ,str3 ,5);
	res3 = StrNCmp(str3 ,str1 ,3);
	
	printf("my StrNCmp:\n");
	printf("str1 - str2 = %d\n" ,res1);
	printf("str1 - str3 = %d\n" ,res2);
	printf("str3 - str1 = %d\n" ,res3);
	
	printf("The original strncmp:\n");
	printf("str1 - str2 = %d\n" ,strncmp(str1 ,str2 ,4));
	printf("str1 - str3 = %d\n" ,strncmp(str1 ,str3 ,5));
	printf("str3 - str1 = %d\n" ,strncmp(str3 ,str1 ,3));
}

void TestStrCaseCmp()
{
	char str1[10] = "HEllo";
	char str2[10] = " World!";
	char str3[10] = "hello";
	int res1 ,res2 ,res3;
	
	printf("\nStrCaseCmp test:\n");
	
	res1 = StrCaseCmp(str1 ,str2);
	res2 = StrCaseCmp(str1 ,str3);
	res3 = StrCaseCmp(str3 ,str1);
	
	printf("my StrCaseCmp:\n");
	printf("str1 - str2 = %d\n" ,res1);
	printf("str1 - str3 = %d\n" ,res2);
	printf("str3 - str1 = %d\n" ,res3);
	
	printf("The original strcasecmp:\n");
	printf("str1 - str2 = %d\n" ,strcasecmp(str1 ,str2));
	printf("str1 - str3 = %d\n" ,strcasecmp(str1 ,str3));
	printf("str3 - str1 = %d\n" ,strcasecmp(str3 ,str1));
}

void TestStrChr()
{
	const char str[] = "I want to sleep!"; 
	const char ch = 'w'; 
	char *p;
	
	printf("\nmy StrChr:\n");
	p = StrChr(str, ch);
	printf("String starting from %c is: %s\n", ch, p);
}

void TestStrCat()
{
	char str1[20] = "Hello ";
	const char str2[] = "World!\n";
	
	printf("\nmy StrCat:\n");
	StrCat(str1 ,str2);
	printf("%s", str1);	
}

void TestStrNCat()
{
	char str1[20] = "Hello ";
	const char str2[] = "World!\n";
	
	printf("\nmy StrNCat:\n");
	StrNCat(str1 ,str2 ,3);
	printf("%s", str1);
	printf("\n");	
}

void TestStrStr()
{
	const char *str = "Hello World!";
	const char *sub_str = "World";
	char *ptr;
	
	printf("\nMy StrStr:\n");
	ptr = StrStr(str ,sub_str);
	printf("First occurrence of string '%s' in '%s' is '%s'", sub_str, str, ptr);
 	printf("\nThe sub string of |%s| is |%s|. \nIn adress |%p|.\n", str ,ptr ,ptr); 
}

void TestStrDup()
{
	char src[] = "Helloween";
	char *dest = StrDup(src);
	
	printf("\nMyStrDup:\n");
	printf("copy string: %s\n" ,dest);
	free(dest);
}

void TestStrSpn()
{
	int len = StrSpn("hello world","hel"); 
	int len2 = StrSpn("hello world","hel");
	
	printf("\nMy StrSpn:\n");
	printf("\nLength of initial segment matching : %d\n", len ); 
	printf("Original strspn : %d\n", len2 );
} 


