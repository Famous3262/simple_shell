![gate of shell](https://user-images.githubusercontent.com/104713477/232478585-7f235962-bbf2-46cc-9424-4aa4a3546e41.jpeg)
C - SIMPLE SHELL:

The shell is a command line interface (CLI) program that takes commands from the keyboard and gives them to the operating system to perform.
A shell is a messanger between the user, the kernel and the machine.

BACKGROUND CONTEXT:
This is a team project on shell in C.
The objective of this project is to write a simple UNIX command interpreter that mimics the Bash shell.

REQUIREMENTS

General:
1. Allowed editors: vi, vim, emacs
2. All files are compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
3. All files ended with a new line
4. All codes used the Betty style.
5. The shell does not have any memory leak
6. No more than 5 functions per file
7. All header files are include guarded
8. System calls are used when needed

List of functions and system calls:
access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)
free (man 3 free)
getcwd (man 3 getcwd)
getline (man 3 getline)
getpid (man 2 getpid)
isatty (man 3 isatty)
kill (man 2 kill)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (__xstat) (man 2 stat)
lstat (__lxstat) (man 2 lstat)
fstat (__fxstat) (man 2 fstat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)

Compilation:
The shell is compiled in the following way:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

Auth:
Famous Adama
Mohammed Buhari Ozegya
