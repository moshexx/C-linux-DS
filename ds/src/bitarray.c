/****************************************************************************
*															 *
*	Worksheet: 	bitarray.c	 			 					 *
*	Author: 		Moshe Cohen 			    						 *
*	Reviewer: 	Yulia				    						 *
*	Date: 		26th October 2020 								 *
*															 *
*****************************************************************************/
#include <stddef.h> /* smallest lib of size_t */
#include <limits.h>	/* CHAR_BIT */
#include <assert.h>

#include "bitarray.h"

#define NUM_OF_BITS sizeof(bitarr_t) * CHAR_BIT  /* 64 */
/*#define ON 1
#define OFF 0*/

bitarr_t BitsArrSetAll(bitarr_t arr)
{
	arr = (size_t)(~0);

	return arr;
}

bitarr_t BitsArrResetAll(bitarr_t arr)
{
	arr &= (size_t)0;

	return arr;
}

char *BitArrToString(bitarr_t arr, char *dest)
{
	int i = 0; 	/* cause size_t can't be negative */

	dest [NUM_OF_BITS] = '\0';
	for (i = (NUM_OF_BITS -1) ; i >= 0 ; --i)
	{
	  if (arr & 1)
	  {
	  	dest[i] = '1';
	  }
	  else
	  {
 		dest[i] = '0';
	  }
	  arr >>= 1;
	}

	return dest;
}

bitarr_t BitsArrSetOn(bitarr_t arr, size_t index)
{
	assert(index <= NUM_OF_BITS); /* 64 */

	return (arr |= ((size_t)1 << index));
}

bitarr_t BitsArrSetOff(bitarr_t arr, size_t index)
{
	assert(index <= NUM_OF_BITS);

	return (arr &= ~((size_t)1 << index));
}

bitarr_t BitsArrSetBit(bitarr_t arr , size_t index, state_t bit_state)
{
	assert(index <= NUM_OF_BITS);

	switch (bit_state)
	{
		case ON:  arr = BitsArrSetOn(arr, index);
			   	  break;
		case OFF: arr = BitsArrSetOff(arr, index);
				  break;
	}

	return arr;
}

state_t BitsArrGetVal(bitarr_t arr, size_t index)
{
	assert(index <= NUM_OF_BITS);
	/* עם רוטציה לימין וגם עם 1 - יעיל יותר*/
	/* return (arr >> index)) && (ON); */
	return (arr & ((size_t)1 << index)) && (ON);
}

bitarr_t BitsArrFlipBit(bitarr_t arr, size_t index)
{
	assert(index <= NUM_OF_BITS);

	return arr ^ ((size_t)1 << index);
}

bitarr_t BitsArrMirror(bitarr_t arr)
{
	arr = ((arr & 0xFFFFFFFF00000000) >> 32) | ((arr & 0x00000000FFFFFFFF) << 32); /* 1*32, 0*32..up to 64 bit */
	arr = ((arr & 0xFFFF0000FFFF0000) >> 16) | ((arr & 0x0000FFFF0000FFFF) << 16); /* 1*16, 0*16..up to 64 bit */
	arr = ((arr & 0xFF00FF00FF00FF00) >> 8)  | ((arr & 0x00FF00FF00FF00FF) << 8);  /* 1*8, 0*8..up to 64 bit */
	arr = ((arr & 0xF0F0F0F0F0F0F0F0) >> 4)  | ((arr & 0x0F0F0F0F0F0F0F0F) << 4);  /* 11110000, 00001111..up to 64 bit */
	arr = ((arr & 0xCCCCCCCCCCCCCCCC) >> 2)  | ((arr & 0x3333333333333333) << 2);  /* 11001100, 00110011..up to 64 bit */
	arr = ((arr & 0xAAAAAAAAAAAAAAAA) >> 1)  | ((arr & 0x5555555555555555) << 1);  /* 101010, 01010101.. up to 64 bit */

	return arr;
}

bitarr_t BitsArrRotR(bitarr_t arr, size_t rotate_times)
{
	bitarr_t tmp;
	/* case the number of rotations is bigger than 64 bit */
	rotate_times %=  NUM_OF_BITS;

	tmp = (arr >> rotate_times);
	arr <<= (NUM_OF_BITS - rotate_times);
	arr |= tmp;

	return arr;
}

bitarr_t BitsArrRotL(bitarr_t arr, size_t rotate_times)
{
	bitarr_t tmp;
	/* case the number of rotations is bigger than 64 bit */
	rotate_times %=  NUM_OF_BITS;

	tmp = (arr << rotate_times);
	arr >>= (NUM_OF_BITS - rotate_times);
	arr |= tmp;

	return arr;
}

size_t BitsArrCountOn(bitarr_t arr)
{
	arr = (arr & 0x5555555555555555) + ((arr >> 1) & 0x5555555555555555); /* 01010101.. */
	arr = (arr & 0x3333333333333333) + ((arr >> 2) & 0x3333333333333333); /* 00110011.. */
	arr = (arr & 0x0f0f0f0f0f0f0f0f) + ((arr >> 4) & 0x0f0f0f0f0f0f0f0f); /* 00001111.. */
	arr = (arr & 0x00ff00ff00ff00ff) + ((arr >> 8) & 0x00ff00ff00ff00ff); /* 0000000011111111.. */
	arr = (arr & 0x0000ffff0000ffff) + ((arr >> 16) & 0x0000ffff0000ffff);/* 16*0 16*1 */
	arr = (arr & 0x00000000ffffffff) + ((arr >> 32) & 0x00000000ffffffff);/* 32*0 32*1 */

	return arr;
}

size_t BitsArrCountOff(bitarr_t arr)
{

	return (NUM_OF_BITS - BitsArrCountOn(arr));
}
