/*
 * Replace the following string of 0s with your student number
 * 180251870
 */
#include <lib.h>    // provides _syscall and message
#include <errno.h>
#include "fsloglib.h"

/*
 * TODO: implement initfslog
 * see fsloglib.h for specification of initfslog
 */
void initfslog(void) {
    stopfslog(FSOP_ALL);
    startfslog(FSOP_NONE);
    return;
}

/* startfslog: implemented, do NOT change */
int startfslog(unsigned short ops2log) {
    if (ops2log < FSOP_NONE || ops2log > FSOP_ALL) {
        errno = EINVAL;
        return -1;
    }
    
    message m;
    m.m1_i1 = (int) ops2log;

    return _syscall(VFS_PROC_NR, STARTFSLOG, &m);
}

/*
 * TODO: implement stopfslog
 * see fsloglib.h for specification of stopfslog
 */
int stopfslog(unsigned short ops2stoplog) {
    if (ops2stoplog < FSOP_NONE || ops2stoplog > FSOP_ALL) { //check within a valid range
        errno = EINVAL; //else error
        return -1;
    }
    message m;
    m.m1_i1 = (int) ops2stoplog; //get the ops value
    return _syscall(VFS_PROC_NR, STOPFSLOG, &m);
}

/*
 * TODO: implement getfsloginf
 * see fsloglib.h for specification of initfslog
 */
int getfsloginf(struct fsloginf *fsloginf) {
    if (fsloginf) {
        message m; //the message
    
        m.m1_p1 = (char *) fsloginf; //the string pointer

        return _syscall(VFS_PROC_NR, GETFSLOGINF, &m); //return what the system call got (or any error from vircopy)
    }
    errno = EINVAL;
    return -1;
}

/*
 * TODO: implement getfslog
 * see fsloglib.h for specification of getfslog
 */
int getfslog(struct fsloginf *fsloginf, struct fslogrec fslog[]) {
    if (fsloginf && fslog) { //ensure not null
        message m; //the message m
    
        m.m1_p1 = (char *) fsloginf; //the first string holds the struct
        m.m1_p2 = (char *) fslog; //the last string holds the record
    
        return _syscall(VFS_PROC_NR, GETFSLOG, &m); //returning the system call
       
    
    }
    errno = EINVAL;
    return -1;
}
