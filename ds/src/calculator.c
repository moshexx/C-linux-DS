/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: calculator.c
*	author: Moshe Cohen
*	reviewer:  Or Yosef

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdlib.h> /* strtod, malloc */
#include <assert.h> /* assert */
/*#include <math.h>*/	/* pow */

#include "calculator.h"
#include "stack.h"

#define NUM_OF_STATES 2
#define ASCII_TABLE_SIZE 256
#define DUMMY_OPRTR '$'
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum state
{
	WAITING_FOR_OPERAND,
	WAITING_FOR_OPERATOR,
	ERROR
} state_t;

typedef struct transition
{
    calc_status_t(*handle_func)(stack_t *oprtr, stack_t *oprnd, char **current_char);
    state_t state;
}transition_t;

static transition_t transition_table[ASCII_TABLE_SIZE][NUM_OF_STATES];

typedef struct operation
{
	/* operation func (+ - / *) */
    calc_status_t(*oper_func)(double first_oprnd, double second_oprnd, double *result);
    int priority;
}operation_t;

static operation_t operation_table[ASCII_TABLE_SIZE];

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~declerations~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static calc_status_t StacksPreparations(stack_t **oprtr, stack_t **oprnd, char *input);
static calc_status_t CalcInit(void);
static calc_status_t RunCalc(stack_t *oprtr, stack_t *oprnd, char *input, double *result);
static void FreeStacks(stack_t *oprtr, stack_t *oprnd);
static void InitToDefault(void);
static void InitTransitionTable(void);
static void InitOperationTable(void);
static calc_status_t ExecutCalculate(stack_t *oprtr, stack_t *oprnd);
static calc_status_t HandleOperations(stack_t *oprtr, stack_t *oprnd, char **current_char);
static calc_status_t HandlePower(stack_t *oprtr, stack_t *oprnd, char **current_char);
static calc_status_t ReturnSyntaxError(stack_t *oprtr, stack_t *oprnd, char **current_char);
static calc_status_t GetOperand(stack_t *oprtr, stack_t *oprnd, char **current_char);
static calc_status_t HandleSpace(stack_t *oprtr, stack_t *oprnd, char **current_char);
static calc_status_t HandleOpenParent(stack_t *oprtr, stack_t *oprnd, char **current_char);
static calc_status_t HandleCloseParent(stack_t *oprtr, stack_t *oprnd, char **current_char);
static calc_status_t HandleEndOfString(stack_t *oprtr, stack_t *oprnd, char **current_char);
static calc_status_t Adding(double first_oprnd, double second_oprnd, double *result);
static calc_status_t Subtract(double first_oprnd, double second_oprnd, double *result);
static calc_status_t Multi(double first_oprnd, double second_oprnd, double *result);
static calc_status_t Divide(double first_oprnd, double second_oprnd, double *result);
static calc_status_t Power(double first_oprnd, double second_oprnd, double *result);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~main function~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

calc_status_t Calculator(const char *input, double *result)
{
	calc_status_t status;
	stack_t *oprtr = NULL;
	stack_t *oprnd = NULL;

	assert(NULL != input);

	CalcInit();
	status = StacksPreparations(&oprtr, &oprnd, (char *)input);
	if (status == ALLOCATING_ERROR)
	{
		return status;
	}

	status = RunCalc(oprtr, oprnd, (char *)input, result);

	StackDestroy(oprtr);
	StackDestroy(oprnd);

	return status;
}
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~helper functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static calc_status_t StacksPreparations(stack_t **oprtr, stack_t **oprnd, char *input)
{
	char *dummy_oprtr = (char *)malloc(sizeof(char));
	if (NULL == dummy_oprtr)
	{
		return ALLOCATING_ERROR;
	}

	*oprtr = StackCreate(sizeof(input));
	*oprnd = StackCreate(sizeof(input));

	*dummy_oprtr = DUMMY_OPRTR;
	StackPush(*oprtr, dummy_oprtr);

	return SUCCESS;
}

static void FreeStacks(stack_t *oprtr, stack_t *oprnd)
{
	while (!StackIsEmpty(oprnd))
	{
		free(StackPeek(oprnd));
		StackPop(oprnd);
	}
	while (!StackIsEmpty(oprtr))
	{
		free(StackPeek(oprtr));
		StackPop(oprtr);
	}
}

static void InitToDefault(void)
{
	size_t i = 0;

    for (i = 0; i < ASCII_TABLE_SIZE; ++i)
    {/* Initialize all the fileds in the transition_table to Syntax ERROR situation */
        transition_table [i][WAITING_FOR_OPERAND].handle_func = ReturnSyntaxError;
        transition_table [i][WAITING_FOR_OPERAND].state = ERROR;

		transition_table [i][WAITING_FOR_OPERATOR].handle_func = ReturnSyntaxError;
        transition_table [i][WAITING_FOR_OPERATOR].state = ERROR;

		/* Initialize all the fileds in the operation_table 0 */
		operation_table[i].oper_func = NULL;
		operation_table[i].priority = 0;
    }
}

static void InitTransitionTable(void)
{
	size_t i = 0;

	for (i = '0'; i < '9'; ++i)
	{/* Initialize only the valid fileds in the transition_table: */
		transition_table [i][WAITING_FOR_OPERAND].handle_func = GetOperand;
        transition_table [i][WAITING_FOR_OPERAND].state = WAITING_FOR_OPERATOR;
	}
	transition_table [' '][WAITING_FOR_OPERAND].handle_func = HandleSpace;
	transition_table [' '][WAITING_FOR_OPERAND].state = WAITING_FOR_OPERAND;

	transition_table ['('][WAITING_FOR_OPERAND].handle_func = HandleOpenParent;
	transition_table ['('][WAITING_FOR_OPERAND].state = WAITING_FOR_OPERAND;
	transition_table [')'][WAITING_FOR_OPERAND].handle_func = ReturnSyntaxError;
	transition_table [')'][WAITING_FOR_OPERAND].state = ERROR;

	transition_table ['*'][WAITING_FOR_OPERATOR].handle_func = HandleOperations;
	transition_table ['*'][WAITING_FOR_OPERATOR].state = WAITING_FOR_OPERAND;
	transition_table ['/'][WAITING_FOR_OPERATOR].handle_func = HandleOperations;
	transition_table ['/'][WAITING_FOR_OPERATOR].state = WAITING_FOR_OPERAND;
	transition_table ['+'][WAITING_FOR_OPERATOR].handle_func = HandleOperations;
	transition_table ['+'][WAITING_FOR_OPERATOR].state = WAITING_FOR_OPERAND;
	transition_table ['-'][WAITING_FOR_OPERATOR].handle_func = HandleOperations;
	transition_table ['-'][WAITING_FOR_OPERATOR].state = WAITING_FOR_OPERAND;
	transition_table ['^'][WAITING_FOR_OPERATOR].handle_func = HandlePower;
	transition_table ['^'][WAITING_FOR_OPERATOR].state = WAITING_FOR_OPERAND;
	transition_table [' '][WAITING_FOR_OPERATOR].handle_func = HandleSpace;
	transition_table [' '][WAITING_FOR_OPERATOR].state = WAITING_FOR_OPERATOR; /* Do nothing */

	transition_table ['('][WAITING_FOR_OPERATOR].handle_func = ReturnSyntaxError;
	transition_table ['('][WAITING_FOR_OPERATOR].state = ERROR;
	transition_table [')'][WAITING_FOR_OPERATOR].handle_func = HandleCloseParent;
	transition_table [')'][WAITING_FOR_OPERATOR].state = WAITING_FOR_OPERATOR;

	transition_table ['\0'][WAITING_FOR_OPERATOR].handle_func = HandleEndOfString;
	transition_table ['\0'][WAITING_FOR_OPERATOR].state = ERROR; /* state to end the loop */
}

static void InitOperationTable(void)
{
	operation_table['^'].oper_func = Power;
	operation_table['^'].priority = 4;
	operation_table['*'].oper_func = Multi;
	operation_table['*'].priority = 3;
	operation_table['/'].oper_func = Divide;
	operation_table['/'].priority = 3;
	operation_table['+'].oper_func = Adding;
	operation_table['+'].priority = 2;
	operation_table['-'].oper_func = Subtract;
	operation_table['-'].priority = 2;
	operation_table['('].priority = 1;
	operation_table[DUMMY_OPRTR].priority = 0;
}

static calc_status_t ExecutCalculate(stack_t *oprtr, stack_t *oprnd)
{
	double first_operand = 0;
	double second_operand = 0;
	double *ans = NULL;
	char *op = NULL;
	calc_status_t status = SUCCESS;

	second_operand = *(double *)(StackPeek(oprnd));
	free(StackPeek(oprnd));
	StackPop(oprnd);
	ans = (double *)(StackPeek(oprnd));
	first_operand = *ans;

	op = (StackPeek(oprtr));
	status = operation_table[(int)*op].oper_func(first_operand, second_operand, ans);

	free(StackPeek(oprtr));
	StackPop(oprtr);

	return status;
}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~handle functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static calc_status_t HandleOperations(stack_t *oprtr, stack_t *oprnd, char **current_char)
{
	calc_status_t status = SUCCESS;
	int index = *(char *)StackPeek(oprtr);
	char *ch = (char *)malloc(sizeof(char));
	if (NULL == ch)
	{
		return ALLOCATING_ERROR;
	}

	*ch = **current_char;
	if (operation_table[index].priority >= operation_table[(int)**current_char].priority)
	{
		status = ExecutCalculate(oprtr, oprnd);
	}

	StackPush(oprtr, ch); /* new operator */
	*(current_char) += 1;

	return status;
}

static calc_status_t HandlePower(stack_t *oprtr, stack_t *oprnd, char **current_char)
{
	calc_status_t status = SUCCESS;
	int index = *(char *)StackPeek(oprtr);
	char *ch = (char *)malloc(sizeof(char));
	if (NULL == ch)
	{
		return ALLOCATING_ERROR;
	}

	*ch = **current_char;
	/* the change in this HandlePower vs HandleOperations is the condition: ( > ): */
	if (operation_table[index].priority > operation_table[(int)**current_char].priority)
	{
		status = ExecutCalculate(oprtr, oprnd);
	}

	StackPush(oprtr, ch); /* new operator */
	*(current_char) += 1;

	return status;
}

static calc_status_t ReturnSyntaxError(stack_t *oprtr, stack_t *oprnd, char **current_char)
{
	(void)oprtr;
	(void)oprnd;
	(void)current_char;
    return SYNTAX_ERROR;
}

static calc_status_t GetOperand(stack_t *oprtr, stack_t *oprnd, char **current_char)
{
	double *current_operand = (double *)malloc(sizeof(double));
	if (NULL == current_operand)
	{
		return ALLOCATING_ERROR;
	}

	*current_operand = strtod(*current_char, current_char);
	StackPush(oprnd, current_operand);

	(void)oprtr;
	return SUCCESS;
}

static calc_status_t HandleSpace(stack_t *oprtr, stack_t *oprnd, char **current_char)
{
	++(*current_char);

	(void)oprnd;
	(void)oprtr;
	return SUCCESS;
}
static calc_status_t HandleEndOfString(stack_t *oprtr, stack_t *oprnd, char **current_char)
{
	calc_status_t status = SUCCESS;

	while (status == SUCCESS && 1 < StackSize(oprnd) && 1 < StackSize(oprtr))
	{
		status = ExecutCalculate(oprtr, oprnd);
	}
	if ('(' == *(char *)StackPeek(oprtr))
	{
		return SYNTAX_ERROR;
	}
	(void)current_char;
	return status;
}

static calc_status_t HandleOpenParent(stack_t *oprtr, stack_t *oprnd, char **current_char)
{
	char *ch = (char *)malloc(sizeof(char));
	if (NULL == ch)
	{
		return ALLOCATING_ERROR;
	}
	*ch = **current_char;
	StackPush(oprtr, ch);
	++(*current_char);

	(void)oprnd;
	(void)oprtr;
	return SUCCESS;
}

static calc_status_t HandleCloseParent(stack_t *oprtr, stack_t *oprnd, char **current_char)
{
	calc_status_t status = SUCCESS;

	while (status == SUCCESS && 1 < StackSize(oprnd) && 1 < StackSize(oprtr) && *(char *)StackPeek(oprtr) != '('
									&& *(char *)StackPeek(oprtr) != DUMMY_OPRTR)
	{
		status = ExecutCalculate(oprtr, oprnd);
	}

	if (*(char *)StackPeek(oprtr) == '(')
	{
		free(StackPeek(oprtr));
		StackPop(oprtr);
	}
	else if (*(char *)StackPeek(oprtr) == DUMMY_OPRTR)
	{
		status = SYNTAX_ERROR;
	}
	++(*current_char);

	return status;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~oper functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static calc_status_t Adding(double first_oprnd, double second_oprnd, double *result)
{
	*result = first_oprnd + second_oprnd;

	return SUCCESS;
}

static calc_status_t Subtract(double first_oprnd, double second_oprnd, double *result)
{
	*result = first_oprnd - second_oprnd;

	return SUCCESS;
}

static calc_status_t Multi(double first_oprnd, double second_oprnd, double *result)
{
	*result = first_oprnd * second_oprnd;

	return SUCCESS;
}

static calc_status_t Divide(double first_oprnd, double second_oprnd, double *result)
{
	if (0 == second_oprnd)
	{
		*result = 0;
		return MATH_ERROR;
	}

	*result = first_oprnd / second_oprnd;

	return SUCCESS;
}

static calc_status_t Power(double first_oprnd, double second_oprnd, double *result)
{
/*	*result = pow(first_oprnd, second_oprnd);
*/	size_t  i;

	*result = 1;

	if (second_oprnd < 0)
	{
		second_oprnd = -second_oprnd;
		first_oprnd = 1 / first_oprnd;
	}

	for (i = 0; i < second_oprnd; i++)
		*result *= first_oprnd;

	return SUCCESS;
}
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~main functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static calc_status_t CalcInit(void)
{
	InitToDefault();
	InitTransitionTable();
	InitOperationTable();

	return SUCCESS;
}

static calc_status_t RunCalc(stack_t *oprtr, stack_t *oprnd, char *input, double *result)
{
	calc_status_t status = SUCCESS;
	state_t state = WAITING_FOR_OPERAND;
	*result = 0;

	while (state != ERROR && status == SUCCESS)
	{ /* '\0' (end) is also --> swtich state to ERROR */
		int input_cpy = *input;
		status = transition_table[(int)*input][state].handle_func(oprtr, oprnd, &input);
		state = transition_table[input_cpy][state].state;
	}

	while (status == SUCCESS && 1 < StackSize(oprnd) && 1 < StackSize(oprtr))
	{
		status = ExecutCalculate(oprtr, oprnd);
	}

	if (!StackIsEmpty(oprnd))
	{
		*result = *(double *)StackPeek(oprnd);
		free(StackPeek(oprnd));
		StackPop(oprnd);
	}

	FreeStacks(oprtr, oprnd);

	return status;
}
