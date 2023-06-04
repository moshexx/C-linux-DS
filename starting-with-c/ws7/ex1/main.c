#include <stdio.h>
#include "g.h"

int main()
{
	g_s = 3;
	
	printf("\nBefore Foo():%d\n" ,g_s);
	Foo();
	printf("After Foo():%d\n" ,g_s);

	return 0;
}

