/*******************************************************************************
*		Descriptions - Hash Table API Functions	        *
*		Date: 10.12.2020						*
*		Group: OL96							*
*******************************************************************************/

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stddef.h> /* size_t */

typedef struct hash_table hash_t;
typedef size_t(*hash_func_t)(const void *key);
typedef int(*hash_is_match_t)(const void *lhs, const void *rhs);

/* in src file
#include "doubly_linked_list.h"

struct hash_table
{
	hash_func_t hash_func;
	hash_is_match_t is_match;
	size_t hash_table_size;
	dl_t **hash_table;
};
end of src file */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
* Description: Create hash table.
* Return value: Pointer to hash table.
* Errors: Return NULL when fail allocate memory.
* Undefined behavior: Function pointer is NULL.
                      hash_func must return a number within the range given as
                     'hash_table_size'.
                      ohterwise - the behavior is undefined.
*
* n = hash_table_size;
* Complexity: O(n).
*/
hash_t *HashCreate(hash_func_t hash_func, hash_is_match_t is_match,
                                            size_t hash_table_size);

/*
* Description: Free all the elements and hash_table structure.
* Return value: none.
* Errors: None
* Undefined behavior: hash_table pointer is NULL.
*
* Complexity: O(n).
*/
void HashDestroy(hash_t *hash_table);

/*
* Description: Find number of elements in the hash_table.
* Return value: number of elements in hash_table.
* Errors:None
* Undefined behavior: hash_table pointer is NULL.
*
* Complexity: O(n).
*/
size_t HashSize(const hash_t *hash_table);

/*
* Description: Checks if hash_table has any elements.
* Return value: 1 if empty, 0 if not empty.
* Errors: None.
* Undefined behavior: hash_table pointer is NULL.
*
* Complexity: O(n).
*/
int HashIsEmpty(const hash_t *hash_table);

/*
* Description: Inserts element into hash_table
* Return value: 0 for SUCCESS, 1 for FAILURE.
* Errors: Return 1 when memory allocation fails.
* Undefined behavior: hash_table pointer is NULL and/or data of different type.
*
* Complexity: O(1).
*/
int HashInsert(hash_t *hash_table, const void *data);

/*
* Description: Remove element from hash_table.
* Return value: none
* Errors: none
* Undefined behavior: hash_table is NULL, key does not exist.
*
* Complexity: O(1)
*/
void HashRemove(hash_t *hash_table, const void *key);

/*
* Description: Finds the element which holds the argument as data
* Return value: the value of key, NULL if not found
* Errors: none
* Undefined behavior: hash_table is NULL
*
* Average case complexity: O(1).
*/
void *HashFind(const hash_t *hash_table, const void *key);

/*
* Description: Performs the inputted function on the data from each element
* Return value: 0 if actions performed sucessfully, 1 if not.
* Errors: none
* Undefined behavior: hash_table is NULL, if action_t is NULL.
*
*
* Complexity: O(n).
*/
int HashForEach(hash_t *hash_table, int (*action_t)(void *data, void *params),
                                                                void *params);

/* Bonus */
double HashLoad(const hash_t *hash_table);

double HashSD(const hash_t *hash_table);


#endif   /*__HASH_TABLE_H___*/
