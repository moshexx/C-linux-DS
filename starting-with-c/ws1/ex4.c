#include <stdio.h>
#define SIZE 14

void ascii_print()
{
	char arr_a[] = {0x22,0x48,0x65,0x6c,0x6C,0x6F,0x20,0x57,0x6F,0x72,0x6C,0x64,0x21,0x22 };
	printf("%s\n",arr_a);
}


int main()
{
	ascii_print();
	return 0;	
}

