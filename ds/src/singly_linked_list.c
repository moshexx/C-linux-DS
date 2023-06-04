/*****************************************************************************
*																			 *
*	Worksheet: 	singly_linked_list.c	 									 *
*	Author: 	Moshe Cohen 			    								 *
*	Reviewer: Ben					    										 *
*	Date: 		1th November 2020 											 *
*																			 *
*******************************************************************************/
#include <stdlib.h> /* malloc, free, size_t */
#include <assert.h>

#include "singly_linked_list.h"

enum result{ FALSE, TRUE };
enum status{ SUCCESS, FAILURE };

struct singly_linked_list
{
  node_t *head;
  node_t *tail;
};

struct node
{
  const void *data;
  node_t *next;
};

/******************************************************************************/
sl_t *SListCreate(void)
{
  sl_iter_t dummy = NULL;
  sl_t *list = NULL;

  /* define node struct */
  dummy = (node_t *)malloc(sizeof(node_t)); /* --> (node_t *) is explicit casting */
  if(NULL == dummy)
  {
    return NULL;
  }
  dummy->data = NULL;
  dummy->next = NULL;

  /* define singly_linked_list struct */
  list = (sl_t *)malloc(sizeof(sl_t));
  if(NULL == list)
  {
    free (list); list = NULL;/***************/
    return NULL;
  }
  list->head = dummy;
  list->tail = dummy;

  return list;
}

void SListDestroy(sl_t *list)
{
  sl_iter_t runner = list->head->next;

  assert(NULL != list);

  while (list->tail != list->head) /* same as foreach */
  {
  	free(list->head);
  	list->head = runner;
    runner = runner->next;
  }
  /* free dummy */
  free(list->tail);
  free(list);  list = NULL;
}

sl_iter_t SListBegin(const sl_t *list)
{
  assert(NULL != list);

  return list->head;
}

sl_iter_t SListEnd(const sl_t *list)
{
  assert(NULL != list);

  return list->tail;
}

int SListIsEmpty(const sl_t *list)
{
  assert(NULL != list);

  if(list->head == list->tail)
  {
    return TRUE;
  }

  return FALSE;
}

sl_iter_t SListNextIter(const sl_iter_t iter)
{
  assert(NULL != iter);

  return (iter->next);
}

/* next time - push back use insert before, not like this: */
int SListInsertBefore(sl_t *list ,sl_iter_t iter, const void *new_data)
{
  sl_iter_t new_iter = NULL;

  assert(NULL != iter);


  if (iter == list->tail)
  {
    return SListPushBack(list, new_data);
  }

  new_iter = (sl_iter_t)malloc(sizeof(node_t));
  if (NULL == new_iter)
  {
    return FAILURE;
  }

  new_iter->next = iter->next;
  iter->next = new_iter;
  iter->next->data = iter->data;
  iter->data = new_data;

  return SUCCESS;
}

int SListPushBack(sl_t *list, const void *new_data)
{
  node_t *new_node = NULL;

  assert(NULL != list);

  new_node = (node_t *)malloc(sizeof(node_t));
  if (NULL == new_node)
  {
    return FAILURE;
  }

  list->tail->next = new_node;
  list->tail->data = new_data;
  list->tail = new_node;
  list->tail->data = NULL;
  list->tail->next = NULL;

  return SUCCESS;
}

void SListPopBack(sl_t *list)
{
  sl_iter_t tmp = list->head;

  assert(NULL != list);
  assert(!SListIsEmpty(list));

  while (SListNextIter(tmp) != list->tail)
  {
    tmp = SListNextIter(tmp);
  }

  SListRemove(list, tmp);
}

size_t SListSize(const sl_t *list) /* next time use foreach */
{
  size_t count = 0;
  sl_iter_t tmp = list->head;

  assert(NULL != list);

  if (TRUE == SListIsEmpty(list))
  {
    return count;
  }
  else
  {
    while (NULL != tmp->next)
    {
      tmp = tmp->next;
      ++count;
    }
  }
  return count;
}

void SListSetData(sl_iter_t iter, const void *new_data)
{
  assert(NULL != iter);

  iter->data = new_data;
}

void *SListGetData(const sl_iter_t iter)
{
  assert(NULL != iter);

  return(void *)(iter->data);
}

int SListIsSameIter(const sl_iter_t one, const sl_iter_t other)
{
  if (one->next == other->next && one->data == other->data)
  {
    return TRUE;
  }

  return FALSE;
}

void SListRemove(sl_t *list ,sl_iter_t iter)
{
  sl_iter_t tmp = NULL;

  assert(NULL != list);
  assert(list->tail != iter);

  tmp = iter->next;
  iter->data = tmp->data;
  iter->next = tmp->next;
  if(tmp == list->tail)
  {
    list->tail = iter;
  }
  free(tmp);
}

int SListForEach(act_func_t act_func, void *params,
                sl_iter_t from, const sl_iter_t to)
{
  int status = 0;

  while (from != to && from->data != NULL)
  {
    status = act_func((void *)from->data, params);
    if(1 == status)
    {
      return FAILURE;
    }
    from = from->next;
  }

  return SUCCESS;
}

sl_iter_t SListFind(sl_iter_t from, cmp_func_t cmp_func,
                    const void *data, size_t n)
{
  assert(NULL != from);

  while (from->next != NULL)
  {
    if (0 == cmp_func(from->data, data, n)) break;
    from = from->next;
  }
/* if didnt fine - return tail */
  return from;
}

void SListAppend(sl_t *dest, sl_t *src)
{
  assert(NULL != dest);
  assert(NULL != src);
  assert(dest->head != src->head);

  /*"InsertBefore" dest->tail:*/
  dest->tail->next = src->head->next;
  dest->tail->data = src->head->data;
  dest->tail = src->tail;
  src->head->data = NULL;
  src->head->next = NULL;
  src->tail = src->head;
}
