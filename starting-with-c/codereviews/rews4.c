#include <stdio.h>
#include <stdlib.h> /*for system function */

void IfElsePrintChar(void);
void SwitchCasePrintChar(void);
void LUTPrintChar(void);
void PrintA(void);
void PrintT(void);
void Empty(void);

int main()
{
	system("stty -icanon -echo");
	LUTPrintChar();
	/* IfElsePrintChar(); */
	/* SwitchCasePrintChar(); */
	system("stty icanon echo");
	return 0;
}
		
void IfElsePrintChar(void)
{
	long unsigned int input;
	
	while (1)
	{
		input = getchar();
		if (65 == input)
		{	
			PrintA();
		}
		else if (84 == input)
		{	
			PrintT();
		}
		else if (27 == input)
			break;
		else
			continue;
	}
}

void SwitchCasePrintChar(void)
{
	long unsigned int input;
	input = getchar();
	switch ((long unsigned int)input)
	{
		case 65 :
			PrintA();
			SwitchCasePrintChar();
			break;
		case 84 :
			PrintT();
			SwitchCasePrintChar();
			break;
		case 27 :
			break;
		default :
			input = getchar();
			SwitchCasePrintChar();
	}
}

void LUTPrintChar(void)
{
	long unsigned int input;
	int i;
	void (*func_ptr[256])(void) = {NULL};
	
	input = getchar();

	for (i = 0; i < 255 ; ++i)
		func_ptr[i] = &Empty;

	func_ptr[65] = &PrintA;
	func_ptr[84] = &PrintT;
	
	while (27 != input)
	{
		func_ptr[input]();
		input = getchar();
	}
}

void PrintA(void)
{
	printf("A pressed\n");
}

void PrintT(void)
{
	printf("T pressed\n");
}

void Empty(void)
{
}

