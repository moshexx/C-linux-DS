/****************************************************************************
*															 *
*	Worksheet: 	mem.h	 			 						 *
*	Author: 		Moshe Cohen 			    						 *
*	Reviewer: 	Chen Mana				    						 *
*	Date: 		20th October 2020 								 *
*															 *
*****************************************************************************/

#ifndef __MEM_H__
#define __MEM_H__
#include <string.h>
#define WORD (sizeof(size_t))

/* A function to copy 'c' n times to adress s.
   Copy "word size" each time when possible */
void  *MemSet(void *s, int c, size_t n);

/* A function to copy block of 'n' bytes from source 
   address 'src' to destination address 'dest'.
   Copy "word size" each time when possible */
void *MemCpy(void *dest, const void *src, size_t n);

/* A function to copy block of 'n' bytes from source 
   address 'src' to destination address 'dest'.
   use when only when there is overlap! */
void *MemMove(void *dest, const void *src, size_t n);

#endif /* __MEM_H__ */
