
#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <stddef.h>/*size_t*/
#include <unistd.h>/*ssize_t*/

/******************************************************************************/
typedef struct circular_buff cbuff_t;
/******************************************************************************/

/*
* Description: Creates struct of circular buffer with capacity size.
* Return : cbuff_t pointer
* Errors: none
* Undefined behavior: none
* complexity: O(1)
*/
cbuff_t *CBuffCreate(size_t capacity);

/*
* Description:  Free all allocated memory.
* Return: none
* Errors: none
* Undefined behavior: cbuff cant be NULL.
* complexity: O(1)
*/
void CBuffDestroy(cbuff_t *cbuff);

/*
* Description: checkes if Buffer is empty.
* Return: 0 = FALSE, 1= TRUE(Buffer empty)
* Errors: none
* Undefined behavior: cbuff cant be NULL.
* complexity: O(1)
*/
int CBuffIsEmpty(const cbuff_t *cbuff);

/*
* Description: Return capacity of buffer.
* Return: capacity of buffer.
* Errors: none
* Undefined behavior: cbuff cant be NULL.
* complexity: O(1)
*/
size_t CBuffCapacity(const cbuff_t *cbuff);

/*
* Description: Return number of free space in buffer.
* Return: number of free space in buffer.
* Errors: none
* Undefined behavior: cbuff cant be NULL.
* complexity: O(1)
*/
size_t CBuffFreeSpace(const cbuff_t *cbuff);

/*
* Description: Reads from cbuff count bytes to dest.
* Return: number of bytes read , negative = Failed
* Errors: none
* Undefined behavior: cbuff cant be NULL, dest cant be NULL.
* complexity: O(n)
*/
ssize_t CBuffRead(cbuff_t *cbuff, void *dest, size_t count);

/*
* Description: Write from src count bytes to cbuff.
* Return: number of bytes wrote , negative = Failed
* Errors: none
* Undefined behavior: cbuff cant be NULL, src cant be NULL.
* complexity: O(n)
*/
ssize_t CBuffWrite(cbuff_t *cbuff, const void* src, size_t count);

#endif   /*__CIRCULAR_BUFFER_H__*/
