#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WORD (sizeof(size_t))

void *MemMove(void *dest, const void *src, size_t n)
{
	size_t i;
	void *dest_copy = dest;
	
	if (src < dest)
	{
		while (n)
		{
			*((unsigned char *)dest + n-1) = *((unsigned char *)src + n-1);
			--n;
		}
	}
	else if (src > dest)
	{
		for(i = 0 ;i < n ;++i)
		{
			*((unsigned char *)dest + i) = *((unsigned char *)src + i);
		}	
	}
	return (dest_copy);
} 

int main()
{
	char *str = (void *)malloc(sizeof(size_t) * 20);
	char *str2 = (void *)malloc(sizeof(size_t) * 20);
	char str3[] = "HelloHelloHello";
	char src1[100] = "MosheCoh"; 
	char src2[100] = "MosheCoh"; 
	
	char s11[] = "abcdegg123456";
	char s12[] = "abcdegg123456";

    
    
	/* OEVERLAPING example */
	char src[100] = "MosheCoh"; 
	MemMove(src + 5, src, strlen(src) + 1); 
	printf("%s\n\n", src); /* PRINT: MosheMosheCoh */
	/* Chen Mana check - return value check */
	printf("%s\n", (char *)MemMove(src1, src1 + 5 , 4));
	printf("%s\n", (char *)memmove(src2, src2 + 5 , 4));

	/* No OEVERLAPING example */
	MemMove(str ,str3 ,12);
	printf("\n(n = 12)\nstr_dest:%s \nstr_src :%s\n\n" ,str ,str3); 
 	
 	
 	printf("return MemMove: %s\n", (char*)MemMove(s11, s11+3, 16));
	printf("return memmove: %s\n\n", (char*)memmove(s12, s12+3, 16));
	printf("dest MemMove: %s\n", s11);
	printf("dest memmove: %s\n\n", s12);
	
 	free(str);
 	free(str2);   
	return 0;
}


