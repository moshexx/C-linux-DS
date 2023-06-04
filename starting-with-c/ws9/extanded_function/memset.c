#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define WORD (sizeof(size_t))

void  *MemSet(void *s, int c, size_t n)
{
	unsigned char *p = s;	
	size_t i;
	size_t remainder;
	size_t mask = (0 | c);
	

	for(i = 0 ;i < WORD ;++i)
	{
		mask = ((mask << WORD) | c); /* mask = $$$$$ השמה */
	} 
	remainder = ((size_t )s) % WORD;  	/* האם אני לא בתחילת צ'אנק? */
	
	/* first - set "byte byte" in the middle of the chunk */
	while(remainder)				/*  במידה ויש שארית אני באמצע צ'אנק - השמה אחד אחד */
 	{
		*p = c;
		++p;
		--remainder;
		--n;
	}
	
	/* in the middle - set one word when we are in a start of a chunk" */
	while (n >= WORD)
	{
		(*(size_t *)p) = mask;
		p += WORD;              /*** check syntax ***/
		n -= WORD;
	}       
	
	/* finally - set the rest of the bytes "byte byte" - because we are 
	   in the middle of the chunk (again) */
	while (n)
	{
		*p = c;
		++p;
		--n;
	}
    
  	
  	return((size_t *)(s));				/* return the adress of the original pointer */
}


int main()
{
	char *str = (void *)malloc(sizeof(size_t) * 20);
	char *str2 = (void *)malloc(sizeof(size_t) * 20);
	
	MemSet(str, 'a', 12);
	printf("MemSet: %s\n", str);
	
	memset(str2, 'a', 12);
	printf("memset: %s\n", str2);
 	
 	free(str);
 	free(str2);   
	return 0;
}

