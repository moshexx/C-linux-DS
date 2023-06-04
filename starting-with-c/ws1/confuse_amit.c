#include<stdio.h>

int X=5;

int foo1()
{
	int x = 5;
	return (x++,++x);
}

int foo2()
{
	int x = 5;
	return (++x,x++);
}
int foo3()
{
	return X++;

}

int foo4()
{
	int y;
	y = foo3(),foo3(),foo3();
	return y;
}

int foo5()
{
	int z;
	z = (foo3(),foo3(),foo3());
	return z;
}

void main()
{
	printf("foo1 = %d\n",foo1());
	printf("foo2 = %d\n",foo2());
	printf("foo3 = %d\n",foo3());
	X = 5;
	printf("foo4 = %d\n",foo4());
	X = 5;
	printf("foo5 = %d\n",foo5());

}
