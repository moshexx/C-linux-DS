#ifndef __STRINGS_H__
#define __STRINGS_H__
#include <stdio.h>  /*no need to rewrite in the .c file */
#include <assert.h> /*no need to rewrite in the .c file */

size_t StrLen(const char *str1);

int StrCmp(const char *str1 ,const char *str2 );

int StrCmpTrueOrFalse(const char *str1 ,const char *str2);

char *StrCpy(char *dest ,const char *src);

char *StrNCpy(char *dest ,const char *src ,size_t n);

size_t StrNCmp(const char *str1 ,const char *str2 ,int n);

int StrCaseCmp(const char *str1 ,const char *str2);

char *StrChr(const char *str ,int c);

char *StrCat(char *dest ,const char *src);

char *StrNCat(char *dest, const char *src, size_t n);

 char *StrStr(const char *str, const char *sub_str);
 
char* StrDup(const char* s);
 
size_t StrSpn(const char *sentence, const char *expression);
 

#endif /* __STRINGS_H__ */


