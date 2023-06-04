/*****************************************************************************
*																			 *
*	Worksheet: 	ws9.c	 			 										 *
*	Author: 	Moshe Cohen 			    								 *
*	Reviewer: 	Adi Cohen			    									 *
*	Date: 		22th October 2020 											 *
*																			 *
*****************************************************************************/
#include "ws9b.h"
#include <assert.h>

char *Itoa(int value, char *str)
{
	sprintf(str, "%d", value);
	
	return str;
}

int Atoi(const char *str)
{
	int num = 0;
	
	sscanf(str, "%d", &num);

	return num;	
}

int DecimalToLowBase(int decimal_num ,int base)
{
	int base_num = 0;
	int location = 1;
	
	while (decimal_num)
	{
		base_num += decimal_num % base*location;
		decimal_num /= base;
		location *= 10;
	}
	
	return base_num;
}

char *DecimalToHighBase(int decimal_num, char *str, int base)
{
	char base_num[100]; 
	int temp  = 0;  
	int i = 0;
	int j=0;
	int Fnegative = 0;
	
	if (decimal_num < 0)
	{
		decimal_num *= -1;
		str[i] = '-';
		++j;
		Fnegative = 1;
	}
	
	while(decimal_num != 0) 
	{    
		temp = 0;
		temp = decimal_num % base;
		decimal_num /= base; 
				
		if (temp < 10) 
		{ 
		/* +48 - to represent digit  in ASCII */
            base_num[i] = temp + 48; 
            ++i; 
		} 
		
		else
		{ 
		/* +55 - to represent A/B/C.. in ASCII */
            base_num[i] = temp + 55; 
            ++i; 
		}
	}    
	

	/* mirror the string: */
	if (!Fnegative)
	{
		str[i] = '\0' ;
		for (--i ; 0 <= i ; --i, ++j) 
		{
			str[j] = base_num[i];	
		}
	}
	
	else /* (Fnegative) */
	{
			str[i+1] = '\0' ;
		for (--i, j = 1; 0 <= i ; --i, ++j) 
		{
			str[j] = base_num[i];	
		}
	}
	
	return (str);
}

char *ItoaAnyBase(int value, char *str, int base)
{
	int base_num = 0;
	
	assert(0 < base);
	assert(NULL != str);
	
	if (10 == base)
	{
		return (Itoa(value, str));
	}
	
	else if(0 < base && base < 10)
	{
		base_num = DecimalToLowBase(value ,base);
		sprintf(str, "%d", base_num);
		
		return (str);
	}
	
	else if(10 < base && base <= 36)
	{
		DecimalToHighBase(value ,str ,base);
		return (str);
	}
	
	else
	{
		printf("Invalid base!\n 0 > base <= 36\n");
		
		return (str);
	}
}


int AtoiAnyBase(const char *any_base_num, int base) 
{    
	int i;
	int len = strlen(any_base_num); 
	int digit_place = 1; 
	int decimal_num = 0; 
      
    /* Extracting characters as digits from last character(LSB) */ 
	for (i = len - 1; i >= 0; --i) 
	{    
		if (any_base_num[i] >= '0' && any_base_num[i] <= '9') 
		{ 
			decimal_num += (any_base_num[i] - '0') * digit_place; 
		} 

		else if (any_base_num[i] >= 'A' && any_base_num[i] <= 'Z') 
		{ 
			decimal_num += (any_base_num[i] - 55) * digit_place; 
		} 
		digit_place *= base; 
	} 
      
	return decimal_num; 
} 

void ThreeArray(char *arr1, char *arr2, char *arr3, size_t first, size_t sec, size_t third)
{
	int ascii_histogram[256] = { 0 }; /*  = היסטוגרמה */
	size_t i;
	
	for (i = 0 ; i < first ; ++i)
	{
		ascii_histogram[ (int)(arr1[i]) ] = 1;
	}
	
	for (i = 0 ; i < third ; ++i)
	{
		ascii_histogram[ (int)(arr3[i]) ] = 0;
	}
	
	printf("The chars which apear arr1 & arr2 ~ arr3:\n");
	for (i = 0 ; i < sec ; ++i)
	{
		if (1 == ascii_histogram[ (int)(arr2[i]) ])
		{
			printf("%c ",arr2[i]);
			ascii_histogram[ (int)(arr2[i]) ] = 0;
		}
	}
	printf("\n");
}

int IsLittleEndian()
{
	int n = 1;

	if(*(char *)&n == 1) 
	{
		return(1);
	}
	
	return(0);
}



