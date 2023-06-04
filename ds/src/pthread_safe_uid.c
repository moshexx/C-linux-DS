/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: pthread_uid.c
*	author: Moshe Cohen
*	reviewer: None

--------------------------------------------------------------------------------
*******************************************************************************/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <assert.h> /* assert */
#include <unistd.h>  /* getpid */
#include <time.h>    /* time */
#include <pthread.h> /* pthread_self */

#include "pthread_safe_uid.h"
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

enum return_value{ FALSE, TRUE };
/*~~~~~~~~~~~~~~~~~~~~~~~~static functions signatures~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~API functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

ilrd_pthread_uid_t PThreadUIDCreate(void)
{
    ilrd_pthread_uid_t uid = { 0 };
    static size_t counter = 0;
    pid_t process_id = getpid();
    time_t time_stamp = time(NULL);
    if (uid.time_stamp == (time_t)-1)
    {
        return (PThreadUIDGetBadUID());
    }

    uid.counter = __sync_add_and_fetch(&counter,1); /* serial number */
    uid.pid = process_id;
    uid.time_stamp = time_stamp;
    uid.pthread_id = pthread_self(); /* returns the ID of the calling thread */


    return uid;
}

int PThreadUIDIsSame(ilrd_pthread_uid_t one, ilrd_pthread_uid_t other)
{
    /* FALSE / TRUE (0/1) */
    return (one.time_stamp == other.time_stamp
            && one.pid == other.pid
            && one.counter == other.counter
            && pthread_equal(one.pthread_id, other.pthread_id));
}

ilrd_pthread_uid_t PThreadUIDGetBadUID(void)
{
    ilrd_pthread_uid_t bad_uid = { 0 };

    bad_uid.time_stamp = -1;

    return bad_uid;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~static functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
