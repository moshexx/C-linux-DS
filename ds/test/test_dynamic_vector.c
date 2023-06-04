#include <stdio.h>

#include"dynamic_vector.h"

#define GREEN_COLOR     "\x1b[0;32m"
#define RED_COLOR     "\x1b[0;31m"
#define DEFAULT_COLOR    "\x1b[0;0m"

#define RUN_TEST(result, name) {\
            printf("Test %s: ", name);\
            if (result)\
            {\
                printf(GREEN_COLOR);\
                printf("Success\n");\
                printf(DEFAULT_COLOR);\
            }\
            else\
            {\
                printf(RED_COLOR);\
                printf("Fail\n");\
                printf(DEFAULT_COLOR);\
            }\
        }


int CheckCreate(dvector_t *dvec)
{
	return( NULL != dvec);
}

int CheckSize(dvector_t *dvec, size_t s)
{
	return(s == DVectorSize(dvec));
}

int CheckResize(dvector_t ** dvec)
{

	int r = (DVectorCapacity(*dvec) == 1);

	*dvec = DVectorRecapacity(*dvec, 3);

	if(dvec == NULL)
	{

		printf("fail allocate memory\n");
		return 0;
	}

	r += (DVectorCapacity(*dvec) == 3);

	return(r == 2);
}


int CheckPush(dvector_t **dvec)
{
	int res = 0;
	int a = 1;
	*dvec = DVectorPushBack(*dvec, &a);
	if(*dvec == NULL)
	{
		printf("alloc fail1 ");
		return(0);
	}
	a = 2;
	*dvec = DVectorPushBack(*dvec, &a);
	if(*dvec == NULL)
	{
		printf("alloc fail2 ");
		return(0);
	}
	a = 3;
	*dvec = DVectorPushBack(*dvec, &a);
	if(*dvec == NULL)
	{
		printf("alloc fail 3");
		return(0);
	}
	a = 4;
	*dvec = DVectorPushBack(*dvec, &a);
	if(*dvec == NULL)
	{
		printf("alloc fail 4");
		return(0);
	}
	res += (DVectorCapacity(*dvec) == 6); /*******/
	a = 5;
	*dvec = DVectorPushBack(*dvec, &a);
	if(*dvec == NULL)
	{
		printf("alloc fail 5");
		return(0);
	}
  printf("res0 = %d\n", res);
	res += (DVectorCapacity(*dvec) == 6); /*******/
  printf("%lu\n", DVectorCapacity(*dvec));
  printf("res1 = %d\n", res);
	res += (*(int*)DVectorAccessElement(*dvec, 0) == 1);
  printf("res2 = %d\n", res);
	res += (*(int*)DVectorAccessElement(*dvec, 1) == 2);
  printf("res3 = %d\n", res);
	res += (*(int*)DVectorAccessElement(*dvec, 2) == 3);
  printf("res4 = %d\n", res);
	res += (*(int*)DVectorAccessElement(*dvec, 4) == 5);
	printf("res5 = %d\n", res);
	return(6 == res);
}

int checkAccess(dvector_t **dvec)
{
	int * temp = (int *)DVectorAccessElement(*dvec, 3);

	*temp = 6;

	return (6 == *(int *)DVectorAccessElement(*dvec, 3));
}


int checkPop(dvector_t **dvec)
{
	int res = 0;

	*dvec = DVectorPopBack(*dvec);
	res += (DVectorSize(*dvec) == 4);
	*dvec = DVectorPopBack(*dvec);
	res += (DVectorSize(*dvec) == 3);
	*dvec = DVectorPopBack(*dvec);
	res += (DVectorSize(*dvec) == 2);
	*dvec = DVectorPopBack(*dvec);
	res += (DVectorSize(*dvec) == 1);
	*dvec = DVectorPopBack(*dvec);
	res += (DVectorSize(*dvec) == 0);

	return(5 == res);
}

int main()
{
	dvector_t * dvec = DVectorCreate(1, 50);

	RUN_TEST(CheckCreate(dvec), "Create" );
	RUN_TEST(CheckSize(dvec, 0), "Size on empty vector" );
	RUN_TEST(CheckResize(&dvec), "Resize" );
	RUN_TEST(CheckPush(&dvec), "Push");
	RUN_TEST(CheckSize(dvec, 5), "Size on 5 push" );
	RUN_TEST(checkAccess(&dvec), "Access");
	RUN_TEST(checkPop(&dvec), "Pop");

	DVectorDestroy(dvec);

	return (0);
}
