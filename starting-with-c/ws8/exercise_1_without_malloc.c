#include <stdio.h>
#include <string.h>

#define SIZE 3

typedef struct 
{
	void *type;
	
}var;

static int i = 5;
static float f = 5.5;
char str[100] = "Chapter";
	
void SetArr(var var_arr[]);
void Print(var var_arr[]);
void GetIntValue();
/********************************/
int main()
{
	GetIntValue();
	return 0;
}	
/********************************/

void SetArr(var var_arr[])
{
	var_arr[0].type = &i;
	var_arr[1].type = &f;
	var_arr[2].type = str; /* לבצע הקצאת זיכרון אח"כ*/
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

void AddChar(var var_arr[] ,int num)
{
	char string[100] = { 0 };
	sprintf(string ,"%d" ,num);
	strcat( ((char *)(var_arr[2].type)) , string );
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
void GetIntValue()
{
	int ans;
	int fcontinue=1;
	int add;
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
			printf("GoodBye\n");
			/***CLEANUP***/
			fcontinue = 0;
		}
		else
		{
			printf("unvalid value\n");
			printf("0/1? ");
		}
		
	}
	
}
