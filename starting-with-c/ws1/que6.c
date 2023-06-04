
#include <stdio.h>

int main ()
{

	int arr[10]={0},i=0;

	printf("%d %d",arr[i],i);

	arr[i]=i++;

	printf("%d %d",arr[i],i);

	return 0;
}
