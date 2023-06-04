#include <stdio.h>

int reverseNum(int num)
{
	int newNum = 0;
	
	while (num)
	{
		newNum *= 10;
		newNum += num%10;
		num /= 10;
	}
	
	return newNum;
}

int main()
{
int num , newNum;

printf("Please enter a number:\n");
scanf("%d",&num);

newNum = reverseNum(num);
printf("\nThe reverse number of %d is %d.\n",num,newNum);

return 0;
}

