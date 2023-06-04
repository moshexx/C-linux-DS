#include <stdio.h>
#include <stdlib.h>

int *MakeArr(int size);
int PrintSurvivor (int *array, int size);

int main()
{
	/*Josephus*/
	
	int n;  /*<---------You can change the number of peope in the circle here*/
	int *arr;
	int i;
	int go = 1;    	          /*If go == 1 - the person needs to kill the next living guy*/ 
	int kills;		  /*How many people are still alive*/
	int new_round = 0;	  /*If new_round == 1 it is the beginning of a new round of killing*/
	int survivor;
	
	printf("Please type how many soldiers are in the circle:\n");  /*******an option which the user enters the number of soldiers.*/
	scanf("%d", &n);
	arr = MakeArr(n);
	kills = n-1;
	
	
	
		for (i = 0 ;i < n && kills > 0 ;++i)  /*Loop untill the last man stands*/
		{

			if (i == n-1)    /*If the loop reache to the last element - start from the beginning*/
			{
				i = -1;
				new_round = 1;
			}
			
			                                                     /*If the last guy the stand in the circle
			                                                      have to kill the guy after starting a new round*/
			else if (go == 1 && new_round == 1 && arr[i] > 0)  
			{
				arr[i] = 0;
				--kills;
				go = 0;
				new_round = 0;
			}
			
			else if (go == 1 && arr[i+1] == 0)            /*If next person is already dead - continue*/
			{
				continue;
			}
			
			else if (go == 1 && arr[i+1] >0)	      /*If next person alive and now is your time to kill -do it*/
			{
				arr[i + 1] = 0;
				--kills;
				go = 0;
				new_round = 0;
			}
							               /*If current person alive and go == 0 
							               it means that he is now the killer*/
			else if (0 == go && arr[i] > 0)		      
			{
				go = 1;
			}
			
			else if (0 == go && arr[i+1] == 0)	      /*If next person is already dead - continue*/
			{
				continue;
			}
			
								       /*If go was 0 before we started a new round it
								        means that the first guy in the next round should be the killer*/
			else if (0 == go && 0 == new_round)	       
			{
				go = 1;
				continue;
			}
			
		}
		survivor = PrintSurvivor(arr,n);
		printf("\nThe survivor is: %d\n\n", survivor);
		free(arr);

   return 0;
}

/**************************************************************************/

int PrintSurvivor (int *array, int size)
{
	int i;
	int survivor;
	for(i = 0 ;i < size ; i++)
	{
		if (array[i] > 0)
		{
			survivor = array[i];
		}
	}
	return survivor;
}

/*Fuction that creates array the size of n with continous numbers*/
int *MakeArr(int size)
{
	int *arr;
	int i;
	arr = (int *)malloc(sizeof(int)*size);
	if (NULL == arr)                     /*************after malloc - we should write what will happen if the malloc failed */
		{
			return NULL;
		}
	for (i=0 ;i < size ;++i)
	{
		arr[i] = i +1;
	}
	return arr;
}


