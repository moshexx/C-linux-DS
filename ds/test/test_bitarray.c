/****************************************************************************
*															 *
*	Worksheet: 	test_bitarray.c	 							 *
*	Author: 		Moshe Cohen 			    						 *
*	Reviewer: 	Yulia				    						 *
*	Date: 		26th October 2020								 *
*															 *
*****************************************************************************/

#include<stdio.h>
#include <string.h> /* for strcmp */
#include "bitarray.h"


#define GREEN_COLOR     "\x1b[0;32m"
#define RED_COLOR     "\x1b[0;31m"
#define DEFAULT_COLOR    "\x1b[0;0m"

#define RUN_TEST(result, name) {\
            printf("Test %s: ", name);\
            if (result)\
            {\
                printf(GREEN_COLOR);\
                printf("Success\n");\
                printf(DEFAULT_COLOR);\
            }\
            else\
            {\
                printf(RED_COLOR);\
                printf("Fail\n");\
                printf(DEFAULT_COLOR);\
            }\
        }

size_t SetAll(bitarr_t arr);
size_t TestSetAll();
size_t RestAll(bitarr_t arr);
size_t TestResetAll();
size_t TestToString();
size_t TestSetOn();
size_t TestSetOff();
size_t TestSetBit();
size_t TestGetVal();
size_t TestFlipBit();
size_t TestMirror();
size_t TestRotR();
size_t TestRotL();
size_t TestCountOn();
size_t TestCountOff();

int main()
{
	RUN_TEST(TestSetAll(), "BitsArrSetAll");
	RUN_TEST(TestResetAll(), "BitsArrResetAll");
	RUN_TEST(TestToString(), "BitArrToString");
	RUN_TEST(TestSetOn(), "BitsArrSetOn");
	RUN_TEST(TestSetOff(), "BitsArrSetOff");
	RUN_TEST(TestSetBit(), "BitsArrSetBit");
	RUN_TEST(TestGetVal(), "BitsArrGetVal");
	RUN_TEST(TestFlipBit(), "BitsArrFlipBit");
	RUN_TEST(TestMirror(), "BitsArrMirror");
	RUN_TEST(TestRotR(), "BitsArrRotR");
	RUN_TEST(TestRotL(), "BitsArrRotL");
	RUN_TEST(TestCountOn(), "BitsArrCountOn");
	RUN_TEST(TestCountOff(), "BitsArrCountOff");



	/* other option to do tests - by Nir
	RUN_TEST((0 == BitsArrRotR(0, 2)), "BitsArrRotR 1");
	RUN_TEST((1 == BitsArrRotR(2, 1)), "BitsArrRotR 2");
	RUN_TEST((0x8000000000000000 == BitsArrRotR(1, 1)), "BitsArrRotR 3");
	RUN_TEST((((size_t)(1) << 63) == BitsArrRotR(1, 1)), "BitsArrRotR 4");
	RUN_TEST((((size_t)(1) << 63) == BitsArrRotR(1, 65)), "BitsArrRotR 5");
    */
 	return 0;
}

size_t SetAll(bitarr_t arr)
{
	bitarr_t comp  = ~0;
	
	if(BitsArrSetAll(arr) != comp)
	{	
		printf("test SetAll failed with array of %lu \n", arr);	
		return 0;
	}
	
	return 1;
}

size_t TestSetAll()
{
	size_t res = 0;
	
	res += SetAll(~0);
	res += SetAll(0);
	res += SetAll(81451321465564658);
	
	return(res == 3);
}  

size_t ResetAll(bitarr_t arr)
{
	bitarr_t comp = 0;
	
	if (BitsArrResetAll(arr) != comp)
	{
		printf ("test RestAll failed with array of %lu \n", arr);
		return 0;
	}
	
	return 1;
}

size_t TestResetAll()
{
	size_t res = 0;
	
	res += ResetAll(~0);
	res += ResetAll(0);
	res += ResetAll(81451321465564658);
	
	
	return(res == 3);
}

size_t TestToString()
{
	
	bitarr_t comp1 = 255;
	bitarr_t comp2 = 12;
	bitarr_t comp3 = 0;
	size_t res = 0;
	char tmp[100];
	
	/* Dont forget if both string are equal strcmp return 0 */
	if (!strcmp(BitArrToString(comp1, tmp), "0000000000000000000000000000000000000000000000000000000011111111"))
	{
		++res;
	}
	else
	{
		printf ("test ToString failed with array of %lu \n", comp1);
	}
	
	if (!strcmp(BitArrToString(comp2, tmp), "0000000000000000000000000000000000000000000000000000000000001100"))
	{
		++res;
	}
	else
	{
		printf ("test ToString failed with array of %lu \n", comp2);
	}
	
	if (!strcmp(BitArrToString(comp3, tmp), "0000000000000000000000000000000000000000000000000000000000000000"))
	{
		++res;
	}
	else
	{
		printf ("test ToString failed with array of %lu \n", comp3);
	}
	
	return (3 == res);
}



size_t TestSetOn()
{
	bitarr_t comp1 = 5555;
	bitarr_t comp2 = 12;
	bitarr_t comp3 = 0;
	size_t res = 0;
	
	
	if (BitsArrSetOn(comp1, 3) == 5563)
	{
		++res;
	}
	else
	{
		printf ("test SetOn failed with array of %lu \n", comp1);
	}
	
	if (BitsArrSetOn(comp2, 3) == 12)
	{
		++res;
	}
	else
	{
		printf ("test SetOn failed with array of %lu \n", comp2);
	}
	
	if (BitsArrSetOn(comp3, 5) == 32)
	{
		++res;
	}
	else
	{
		printf ("test SetOn failed with array of %lu \n", comp3);
	}
	
	return (3 == res);
	
}

size_t TestSetOff()
{
	bitarr_t comp1 = 5555;
	bitarr_t comp2 = 12;
	bitarr_t comp3 = 1835023;
	size_t res = 0;
	
	
	if (BitsArrSetOff(comp1, 12) == 1459)
	{
		++res;
	}
	else
	{
		printf ("test SetOff failed with array of %lu \n", comp1);
	}
	
	if (BitsArrSetOff(comp2, 3) == 4)
	{
		++res;
	}
	else
	{
		printf ("test SetOff failed with array of %lu \n", comp2);
	}
	
	if (BitsArrSetOff(comp3, 19) == 1310735)
	{
		++res;
	}
	else
	{
		printf ("test SetOff failed with array of %lu \n", comp3);
	}
	
	return (3 == res);
}

size_t TestSetBit()
{
	bitarr_t comp1 = 5555;
	bitarr_t comp2 = 12;
	bitarr_t comp3 = 256;
	size_t res = 0;
	
	
	if (BitsArrSetBit(comp1, 12, ON) == 5555)
	{
		++res;
	}
	else
	{
		printf ("test Setbit failed with array of %lu \n", comp1);
	}
	
	if (BitsArrSetBit(comp2, 3, OFF) == 4)
	{
		++res;
	}
	else
	{
		printf ("test Setbit failed with array of %lu \n", comp2);
	}
	
	if (BitsArrSetBit(comp3, 15, ON) == 33024)
	{
		++res;
	}
	else
	{
		printf ("test Setbit failed with array of %lu \n", comp3);
	}
	
	return (3 == res);
}

size_t TestGetVal()
{
	bitarr_t comp1 = 5555;
	bitarr_t comp2 = 12;
	bitarr_t comp3 = 256;
	size_t res = 0;
	
	
	if (BitsArrGetVal(comp1, 12) == ON)
	{
		++res;
	}
	else
	{
		printf ("test GetVal failed with array of %lu \n", comp1);
	}
	
	if (BitsArrGetVal(comp2, 3) == ON)
	{
		++res;
	}
	else
	{
		printf ("test GetVal failed with array of %lu \n", comp2);
	}
	
	if (BitsArrGetVal(comp3, 20) == OFF)
	{
		++res;
	}
	else
	{
		printf ("test GetVal failed with array of %lu \n", comp3);
	}
	
	return (3 == res);

}

size_t TestFlipBit()
{
	bitarr_t comp1 = 5555;
	bitarr_t comp2 = 12;
	bitarr_t comp3 = 256;
	size_t res = 0;
	
	if (BitsArrFlipBit(comp1, 12) == 1459)
	{
		++res;
	}
	else
	{
		printf ("test FlipBit failed with array of %lu \n", comp1);
	}
	
	if (BitsArrFlipBit(comp2, 2) == 8)
	{
		++res;
	}
	else
	{
		printf ("test FlipBit failed with array of %lu \n", comp2);
	}
	
	if (BitsArrFlipBit(comp3, 20) == 1048832)
	{
		++res;
	}
	else
	{
		printf ("test FlipBit failed with array of %lu \n", comp3);
	}
	
	return (3 == res);
}

size_t TestMirror()
{
	bitarr_t comp1 = 0xF800000000000000;
	bitarr_t comp2 = 3221225472;
	bitarr_t comp3 = 2290649224;
	size_t res = 0;
	
	if (BitsArrMirror(comp1) == 31)
	{
		++res;
	}
	else
	{
		printf ("test Mirror failed with array of %lu \n", comp1);
	}
	
	if (BitsArrMirror(comp2) == 12884901888)
	{
		++res;
	}
	else
	{
		printf ("test Mirror failed with array of %lu \n", comp2);
	}
	
	if (BitsArrMirror(comp3) == 1229782937960972288)
	{
		++res;
	}
	else
	{
		printf ("test Mirror failed with array of %lu \n", comp3);
	}
	
	return (3 == res);
}

size_t TestRotR()
{
	bitarr_t comp1 = 1;
	bitarr_t comp2 = 12;
	bitarr_t comp3 = 256;
	size_t res = 0;
	
	if (BitsArrRotR(comp1, 1) == 0x8000000000000000) 
	{
		++res;
	}
	else
	{
		printf ("test RotR failed with array of %lu \n", comp1);
	}
	
	if (BitsArrRotR(comp2, 2) == 3)
	{
		++res;
	}
	else
	{
		printf ("test RotR failed with array of %lu \n", comp2);
	}
	
	if (BitsArrRotR(comp3, 20) == 4503599627370496)
	{
		++res;
	}
	else
	{
		printf ("test RotR failed with array of %lu \n", comp3);
	}
	
	return (3 == res);
}

size_t TestRotL()
{
	bitarr_t comp1 = 12;
	bitarr_t comp2 = 12;
	bitarr_t comp3 = 256;
	size_t res = 0;
	
	if (BitsArrRotL(comp1, 6) ==  768) 
	{
		++res;
	}
	else
	{
		printf ("test RotL failed with array of %lu \n", comp1);
	}
	
	if (BitsArrRotL(comp2, 64) == 12) /* = 0 rotation */
	{
		++res;
	}
	else
	{
		printf ("test RotL failed with array of %lu \n", comp2);
	}
	
	if (BitsArrRotL(comp3, 65) == 512) /* = only 1 rotation */
	{
		++res;
	}
	else
	{
		printf ("test RotL failed with array of %lu \n", comp3);
	}
	
	return (3 == res);
}

size_t TestCountOn()
{
	bitarr_t comp1 = 5555;
	bitarr_t comp2 = 12;
	bitarr_t comp3 = 256;
	size_t res = 0;
	
	if (BitsArrCountOn(comp1) == 8)
	{
		++res;
	}
	else
	{
		printf ("test CountOn failed with array of %lu \n", comp1);
	}
	
	if (BitsArrCountOn(comp2) == 2)
	{
		++res;
	}
	else
	{
		printf ("test CountOn failed with array of %lu \n", comp2);
	}
	
	if (BitsArrCountOn(comp3) == 1)
	{
		++res;
	}
	else
	{
		printf ("test CountOn failed with array of %lu \n", comp3);
	}
	
	return (3 == res);
}

size_t TestCountOff()
{
	bitarr_t comp1 = 5555;
	bitarr_t comp2 = 12;
	bitarr_t comp3 = 256;
	size_t res = 0;
	
	if (BitsArrCountOff(comp1) == 56)
	{
		++res;
	}
	else
	{
		printf ("test CountOff failed with array of %lu \n", comp1);
	}
	
	if (BitsArrCountOff(comp2) == 62)
	{
		++res;
	}
	else
	{
		printf ("test CountOff failed with array of %lu \n", comp2);
	}
	
	if (BitsArrCountOff(comp3) == 63)
	{
		++res;
	}
	else
	{
		printf ("test CountOff failed with array of %lu \n", comp3);
	}
	
	return (3 == res);
}
