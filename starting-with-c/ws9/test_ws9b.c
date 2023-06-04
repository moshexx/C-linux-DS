/****************************************************************************
*															 *
*	Worksheet: 	test_ws9.c	 			 						 *
*	Author: 		Moshe Cohen 			    						 *
*	Reviewer: 	Adi Cohen		    								 *
*	Date: 		20th October 2020 								 *
*															 *
*****************************************************************************/
#include "ws9b.h"


int main()
{
	int n;
	char str1[10];
	int num1 = 10;
	char str2[] = "102";
	int num2;
	char *str3;
	char *str4 ="DC";
	char str5[10];
	char arr1[] = { '1','2','3','4','5','6','7','8','9' };
	char arr2[] = { '1','2','3','4','5' };
	char arr3[] = { '1','2','3' };
	size_t first = sizeof(arr1)/sizeof(arr1[0]);
	size_t sec = sizeof(arr2)/sizeof(arr2[0]);
	size_t third = sizeof(arr3)/sizeof(arr3[0]);
	
	
	Itoa(num1, str1);
	printf("Itoa: num1(10) is %s\n", str1);
	
	num2 = Atoi(str2);
	printf("Atoi: num2(""102"") is %d\n", num2);
	
	printf("Test NumBase:\n");
	num2 = DecimalToLowBase(220 , 8);
	printf("Decimal 220 in base 8 = %d\n", num2);
	num2 = DecimalToLowBase(220 , 2);
	printf("Decimal 220 in base 2 = %d\n", num2);
	DecimalToHighBase(220 ,str1, 16);	/*PRINT: * DC */
	printf("\n%s\n", str1);	
	

	
	str3 = ItoaAnyBase( 220,  str1,  16);
	printf("\nItoaAnyBase(DC):%s\n", str1);	
	printf("%s\n", str3);

	ItoaAnyBase(-1023, str5, 16);
	printf("\nItoaAnyBase(-3FF):%s\n", str5);	

	num2 = AtoiAnyBase(str4, 16);
	printf("AtoiAnyBase: DC base16 in Decimal  = %d\n", num2); /* 220*/
	printf("AtoiAnyBase: Decimal 220 in base 16 = %d\n", AtoiAnyBase(str4, 16));
	
	printf("ThreeArray:\n");
	ThreeArray(arr1,  arr2,  arr3, first, sec, third);

	n = IsLittleEndian();
	printf("Is Little?%d\n", n);
	
	/* MACRO */
    IS_LITTLE_ENDIAN() == 1 ? printf("Little\n"): printf("Big\n");
	
    return 0;
}

