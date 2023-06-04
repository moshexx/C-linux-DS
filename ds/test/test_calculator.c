/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_calculator.c
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    #include <stdio.h> /*printf */
    #include <stdlib.h> /* malloc, free */

    #include "calculator.h"

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

    enum matching
    {
    	NO,
    	YES
    };
    	/*~~~~~~~~~~~~~~~~~~~~~~static func declarations~~~~~~~~~~~~~~~~~~~~~~~~*/
    static int TestBasicSuccess();
    static int TestAdvencedSuccess();
    static int TestBasicPower();
    static int TestBasicSyntaxError();
    static int TestBasicMathError();
    static int TestBasicParenthesis();
    static int TestParenthesisSyntaxError();
    /*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ main ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
    int main()
    {
        double result = 0;
        char *osnat = "(105 - 75) * 3";
        Calculator(osnat, &result);
        printf("result = %f\n", result);

        TestBasicSuccess();
        TestAdvencedSuccess();
        TestBasicPower();
        TestBasicSyntaxError();
        TestBasicMathError();
        TestBasicParenthesis();
        TestParenthesisSyntaxError();

    	return 0;
    }

    /*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
    	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~static functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    static int TestBasicSuccess()
    {
        char *str_arr[] = {"1+1", "1 + 1", "2-1", "1+4-3", "2*2", "10/5", "1+3*4",
                                                                    "10*2/1/10"};
        double num_arr[] = {2, 2, 1, 2, 4, 2, 13, 2};
        double result = 0;
        size_t i = 0;
        size_t len = sizeof(num_arr) / sizeof(num_arr[0]);

        YELLOW;
        printf("---Test Basic Success---\n");
        RESET;
        for (i = 0; i < len; ++i)
        {
            RUN_TEST(SUCCESS == Calculator(str_arr[i], &result), str_arr[i]);
            RUN_TEST(num_arr[i] == result,"result");
            printf("--------------------\n");
        }

        return SUCCESS;
    }

    static int TestAdvencedSuccess()
    {

        char *str_arr[] = {"1.2+1", "1.1 + 1.1", "3-1.7", "1+4.5-3", "2*1.5", "12/5", "1+3.3*4",
                                                                    "101*2/1/10"};
        double num_arr[] = {2.2, 2.2, 1.30, 2.5, 3, 2.4, 14.2, 20.2};
        double result = 0;
        size_t i = 0;
        size_t len = sizeof(num_arr) / sizeof(num_arr[0]);

        YELLOW;
        printf("---Test Advenced Success---\n");
        RESET;
        for (i = 0; i < len; ++i)
        {
            RUN_TEST(SUCCESS == Calculator(str_arr[i], &result), str_arr[i]);
            RUN_TEST(num_arr[i] == result,"result");
            printf("result = %.2f\n", result);
            printf("--------------------\n");
        }

        return SUCCESS;

    }

    static int TestBasicPower()
    {
        char *str_arr[] = {"1^1", "1 ^ 1", "2^1", "1+4^3", "2^0", "10^5", "2^3*4",
                                                                    "10*2/1^10"};
        double num_arr[] = {1, 1, 2, 65, 1, 100000, 32, 20};
        double result = 0;
        size_t i = 0;
        size_t len = sizeof(num_arr) / sizeof(num_arr[0]);

        YELLOW;
        printf("---Test Basic Power---\n");
        RESET;
        for (i = 0; i < len; ++i)
        {
            RUN_TEST(SUCCESS == Calculator(str_arr[i], &result), str_arr[i]);
            RUN_TEST(num_arr[i] == result,"result");
            printf("--------------------\n");
        }

        return SUCCESS;
    }


    static int TestBasicSyntaxError()
    {
        char *str_arr[] = {"*1+1", "/1 + 1", "2**1", "1+*3", "2*2*", "a+10/5", "1 1+4"};
        double num_arr[] = {2, 2, 1, 2, 4, 2, 13};
        double result = 0;
        size_t i = 0;
        size_t len = sizeof(num_arr) / sizeof(num_arr[0]);

        YELLOW;
        printf("---Test Basic SyntaxError---\n");
        RESET;
        for (i = 0; i < len; ++i)
        {
            RUN_TEST(SYNTAX_ERROR == Calculator(str_arr[i], &result), str_arr[i]);
            /*RUN_TEST(num_arr[i] == result,"result");*/
            printf("--------------------\n");
        }

        return SUCCESS;
    }

    static int TestBasicMathError()
    {
        char *str_arr[] = {"1/0", "2-1/0", "2/0+3"};
        double num_arr[] = {0, 0, 0};
        double result = 0;
        size_t i = 0;
        size_t len = sizeof(num_arr) / sizeof(num_arr[0]);

        YELLOW;
        printf("---Test Basic MathError---\n");
        RESET;
        for (i = 0; i < len; ++i)
        {
            RUN_TEST(MATH_ERROR == Calculator(str_arr[i], &result), str_arr[i]);
            printf("--------------------\n");
        }

        return SUCCESS;
    }

    static int TestBasicParenthesis()
    {
        char *str_arr[] = {"(1+1)", "(1) + 1", "(2 )-1", "(4-3)*3", "2 * (1 +2*2)", "10/(5+5)+2", "(2+2*4)/(2*5)",
                                                                    "(1+ 12/(3*4)) * (1+5)"};
        double num_arr[] = {2, 2, 1, 3, 10, 3, 1, 12};
        double result = 0;
        size_t i = 0;
        size_t len = sizeof(num_arr) / sizeof(num_arr[0]);

        YELLOW;
        printf("---Test Basic Parenthesis---\n");
        RESET;
        for (i = 0; i < len; ++i)
        {
            RUN_TEST(SUCCESS == Calculator(str_arr[i], &result), str_arr[i]);
            RUN_TEST(num_arr[i] == result,"result");
            printf("result = %f\n", result);
            printf("--------------------\n");
        }

        return SUCCESS;
    }

    static int TestParenthesisSyntaxError()
    {
        char *str_arr[] = {"(1 +1))", "((1 + 1)", "2)*1", "1+()", "2*(2*)"};
        double num_arr[] = {2, 2, 1, 2, 4};
        double result = 0;
        size_t i = 0;
        size_t len = sizeof(num_arr) / sizeof(num_arr[0]);

        YELLOW;
        printf("---Test Parenthesis Syntax Error---\n");
        RESET;
        for (i = 0; i < len; ++i)
        {
            RUN_TEST(SYNTAX_ERROR == Calculator(str_arr[i], &result), str_arr[i]);
            /*RUN_TEST(num_arr[i] == result,"result");*/
            printf("--------------------\n");
        }

        return SUCCESS;
    }
