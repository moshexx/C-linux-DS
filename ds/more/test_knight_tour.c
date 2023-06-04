/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_knight_tour.c
*	author: Moshe Cohen
*	reviewer: Yoni Ladijensky

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */

#include "../include/knight_tour.h"

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

enum successful {SUCCESS, FAILURE};
enum matching {NO, YES};
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main()
{
    size_t board[OUTLINE_SIZE * OUTLINE_SIZE] = {0};
    size_t i = 0;

    KnightTour(board, 0, 0);

    for (i = 0; i < OUTLINE_SIZE * OUTLINE_SIZE; ++i)
    {
        if (0 == i % OUTLINE_SIZE)
        {
            printf("\n");
        }
        printf("%lu\t", board[i]);
    }

    printf("\n\n");

	return SUCCESS;
}

/*************************************************************/



/* in src file - should be in the end of the function DefineMovesTable
   help to print the LUTs:

int j = 0;
int k = 0;

printf("Move LUTs are: \n");
for (j = 0; j < TOTAL_MOVES_OPTIONS; ++j)
{
printf("\nNext LUT offset: %d\n", j);
for (k = 0; k < BOARD_SIZE; ++k)
{
  if (0 == k % OUTLINE_SIZE && 0 != k)
  {
    printf("\n\n");
  }
  printf("%d\t", moves_table[k][j]);
}
printf("\n\n");
}

printf("Nir printing:\n");

for ( k = 0 ; k < BOARD_SIZE + 1; ++k)
{
printf("%d:\t", k);
for (j = 0; j < TOTAL_MOVES_OPTIONS + 1; j++)
{
    printf("%d\t", moves_table[k][j]);
}
printf("\n");
}
*/
