#include <stdio.h>
#include <stdlib.h> /*for system function */


/* void (*lut[256])(void); */  /*This is another option to declare *lut[256]() - as a global variable. in this case I can put just NULL in the rest of the array members(indexes) */ 

void clearInputBuffer();
void PressIf();
void PressSwitch();
void PressA();
void PressT();
void Lazy();
void PressLUT();

int main()
{
	int choose;
	
	printf("You have 3 option the function can occure,\nPress 1 for ""if-else""\nPress 2 for ""switch-case""\npress 3 for LUT(Please Don't!)\n");
	scanf("%d" ,&choose);
	clearInputBuffer();
	
	system("stty -icanon -echo");
	if (1 == choose)
	{
		PressIf();
	}
	
	if (2 == choose)
	{
		PressSwitch();
	}
	
	if (3 == choose)
	{
		PressLUT();
	}
	system("stty icanon echo");
	
	return 0;
}

/***************************/

void clearInputBuffer() /* works only if the input buffer is not empty */
{
	char c;
	do 
	{
        c = getchar();
	} while (c != '\n' && c != EOF);
}

void PressIf()
{
	char press;
	int flag = 1;
	
	printf("\nWelcome to |If - Else|:\n");
	printf("\nPlease enter ""T"" or ""A"",\tPress ESC to exit:\n");
	
	do
	{
		scanf("%c" ,&press);
		if ('T' == press || 't' == press)
		{
			printf("T Pressed\n");
		}
		
		else if ('A' == press || 'a' == press)
		{
			printf("A Pressed\n");
		}
		
		else if (27 == press)
		{
			flag = 0;
			printf("Bye! \n");
		}
		else 
		{
			printf("please choose A or T.\n");
		}
	} while (flag);
	
}

void PressSwitch()
{
	char press;
	int flag = 1;
	
	printf("\nWelcome to |Switch - Case|:\n");
	printf("\nPlease enter ""T"" or ""A"",\tPress ESC to exit:\n");
	
	do
	{
		scanf("%c" ,&press);
		switch (press)
		{
			case 't' : printf("t Pressed\n");
				break;
			case 'T' : printf("T Pressed\n");
				break;
			case 'a' : printf("a Pressed\n");
				break;
			case 'A' : printf("A Pressed\n");
				break;
			case 27 :         flag = 0;
				break;
			default:   printf("please choose A or T.\n");
				continue;
		}	

	} while (flag);
	
	printf("Good bye :)\n");

}

void PressA()
{
	printf("A Pressed\n");
}

void PressT()
{
	printf("T Pressed\n");
}

void Lazy()			/* an empty function just to fulfill the array */
{
}

void PressLUT()
{
	char press;
	int flag = 1;
	size_t i = 0;
	void (*lut[256])();			/* declare a pointer to arr with 256 pointers to functions. the functions get NO arguments and return void. */
	
	printf("\nWelcome to |LUT|:\n");
	printf("\nPlease enter ""T"" or ""A"",\tPress ESC to exit:\n");
	
	for (i = 0 ; i < 256 ; ++i)
	{
		lut[i] = Lazy;
	}
	
	lut['A'] = PressA;
	lut['T'] = PressT;
	lut['a'] = PressA;
	lut['t'] = PressT;
	
	do
	{
		scanf("%c" ,&press);
		if (27 == press)							/*if the user press Esc*/
		{
			flag = 0;
		}
		else if ('T' == press || 't' == press || 'A' == press || 'a' == press)
		{
			lut[(unsigned int)press]();                 /*as we asked - cast to unsigned*/
		}
		else
		{
			printf("please choose A or T.\n");
		}
	} while(flag);
	
}

/* notes for void clearInputBuffer()
getchar() returns the first character in the input buffer, and removes it from the input buffer. But other characters are still in the input buffer (\n in your example). You need to clear the input buffer before calling getchar() again:
*/
