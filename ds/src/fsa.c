/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: fsa.c
*	author: Moshe Cohen
*	reviewer: Topaz Pais

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <assert.h> /* assert */

#include "fsa.h"

#define WORD (sizeof(size_t))

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct fsa
{
	size_t next_free;
};

typedef struct block
{
	size_t next_free;
}block_t;
	/*~~~~~~~~~~~~~~~~~~~~~~~~helper functions~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* make sure buffer align to word size */
static void *AlignBuffer(void *buffer, size_t *align_buffer_size)
{
	size_t align_buffer = (size_t)buffer;
	size_t remainder = align_buffer % WORD;

	if (0 != remainder)
	{
		remainder = WORD - remainder;
	    (*align_buffer_size) -= remainder;
		align_buffer = align_buffer - (align_buffer % WORD) + WORD;
	}

	return (void *)align_buffer;
}

/* make sure block_size align to word size (8/16/24/32...)
   minimum block_size = 8 (sizeof(block_t))*/
static size_t AlignBlockSize(size_t block_size)
{
	if ( block_size % WORD != 0)
	{
		block_size = block_size - (block_size % WORD) + WORD;
	}

	return block_size;
}
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

fsa_t *FSAInit(void *buffer, size_t buffer_size, size_t block_size)
{
	char *buffer_runner = NULL;
	size_t offset = 0;
	size_t count = 1;
	size_t align_buffer_size = buffer_size;

	assert (NULL != buffer);
	assert (0 < buffer_size);
	assert (0 < block_size);

	/* Alignment */
	buffer = AlignBuffer(buffer, &align_buffer_size);
	block_size = AlignBlockSize(block_size);

	/* define helper variables */
	buffer_runner = buffer;
	offset = (size_t)buffer_runner + sizeof(fsa_t);

	/* create admin struct & initialize 'next' to the first block */
	((fsa_t *)buffer_runner)->next_free = offset;

	buffer_runner = (char *)offset;
	/* create the middle blocks */
	for (; 1 < (align_buffer_size - sizeof(fsa_t)) / block_size
		 ; align_buffer_size -= block_size)
	{

		((block_t *)buffer_runner)->next_free = offset + block_size * count;
		buffer_runner += block_size;
		++count;
	}

	/* create the last block */
	((block_t *)buffer_runner)->next_free = 0;

	return (fsa_t *)buffer;
}

void *FSAAlloc(fsa_t *fsa)
{
	block_t *allocated_block = NULL;

	assert (NULL != fsa);

	/* if not full */
	if (0 != fsa->next_free)
	{
		allocated_block = (block_t *)fsa->next_free;
		fsa->next_free = (size_t)(allocated_block->next_free);
	}

	return (void *)allocated_block;
}

void FSAFree(fsa_t *fsa, void *block)
{
	assert (NULL != fsa);

	if (NULL == block)
	{
		return;
	}

	((block_t *)block)->next_free = fsa->next_free;
	fsa->next_free = (size_t)block;
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t count = 0;
	block_t *block_runner = NULL;

	assert (NULL != fsa);

	if (0 == fsa->next_free)
	{
		return count;
	}

	for (count = 1, block_runner = (block_t *)(fsa->next_free);
		 0 != block_runner->next_free;
		 block_runner = (block_t *)(block_runner->next_free))
	{
		++count;
	}

	return count;
}

size_t FSASuggestSize(size_t block_size, size_t blocks_number)
{
	assert (0 < blocks_number);
	assert (0 < block_size);

	block_size = AlignBlockSize(block_size);

	return ((block_size * blocks_number) + sizeof(fsa_t));
}
