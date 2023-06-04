/*******************************************************************************
*
*	Worksheet: 	queue.c
*
*	Author: 	Moshe Cohen
*	Reviewer:
*	Date: 		2.11.2020
*
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "singly_linked_list.h"
#include "queue.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
struct queue
{
    sl_t *slist;
};
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* FIFO - First In, First Out. insert from End, pop from Begin */
queue_t *QCreate(void)
{
  queue_t * queue = malloc(sizeof(queue_t));
  if(NULL == queue)
  {
    return NULL;
  }
  queue->slist = SListCreate();

  return queue;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void QDestroy(queue_t *queue)
{
  assert(NULL != queue);

  SListDestroy(queue->slist);
  free(queue); queue = NULL;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int QIsEmpty(const queue_t *queue)
{
  assert(NULL != queue);

  return SListIsEmpty(queue->slist);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int QEnqueue(queue_t *queue, const void *data)
{
  assert(NULL != queue);

  return SListPushBack(queue->slist, data);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void QDequeue(queue_t *queue)
{
  assert(NULL != queue);

  SListRemove(queue->slist, SListBegin(queue->slist));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void *QPeek(const queue_t *queue) /* Get Data */
{
  assert(NULL != queue);

  return SListGetData(SListBegin((queue->slist)));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
size_t QSize(const queue_t *queue)
{
  assert(NULL != queue);

  return SListSize(queue->slist);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void QAppend(queue_t *dest, queue_t *src)
{
  assert(NULL != src);
  assert(NULL != dest);
  assert(dest != src);

  SListAppend(dest->slist, src->slist);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
