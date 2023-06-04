#include <stdio.h>
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~typedef~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
typedef struct node
{
void *data;
struct node *next;
} node_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~main~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main()
{
	int n1 = 111;
	int n2 = 222;
	int n3 = 333;
	int n4 = 444;
	int n5 = 555;
	int *p1 = &n1;
	int *p2 = &n2;
	int *p3 = &n3;
	int *p4 = &n4;
	int *p5 = &n5;

  node_t node1, node2, node3, node4;
  node_t *head = &node1;

	/* ex1 */
  node_t *prev = NULL;
  node_t *current = &node1;
  node_t *next = &node2;

	/* ex2 */
	node_t *walk = NULL;
	node_t *run = NULL;
	int floop = 0;

	/* ex3 */
	node_t node5;
	node_t *head2 = &node5;
	node_t *iter = NULL;
	node_t *iter2 = NULL;
	int flag = 1;

	/****	create the llist	****/
  node1.data = p1;
  node2.data = p2;
  node3.data = p3;
  node4.data = p4;
  node1.next = &node2;
  node2.next = &node3;
  node3.next = &node4;
  node4.next = NULL;

  printf("The list at the beginning:\n");
  printf("%d ->", *(int *)head->data);
  printf("%d ->", *(int *)head->next->data);
  printf("%d ->", *(int *)head->next->next->data);
  printf("%d ->\n\n", *(int *)head->next->next->next->data);

	/***********************************Flip*************************************/
  while (NULL != current)
  {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  head = prev;

  printf("The list after FLIP:\n");
  printf("%d ->", *(int *)head->data);
  printf("%d ->", *(int *)head->next->data);
  printf("%d ->", *(int *)head->next->next->data);
  printf("%d ->\n\n", *(int *)node4.next->next->next->data);


  /***************** HasLoop - Floyd's Cycle-Finding Algoritm *****************/
	/* if the pinters (slow and fast) will meet so there is a loop */
	/* no loop check */
	printf("Check singly linked list without a loop: \n");
	printf("%d ->", *(int *)head->data);
  printf("%d ->", *(int *)head->next->data);
  printf("%d ->", *(int *)head->next->next->data);
  printf("%d ->\n", *(int *)node4.next->next->next->data);
	walk = head;
	run = head;
	floop = 0;

	/* because the different pace that can arrive to NULL in different time */
	while (walk && run && run->next && !floop)
	{
		walk = walk->next;
		run = run->next->next;
		if (walk == run)
		{
			floop = 1;
		}
	}

	if (floop)
	{
		printf("LLLLOOP!\n\n");
	}
	else
	{
		printf("just a boring list!\n\n");
	}

	/* with loop check */
	/****	create the loop llist	****/
	head = &node1;
  node1.data = p1;
  node2.data = p2;
  node3.data = p3;
  node4.data = p4;
  node1.next = &node2;
  node2.next = &node3;
  node3.next = &node4;
  node4.next = &node2; /* loop! (instead of NULL)*/

	printf("Check singly linked list with a loop:\n");
	printf("%d ->", *(int *)head->data);
  printf("%d ->", *(int *)head->next->data);
  printf("%d ->", *(int *)head->next->next->data);
  printf("%d ->", *(int *)head->next->next->next->data);
	printf("%d ->", *(int *)head->next->next->next->next->data);
	printf("%d ->.....\n", *(int *)head->next->next->next->next->next->data);


	walk = head;
	run = head;
	floop = 0;

	while (walk && run && run->next && !floop)
	{
		walk = walk->next;
		run = run->next->next;
		if (walk == run)
		{
			floop = 1;
		}
	}

	if (floop)
	{
		printf("LLLLOOP!\n\n");
	}
	else
	{
		printf("just a boring list!\n\n");
	}


	/***************************** Find Intersection ****************************/
	head = &node1;
	node1.data = p1;
  node2.data = p2;
  node3.data = p3;
  node4.data = p4;
  node1.next = &node2;
  node2.next = &node3;
  node3.next = &node4;
  node4.next = NULL;

	head2 = &node5;
	node5.data = p5;
	node5.next = &node2;

	printf("Find Intersection in two singly linked list:\n");
	printf("First List:\n");
	printf("%d ->", *(int *)head->data);
	printf("%d ->", *(int *)head->next->data);
	printf("%d ->", *(int *)head->next->next->data);
	printf("%d ->\n\n", *(int *)head->next->next->next->data);

	printf("Second List:\n");
	printf("%d ->", *(int *)head2->data);
	printf("%d ->", *(int *)head2->next->data);
	printf("%d ->", *(int *)head2->next->next->data);
	printf("%d ->\n\n", *(int *)head->next->next->next->data);


	iter = head;
	iter2 = head2;
	flag = 1;

	for (iter = head; NULL != iter->next && flag; iter = iter->next)
	{
		iter2 = head2;
		for (iter2 = head2; NULL != iter2 && flag; iter2 = iter2->next)
		{
			if(iter == iter2)
			{
				printf("The insertion is in %d\n\n", *(int *)iter->data);
				flag = 0;
			}
		}
	}
	if (1 == flag)
	{
		printf("There is no insertion.\n");
	}

	/* 'iter' & 'iter2' point to the insertion node now */
	/*test*/
	printf("insertion %s.\n", iter == iter2? "SUCCESS":"FALIURE");


	return 0;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
