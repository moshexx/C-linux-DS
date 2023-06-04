/******************************************************************************/
/*		Descriptions - PThread_SAFE_UID API Functions v1					  */
/*		Date: 03.01.2021					    	                          */
/*		Group: OL96						    								  */
/******************************************************************************/

#ifndef __PThread_SAFE_UID__
#define __PThread_SAFE_UID__

#include <sys/types.h>
#include <pthread.h>
#include <time.h>

typedef struct uid
{
    time_t time_stamp;
    pid_t pid;
    pthread_t pthread_id; /*pthread_self()*/
    size_t counter; /* atomic */
} ilrd_pthread_uid_t;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*
* Description: Creates a PThread_SAFE_UID
* Return value: a newly created struct UID (ilrd_uid_t)
* Errors: Returns a "bad" uid if one of the fields failed
* Undefined behavior: none.
*
* Complexity: O(1)
*/
ilrd_pthread_uid_t PThreadUIDCreate(void);

/*
* Description: checks if one and other are identical
* Return value: 1(TRUE) if they are, 0(FALSE) else
* Errors: none.
* Undefined behavior: none.
*
* Complexity: O(1)
*/
int PThreadUIDIsSame(ilrd_pthread_uid_t one, ilrd_pthread_uid_t other);

/*
* Description: creates an instance of bad UID for comparison
* Return value: a bad UID
* Errors: none.
* Undefined behavior: none.
*
* Complexity: O(1)
*/
ilrd_pthread_uid_t PThreadUIDGetBadUID(void);

#endif   /*__PThread_SAFE_UID__*/
