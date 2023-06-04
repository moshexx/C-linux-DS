#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WORD (sizeof(size_t))

void *MemCpy(void *dest, const void *src, size_t n)
{
	char *copy_src = (char *)src; 
	char *copy_dest = (char *)dest; 
	size_t remainder;

	remainder = ((size_t )dest) % WORD; 
	while (remainder)
	{
		*copy_dest = *copy_src;
		copy_src++;
		copy_dest++;
		--remainder;
		--n;
	}

	while (n >= WORD)  
	{
		*(size_t *)copy_dest = *(size_t *)copy_src;
		copy_src += WORD;
		copy_dest += WORD;              
		n -= WORD;
	}       

	while (n)
	{
		*copy_dest = *copy_src;
		copy_src++;
		copy_dest++;
		--n;
	}

	return (dest);	
}

int main()
{
	char *str = (void *)malloc(sizeof(size_t) * 20);
	char *str2 = (void *)malloc(sizeof(size_t) * 20);
	char str3[] = "HelloHelloHello";
	
	
	
	
		
	
	MemCpy(str ,str3 ,12);
	printf("str_dest:%s \nstr_src :%s\n" ,str ,str3); 
 	printf("size: %lu\n", strlen(str));
 	free(str);
 	free(str2);   
	return 0;
}

