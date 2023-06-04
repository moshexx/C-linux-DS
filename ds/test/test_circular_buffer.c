/*****************************************************************************
*
*	Worksheet: test_circular_buffer.c
*	Author: 	Moshe Cohen
*	Reviewer:
*	Date: 		4.11.2020
*
*****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "circular_buffer.h"

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
	/*int *p5 = NULL;*/
  size_t i;

  char ex_buffer[81] = {0};


  size_t capacity = 100;
  size_t capacity2 = 20;
  cbuff_t *cbuff = CBuffCreate(capacity);
  cbuff_t *cbuff2 = CBuffCreate(capacity2);


	/********************* CBuffCreate *********************/


  /********************* CBuffIsEmpty *********************/
  RUN_TEST(1 == CBuffIsEmpty(cbuff), "CBuffIsEmpty (empty)1");
  RUN_TEST(1 == CBuffIsEmpty(cbuff2), "CBuffIsEmpty (empty)2");

  /********************* CBuffCapacity *********************/
  RUN_TEST(capacity == CBuffCapacity(cbuff), "CBuffCapacity 1");
  RUN_TEST(capacity2 == CBuffCapacity(cbuff2), "CBuffCapacity 2");

  /********************* CBuffFreeSpace *********************/
  RUN_TEST(capacity == CBuffFreeSpace(cbuff), "CBuffFreeSpace 1");
  RUN_TEST(capacity2 == CBuffFreeSpace(cbuff2), "CBuffFreeSpace 2");

  /********************* CBuffWrite *********************/
  RUN_TEST(4 == CBuffWrite(cbuff, p1, 4), "CBuffWrite 1");
  RUN_TEST(4 == CBuffWrite(cbuff, p2, 4), "CBuffWrite 1");
  RUN_TEST(2 == CBuffWrite(cbuff, p3, 2), "CBuffWrite 1");

  RUN_TEST(capacity - 10 == CBuffFreeSpace(cbuff),
                  "CBuffFreeSpace(After Write) 3");

  /********************* CBuffRead *********************/
  RUN_TEST(4 == CBuffRead(cbuff, ex_buffer, 4), "CBuffRead 1");
  RUN_TEST(capacity - 10 + 4 == CBuffFreeSpace(cbuff),
                  "CBuffFreeSpace(After Write) 4");
  RUN_TEST(4 == CBuffRead(cbuff, ex_buffer, 4), "CBuffRead 2"); 

  /********************* CBuffDestroy *********************/
  CBuffDestroy(cbuff);
  CBuffDestroy(cbuff2);
  printf("\nThis time - Do not forget to check valgrind :)\n");

  return 0;
}
