/*------------------------------------------------------------------------------
*	file name: test_knight_tour.c
*	author: Thanks to Ben Ronen
*	reviewer:
------------------------------------------------------------------------------*/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h>

#include "knight_tour.h"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define BLACK_BCK "\x1b[40m"
#define WHITE_BCK "\x1b[47m"
#define RESET_BK   "\x1b[0m"


#define RED_B "\033[01;31m"
#define GREEN_B "\033[01;32m"
#define YELLOW_B "\033[01;33m"
#define BLUE_B "\033[01;34m"
#define BLACK_B "\033[01;30m"
#define WHITE_B "\033[01;37m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define RESET 	"\033[0m"
#define BLUE "\033[0;34m"
#define BLACK "\033[0;30m"
#define WHITE "\033[0;37m"
#define RUN_TEST_B(result, name) {\
            printf(YELLOW_B"Test %s: "RESET, name);\
            if (result)\
            {\
                printf(GREEN_B"Success\n"RESET);\
            }\
            else\
            {\
                printf(RED_B"Failed\n"RESET); \
            }\
        }

#define RUN_TEST(result, name) {\
            printf(YELLOW"\t%s: "RESET, name);\
            if (result)\
            {\
                printf(GREEN"Success\n"RESET);\
            }\
            else\
            {\
                printf(RED"Failed\n"RESET); \
            }\
        }

        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void PrintChessBoard(size_t *board)
{
	size_t i = 0;
	int color = 1;

	for (i = 0; i < OUTLINE_SIZE * OUTLINE_SIZE; ++i, color *= -1)
	{
		if (0 == i % OUTLINE_SIZE)
		{
			printf("\n");
			color *= (0 == OUTLINE_SIZE % 2) ? -1 : 1;
		}
		if (0 > color)
		{
			if (10 > board[i])
			{
				printf(BLACK_BCK WHITE_B" %lu  "RESET_BK RESET, board[i]);
			}
			else
			{
				printf(BLACK_BCK WHITE_B" %lu "RESET_BK RESET, board[i]);
			}
		}
		else
		{
			if (10 > board[i])
			{
				printf(WHITE_BCK BLACK_B" %lu  "RESET_BK RESET, board[i]);
			}
			else
			{
				printf(WHITE_BCK BLACK_B" %lu "RESET_BK RESET, board[i]);
			}
		}

	}printf("\n"RESET);
}

void Nullifyarr(size_t *arr, size_t size)
{
	for (; size > 0; --size)
	{
		arr[size - 1] = 0;
	}
}

void TestKnightTour(size_t *arr, size_t frame_size, size_t col, size_t row)
{
	printf(YELLOW_B"%lux%lu - ", frame_size, frame_size);
	printf(YELLOW"starting at col %lu and row %lu:\n"RESET, col, row);
	Nullifyarr(arr, frame_size * frame_size);
	KnightTour(arr, col, row);
	PrintChessBoard(arr);
	printf("\n");
}

int main ()
{
	size_t arr[64] = {0};
	size_t i = 0, j = 0;

	for (i = 0; i < OUTLINE_SIZE; ++i)
	{
		for (j = 0; j < OUTLINE_SIZE; ++j)
		{
			if (0 != (i + j) % 2)
			{
				continue;
			}
			TestKnightTour(arr, OUTLINE_SIZE, i, j);
		}
	}

	return 0;
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
