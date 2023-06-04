#include "Strings.h"
#include <string.h>
#include <strings.h>            /* for strcasecmp & strncasecmp */
#include <ctype.h>
#include <stdlib.h>

size_t StrLen(const char *str1)
{
	size_t lenth = 0;

	while (*str1 != '\0')
	{
		str1++;
		lenth++;
	}
	 assert('\0' == *str1);

	return lenth;
}

int StrCmp(const char *str1 ,const char *str2 )
{
	assert(NULL != str1);
	assert(NULL != str2);

	while (*str1 == *str2)
	{
		if ('\0' == *str1)
			return 0;
		str1++;
		str2++;
	}

	return (*str1 - *str2);
}

int StrCmpTrueOrFalse(const char *str1 ,const char *str2)
{
	while (*str1 == *str2)
	{
		if ('\0' == *str1) /*אם 2 המחרוזות הגיעו ל\0 אזי שהן נגמרו והן שוות*/
			return 0;
		str1++;
		str2++;
	}

	if (*str1 < *str2) /*ערך האסקי קטן יותר*/
	{
		return -1;
	}
	return 1;
}

char *StrCpy(char *dest ,const char *src)
{
	char *str = dest;
	size_t len_dest = StrLen(dest);
	size_t len_src = StrLen(src);
	/*printf("%d %d\n", len_dest ,len_src); */

	assert(NULL != src);
	assert(NULL != dest);
	/*assert(len_dest <= len_src); */

	while ('\0' != *src)
	{
		*dest = *src;
		*dest++;
		*src++;
	}

	*dest = '\0';

	assert(dest != src);
	return str;
}


char *StrNCpy(char *dest ,const char *src ,size_t n)
{
	char *str = dest;

	assert(NULL != src);
	assert(NULL != dest);

	while ('\0' != *src && n)
	{
		*dest = *src;
		*dest++;
		*src++;
		n--;
	}

	*dest = '\0';
	assert(dest > src);

	return str;
}


size_t StrNCmp(const char *str1 ,const char *str2 ,int n)
{
	assert(NULL != str1);
	assert(NULL != str2);

	while ( (*str1 == *str2) && n )
	{
		if ('\0' == *str1)
			return 0;
		str1++;
		str2++;
		n--;
	}

	return (*str1 - *str2);
}

/* dont forget to improve... */
int StrCaseCmp(const char *str1 ,const char *str2)
{
	char *str1_copy = (char *)str1;
	char *str2_copy = (char *)str2;

	assert(NULL != str1);
	assert(NULL != str2);

	*str1_copy = tolower(*str1_copy);
	*str2_copy = tolower(*str2_copy);

	while (*str1_copy == *str2_copy)
	{
		if ('\0' == *str1_copy) /*אם 2 המחרוזות הגיעו ל\0 אזי שהן נגמרו והן שוות*/
			return 0;
		str1_copy++;
		str2_copy++;
		*str1_copy = tolower(*str1_copy);
		*str2_copy = tolower(*str2_copy);
		}

	return (*str1_copy - *str2_copy);
}


char *StrChr(const char *str ,int c)
{
	char *s = (char *)str;

	assert(NULL != str);

	while ('\0' != *s)
	{
		if(*s == (char)c)
		{
			return s;
		}
		++s;
	}
	return NULL;

}

char *StrCat(char *dest ,const char *src)
{
	char *str = (char *)src;
	char *dest2 = dest; /* dest2 = runner */

	assert(NULL != src);
	assert(NULL != dest);

	while ('\0' != *dest)
	{
		++dest;
	}

	while ('\0' != *str)
	{
		*dest = *str;
		++dest;
		++str;
	}
	return dest2;
}

char *StrNCat(char *dest, const char *src, size_t n)
{
	char *str = (char *)src;
	char *dest2 = dest;

	assert(NULL != src);
	assert(NULL != dest);

	while ('\0' != *dest)
	{
		++dest;
	}

	while ('\0' != *str && n)
	{
		*dest = *str;
		++dest;
		++str;
		--n;
	}
	return dest2;
}

char *StrStr(const char *str, const char *sub_str)
 {
 	size_t len_sub_string = strlen(sub_str) -1;		/* use <string.h> for implament. ניסוי וטעיה - עובד עם מינוס 1 */

 	while ('\0' != *str)
 	{
 		if(!(StrNCmp(str ,sub_str ,len_sub_string)))
 		{
 			return (char *)str;
 		}
 		++str;
 	}
 	return NULL;
 }

char* StrDup(const char *s)
{
	size_t len_s = strlen(s);
	char *dest;
	dest = (char *) malloc(len_s);
	StrCpy(dest ,s);

	/* if (!(strcmp(dest ,s)))
	{
		return NULL;
	} */
	return dest;
}

size_t StrSpn(const char *sentence, const char *expression)
{
	size_t i, j;
	int len1 = strlen(sentence);
	int len2 = strlen(expression);
	int fcontinue = 1;

	for(i=0 ; i<len1 && fcontinue; ++i)
	{
		fcontinue = 0;
		for(j=0 ; j<len2 ; ++j)
		{
			if(sentence[i] == expression[j])
			{
				fcontinue = 1;
			}
		}
	}
	return i-1;
}
