/*****************************************************************************
*
*	Worksheet: test_doubly_linked_list.c
*	Author: 	Moshe Cohen
*	Reviewer:
*	Date: 		5.11.2020
*
*****************************************************************************/
#include <stdio.h>
#include <string.h>

#include "doubly_linked_list.h"

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

/********************************************/
struct node
{
    void *data;
    node_t *next;
    node_t *prev;
};

struct doubly_linked_list
{
    node_t head;
    node_t tail;
};
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

  dl_t *dlist = DListCreate();





	/********************* DListCreate *********************/


  /********************* DListIsEmpty *********************/
  RUN_TEST(1 == DListIsEmpty(dlist), "DListIsEmpty (empty)1");

  /********************* DListSize *********************/
  RUN_TEST(0 == DListSize(dlist), "DListSize(empty) 1");

  /********************* DListBegin *********************/
  RUN_TEST(&dlist->tail == DListBegin(dlist), "DListBegin(empty list) 1");
/**/
/********************* DListEnd *********************/
  RUN_TEST(DListEnd(dlist) == DListBegin(dlist), "DListEnd(empty list) 1");

  /********************* DListIsSameIter *********************/
  RUN_TEST(1 == DListIsSameIter(DListBegin(dlist), DListEnd(dlist)), "DListIsSameIter 1");

  /********************* DListInsertBefore *********************/
  /*DListInsertBefore((dl_iter_t)&dlist->tail,p1);*/
  RUN_TEST(0 == DListInsertBefore(DListEnd(dlist), p2), "DListInsertBefore 1");

  /********************* DListDestroy *********************/
  DListDestroy(dlist);
  printf("\nThis time - Do not forget to check valgrind :)\n");

  return 0;
}
