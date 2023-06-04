/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: hash_table.c
*	author: Moshe Cohen
*	reviewer: Lidor Cohen

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <math.h> /* sqrt */

#include "hash_table.h"
#include "doubly_linked_list.h" /*d_list in hash_table_t */

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
enum status_t {SUCCESS, FAILURE};
enum answer_t {FALSE, TRUE};

struct hash_table
{
	hash_func_t hash_func;
	hash_is_match_t is_match;
	size_t hash_table_size;
	dl_t **hash_table;
};
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

hash_t *HashCreate(hash_func_t hash_func, hash_is_match_t is_match,
                                            size_t hash_table_size)
{
    hash_t *hash_table = NULL;
    size_t i = 0;

    assert( NULL != hash_func);
    assert( NULL != is_match);
    assert(0 < hash_table_size);

    hash_table = (hash_t *)malloc(sizeof(hash_t));
    if (NULL == hash_table)
    {
        return NULL;
    }
	hash_table->hash_table = (dl_t **)malloc(hash_table_size * (sizeof(dl_t *)));
	if (NULL == hash_table->hash_table)
    {
		free(hash_table); hash_table = NULL;
        return NULL;
    }

    for (; i < hash_table_size; ++i)
    {
        hash_table->hash_table[i] = DListCreate();
        if (NULL == hash_table->hash_table[i])
        {
			size_t j = 0;
			for (j = 0; j < i; ++j)
			{
				free (hash_table->hash_table[j]);
				hash_table->hash_table[j] = NULL;
			}
			free(hash_table->hash_table); hash_table->hash_table = NULL;
			free(hash_table); hash_table = NULL;
            return NULL;
        }

    }
    hash_table->hash_func = hash_func;
    hash_table->is_match = is_match;
    hash_table->hash_table_size = hash_table_size;

    return hash_table;
}

void HashDestroy(hash_t *hash_table)
{
    size_t i = 0;

    assert(NULL != hash_table);

    for (; i < hash_table->hash_table_size; ++i)
    {
        DListDestroy(hash_table->hash_table[i]);
		hash_table->hash_table[i] = NULL;
    }
	free(hash_table->hash_table); hash_table->hash_table = NULL;
    free(hash_table); hash_table = NULL;
}

size_t HashSize(const hash_t *hash_table)
{
    size_t i = 0;
    size_t count = 0;

    assert(NULL != hash_table);

    for (; i < hash_table->hash_table_size; ++i)
    {
        count += DListSize(hash_table->hash_table[i]);
    }

    return count;
}

int HashIsEmpty(const hash_t *hash_table)
{
	size_t i = 0;
	int is_empty = TRUE;

    assert(NULL != hash_table);

	for (i = 0; i < hash_table->hash_table_size && is_empty; ++i)
	{
		is_empty = DListIsEmpty(hash_table->hash_table[i]);
	}

    return (is_empty);
}

int HashInsert(hash_t *hash_table, const void *data)
{
    int status = SUCCESS;
    size_t index = 0;

    assert(NULL != hash_table);
    assert(NULL != data);

    index = hash_table->hash_func(data);
    status = DListPushFront(hash_table->hash_table[index], data);

    return status;
}

void HashRemove(hash_t *hash_table, const void *key)
{
    dl_iter_t iter_to_remove = NULL;
    size_t index = 0;
	void *data_to_remove = NULL;

    assert(NULL != hash_table);
    assert(NULL != key);

    index = hash_table->hash_func(key);

    for (iter_to_remove = DListBegin(hash_table->hash_table[index]);
		 !DListIsSameIter(iter_to_remove, DListEnd(hash_table->hash_table[index]));
	 	 iter_to_remove = DListNext(iter_to_remove))
	{
		data_to_remove = DListGetData(iter_to_remove);
		if (hash_table->is_match(data_to_remove, key))
		{
			data_to_remove = DListGetData(iter_to_remove);
			DListRemove(iter_to_remove); iter_to_remove = NULL;
			break;
		}
	}

	return /*data_to_remove*/;
}

void *HashFind(const hash_t *hash_table, const void *key)
{
	dl_iter_t iter_to_find = NULL;
    size_t index = 0;
	void *data_to_return = NULL;

    assert(NULL != hash_table);
    assert(NULL != key);

	index = hash_table->hash_func(key);
	for (iter_to_find = DListBegin(hash_table->hash_table[index]);
         !DListIsSameIter(iter_to_find, DListEnd(hash_table->hash_table[index]));
	 	 iter_to_find = DListNext(iter_to_find))
	{
		if (hash_table->is_match(DListGetData(iter_to_find), key))
		{
			data_to_return = DListGetData(iter_to_find);
			break;
		}
	}

	/* cashing: */
	DListRemove(iter_to_find);
	if (FAILURE == HashInsert((hash_t *)hash_table, data_to_return))
	{
		return NULL;
	}

    return data_to_return;
}

int HashForEach(hash_t *hash_table, int (*action_t)(void *data, void *params),
                                                                void *params)
{
	size_t i = 0;
	int status = SUCCESS;

    assert(NULL != hash_table);

	for (; i < hash_table->hash_table_size && status == SUCCESS; ++i)
	{
		dl_iter_t from = DListBegin(hash_table->hash_table[i]);
		dl_iter_t to = DListEnd(hash_table->hash_table[i]);

		status = DListForEach(from, to, action_t, params);
	}

    return status;
}

double HashLoad(const hash_t *hash_table)
{
	assert(NULL != hash_table);

	return ((double)HashSize(hash_table) / hash_table->hash_table_size);
}

double HashSD(const hash_t *hash_table)
{
	size_t i = 0;
	double average = 0;
	double sum = 0;
	double sd = 0;

	assert(NULL != hash_table);

	average = HashLoad(hash_table);

	for (i = 0; i < hash_table->hash_table_size; ++i)
	{
		double diff = 0;
		diff = DListSize(hash_table->hash_table[i]) - average;
		sum += (diff * diff);
	}

	sd = sqrt(sum / hash_table->hash_table_size);

	return sd;
}
