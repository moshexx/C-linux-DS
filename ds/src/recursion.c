/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: recursion.c
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> /* assert */

#include "../include/recursion.h"
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~Declarations~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

unsigned int FiboIter(unsigned int n);
unsigned int FiboRecur(unsigned int n);
node_t *FlipList(node_t *head);
size_t StrLen(const char *str);
int StrCmp(const char *str1 ,const char *str2 );
char *StrCpy(char *dest ,const char *src);
char *StrCat(char *dest ,const char *src);
char *StrStr(const char *str, const char *sub_str);
stack_t *SortStack(stack_t **stack);
static void SortedInsert(struct stack** stack, int *x);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* o(n) */
unsigned int FiboIter(unsigned int n)
{
    /* define the first 2 members in Fib series*/
    unsigned int a = 0;
    unsigned int b = 1;

    unsigned int c;
    size_t i = 0;

    /* basic case */
    if (n == 0)
    {
        return a;
    }

    for (i = 2; i <= n; ++i)
    {
        c = a + b;
        a = b;
        b = c;
    }

    return b;
}

/* o(2^n) - every call is spliting for two calls*/
unsigned int FiboRecur(unsigned int n)
{
    /* two basic cases */
    if (0 == n)
    {
        return 0;
    }
    else if (1 == n)
    {
        return 1;
    }

    return (FiboRecur(n-1) + FiboRecur(n-2));

}

node_t *FlipList(node_t *head)
{
    node_t *new_head = NULL;

    assert(NULL != head);

    /* base case = exit condition */
    if (NULL == head->next)
    {
        return head;
    }
    /* the order is importent: */
    new_head = FlipList(head->next);
    head->next->next = head;
    head->next = NULL;

    return new_head;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Strings~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

size_t StrLen(const char *str)
{
    assert(NULL != str);
    /* basse case */
    if ('\0' == *str)
    {
        return 0;
    }

    return (1 + StrLen(str + 1));
}

int StrCmp(const char *str1 ,const char *str2 )
{
    assert(NULL != str1);
    assert(NULL != str2);

    /* base case (stop when:) */
    if ('\0' == *str1)
    {
        return 0;
    }
    else if (*str1 == *str2)
    {
        return StrCmp(++str1, ++str2);
    }
    else /* if (*str1 != *str2) */
    {
        return (*str1 - *str2);
    }
}

char *StrCpy(char *dest ,const char *src)
{
    static size_t i;

    assert(NULL != src);
    assert(NULL != dest);

    *dest = *src;

    /* base case (stop when:) */
    if ('\0' == *src)
    {
        return (dest - i);
    }
    else
    {
        ++i;
        return (StrCpy(++dest, ++src));
    }

    /* Version without the static index */
    /*
    if ('\0' == *src)
      {
        *dest = '\0';
        return dest;
      }

      *dest = *src;
      StrCpyRecur(dest + 1, src + 1);

      return dest;
     */
}

char *StrCat(char *dest ,const char *src)
{
    assert(NULL != src);
    assert(NULL != dest);

    if (*dest != '\0')
    {
      StrCat(dest + 1, src);
    }
    else if ((*dest = *src) != '\0')
    {
      StrCat(dest + 1, src + 1);
    }

    return dest;
}
/* str(haystack), sub_str(needle) */
char *StrStr(const char *haystack, const char *needle)
{
    size_t i = 0;

    /* base case */
    if (*needle == '\0')
    {
        return (char *)haystack;
    }

   for (i = 0 ; i < StrLen(haystack); ++i)
   {
       if (*(haystack + i) == *needle)
       {
           char* ptr = StrStr(haystack + i + 1, needle + 1);
           if (NULL == ptr)
           {
               return ptr;
           }
           else
           {
               return ptr - 1;
           }
       }
   }

   return NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~SortStack~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

stack_t *SortStack(stack_t **stack)
{
    /*If stack is not empty*/
    if (!StackIsEmpty(*stack))
    {
        /*Remove the top item*/
        int *x = (int *)StackPeek(*stack);
        StackPop(*stack);

        /*Sort remaining stack*/
        SortStack(stack);

        /*Push the top item back in sorted stack*/
        SortedInsert(stack, x);
    }

    return *stack;
}

/*Recursive function to insert an item x in sorted way*/
static void SortedInsert(struct stack** stack, int *x)
{
    int *temp;
    /*Base case: Either stack is empty or newly inserted
    item is greater than top (more than all existing)*/
    if (StackIsEmpty(*stack) || *x > *(int *)StackPeek(*stack))
    {
        StackPush(*stack, x);
        return;
    }

    /*If top is greater, remove the top item and recur*/
    temp = (int *)StackPeek(*stack);
    StackPop(*stack);
    SortedInsert(stack, x);

    /*Put back the top item removed earlier*/
    StackPush(*stack, temp);
}
