/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: uid.c
*	author: Moshe Cohen
*	reviewer: Topaz

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <unistd.h>

#include "uid.h"
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
enum return_value{ FALSE, TRUE };
static int counter = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ilrd_uid_t UIDCreate(void)
{
    ilrd_uid_t uid = { 0 };
    pid_t process_id = getpid();
    time_t time_stamp = time(NULL);

    uid.counter = ++counter; /* serial number */
    uid.pid = process_id;
    uid.time_stamp = time_stamp;

    if (uid.time_stamp == (time_t) -1)
    {
        return (UIDGetBadUID());
    }

    return uid;
}

int UIDIsSame(ilrd_uid_t one, ilrd_uid_t other)
{
    if (one.time_stamp == other.time_stamp
            && one.pid == other.pid
            && one.counter == other.counter)
    {
        return TRUE;
    }

    return FALSE;
}

ilrd_uid_t UIDGetBadUID(void)
{
    ilrd_uid_t bad_uid = { 0 };

    bad_uid.time_stamp = -1;

    return bad_uid;
}
