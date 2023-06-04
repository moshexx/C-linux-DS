/*****************************************************************************
*																			 *
*	Worksheet: test_queue.c	 			 										 *
*	Author: 	Moshe Cohen 			    								 *
*	Reviewer: 					    									 *
*	Date: 		2.11.2020 											 *
*																			 *
*****************************************************************************/

#include <stdio.h>
#include <string.h>

/*#include "singly_linked_list.h"*/
#include "queue.h"

#define GREEN_COLOR     "\x1b[0;32m"
#define RED_COLOR     "\x1b[0;31m"
#define DEFAULT_COLOR    "\x1b[0;0m"

#define RUN_TEST(result, name) {\
            printf("Test %s: ", name);\
            if (result)\
            {\
                printf(GREEN_COLOR);\
                printf("Success\n");\
                printf(DEFAULT_COLOR);\
            }\
            else\
            {\
                printf(RED_COLOR);\
                printf("Fail\n");\
                printf(DEFAULT_COLOR);\
            }\
        }
/*
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

struct queue
{
    sl_t *slist;
};*/
/********************************************/
int main()
{
  /* just data for the tests */
  int n1 = 111;
	int n2 = 222;
	int n3 = 333;
	int n4 = 444;
	int n5 = 555;
	int *p1 = &n1;
	int *p2 = &n2;
	int *p3 = &n3;
	int *p4 = &n4;
	int *p5 = &n5;

  queue_t *queue = NULL;
  queue_t *queue2 = NULL;

  queue = QCreate();
  queue2 = QCreate();

	/* QCreate */
  /*RUN_TEST(10 == , "QCreate 1");*/

  /* QIsEmpty */
  RUN_TEST(1 == QIsEmpty(queue), "QIsEmpty (empty)1");
  RUN_TEST(1 == QIsEmpty(queue2), "QIsEmpty (empty)2");

  /* QEnqueue */
  /*PrintSl((sl_t *)queue);*/
  QEnqueue(queue, p1);
  QEnqueue(queue, p2);
  QEnqueue(queue, p3);
  RUN_TEST(0 == QIsEmpty(queue), "QIsEmpty (not empty)3");

  /* QDequeue */
  QDequeue(queue);
  QDequeue(queue);
  QDequeue(queue);
  /*PrintSl((sl_t *)queue);*/
  RUN_TEST(1 == QIsEmpty(queue), "QDequeue 1");
  QEnqueue(queue, p1);
  QEnqueue(queue, p2);
  QEnqueue(queue, p3);
  /*PrintSl((sl_t *)queue);*/

  /* QPeek */
  RUN_TEST(p1 == QPeek(queue), "QPeek 1");

  /* Qsize */
  RUN_TEST(3 == QSize(queue), "QSize 1");
  RUN_TEST(0 == QSize(queue2), "QSize 2");

  /* QAppend */
  QEnqueue(queue2, p4);
  QEnqueue(queue2, p5);

  QAppend(queue, queue2);
  /*RUN_TEST(1 == QIsEmpty(queue2), "QAppend (empty src)1");*/
  RUN_TEST(5 == QSize(queue), "QAppend (size dest)2");


  /* QDestroy */
  QDestroy (queue);
  QDestroy (queue2);
  printf("\nThis time - dont forget to check valgring :)\n");

  return 0;
}
