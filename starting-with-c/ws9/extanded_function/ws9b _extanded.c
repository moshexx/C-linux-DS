/****************************************************************************
*															 *
*	Worksheet: 	ws9.c	 			 						 *
*	Author: 		Moshe Cohen 			    						 *
*	Reviewer: 				    								 *
*	Date: 		20th October 2020 								 *
*															 *
*****************************************************************************/
#include "ws9b.h"

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
	int j;
	
	while(decimal_num != 0) 
	{    
		temp = 0;
		temp = decimal_num % base;
		
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
		decimal_num /= base; 
	}    
	
	/* PRINT CHECK
	for (j = i - 1 ; j >= 0 ; --j) 
	{
		printf( "%c", base_num[j]);
	}
	*/
	/* make arr of char to string: */
	str[i] = '\0' ;
	/* mirror the string: */
	for (--i, j = 0 ; i >= 0 ; --i, ++j) 
	{
		str[j] = base_num[i];	
	}
	
	return (str);
}

char *ItoaAnyBase(int value, char *str, int base)
{
	int base_num = 0;
	
	if (base == 10)
	{
		return (Itoa(value, str));
	}
	
	else if(base < 10)
	{
		base_num = DecimalToLowBase(value ,base);
		sprintf(str, "%d", base_num);
		
		return (str);
	}
	
	else if(base > 10 && base <= 36)
	{
		DecimalToHighBase(value ,str ,base);
		return (str);
	}
	
	else
	{
		printf("Invalid base!\n");
		
		return (str);
	}
}

/* decimal to any base */
int AtoiAnyBase(const char *any_base_num, int base) 
{    
	int i;
	int len = strlen(any_base_num); 
    /* Initializing base value to 1, i.e 16^0 */
	int digit_place = 1; 
	int decimal_num = 0; 
      
    /* Extracting characters as digits from last(right side) character(LSB) */ 
	for (i = len - 1; i >= 0; --i) 
	{    
        /* if character lies in '0'-'9', converting  
           it to integral 0-9 by subtracting 48 from 
           ASCII value. */
		if (any_base_num[i] >= '0' && any_base_num[i] <= '9') 
		{ 
			decimal_num += (any_base_num[i] - 48) * digit_place; 
		} 
  
        /* if character lies in 'A'-'F' , converting  
           it to integral 10 - 15 by subtracting 55  
           from ASCII value  */
		else if (any_base_num[i]>='A' && any_base_num[i]<='Z') 
		{ 
			decimal_num += (any_base_num[i] - 55) * digit_place; 
		} 
         /* incrementing base by power */
		digit_place *= base; 
	} 
      
	return decimal_num; 
} 

void ThreeArray(char *arr1, char *arr2, char *arr3, size_t first, size_t sec, size_t third)
{
	int arr_ascii[256] = { 0 };
	size_t i;
	
	for (i = 0 ; i < first ; ++i)
	{
		arr_ascii[ (int)(arr1[i]) ] = 1;
	}
	
	for (i = 0 ; i < third ; ++i)
	{
		arr_ascii[ (int)(arr3[i]) ] = 0;
	}
	
	printf("The chars which apear arr1 & arr2 ~ arr3:\n");
	for (i = 0 ; i < sec ; ++i)
	{
		if (1 == arr_ascii[ (int)(arr2[i]) ])
		{
			printf("%c ",arr2[i]);
			arr_ascii[ (int)(arr2[i]) ] = 0;
		}
	}
	printf("\n");
}

int IsLittleEndian()
{
	int n = 1;
	/*
	כאשר מערכת עובדת לפי little endian, אזי הByte הכי "חלש" יהיה בכתובת קטנה יותר, למשל מספר עשרוני מסוג int שייצוגו הבינארי הוא באמצעות 2 בתים
	הבית המשמעותי יותר יהיה בכתובת גבוהה יותר בזיכרון, כלומר, מתחילים לכתוב את הבית הראשון בכתובת הקטנה יותר, לכן, נעשה int num=1, נפנה למשתנה
	מסוג int באמצעות מצביע לchar כדי להסתכל על הבית הראשון מתוך ארבעה בתים. אם ה1 מאוחסן שם(00000001), אזי שמדובר במערכת מסוג little.
	במערכת מסוג big endian היינו מצפים שה00000001 יאוחסן בByte הרביעי מתוף ארבעה בתים (הbytes בתמונת מראה, לא הbits שמסודרים בתוך כל Byte!!!!!)
	*/
	if(*(char *)&n == 1) 
	{
		return(1);
	}
	
	return(0);
}



