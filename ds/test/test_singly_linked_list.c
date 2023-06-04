/*****************************************************************************
*																			 *
*	Worksheet: test_singly_linked_list.c	 			 										 *
*	Author: 	Moshe Cohen 			    								 *
*	Reviewer: 					    									 *
*	Date: 		29th October 2020 											 *
*																			 *
*****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "singly_linked_list.h"

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
/*********************************************/
int PrintSl(sl_t *list)
{
   sl_iter_t temp = SListBegin(list);
   size_t i;

   if(temp == SListEnd(list))
   {
       printf("head -> tail");

       return 0;
   }
   printf("head-%d->",*(int *)SListGetData(temp));
   for(i = 0; i < SListSize(list) -1;++i)
   {
       temp = SListNextIter(temp);
       printf("%d->",*(int *)SListGetData(temp));
   }
   printf("tail\n");

   return 0;
}

int MyFunc(void *data, void *params)
{
  *(int *)data = 1000;


  return 0; /* SUCCESS */
}
/********************************************/
int main()
{
	sl_t *my_slist = SListCreate();
	sl_t *my_slist2 = SListCreate();

  int n1 = 111;
  int n2 = 222;
  int n3 = 333;
  int n4 = 444;
  int n5 = 555;
  int *p1 = &n1;
  int *p2 = &n2;
  int *p3 = &n3;
  int *p4 = &n4;


	/* Create */
  /*RUN_TEST(10 == , "SListCreate 1");*/

  /* IsEmpty */
  RUN_TEST(1 == SListIsEmpty(my_slist), "SListIsEmpty 1");
  RUN_TEST(1 == SListIsEmpty(my_slist2), "SListIsEmpty 2");

  /* pushback + size */
  SListPushBack(my_slist, p1);
  SListPushBack(my_slist, p2);
  SListPushBack(my_slist, p3);

  RUN_TEST(0 == SListIsEmpty(my_slist), "SListIsEmpty 3");
  RUN_TEST(0 == SListSize(my_slist2), "SListSize 1");
  RUN_TEST(3 == SListSize(my_slist), "SListSize 2");
  /*printf("1. head->data: %d\n",*(int *)my_slist->head->data);
  printf("2. head->next->data: %d\n",*(int *)my_slist->head->next->data);
  printf("3. head->next->next->data %d\n",*(int *)my_slist->head->next->next->data);*/
  PrintSl(my_slist);


  /* SetData */
  SListSetData(my_slist->head->next->next, p4);
  RUN_TEST(*p4 == *(int *)(my_slist->head->next->next->data), "SListSetData 1");
  /*printf("3. head->next->next->data %d\n",*(int *)my_slist->head->next->next->data);*/
  PrintSl(my_slist);
  SListSetData(my_slist->head->next->next, p3);

  /* GetData */
  RUN_TEST(*p3 == *(int *)(SListGetData(my_slist->head->next->next)), "SListGetData 1");

  /* PopBack */

  SListPopBack(my_slist);
  RUN_TEST(2 == SListSize(my_slist), "SListPopBack 1");
  /*printf("1. head->data: %d\n",*(int *)my_slist->head->data);
  printf("2. head->next->data: %d\n",*(int *)my_slist->head->next->data);*/
  PrintSl(my_slist);
  SListPushBack(my_slist, p3);
  printf("After PushBack(3): size = %ld\n", SListSize(my_slist));

  PrintSl(my_slist);
  /*  InsertBefore */
  SListInsertBefore(my_slist ,my_slist->head->next->next->next, p4);
  RUN_TEST(*p4 == *(int *)(SListGetData(my_slist->head->next->next->next)), "InsertBefore (last)");
  SListPopBack(my_slist);
  SListInsertBefore(my_slist ,my_slist->head->next->next, p3);
  RUN_TEST(*p3 == *(int *)(SListGetData(my_slist->head->next->next)), "InsertBefore (middle)");

  PrintSl(my_slist);

  /* FOrEach */


  SListPushBack(my_slist, p4);
  PrintSl(my_slist);
  SListForEach(MyFunc, (int *)my_slist->head->data,
    my_slist->head->next, my_slist->head->next->next->next);
  PrintSl(my_slist);

  /* Destroy */
  SListDestroy (my_slist);
  SListDestroy (my_slist2);
  /*RUN_TEST(10 == ********, "SListDestroy 1");*/




  return 0;
}
