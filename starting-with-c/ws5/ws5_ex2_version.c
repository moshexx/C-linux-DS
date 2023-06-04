/********************************************
*File name: ws5_ex2.c
Author: Moshe Cohen
Reviwer:  Yoni
*******************************************/
#include <assert.h> /*for printf*/
#include <stdio.h>  /*for printf*/
#include <string.h> /*for strncmp */
#include <string.h> /*for strings functions*/
#define SIZE 5

/* define and declare struct special_input type */
typedef struct
{
	const char *str;
	int (*compare_ptr)(const char* cmd_name ,const char* user_input);
	int (*operation_ptr)(const char* file_name,const char* user_input);
}special_input;

/* define and declare enumeration - status operations */
enum status {SUCCESS = 0 ,FAILURE = 1} operation_status;

int Phase1(const char *str ,const char *file_name);
int StrNCmp(const char *str1 ,const char *str2);
int Remove(const char *str ,const char *file_name);
int Count(const char *str ,const char *file_name);
int Exit(const char *str ,const char *file_name);
int ToTheLeft(const char *str ,const char *file_name);
int SetArrSpecial(special_input arr_special[]);
int ActiveLogger(const char *file_name);

/* we want to get only one member in *argv[] -> this one will be name of out file*/
int main(int argc ,char *argv[])
{
	if (1 < argc)	
	{
		ActiveLogger(argv[1]);
	}
	
	else
	{
		printf("rerun the progrem and put name to argv[1] this time :)\n");
	}
	
	return SUCCESS;
}

/* This function is the default. when all the special inputs don't occur the program will execute this function.
the function will get a string from the stdin and cat it to the end of the file. */
int Phase1(const char *str ,const char *file_name)
{
	/*char str[80] = "\0"; belong to phase 1 ex - no need anymore */
	FILE *f;
	f = fopen(file_name ,"a");
	
	if(NULL == f)
	{
		printf("Error: unable to open the file\n");
		return FAILURE;
	}
	
	/* fgets(str ,80 ,stdin); belong to phase 1 ex - no need anymore */
	fseek(f ,0 ,SEEK_END);
	fputs(str ,f);
	fclose(f);
	
	return SUCCESS;
}

int StrNCmp(const char *str1 ,const char *str2)
{
	size_t n = strlen(str2);
	
	assert(NULL != str1);
	assert(NULL != str2);
	
	if(n == strlen(str1)-1 || str2[0] == '<' )
	{
		return((strncmp(str1 ,str2 ,n)));
	}
	
	return FAILURE;
}

int Remove(const char *str ,const char *file_name)
{
	int ret = remove(file_name);
	
		if(0 == ret) 
		{
			printf("File deleted successfully\n");
		} 
		else 
		{
			printf("Error: unable to delete the file\n");
			return FAILURE;
		}
	
	(void)str;
	return SUCCESS;
}

int Count(const char *str ,const char *file_name)
{
	int count = 0;
	char c;
	FILE *f;
	
	f = fopen(file_name, "r"); 
	/* Check if file exists */
	if (f == NULL) 
	{ 
		printf("EROR: Could not open file %s", file_name); 
		return 0; /* even if the file doesn't exist we won't the program to stop running - in case this special input will be the first srting */
	} 
	/* Extract characters from file and store in character c */
	for (c = getc(f); c != EOF; c = getc(f))
	{
		if (c == '\n') /* Increment count if this character is newline */ 
		{
			++count; 
		}
  	}
  	
	fclose(f); 
	printf("The file %s has %d lines\n ", file_name, count); 

  	(void)str;
	return SUCCESS;
}

int Exit(const char *str ,const char *file_name)
{
	(void)str;
	(void)file_name;
	return FAILURE;
}

/* This function write the string to the beginning of the file */
int ToTheLeft(const char *str, const char *file_name)
{
	char c;
	FILE *f;
	FILE *temp;
	
	f = fopen(file_name, "a+");
	temp = fopen("temp", "a+");
	if( NULL == f || NULL == temp)
	{
		printf("Error: unable to open the file\n");
		return FAILURE;
	}
	
	fputs(str + 1 ,temp);
	fseek(f ,0 ,SEEK_SET);
	while( (c = fgetc(f)) != EOF)
	{
		fputc(c, temp);
	}
	
	fclose(f);
	fclose(temp);
	remove (file_name);
	rename("temp", file_name);
	
	return SUCCESS;
}


/* This function set the array of 5 members special_input structs-type  */
int SetArrSpecial(special_input arr_special[])
{
	arr_special[0].str = "-remove";
	arr_special[0].compare_ptr = StrNCmp;
	arr_special[0].operation_ptr = Remove;
	
	arr_special[1].str = "-count";
	arr_special[1].compare_ptr = StrNCmp;
	arr_special[1].operation_ptr = Count;
	
	arr_special[2].str = "-exit";
	arr_special[2].compare_ptr = StrNCmp;
	arr_special[2].operation_ptr = Exit;
	
	arr_special[3].str = "<";
	arr_special[3].compare_ptr = StrNCmp;
	arr_special[3].operation_ptr = ToTheLeft;
	
	arr_special[4].str = "Phase1";
	arr_special[4].compare_ptr = StrNCmp;
	arr_special[4].operation_ptr = Phase1; /* if the input string pass all the previous stations it's getting to Phase 1 and add the file */
	
	return SUCCESS;
}


/* This function role the main - the body of the program runs here */
int ActiveLogger(const char *file_name)
{
	size_t i;
	size_t fStop = 0;
	char str[80];
	special_input arr_special[SIZE];
	
	SetArrSpecial(arr_special); /* hardcoded to arr */
	
	while(!(fStop))
	{
		fgets(str ,80 ,stdin);
		for(i=0 ; i < SIZE ;++i)
		{  			
			if(0 == arr_special[i].compare_ptr(str ,arr_special[i].str))
			{
				fStop = arr_special[i].operation_ptr(str ,file_name);
				break;		/* if the str == some of the 'special_input's we won't go to check the others */
			}
			else
			{
				if(SIZE-1 == i) /* in case we have chaced eveerything and.,...*/
				{
					fStop = arr_special[i].operation_ptr(str ,file_name);
				}
			}
		}
	}
	
	return SUCCESS;
}
