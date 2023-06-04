
/*
#include <stdio.h>

void SwapT(size_t *first, size_t *second);


int main()
{
	size_t a = 17;
	size_t b = 34;
	printf("\n %ld, %ld, \n",a,b);
	SwapT(&a,&b);
	printf("\n %ld, %ld, \n",a,b);
	return 0;

}









void SwapT(size_t *first, size_t *second)
{
	size_t temp = *first;
	*first = *second;
	*second = temp;
}
*/

#include<stdio.h>

void SwapTPointers(size_t **ptrc, size_t **ptrd);

int main()
{

	size_t a = 5;
	size_t b = 10;
	size_t *c = &a;
	size_t *d = &b; 
	
	/*size_t **ptrc = &c;
	size_t **ptrd = &d;
	*/
	
	printf("\naddress of pointer c: %p\n",(void *)c);
	printf("\naddress of pointer d: %p\n",(void *)d);
	
	SwapTPointers(&c ,&d);
	printf("\naddress of pointer c: %p\n",(void *)c);
	printf("\naddress of pointer d: %p\n",(void *)d);
	
	
	return 0;

}




void SwapTPointers(size_t **ptrc, size_t **ptrd)  
{
size_t *temp=NULL;
temp = *ptrc;
*ptrc = *ptrd;
*ptrd = temp;
}

/*
בהגדרה של פוינטר כותבים 
int *var = NULL;

כשרוצים לשנות את ערך הפוינטר, כלומר את הכתובת אליה הוא מצביע, לא שמים *:
var = &x;

אם נרצה לשנות את התוכן אליו הפוינטר מצביע, נוסיף *:
*var = 2;
x=2;
*/





















