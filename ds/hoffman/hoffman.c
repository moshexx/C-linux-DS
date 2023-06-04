
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <pthread.h>    /* threads */
#include <stdio.h>      /* printf */
#include <string.h>     /* C lib: strlen, strcmp */
#include <strings.h>    /* POSIX lib: strcasecmp */
#include <errno.h>      /* errno */
#include <stdlib.h>     /* malloc(), free (), qsort() */
#include <assert.h>     /* assert */
#include <time.h>       /* time */
#include <unistd.h>     /* write */
/* mmap */
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "heap.h"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define NUM_OF_THREADS 5
#define MAX_TREE_HT 200

enum status_t
{    ALLOCATION_FAILURE = -1,
     SUCCESS = 0,
     FAILURE = 1
};

typedef struct 
{
    size_t his[256];
    unsigned char *runner;
    size_t num_of_ch_to_count;
}vars_t;

typedef struct MinHeapNode MinHeapNode;
struct MinHeapNode 
{
	char data;
	unsigned freq;
	MinHeapNode *left;
    MinHeapNode *right;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~helper functions signatures~~~~~~~~~~~~~~~~~~~~~~~*/
static unsigned char *OpenFile(char *file_path, size_t *_size_of_dictionary);
static void *CountThread(void *data);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~API function~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

MinHeapNode *CreateNode(char data, unsigned freq)
{
	MinHeapNode *newNode = (MinHeapNode *)malloc(sizeof(MinHeapNode));
    if (NULL == newNode) { return NULL; }

	newNode->left = NULL;
    newNode->right = NULL;
	newNode->data = data;
	newNode->freq = freq;

	return newNode;
}

/* The cmp function  return  an  integer less than, equal to, or greater than
zero if @lhs is, respectively, before , match, or after @rhs. */
static int CmpFuncHeapMin(const void *lhs, const void *rhs)
{
    return (((MinHeapNode *)rhs)->freq < ((MinHeapNode *)lhs)->freq);
}

heap_t *CreateAndBuildMinHeap(size_t freq[], size_t size)	
{
	heap_t *minHeap = HeapCreate(CmpFuncHeapMin);
    size_t i = 0;
    
	for (; i < size; ++i)
    {
        if (0 < freq[i])
        {
		    HeapPush(minHeap, CreateNode((char)i, freq[i]));
        }
    }

	return minHeap;
}

MinHeapNode *BuildHuffmanTree(size_t freq[], size_t size)
{
	MinHeapNode *left;
    MinHeapNode *right;
    MinHeapNode *top;

	heap_t *minHeap = CreateAndBuildMinHeap(freq, size);
    if (NULL == minHeap) { return NULL; }

	while (1 < HeapSize(minHeap)) 
    {
		left = HeapPeek(minHeap);
        HeapPop(minHeap);
		right = HeapPeek(minHeap);
        HeapPop(minHeap);

		top = CreateNode(-1, left->freq + right->freq);
		top->left = left;
		top->right = right;

		HeapPush(minHeap, top);
	}

	return HeapPeek(minHeap);
}

int isLeaf(MinHeapNode* node)
{
	return !(node->left) && !(node->right);
}

void PrintArr(unsigned char arr[], size_t size)
{
	size_t i;
	for (i = 0; i < size; ++i)
    {
		printf("%d", arr[i]);
    }

	printf("\n");
}

void PrintCodes(MinHeapNode *root, unsigned char arr[], unsigned char top)
{
	if (NULL != root->left) 
    {
		arr[top] = 0;
		PrintCodes(root->left, arr, top + 1);
	}

	if (NULL != root->right) 
    {
		arr[top] = 1;
		PrintCodes(root->right, arr, top + 1);
	}

	if (isLeaf(root)) 
    {
		printf("%c: ", root->data);
		PrintArr(arr, top);
	}
}

void HuffmanCodes(size_t freq[], size_t size)
{
	MinHeapNode *root = BuildHuffmanTree(freq, size);
		
    static unsigned char arr[MAX_TREE_HT] = {0};

	PrintCodes(root, arr, 0);
}

int Counting(char *file_path, size_t *freq)
{
    pthread_t threads[NUM_OF_THREADS] = {0};
    vars_t vars[NUM_OF_THREADS] = {0};
   
    unsigned char *maped_file = NULL;
    size_t size_of_dictionary = 0;
    size_t i = 0;

    maped_file = OpenFile(file_path, &size_of_dictionary);

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        vars[i].runner = maped_file + i * (size_of_dictionary/NUM_OF_THREADS);
        vars[i].num_of_ch_to_count = size_of_dictionary/NUM_OF_THREADS;
    }
    vars[i - 1].num_of_ch_to_count += size_of_dictionary % NUM_OF_THREADS;

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
       pthread_create(&threads[i], NULL, CountThread, &vars[i]);
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    memset(freq, 0, 256 * sizeof(size_t));
    /* printf("The occurrence of the characters in the file ''%s'':\n", file_path); */
    for (i = 0; i < 256; ++i)
    {
        size_t j = 1;
        for (j = 1; j < NUM_OF_THREADS; ++j)
        {
            vars[0].his[i] += vars[j].his[i];
        }
        if (0 < vars[0].his[i])
        {
            freq[i] = vars[0].his[i];
            /* printf("%c:\t%lu\n",(unsigned char)i, vars[0].his[i]); */
        }
    }

	return SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~static functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static unsigned char *OpenFile(char *file_path, size_t *_size_of_dictionary)
{
    unsigned char *map;
    size_t size;
    struct stat s;
    int fd = open(file_path, O_RDONLY);
    int status = fstat(fd, &s); /* count num of byte in the file */
    if (-1 == status)
    {
        printf("Error: %s\n", strerror(errno));
        return NULL;     
    }
    size = s.st_size;

    map = (unsigned char *)mmap(NULL, size ,PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if(map == MAP_FAILED)
	{
		return NULL;
	}	

    *_size_of_dictionary = size;
    return map;
}

static void *CountThread(void *data)
{
    vars_t *vars = (vars_t *)data;
    size_t i = 0;

    for (i = 0; i < vars->num_of_ch_to_count; ++i)
    {
        vars->his[*vars->runner] += 1;
        ++vars->runner;
    }

    return NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~main~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main(int argc, char **argv)
{
    char *file_path = argv[1];
    static size_t freqArr[256];

    Counting(file_path, freqArr);
	HuffmanCodes(freqArr, 256);

    /* HeapDestroy () TODO:*/
    (void)argc;
    return 0;
}
