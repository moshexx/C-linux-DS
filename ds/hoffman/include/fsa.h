/******************************************************************************/
/*		Descriptions - FSA API Functions								  	  */
/*		Date: 16.11.2020					     						   	  */
/*		Group: OL96						      								  */
/******************************************************************************/

#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* size_t */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef	struct fsa fsa_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
* Description: Initializes the the fsa and divides the memory buffer to
* fixed size blocks. buffer size and block size must be bigger than zero.
* Return value: fsa_t pointer to the initialized memory segment
* Errors: none.
* Undefined behavior: pionter to fsa must be valid.
*
* Complexity: O(n).
*/
fsa_t *FSAInit(void *buffer, size_t buffer_size, size_t block_size);

/*
* Description: Allocates one block of available memoey from the memory pool
* to the user.
* Return value: pointer to the address allocated to the user.
* 				returns NULL if out if memory.
* Errors: none.
* Undefined behavior: pionter to fsa must be valid.
*
* Complexity: O(1).
*/
void *FSAAlloc(fsa_t *fsa);

/*
* Description: Return one block of memory from the user and add to memory pool.
* Return value: none.
* Errors: sending pointer to NULL.
* Undefined behavior: Trying to free a block that is free.
*
* Complexity: O(1)
*/
void FSAFree(fsa_t *fsa, void *block);

/*
* Description: Count the number of free blocks available in the memore pool.
* Return value: number of free blocks.
* Errors:
* Undefined behavior: *fsa must be valid.
*
* Complexity: O(n)
*/
size_t FSACountFree(const fsa_t *fsa);

/*
* Description: Suggest the size of fsa needed for parameters given
* (including metadata).
* Return value: Suggest size.
* Errors: none.
* Undefined behavior: block size and block number can't be zero.
*
* Complexity: O(1).
*/
size_t FSASuggestSize(size_t block_size, size_t blocks_number);


#endif   /*__FSA_H__*/
