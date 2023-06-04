#include <stdio.h>

int tenPowerNum(int num)
{
	int newNum=1,i;
	
	for(i=0;i<num;i++)
	{
		newNum *= 10;
	}
	return newNum;
}

int main()
{
int num,newNum;

printf("Please enter a number:\n");
scanf("%d",&num);

newNum = tenPowerNum(num);
printf("\n10 power %d is %d.\n",num,newNum);


return 0;
}
