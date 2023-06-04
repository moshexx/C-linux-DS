/*****************************************************************************
*																			 *
*	Worksheet: 	dynamic_vector.c	 										 *
*	Author: 	Moshe Cohen 			    								 *
*	Reviewer: 					    										 *
*	Date: 		26th October 2020 											 *
*																			 *
*****************************************************************************/
#include <stdlib.h> /* malloc, free, size_t */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include <stdio.h>

#include "dynamic_vector.h"

struct dynamic_vector
{
    size_t capacity;
    size_t elem_size;
    size_t end_index;
    void   *element;
};

dvector_t *DVectorCreate(size_t capacity, size_t elem_size)
{
	dvector_t *dvector = NULL;

	assert(capacity > 0);
	assert(elem_size > 0);

	dvector = (dvector_t *)malloc(capacity * elem_size + sizeof(dvector_t));
	if (NULL == dvector)
	{
		return NULL;
	}
	dvector->capacity = capacity;
	dvector->elem_size = elem_size;
	dvector->end_index = 0;
	dvector->element = (void *)(dvector + 1);

	return dvector;
}

void DVectorDestroy(dvector_t *dvector)
{
  free(dvector); dvector = NULL;
}

size_t DVectorSize(const dvector_t *dvector)
{
  assert(dvector);

  return (dvector->end_index);
}

dvector_t *DVectorPushBack(dvector_t *dvector, void *element)
{
  assert(dvector);
  assert(element);

  if(dvector->capacity ==  dvector->end_index)
  {
    dvector = DVectorRecapacity(dvector, dvector->capacity * 2);
    if (NULL == dvector)
    {
      return NULL;
    }
  }
  memcpy((char *)dvector->element + dvector->elem_size * dvector->end_index,
                                    element, dvector->elem_size);
  ++dvector->end_index;

  return dvector;
}

dvector_t *DVectorPopBack(dvector_t *dvector)
{
  assert(dvector);
  assert(0 != dvector->end_index);

  --(dvector->end_index);
  /* If the capacity big 4 times than the actual size */
  if(dvector->capacity >=  dvector->end_index * 4)
  {
    /* Decrease capacity by half */
    dvector = DVectorRecapacity(dvector, dvector->capacity / 2);
    if (NULL == dvector)
    {
      return NULL;
    }
  }

  return(dvector);
}

void *DVectorAccessElement(const dvector_t *dvector, size_t index)
{
  assert(dvector);
  assert(0 != dvector->end_index);
  assert(index < dvector->end_index);

  return (void *)((char *)dvector->element + dvector->elem_size * index);
}

size_t DVectorCapacity(const dvector_t *dvector)
{
  assert(dvector);

  return(dvector->capacity);
}

dvector_t *DVectorRecapacity(dvector_t *dvector, size_t new_capacity)
{
  assert(dvector);
  /*printf("new_capacity: %lu\n", new_capacity);*/
  assert(dvector->end_index < new_capacity);

  dvector = (dvector_t *)realloc(dvector, new_capacity * dvector->elem_size + sizeof(dvector_t));
  if (NULL == dvector)
  {
    return NULL;
  }
  dvector->element = (void *)(dvector + 1);
  dvector->capacity = new_capacity;

  return(dvector);
}
