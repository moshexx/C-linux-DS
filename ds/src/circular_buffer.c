/*******************************************************************************
*
*	Worksheet: 	circular_buffer.c
*
*	Author: 	Moshe Cohen
*	Reviewer:   Lia
*	Date: 		4.11.2020
*
*******************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SYNOPSIS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
We made a circular buffer (constant size capacity) and used a flexible array
for its elements. The memory allocation included the "administrative" struct
and capacity size of elements (1 of these is an allocation for a floating byte).

i_read- represents the index in which i want to read (and delete).
i_write- represents the index in which i want to write (and insert).

This floating byte represents the end of a lap. Once read reaches this floating
byte it means he catched up to write.    [] [] [] [] [r/w] [f] [] []
In case the array is full read will be ahead of the write with the floating
byte in the middle.                      [] [] [] [] [w] [f] [r] []
*/

#include <stdlib.h> /* size_t, malloc, free */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include <stdio.h> /* printf */

#include "circular_buffer.h"

#define MIN2(a, b) ((a < b) ? a : b)
#define MIN3(a, b, c) (MIN2(a, b) < c ? MIN2(a, b) : c)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Admin~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
enum returnval {FALSE, TRUE};

struct circular_buff
{
    #ifndef DNDEBUG /* DNDEBUG - if we will compile with gc */
    size_t magic;
    #endif
    size_t i_read;
    size_t i_write;
    size_t capacity;
    char buffer[1];
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

cbuff_t *CBuffCreate(size_t capacity)
{
  cbuff_t *cbuff = (cbuff_t *)malloc(offsetof(cbuff_t, buffer) + capacity + 1);
  if (NULL == cbuff)
  {
    printf("Malloc failed!\n");
    return NULL;
  }
  #ifndef DNDEBUG /* = ifdef DEBUG */
	cbuff->magic = 0xDEADBEEF;
	#endif

  cbuff->i_read = 0;
  cbuff->i_write = 0;
  cbuff->capacity = capacity;

  return cbuff;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void CBuffDestroy(cbuff_t *cbuff)
{
  assert(NULL != cbuff);

  free(cbuff);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int CBuffIsEmpty(const cbuff_t *cbuff)
{
  assert(NULL != cbuff);

  return (cbuff->i_read == cbuff->i_write);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
size_t CBuffCapacity(const cbuff_t *cbuff)
{
  assert(NULL != cbuff);

  return cbuff->capacity;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
size_t CBuffFreeSpace(const cbuff_t *cbuff)
{
  assert(NULL != cbuff);

  return((cbuff->i_read + cbuff->capacity - cbuff->i_write)
                                  % (cbuff->capacity + 1));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ssize_t CBuffWrite(cbuff_t *cbuff, const void* src, size_t count)
{
  size_t free_space;
  size_t fill_circle;
  char *src_runner = NULL;

  assert(NULL != cbuff);
  assert(NULL != src);
  #ifndef DNDEBUG
	if (cbuff->magic != 0xDEADBEEF)
	{
		printf("Unrecognized struct sent!\n");
		return -1;
	}
	#endif

  free_space = CBuffFreeSpace(cbuff);
  fill_circle = cbuff->capacity + 1 - cbuff->i_write;
  src_runner = (char *)src;

  /* we will copy according the smaller size */
  count = MIN2(count, free_space);

  if (fill_circle >= count)
  {
    memcpy(cbuff->buffer + cbuff->i_write, src, count);
    cbuff->i_write += count;

    return count;
  }
  /* Two shots copy */
  else /* (fill_circle < count) */
  {
    memcpy(cbuff->buffer + cbuff->i_write, src_runner, fill_circle);
    cbuff->i_write = 0;
    src_runner += fill_circle;
    memcpy(cbuff->buffer, src_runner, count - fill_circle);
    cbuff->i_write = count - fill_circle;

    return count;
  }
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ssize_t CBuffRead(cbuff_t *cbuff, void *dest, size_t count)
{
size_t fill_circle;
size_t can_read;
char *dest_runner = NULL;
size_t b_to_read;
size_t copied = 0;
size_t free_space;

assert(NULL != cbuff);
assert(NULL != dest);
#ifndef DNDEBUG
if (cbuff->magic != 0xDEADBEEF)
{
  printf("Unrecognized struct sent!\n");
  return -1;
}
#endif

free_space = CBuffFreeSpace(cbuff);
fill_circle = cbuff->capacity + 1 - cbuff->i_read; /* spaces between read to write */
dest_runner = (char *)dest;
can_read = cbuff->capacity - free_space; /* how much actually write and so can read */

/* we want to copy according the smaller */
count = MIN2(count, can_read);

b_to_read = MIN3(count, can_read, fill_circle);
memcpy(dest_runner, cbuff->buffer + cbuff->i_read, b_to_read);
copied += b_to_read;
cbuff->i_read = (cbuff->i_read + b_to_read) % (cbuff->capacity + 1);
dest_runner += b_to_read;
count -= b_to_read;

/* if (fill_circle < count) --> we need one more copy */
if (0 != count)
{
  memcpy(dest_runner, cbuff->buffer + cbuff->i_read, count);
}
copied += count;
cbuff->i_read += count;

return copied;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
