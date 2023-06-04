#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h>
#include "../include/stack.h"

typedef	struct node node_t;
struct node
{
  const void *data;
  node_t *next;
};


unsigned int FiboIter(unsigned int n);
unsigned int FiboRecur(unsigned int n);
node_t *FlipList(node_t *head);

size_t StrLen(const char *str);
int StrCmp(const char *str1 ,const char *str2 );
char *StrCpy(char *dest ,const char *src);
char *StrCat(char *dest ,const char *src);
char *StrStr(const char *str, const char *sub_str); /* implement by strchar + str cpy */

stack_t *SortStack(stack_t **stack);


#endif   /*__RECURSION_H__*/
