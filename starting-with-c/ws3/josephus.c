#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int josephus(int n)
{
	int i;
	int enemies=n;
	int *arr = (int *)malloc(n * sizeof(int));
	if (NULL == arr)
	{
		printf("EROR: There is no enough memory space.\n");
		/* no need to free the memory because the malloc return NULL anyway*/
		return -1;
	}
	
	for(i = 0 ; i < n ; ++i)
	{
		arr[i] = 1;
	}
	/*i=0*/
	while(enemies > 1)
	{
		i++;
		while(0 == arr[i%n])
		{
			++i;
		}
		
		arr[i%n] = 0;
		--enemies;
		
		while(0 == arr[i%n])
		{
			++i;
		}
	}
	
	free(arr);
	return (i%n)+1;
}
int main()
{
	int n;
	int the_lone_survivor;
	
	printf("Commander!\nPlease enter the number of soldiers:\n");
	scanf("%d" ,&n);
	
	the_lone_survivor = josephus(n);
	
	printf("\nThe only and the one is soldier number |%d|.\n" ,the_lone_survivor); 
	return 0;	
}
