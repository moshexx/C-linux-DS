/*******************************************************************************
*		Descriptions - Knight Tour API Function	                               *
*		Date: 21.12.2020						                               *
*		Group: OL96							                                   *
*******************************************************************************/

#ifndef __KNIGHT_TOUR_H_ILRD_OL96__
#define __KNIGHT_TOUR_H_ILRD_OL96__

#include <stddef.h> /* size_t */

#define OUTLINE_SIZE 8

/*
* Description: given a chess board of size [OUTLINE_SIZE * OUTLINE_SIZE] and a
			   knight at its starting position (@col, @row), the function finds
			   a path for the knight to go through all the squares on the board
			   without stepping more than once on each square, and writes the
			   order of the path is written to the array @board.
* Return value: none
* Errors: none
* Undefined behavior: there is no solution when OUTLINE_SIZE is less than 5
					  @col and @row must be less than OUTLINE_SIZE
* Complexity: ???
*/
void KnightTour(size_t board[OUTLINE_SIZE * OUTLINE_SIZE], size_t col, size_t row);

#endif   /*__KNIGHT_TOUR_H_ILRD_OL96__*/
