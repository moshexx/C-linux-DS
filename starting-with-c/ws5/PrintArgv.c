#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


int main(int argc ,char *argv[] ,char *envp[])
{
	size_t i=0;
	
	for(i=0 ; i<argc ; ++i)
	{
		printf("Arg %d = %s\n" ,i ,argv[i]);
	}
	return 0;
}


