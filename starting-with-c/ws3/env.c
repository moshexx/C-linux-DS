#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int CountAndPrintArr(char **arr);
void CopyStrings(char **arr ,char **arr_copy);
void FreeMalloc(char **arr, size_t size);


int main(int argc ,char *argv[] ,char *envp[])
{
	int i ;
	int count = 0;
	char **envp_copy;
	
	printf("The original envp are:\n");                                           /* print the original and count the strings */
	count = CountAndPrintArr(envp);

	envp_copy = (char **)malloc(sizeof(char *) * count);                            /* make some spcae for the copy of **envp */
	if (NULL == envp_copy)
/*משום שמדובר במאלוק הראשי במידה והוא נכשל אז לא יתבצע אילקוץ לזיכרון ולכן לא צריך לשחרר זיכרון אלא רק להחזיר שגיאה */ 
	{/*s*/
		printf("EROR: There is no enough memory space.\n");
		return -1;
	}
	
	
	for (i = 0 ; envp[i] != NULL ; ++i)
	{
		*(envp_copy+i) = (char *)malloc( (strlen(*(envp+i))+1) * sizeof(char) );   /* make some spcae for the copy of the strings */
/*משום שכת במידה ומאלוק יכשל - הוא יכשל לאחר שכבר הקצנו את המאלוק הגדול ל**, ואחרי שהקצה כמה מאלוקים קטנים למספר * - מערכים של מחרוזות, אנחנו נצטרך לשחרר את התאים הקטנים שכבר הוקצו - עדI ולאחר מכן את המאלוכ הגדול.*/
		if (NULL == envp_copy)                                                        
		{
			printf("EROR: There is no enough memory space.\n");
			FreeMalloc(envp_copy ,i);
			return -1;
		}
		
	}
	
	CopyStrings(envp ,envp_copy);
	
	printf("\n\n\n\n\nThe envp copy in lower case:\n\n\n");
	
	for (i = 0 ; i < count ; ++i)
	{
		printf("%s \n" ,envp_copy[i]);
	}
	
	
	FreeMalloc(envp_copy ,count);
	
	(void) argc;
	(void) argv;
	return 0;
}


int CountAndPrintArr(char **arr)
{
	size_t i;
	int count = 0;
	
	for (i = 0 ; arr[i] != NULL ; ++i)
	{
        printf("%s \n" ,arr[i]);
        ++count;
	}
	return count;
}

void CopyStrings(char **arr ,char **arr_copy)
{
	size_t i ,j;
	
	for (i = 0 ; arr[i] != NULL ; ++i)
	{
		j = 0;
		while (arr[i][j] != '\0')
		{
			(arr_copy[i][j]) = (tolower(arr[i][j]));
			++j;
		}
	}
}

void FreeMalloc(char **arr, size_t size)
{
	size_t i;
	for (i = 0 ; i < size ; ++i)
	{
		free(*(arr+i));
	}
	
	free(arr);
}

