/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_hash_table.c
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <stdlib.h>
#include <string.h> /* memcmp */
/* mmap */
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "../include/hash_table.h"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define RED printf("\033[0;31m")
#define GREEN printf("\033[0;32m")
#define YELLOW printf("\033[01;33m")
#define BLUE printf("\033[0;34m")
#define RESET printf("\033[0m")
#define RUN_TEST(result, name) {\
            printf("Test %s: ", name);\
            if (result)\
            {\
                GREEN;\
                printf("Success\n");\
                RESET;\
            }\
            else\
            {\
                RED;\
                printf("Failed\n");\
                RESET;\
            }\
        }

#define HASH_TABLE_SIZE 11
#define DICTIONARY_SIZE 10000
#define TOTAL_DICTIONARY_WORDS 102774
#define PATH "/usr/share/dict/words"

enum successful {SUCCESS, FAILURE};
enum matching {FALSE, TRUE};
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions declarations~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

size_t hash_func(const void *key);
size_t DicHashFunc(const void *key);
int IsMatch(const void *lhs, const void *rhs);
int PrintHash(void *data, void *params);
void BasicTest(void);
void CollisionsTest(void);
void *LinuxDictionary(char *key);
int MmapLinuxDictionary(char *key);

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~main~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main(int argc ,char *argv[])
{
    if (1 < argc)
	{
        printf("Linux Dictionary by File:\n");
		if (NULL != LinuxDictionary(argv[1]))
        {
            GREEN;
            printf("The term |%s| is existing in Linux dictionary.\n", argv[1]);
            RESET;
        }
        else
        {
            RED;
            printf("The term |%s| is NOT existing in Linux dictionary.\n", argv[1]);
            RESET;
        }

        /*printf("Linux Dictionary by mmap:\n");
        switch (MmapLinuxDictionary(argv[1]))
        {
            case TRUE:  GREEN;
                        printf("The term |%s| is existing in Linux dictionary.\n", argv[1]);
                        RESET;
                        break;
            default:    RED;
                        printf("The term |%s| is NOT existing in Linux dictionary.\n", argv[1]);
                        RESET;
                        break;
        }*/
	}

	else
	{
        printf("Hash Table tests: :)\n");
        BasicTest();
        CollisionsTest();
        printf("To load Linux Dictionary return the progrem and put name to argv[1] this time :)\n");
	}

	return SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~helper functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

size_t hash_func(const void *key)
{
    char *str = (char *)key;
    size_t sum = 0;
    size_t i = 0;

    /*while (*str != '\0') */
    for( ; str[i] != '\0'; ++i)
    {
        sum += str[i];
    }

    return (sum % HASH_TABLE_SIZE);
}

int IsMatch(const void *lhs, const void *rhs)
{
    /*size_t ln = strlen((char *)lhs);
    size_t rn = strlen((char *)rhs);

    return (0 == memcmp(lhs, rhs, ln) &&
        0 == memcmp(lhs, rhs, rn));*/
    return (0 == strcmp((char *)lhs, (char *)rhs));
}

int PrintHash(void *data, void *params)
{
    char *str = (char *)data;
    printf("%s\n", str);
    (void)params;
    return 0;
}

size_t DicHashFunc(const void *key)
{
    char *str = (char *)key;
    size_t sum = 0;
    size_t i = 0;

    for( ; str[i] != '\0'; ++i)
    {
        sum += str[i];
    }
    return (sum % DICTIONARY_SIZE);

/*    unsigned hashval;
    char *str = (char *)key;
    for (hashval = 0; *str != '\0'; str++)
    {
        hashval = *str + 101*hashval;
    }
    return hashval % (DICTIONARY_SIZE);*/
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~test functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* test with no collisions */
void BasicTest(void)
{
    hash_t *hash_table = HashCreate(hash_func, IsMatch, HASH_TABLE_SIZE);
    const char *name_list[] = {"Mia", "Tim", "Bea", "Zoe", "Sue", "Len",
                                "Moe", "Lou", "Rae", "Max", "Tod"};
    const char *name = "Tim";
    size_t i = 0;

    BLUE;
    printf("\n~~~~~~~~~Basic Test~~~~~~~~~\n");
    RESET;

    RUN_TEST(0 == HashSize(hash_table), "Size after create");
    RUN_TEST(TRUE == HashIsEmpty(hash_table), "IsEmpty after create");

    for (; i < HASH_TABLE_SIZE; ++i)
    {
        HashInsert(hash_table, name_list[i]);
    }
    YELLOW;
    printf("PrintHash with HashForEach:\n");
    RESET;
    HashForEach(hash_table, PrintHash, NULL);
    RUN_TEST(HASH_TABLE_SIZE == HashSize(hash_table), "Size after insertions");
    RUN_TEST(FALSE == HashIsEmpty(hash_table), "IsEmpty after insertions");

    RUN_TEST(TRUE == IsMatch(HashFind(hash_table, name), name_list[1]), "Find");

    HashRemove(hash_table, name);
    RUN_TEST(HASH_TABLE_SIZE - 1 == HashSize(hash_table), "Remove Tim");
    YELLOW;
    printf("PrintHash with HashForEach:\n");
    RESET;
    HashForEach(hash_table, PrintHash, NULL);


    HashDestroy(hash_table); hash_table = NULL;
}

void CollisionsTest(void)
{
    hash_t *hash_table = HashCreate(hash_func, IsMatch, HASH_TABLE_SIZE);
    const char *name_list[] = {"Mia", "Tim", "Bea", "Zoe", "Sue", "Len",
                                "Moe", "Lou", "Rae", "Max", "Tod",
                                "Misha", "ishaM", "isMha", "aba", "baa"};
    const char *name = "Misha";
    size_t i = 0;
    size_t size = 16;

    BLUE;
    printf("\n~~~~~~~~~Collisions Test~~~~~~~~~\n");
    RESET;

    RUN_TEST(0 == HashSize(hash_table), "Size after create");
    RUN_TEST(TRUE == HashIsEmpty(hash_table), "IsEmpty after create");

    for (; i < size; ++i)
    {
        HashInsert(hash_table, name_list[i]);
    }
    YELLOW;
    printf("PrintHash with HashForEach:\n");
    RESET;
    HashForEach(hash_table, PrintHash, NULL);
    RUN_TEST(size == HashSize(hash_table), "Size after insertions");
    RUN_TEST(FALSE == HashIsEmpty(hash_table), "IsEmpty after insertions");

    RUN_TEST(TRUE == IsMatch(HashFind(hash_table, name), name_list[11]), "Find");

    HashRemove(hash_table, name);
    RUN_TEST(size - 1 == HashSize(hash_table), "Remove Misha");
    YELLOW;
    printf("PrintHash with HashForEach:\n");
    RESET;
    HashForEach(hash_table, PrintHash, NULL);


    HashDestroy(hash_table); hash_table = NULL;
}

void * LinuxDictionary(char *key)
{
    size_t i  = 0;
    char **dictionary = NULL;
    hash_t *hash_table = NULL;
    int status = SUCCESS;
    void *data_to_return = NULL;

    FILE *fp = fopen(PATH, "r");
    if (NULL == fp)
    {
        return NULL;
    }

    dictionary = (char **)malloc(TOTAL_DICTIONARY_WORDS * sizeof(char *));
    if (NULL == dictionary)
    {
        return NULL;
    }
    hash_table = HashCreate(DicHashFunc, IsMatch, DICTIONARY_SIZE);
    if (NULL == hash_table)
    {
        return NULL;
    }


    for (i  = 0; i < TOTAL_DICTIONARY_WORDS && status == SUCCESS; ++i)
    {
        dictionary[i] = (char *)malloc(30);
        if (NULL == dictionary[i])
        {
            return NULL;
        }
        /*same as fscanf(fp,"%s", dictionary[i]);*/
        fgets(dictionary[i], 30, fp);
        /* replace '\n' to '\0' */
        dictionary[i][strlen(dictionary[i]) - 1] = '\0';

        status = HashInsert(hash_table, dictionary[i]);
        if (FAILURE == status)
        {
            return NULL;
        }
    }
    fclose(fp);

    data_to_return = HashFind(hash_table, key);

    for (i = 0 ; i < TOTAL_DICTIONARY_WORDS; ++i)
    {
        free(dictionary[i]); dictionary[i] = NULL;
    }
    free(dictionary); dictionary = NULL;

    HashDestroy(hash_table); hash_table = NULL;

    return data_to_return;
}

int MmapLinuxDictionary(char *key)
{
    unsigned char *map;
    unsigned char *temp;
    size_t size;
    unsigned char *runner;
    struct stat s;
    int fd = open(key, O_RDONLY);
    int status = fstat(fd, &s);
    hash_t *hash_table = HashCreate(DicHashFunc, IsMatch, DICTIONARY_SIZE);


    size = s.st_size;

    map = (unsigned char *)mmap(NULL, size ,PROT_READ | PROT_WRITE,
                                                MAP_PRIVATE, fd, 0);
    runner = map;
    while(runner != map + size)
    {
        temp = runner;
        runner = (unsigned char *)memchr(runner,'\n',80);
        *runner = '\0';
        ++runner;
        HashInsert(hash_table, temp);
    }

    HashDestroy(hash_table);

    return status;
}
