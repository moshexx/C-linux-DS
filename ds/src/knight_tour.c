/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: knight_tour.c
*	author: Moshe Cohen
*	reviewer: Sir Yoni Ladijensky

--------------------------------------------------------------------------------
*******************************************************************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SYNOPSIS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
A knight's tour is a sequence of moves of a knight on a chessboard such that
the knight visits every square exactly once. If the knight ends on a square
that is one knight's move from the beginning square
(so that it could tour the board again immediately, following the same path),
the tour is closed; otherwise, it is open.

The knight's tour problem is the mathematical problem of finding a knight's tour.
Creating a program to find a knight's tour is a common problem given to
computer science students.[3] Variations of the knight's tour
problem involve chessboards of different sizes than the usual 8 × 8,
as well as irregular (non-rectangular) boards.

Sir Yoni, You are about to meet with the optimized algorithm of chess masters.
*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~home_made includes~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <assert.h> /* assert */

#include "knight_tour.h"
#include "bitarray.h"
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define TOTAL_MOVES_OPTIONS 8
#define BOARD_SIZE OUTLINE_SIZE * OUTLINE_SIZE
#define NO_VALID_MOVE 64
#define COL_FOR_COUNT_VALID_MOVES 8

enum status_t {SUCCESS, FAILURE};
/*~~~~~~~~~~~~~~~~~~~~~~~~static functions signatures~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void DefineMovesTable(size_t outline_size,
        int moves_table[][TOTAL_MOVES_OPTIONS + 1]);
static int Solve(size_t *board, bitarr_t map,
        int moves_table[][TOTAL_MOVES_OPTIONS + 1], int index);
static int CountNumOfValidMoves(int index,  bitarr_t map,
        int moves_table[][TOTAL_MOVES_OPTIONS + 1]);
static void UpdateValidMovesOfNextMoves(bitarr_t map,
       int moves_table[][TOTAL_MOVES_OPTIONS + 1], int index);
static void BubbleSortOptimized(int moves_table[][TOTAL_MOVES_OPTIONS + 1],
                        int row[], size_t size, int index);
static void SortIndexRow(bitarr_t map,
        int moves_table[][TOTAL_MOVES_OPTIONS + 1], int index);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~API function~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void KnightTour(size_t board[BOARD_SIZE], size_t col, size_t row)
{
    bitarr_t map = 0;
    int index = (row * OUTLINE_SIZE) + col;
    static int moves_table[BOARD_SIZE + 1][TOTAL_MOVES_OPTIONS + 1] = {0};

    assert(NULL != board);
    assert(col < OUTLINE_SIZE);
    assert(row < OUTLINE_SIZE);

    DefineMovesTable(OUTLINE_SIZE, moves_table);
    map = BitsArrResetAll(map);

    Solve(board, map, moves_table, index);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~static functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void DefineMovesTable(size_t outline_size,
            int moves_table[][TOTAL_MOVES_OPTIONS + 1])
{
    size_t i = 0;

    for (i = 0; i < BOARD_SIZE; ++i)
    {/* Define every field for the next possible move */
        moves_table[i][0] = -(outline_size * 2 + 1) + i;  /* -17 */
        moves_table[i][1] = -(outline_size * 2 - 1) + i;  /* -15 */
        moves_table[i][2] = -(outline_size + 2) + i;      /* -10 */
        moves_table[i][3] = -(outline_size - 2) + i;      /* -6  */
        moves_table[i][4] = outline_size - 2  + i;        /*  6  */
        moves_table[i][5] = outline_size + 2  + i;        /* 10  */
        moves_table[i][6] = (outline_size * 2) - 1  + i;  /* 15  */
        moves_table[i][7] = (outline_size * 2) + 1  + i;  /* 17  */

        /* Define the specific fields with no possible move to unvalid */
        if (0 == i % outline_size)
        {
            moves_table[i][0] = NO_VALID_MOVE;
            moves_table[i][2] = NO_VALID_MOVE;
            moves_table[i][4] = NO_VALID_MOVE;
            moves_table[i][6] = NO_VALID_MOVE;
        }

        if (1 == i % outline_size)
        {
            moves_table[i][2] = NO_VALID_MOVE;
            moves_table[i][4] = NO_VALID_MOVE;
        }

        if (outline_size - 1 == i % outline_size)
        {
            moves_table[i][1] = NO_VALID_MOVE;
            moves_table[i][3] = NO_VALID_MOVE;
            moves_table[i][5] = NO_VALID_MOVE;
            moves_table[i][7] = NO_VALID_MOVE;
        }

        if (outline_size - 2 == i % outline_size)
        {
            moves_table[i][3] = NO_VALID_MOVE;
            moves_table[i][5] = NO_VALID_MOVE;
        }

        if (i < outline_size)
        {
            moves_table[i][0] = NO_VALID_MOVE;
            moves_table[i][1] = NO_VALID_MOVE;
            moves_table[i][2] = NO_VALID_MOVE;
            moves_table[i][3] = NO_VALID_MOVE;
        }

        if (i < outline_size * 2)
        {
            moves_table[i][0] = NO_VALID_MOVE;
            moves_table[i][1] = NO_VALID_MOVE;
        }

        if (((outline_size - 2) * outline_size) <= i)
        {
            moves_table[i][6] = NO_VALID_MOVE;
            moves_table[i][7] = NO_VALID_MOVE;
        }

        if ((outline_size - 1) * outline_size <= i)
        {
            moves_table[i][4] = NO_VALID_MOVE;
            moves_table[i][5] = NO_VALID_MOVE;
            moves_table[i][6] = NO_VALID_MOVE;
            moves_table[i][7] = NO_VALID_MOVE;
        }
    }
    /* last row (64) - is unvalid row and use to help with the sort issue
       last col (8) - use to store data for the sort issue - COUNT_VALID_MOVES */
    moves_table[BOARD_SIZE][COL_FOR_COUNT_VALID_MOVES] = TOTAL_MOVES_OPTIONS + 1;

}

static int Solve(size_t *board, bitarr_t map,
        int moves_table[][TOTAL_MOVES_OPTIONS + 1], int index)
{
    int move = 0;

    if (BOARD_SIZE == BitsArrCountOn(map))
    {
        return SUCCESS;
    }

    if (NO_VALID_MOVE == index || 1 == BitsArrGetVal(map, index))
    {
        return FAILURE;
    }

    map = BitsArrSetOn(map, index);
    SortIndexRow(map, moves_table, index);

    for (move = 0; move < TOTAL_MOVES_OPTIONS; ++move)
    {
        if (SUCCESS == Solve(board, map, moves_table, moves_table[index][move]))
        {
            board[index] = BitsArrCountOn(map) - 1;

            return SUCCESS;
        }
    }
    map = BitsArrSetOff(map, index);

    return FAILURE;
}

static int CountNumOfValidMoves(int index,  bitarr_t map,
        int moves_table[][TOTAL_MOVES_OPTIONS + 1])
{
    int count = 0;
    size_t i = 0;

    for (i = 0; i < TOTAL_MOVES_OPTIONS; ++i)
    {
        if (NO_VALID_MOVE != moves_table[index][i] &&
            1 != BitsArrGetVal(map, index))
        {
            ++count;
        }
    }
    moves_table[index][COL_FOR_COUNT_VALID_MOVES] = count;

    return count;
}

static void UpdateValidMovesOfNextMoves(bitarr_t map,
       int moves_table[][TOTAL_MOVES_OPTIONS + 1], int index)
{
    size_t i = 0;

    for (i = 0; i < TOTAL_MOVES_OPTIONS; ++i)
    {
        int next_move = moves_table[index][i];

        CountNumOfValidMoves(next_move, map, moves_table);
    }
}

static void BubbleSortOptimized(int moves_table[][TOTAL_MOVES_OPTIONS + 1],
                         int row[], size_t size, int index)
{
    size_t j;
    int tmp = 0;
    short fsorted = 0;

    for (j = 0; 0 < size && !fsorted; ++j, --size)
    {
        fsorted = 1;
        for (j = 0; j < size - 1; ++j)
        {
            int next_move_one = moves_table[index][j];
            int next_move_other = moves_table[index][j + 1];

            if (moves_table[next_move_one][TOTAL_MOVES_OPTIONS] >
                moves_table[next_move_other][TOTAL_MOVES_OPTIONS])
            {
                tmp = row[j];
                row[j] = row[j + 1];
                row[j + 1] = tmp;
                fsorted = 0;
            }
        }
    }
}

static void SortIndexRow(bitarr_t map,
       int moves_table[][TOTAL_MOVES_OPTIONS + 1], int index)
{
    UpdateValidMovesOfNextMoves(map, moves_table, index);

    BubbleSortOptimized(moves_table, moves_table[index], TOTAL_MOVES_OPTIONS,
                        index);
}
