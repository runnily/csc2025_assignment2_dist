# csc2025_assignment2_dist
CSC2025 Assignment 2 - Implementing Minix system calls

Due: 15:00 on Friday 13 December 2019

Maximum mark: 10

This assignment is worth 10% of the overall module mark, 50% of the coursework component.

Contents

Introduction
Aim
Learning/skills outcomes
What you are given
What you have to do 
5.1 Completing the implementation of system calls in fslog.c 
5.2 Completing the implementation of user-level library functions in fsloglib.c 
5.3 Logging filesystem operations 
5.4 How to work - compiling and testing work
Breakdown of marks
Deadline for submission and what to submit
1. Introduction

In this assignment you are given a partially complete system for in-memory logging of filesystem operations. It is your task to:

complete the implementation of the system calls that control which filesystem operations are logged, that obtain logging meta-information and the filesystem log itself, and that log filesystem operation information
complete the implementation of user-level library functions corresponding to the system calls
complete the logging of the success or failure of filesystem operations
The filesystem operations to log are: open (including create), read, write, close and unlink. Note, logging of open and create operations is done for you.

Important notes

The coursework specification includes:
this document
the source code provided and comments in C files and function specifications in header files
a suite of tests for both system calls and library functions
apps for additional example usage of the libraries
You are expected to familiarise yourself with this material.
There are references to the "user" in the materials provided. This means a programmer (possibly yourself) who uses a library function or system call in their program (as opposed to an end user of an appliation).
You are completing the implementation of libraries not an application program. The example apps and tests are the applications that use those libraries. There is no need to write any other application programs.
Library functions do not produce print out. There should not be any printf or perror or other such statements in the implementations of system calls or library functions that you submit.
2. Aim

The aim of this assignment is for you to gain an understanding of how system calls are implemented in Minix and to access and use operating system data structures. To this end, you will add system calls to the Minix Filesystem Server (VFS) and implement user-level library functions that invoke the system calls.

3. Learning/skills outcomes

C programming skills, including programming to an interface and programming to test
Operating systems programming
Code comprehension skills - understanding, analysing and modifying code provided by others
Formulate problems and identify suitable approaches to solving them
Cognitive/intellectual skills and self management (see graduate skills framework)
4. What you are given

You are given initial source code for your solution in the zip archive csc2025-assignment2-dist.zip. It contains the following directories and files:

    csc2025-assignment2-dist/
        include/               
            minix/      
                callnr.h        - the definition of Minix system call numbers
                                  provided for you
            unistd.h            - includes definition of NR_FSLOGREC, 
                                  FSOP_* constants, struct fsloginf and 
                                  struct fslogrec
        lib/
            fsloglib.c          - implementation of startfslog, 
                                  and initial versions of initfslog, stopfslog,
                                  getfsloginf and getfslog user-level
                                  library functions
            fsloglib.h          - definition/specification of user-level 
                                  library functions
        revert/                 - directory of Minix source code used by 
                                  the revert script
        revert.sh               - a shell script to revert Minix source code to 
                                  its original state
        servers/
            vfs/
                fslog.c         - implementations of do_startfslog,         
                                  logfserr, logfserr_nopath and logfsop_nopath,
                                  and initial versions of do_stopfslog,
                                  do_getfsloginf, do_getfslog and logfsop
                fslog.h         - definition/specification of logging functions
                link.c          - implementation of Minix unlink and related
                                  system calls
                Makefile        - Minix compilation script for vfs server
                open.c          - implemenation of Minix open and close and 
                                  related system calls
                proto.h         - definition of Minix vfs system calls
                read.c          - implementation of Minix read and write and 
                                  related system calls
                table.c         - table mapping Minix call numbers to vfs server 
                                  system calls   
                                  
        test/                   - test code
            fsloglib/           - library function test code        
                getfslog.c      - application to get and print the filesystem
                                  log using the getfslog library function
                getfsloginf.c   - application to get and print the filesystem
                                  log meta-information using the getfsloginf
                                  library function
                initfslog.c     - application to initialise the filesystem log
                                  using the initfslog library function
                Makefile        - compilation script for library function tests
                                  and apps
                startfslog.c    - application to start filesystem logging
                                  using the startfslog library function
                stopfslog.c     - application to stop filesystem logging
                                  using the stopfslog library function
                test_fsloglib.c - test of library functions
            Makefile            - compilation script to make both library 
                                  function and system call tests
            syscalls/           - system call test code    
                do_getfslog.c   - application to get and print the filesystem
                                  log using the do_getfslog system call
                do_getfsloginf.c - application to get and print the filesystem
                                  log meta-information using the do_getfsloginf
                                  system call
                do_startfslog.c - application to start filesystem logging 
                                  using the do_startfslog system call
                do_stopfslog.c  - application to stop filesystem logging using
                                  the do_stopsfslog system call
                Makefile        - compilation script for system call tests and 
                                  apps
                test_syscalls.c - test of system calls
            test_output.txt     - example output from successful test runs of 
                                  either test_fsloglib or test_syscalls
            util/
                fslog_testutil.c - test utility functions
                fslog_testutil.h - test utility definitions

            update.sh           - a shell script to update Minix source code 
                                  with the system call code for the assignment
                                  prior to re-compilation of the Minix boot 
                                  image
The above source code is the starting point for your solution and also forms part of the coursework specification, particularly the function specifications and comments in fslog.h, fslog.c, fsloglib.h and fsloglib.c. The files you edit are highlighted. That is, you modify fslog.c, fsloglib.c, link.c and read.c. Do not modify any other files.

Modifications to Minix source code in the files listed above are surrounded by the following comments:

/* CSC2025 mod start */
...
...
/* CSC2025 mod end */
You must surround modifications you make to link.c and read.c with the same comments.

5. What you have to do

You will modify functions in fslog.c, fsloglib.c, link.c and read.c. These modifications must be made according to this specification and according to comments in fslog.h, fslog.c, fsloglib.h and fsloglib.c.

The source files fslog.c and fsloglib.c include TODO comments to indicate which parts you are expected to change.

Do not modify any other files or functions than those specified.

The order in which you do things is up to you. The tests provided will not run successfully unless you have completed the system calls in part 5.1. However, you can implement and compile the library functions in part 5.2 without doing the systems calls in Part 5.1. The logging of open (and create) and close system calls is done for you. This means you can implement and test the code in Parts 5.1 and 5.2 without completing Part 5.3.

Before you attempt any of this assignment you should do the following two previously announced system call exercises to gain an understanding of how system calls are implemented in Minix:

Minix system call exercise 1
Minix system call exercise 2
5.1 Completing the implementation of system calls in fslog.c (4 marks)

In this part you must complete the implementation of the following system calls:

    do_stopfslog 
    do_getfsloginf
    do_getfslog
and the following logging function:

    logfsop
in servers/vfs/fslog.c according to their specifications and other comments in fslog.h and fslog.c.

Modifications to the system call table, prototype definitions and call numbers have been done for you. Therefore you do not have to modify files such as table.c, proto.h or callnr.h.

The do_startfslog system call, and the logfserr, logfserr_nopath and logfsop_nopath logging functions have been done for you. Do not modify these functions.

When completing the implementation of the system calls you should pay attention to the information about NR_FSLOGREC, FSOP_* constants, struct fsloginf and struct fslogrec that are defined in unistd.h. You can also see usage of these constants and structs (and the array of fslogrec structs) in the logfsop function that is in fslog.c. struct fsloginf is also used in the do_startfslog system call.

do_stopfslog requires that you update fields of the fsloginf struct that is declared for you in fslog.c (see line 26). For do_getfsloginf, you have to copy the fsloginf struct. For do_getfslog, you have to copy both the fsloginf struct and the array of fslogrec structs (called fslog), which is also declared for you in fslog.c (see line 31).

Copying between Minix processes is explained in the following note:

http://homepages.cs.ncl.ac.uk/nick.cook/csc2025/minix/minix-copy.html
and an example of copying between processes is part of Minix system call exercise 2.

To complete the logfsop function you have to access the filesystem process table entry of the current process. This is declared as the global variable fp in /usr/src/servers/vfs/glo.h. The variable fp is a pointer to an fproc struct which is defined in /usr/src/servers/vfs/fproc.h. You need to access the process id and and process name fields of the struct.

5.2 Completing the implementation of user-level library functions in fsloglib.c (3 marks)

In this part you complete the following four library functions in fsloglib.c:

    /* user level library function to initialise the filesystem log */
    void initfslog(void);

    /* user level library function for do_stopfslog system call */
    int stopfslog(unsigned short ops2stoplog);
    
    /* user level library function for do_getfsloginf system call */
    int getfsloginf(struct fsloginf *fsloginf);
    
    /* user level library function for do_getfslog system call */
    int getfslog(struct fsloginf *fsloginf, struct fslogrec fslog[]);
according to their specification in fsloglib.h.

These library functions serve a similar purpose to the printmsg and getmnpaths library functions in vfsexlib.c in the Minix system call exercises.

The system call numbers you use are:

    STOPFSLOG       // for do_stopfslog
    GETFSLOGINF     // for do_getfsloginf
    GETFSLOG        // for do_getfslog
and the process number of the filesystem server that will handle each call is VFS_PROC_NR.

For the functional parts of stopfslog, getfsloginf and getfslog library functions, look at relevant code in the test_syscalls.c and/or in do_startfslog.c, do_stopfslog.c, do_getfsloginf.c and do_getfslog.c in the csc2025-assignment2-dist/test/syscalls directory. Also, look at the implementation of startfslog that is provided for you.

For the non-functional parts, you should apply the fail early principle by checking parameters and not allowing erroneous input to propagate down the system. That is, set the errno and return with the appropriate error value before invoking a computationally expensive system call and potentially propagating errors to the operating system level. Hint: look at the implementation of startfslog.

initfslog is an example of a user-level library function that does not have a corresponding system call and is instead implemented by calling a combination of two other library functions. Hint: look in test_syscalls.c to find out which combination of system calls, and therefore library functions, can be used to initialise the filesystem log.

5.3 Logging filesystem operations (3 marks)

In this part you will log the success or failure of the following filesystem operations:

unlink in servers/vfs/link.c
read and write in servers/vfs/read.c
You do this by using the following logging functions:

void logfserr(int opcode, int result, char *path);
void logfserr_nopath(int opcode, int result);
void logfsop(int opcode, int result, char *path, int fd_nr, mode_t omode, 
    off_t size);
void logfsop_nopath(int opcode, int result, int fd_nr, mode_t omode,
    off_t size);
in appropriate places in the relevant operation source code in link.c and read.c (i.e. at appropriate places before the relevant operation returns).

The logging functions are provided for you in fslog.c and documented in fslog.h. Note: you complete the implementation of logfsop in Part 5.2 but the version provided will still log some of the information required and will still work if used in the filesystem code.

Logging of open (and create) and close operations has been done for you in open.c. You can look at the modifications in open.c to work out how to log the read, write and unlink operations. In the case of read and write, you will have to work out where and how to distinguish between a read operation and a write operation because they are handled by the same internal function.

You will have to #include "fslog.h" in link.c and read.c to use the logging functions.

For full marks for this part you must log successful operations and errors.

As shown in open.c, any modifications you make to link.c or read.c must be surrounded by the following modification comments:

/* CSC2025 mod start */
    // logging statements go here
/* CSC2025 mod end */
If you miss out these comments then markers will miss your modifications and you will not get any credit for this part.

To log successful filesystem operations, you need to access the following information (when available in the operation code):

The file descriptor number (fd_nr), which is usually available either as a parameter to a filesystem operation or as a field of a job_m_in message variable or as a field of scratch(fp).file.
A vnode struct that has fields for file open mode and size. The vnode struct is defined in /usr/src/servers/vfs/vnode.h. The vnode is often obtained as a field of a filp struct that represents a file.
5.4 How to work - compiling and testing work

As in the system call exercises, you modify files in your csc2025-assignment2-dist directory and use the update.sh script to copy changes to the corresponding Minix directories in /usr/src. You can use revert.sh to revert the /usr/src directory tree to its original state and undo any changes you have made.

That is, to compile changes made in Parts 5.1 and 5.3 and include them in the OS boot image, complete the following steps:

In csc2025-assignment2-dist run the update.sh script: 
    # ./update.sh 
to copy your updates to the system /usr/src directory tree
In /usr/src/releasetools compile and install services: 
    # make services 
    # make install
shutdown Minix and restart it to run the new version of the OS.
Once Minix has restarted you can test your solution (see below). You can use Minix boot menu options to select the boot image you use to start Minix.

Note: if there have been no changes to the Minix system call code, you do not have to run update.sh and recompile the Minix boot image to test the user-level library functions in fsloglib.c (Part 5.2).

Testing system calls (part 5.1)

The csc2025-assignment2-dist/test/syscalls directory contains the following files:

    do_getfslog.c       - application to get and print the filesystem
                          log using the do_getfslog system call
    do_getfsloginf.c    - application to get and print the filesystem
                          log meta-information using the do_getfsloging
                          system call
    do_startfslog.c     - application to start filesystem logging using the
                          do_startfslog system call
    do_stopfslog.c      - application to stop filesystem logging using the
                          do_stopsfslog system call
    Makefile            - compilation script for tests and apps
    test_syscalls.c     - test of system calls
You can compile the above programs either by typing:

    # make clean
    # make 
in csc2025-assignment2-dist/test/syscalls to compile the system call test program (test_syscalls) and the system call applications (do_startfslog, do_stopfslog, do_getfsloginf and do_getfslog). Or by typing:

    # make 
in csc2025-assignment2-dist/test to compile both system call and library function tests and applications.

If the compilation is successful, in csc2025-assignment2-dist/test/syscalls, type:

    # ./test_syscalls
or:

    # ./syscalls/test_syscalls
in csc2025-assignment2-dist/test

to run the system call tests. You can then compare the output with the example output in test/test_output.txt. You are aiming for a success message after each test. The exact log listing at the end will be different to test_output.txt and will depend which operations you select to log. If you have completed Part 5.3 and select to log all operations (input 127, which is FSOP_ALL), the log listing should have 200 entries and end with entries for unlinking/deleting files.

You can use the other applications (do_startfslog, do_stopfslog, do_getfsloginf and do_getfslog) to run the system calls separately to control logging, get and print logging meta-information, and get and print the filesystem log.

Testing user-level library functions (part 5.2)

The csc2025-assignment2-dist/test/fsloglib directory contains the following files:

    getfslog.c          - application to get and print the filesystem log
                          using the getfslog library function
    getfsloginf.c       - application to get and print the filesystem log
                          meta-information using the getfslog library function
    initfslog.c         - application to initialise the filesystem log
    Makefile            - compilation script for tests and apps
    startfslog.c        - application to start filesystem logging using the
                          startfslog library function
    stopfslog.c         - application to stop filesystem logging using the
                          stopfslog library function
    test_fsloglib.c     - test of library functions
In the test/fsloglib directory, type:

    # make clean
    # make 
or:

    # make
in the test directory to compile the user-level library function test program (test_fsloglib) and the library function applications (initfslog, startfslog, stopfslog, getfsloginf and getfslog).

If the compilation is successful, in the lib/test directory, type:

    # ./test_fsloglib
or:

    # ./fsloglib/test_fsloglib
in the test directory to run the library function tests. You can then compare the output with the example output in test_output.txt. You are aiming for a success message after each test. The exact log listing at the end will be different to test_output.txt and will depend which operations you select to log. If you have completed Part 5.3 and select to log all operations (input 127, which is FSOP_ALL), the log listing should have 200 entries and end with entries for unlinking/deleting files.

You can use the other applications (initfslog, startfslog, stopfslog, getfsloginf and getfslog) to run the library functions separately to control logging, get and print logging meta-information, and get and print the filesystem log.

6. Breakdown of marks

The indicative breakdown of marks for each part of the assignment is as follows:

system calls and logfsop function in fslog.c - 4 marks
library functions in fsloglib.c - 3 marks
logging in link.c and read.c - 3 marks
Your work will be marked for both specified functional and non-functional aspects (not overcomplicating solutions, programming defensively with respect to parameters to functions you implement, failing early etc.)

7. Deadline for submission and what to submit

Your coursework must be submitted to the NESS system by 15:00 on Friday 13 December 2019. The deadline is rigorously imposed by NESS. Work that is a few seconds beyond the submission deadline will be flagged as late.

You must submit the following four files:

fslog.c
fsloglib.c
link.c
read.c
Submit a tgz or zip archive of a directory called csc2025-assignment2 that contains the four files. That is, the archive should have the following contents:

    csc2025-assignment2/
        fslog.c
        fslolib.c
        link.c
        read.c
Do not submit any other files. Anything other than the four files listed above will be ignored.

Each file should start with the following comment:

/*
 * Replace the following string of 0s with your student number
 * 000000000
 */
where, as instructed, you replace 000000000 with your student number.

