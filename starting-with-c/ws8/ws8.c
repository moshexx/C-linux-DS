/*******************************************************************************
*													  		    *
*	Worksheet: 	ws8.c	 			 						    *
*	Author: 		Moshe Cohen 			    						    *
*	Reviewer: 	Roy Chen				    						    *
*	Date: 		19th October 2020 								    *
*															    *
*******************************************************************************/
#include <stdio.h> 	/* printf etc. */
#include <string.h> /* strcpy and other string functions */
#include <stdlib.h> /* malloc */
#define SIZE 3

/***Define Variables***********************************************************/
typedef struct 
{
	void *type;
	
}var;
static int i = 5;
static float f = 5.5;
char *str = "Welcome to my place";
/* define and declare enumeration - status operations */
enum status_t {SUCCESS = 0 ,FAILURE = -1} operation_status;  
/***Declare Functions**********************************************************/
int SetArr(var var_arr[]);
void Print(var var_arr[]);
void AddInt(var var_arr[] , int num);
void AddFloat(var var_arr[] ,int num);
int AddChar(var var_arr[] ,int num);
void Add(var var_arr[] ,int num);
void CleanUp(var var_arr[]);
size_t CountDigits(int num);
void GetIntValue();

/******************************************************************************/
int main()
{	
	GetIntValue();
	return SUCCESS;
}	
/******************************************************************************/

int SetArr(var var_arr[])
{
	var_arr[0].type = &i;
	var_arr[1].type = &f;
	var_arr[2].type = (char *)malloc(sizeof(char) * (strlen(str)+1));
	if (NULL == (var_arr[2].type))
	{
		printf("EROR: There is no enough memory space.\n");
		return FAILURE;
	}
	strcpy(var_arr[2].type ,str);

	return SUCCESS;
}
	
void Print(var var_arr[])
{
	printf("Int:   %d \n",*(int *)(var_arr[0].type));
	printf("Float: %f \n",*(float *)(var_arr[1].type));
	printf("char:  %s \n",(char *)(var_arr[2].type));
}

void AddInt(var var_arr[] , int num)
{
	(*(int *)(var_arr[0].type)) += num;
}

void AddFloat(var var_arr[] ,int num)
{
	(*(float *)(var_arr[1].type)) += (float)num;
}

int AddChar(var var_arr[] ,int num)
{
	size_t strlen_tmp = CountDigits(num) + 1;
	char *tmp = (char *)malloc(strlen_tmp);

	if (NULL == tmp)
	{
		printf("EROR: There is no enough memory space.\n");
		return -1;
	}
	sprintf(tmp ,"%d" ,num);
	
	var_arr[2].type = realloc(var_arr[2].type, (strlen(var_arr[2].type) + strlen_tmp));
	if (NULL == (var_arr[2].type))
	{
		printf("EROR: There is no enough memory space.\n");
		return FAILURE;
	}

	strcat( (var_arr[2].type) , tmp );
	free(tmp); tmp = NULL;
	
	return SUCCESS;
}

void Add(var var_arr[] ,int num)
{
	printf("\nArray before ADD:\n");
	Print(var_arr);
	AddInt(var_arr ,num);
	AddFloat(var_arr ,num);
	AddChar(var_arr ,num);
	printf("\nArray after ADD:\n");
	Print(var_arr);
}

void CleanUp(var var_arr[])
{
	free(var_arr[2].type);
}

size_t CountDigits(int num)
{
	size_t count = 0;
	
	while(num)
	{
		num /= 10;
		++count;
	}
	
	return count;
}

void GetIntValue()
{
	int ans;
	int add;
	int fcontinue = 1;
	var var_arr[SIZE] = { 0 };
	
	SetArr(var_arr);
	printf("The array now look like:\n");
	Print(var_arr);
	
	printf("If you want to ADD integer - press 1\n");
	printf("If you want to EXIT - press 0\n");
	
	while (fcontinue)
	{
		scanf("%d" ,&ans);
		if (1 == ans)
		{
			printf("Please enter a number to add:\n");
			scanf("%d" ,&add);
			Add(var_arr ,add);
			printf("0/1? ");
		}
		else if (0 == ans)
		{
			printf("\033[1;31m");
			printf("GoodBye!\n");
			printf("\033[0m;");

			CleanUp(var_arr);
			fcontinue = 0;
		}
		else
		{
			printf("Unvalid value\n");
			printf("0/1? ");
		}
	}
}
