/********************************************************
*											 *
*	Worksheet: 	WS8(MACROS)	 		 		 *
*	Author: 		Moshe Cohen 			    		 *
*	Reviewer: 	Roy Chen				    		 *
*	Date: 		19th October 2020 				 *
*											 *
*********************************************************/
#include <stdio.h>
#define MAX2(a ,b) (a) > (b)? a : b
#define MAX3(a ,b ,c) MAX2(MAX2(a ,b) ,MAX2(b ,c)) 
#define SIZEOF_VAR(var) (char *)(&var+1)-(char*)(&var) 		 
#define SIZEOF_TYPE(type) ((size_t)((type *)0 + 1))

struct student
{
	int grade1;
	int grade2;
	char name[20];
} student1;

int main()
{
	int d = MAX2(5 ,12);
	int s = MAX3(5 ,12 ,3);
	int arr[] = {1 ,2 ,3 ,4 ,5};
	
	union numbers /* size of double = 8 byte. האיבר הכי גדול */
	{
		int i;
		float f;
		double d;
	};
	

	
	struct X /* size = 3 * 8 = 24 byte. int+char first ,double second ,short third*/ 
	{
		int i;
		char c;
		double d;
		short s;
	};
	   
	/* the size with padding will be 4 bytes(= 32 bit),
	2 bit + 4 bit = 6 bit
	padding will add 32 - 6 = 26 bits
	why? because padding will add empty bits up to 4 byte which
	is the sizeof type (unsigned int)
	*/   
	struct card  /* 4 byte */
	{
		unsigned int suit : 2; 
		unsigned int face_value : 4;
	};
	
	/* tests:
	printf("MAX2(5 ,12) = %d\n" ,d);
	printf("MAX3(5 ,12 ,3) = %d\n" ,s);
	printf("SIZEOF_VAR(d) = %ld\n", SIZEOF_VAR(d)); 
	printf("SIZEOF_VAR(arr[]) = %ld\n", SIZEOF_VAR(arr)); 
	printf("SIZEOF_VAR(student1(struct)) = %ld\n", SIZEOF_VAR(student1)); 
	printf("SIZEOF_TYPE(d) = %ld\n", SIZEOF_TYPE(int));
	
	
	printf("union numbers size: %lu\n" ,sizeof(union numbers));
	printf("struct X size: %lu\n" ,sizeof(struct X));
	printf("struct card size: %lu\n" ,sizeof(struct card));
	*/
		printf("struct card size: %lu\n" ,sizeof(struct card));
	return 0;
}


