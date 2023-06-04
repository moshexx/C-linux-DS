#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*void foo(int a[], int size);*/
char **copypointer(char **dest, char **source, size_t size_source);
char *MakeLower(char *str);
char *StrSpace(const char *string);

int main(int argc, char **argv, char **envp)
{
	
	size_t i;				/********int i - We should prefer using size_t */
	size_t size_envp;
	char **env_new;
	
	for (i = 0 ; 0 != *(envp+i) ; ++i)	
	{}
	size_envp = i; 
	env_new = (char **)malloc(size_envp * sizeof(char*));
	if (NULL == env_new)
	{
		return 1;
	}
	
	env_new = copypointer(env_new, envp, size_envp);
	if(NULL == env_new)
	{
		return 1;
	}
	
	for (i = 0 ;i < size_envp ; i++)
	{
		printf("%s\n", *(env_new+i));
		free(*(env_new+i));
	}
	free(env_new);				/*******vlg check found a little leak*/
	(void) argc;
	(void) *argv;
	
	
 return 0; 	  
}



/*******************************************************************************************/


/*This function makes a copy of source in the dest multiplied
 by the size of the source array size.*/
char **copypointer(char **dest, char **source, size_t size_source)
{
	size_t i;
	for(i = 0 ; i < size_source ; ++i)
	{
		*(dest +i) = StrSpace(*(source + i));
		*(dest +i) = MakeLower(*(dest+i));
	}
	return dest;
}


/*This function creates a place in the momory in the size of
 the input string and return a pointer to that location*/
char *StrSpace(const char *string)
{
	size_t len = strlen(string)+1;
	char *dup = (char*)malloc(len * sizeof(char));
	if (NULL == dup)
	{
		return NULL;
	}
	return strcpy(dup,string);
}



/*This function turn upper to lower case letters.*/
char *MakeLower(char *str)
{
	size_t i =0;
	while (str[i])
	{
		str[i] = tolower(str[i]);
		++i;
	}
	return str;
}


