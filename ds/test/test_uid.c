/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_uid.c
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <stdio.h> /*printf */
#include <stdlib.h>
#include <sys/types.h> /**/
#include <unistd.h> /**/

#include "uid.h"

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

enum successful {SUCCEES, FAILURE};
enum matching {NO, YES};
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main()
{
    ilrd_uid_t uid3 = { 0 };
    ilrd_uid_t uid1 = UIDCreate();
    ilrd_uid_t uid2 = UIDCreate();
    ilrd_uid_t bad_guy = UIDGetBadUID();
    uid3 = UIDCreate();

    /*RUN_TEST(uid, "UIDCreate");*/
    printf("Test for UIDCreate\n");

    printf("pid1: %d\n", uid1.pid);
    printf("time_stamp1: %ld\n", uid1.time_stamp);
    printf("counter1: %ld\n", uid1.counter);

    printf("pid2: %d\n", uid2.pid);
    printf("time_stamp2: %ld\n", uid2.time_stamp);
    printf("counter2: %ld\n", uid2.counter);

    printf("pid3: %d\n", uid3.pid);
    printf("time_stamp3: %ld\n", uid3.time_stamp);
    printf("counter3: %ld\n", uid3.counter);

    printf("************************\n");

    printf("Test for UIDGetBadUID\n");
    printf("BadUID PID: %d\n", bad_guy.pid);
    printf("BadUID time_stamp: %ld\n", bad_guy.time_stamp);
    printf("BadUID counter: %ld\n", bad_guy.counter);

    printf("************************\n");

    RUN_TEST(NO == UIDIsSame(uid1, uid2), "UIDIsSame(not same)");
    RUN_TEST(NO == UIDIsSame(uid1, bad_guy), "UIDIsSame(not same)");
    RUN_TEST(YES == UIDIsSame(uid1, uid1), "UIDIsSame(same)");

	return 0;
}
