/****************************************************************************
*															 *
*	Worksheet: 	mem.c	 			 						 *
*	Author: 		Moshe Cohen 			    						 *
*	Reviewer: 	Chen Mana				    						 *
*	Date: 		19th October 2020 								 *
*															 *
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "mem.h"


void *MemSet(void *s, int c, size_t n)
{
	unsigned char *p = s;	
	size_t i;
	size_t remainder;
	size_t mask = 0;
	
	/* mask --> cccccccc */
	for (i = 0 ;i < WORD ;++i)
	{
		mask = ((mask << WORD) | c); 
	} 
	remainder = ((size_t )s) % WORD;  	
	
	/* first - set "byte byte" in the middle of the chunk */
	while(remainder)				
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
		p += WORD;              
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
    
  	return((size_t *)(s));
}

void *MemCpy(void *dest, const void *src, size_t n)
{
	char *copy_src = (char *)src; 
	char *copy_dest = (char *)dest; 
	size_t remainder;

	/* הגדלת ראש - ניתן להכניס לכאן תנאי שבמידה ויש אובר לאפס אז משתמשים בממ מוב במקום - כמו לידור */
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

void *MemMove(void *dest, const void *src, size_t n)
{
	size_t i;
	void *dest_copy = dest;
	
	/* יעילות -  ניתן לבדוק - במידה ואין חפיפה - לקרוא לממ קופי כי היא קטנה יותר*/
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
