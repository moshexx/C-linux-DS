/******************************************************************************/
/*                                                                            */
/*                  Descriptions - Calculator - API Functions                 */
/*                             Date: 1.12.2020                                */
/*                                Group: OL96                                 */
/*                                                                            */
/******************************************************************************/

#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__


typedef enum calc_status
{
	SUCCESS,
	MATH_ERROR,
	SYNTAX_ERROR,
	ALLOCATING_ERROR
} calc_status_t;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
* Description: The function calculates the math expression in the input string
* Return value: status of calculation.
				SUCCESS/ MATH_ERROR/ SYNTAX_ERROR/ ALLOCATING_ERROR
* Errors: calculator can fail on syntax or on math mistakes
* Undefined behavior: pointer to input or result is NULL
*
* Complexity: O(n).
*/
calc_status_t Calculator(const char *input, double *result);

#endif   /*__CALCULATOR_H__*/
