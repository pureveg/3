The exec family of functions in C is used to execute a file (program) in the context of the calling process. There are several variations of the exec function, each with slightly different behaviors. Here's a program that demonstrates the use of some of these variations:


Copy code
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // Example executable file
    char *argv[] = {"/bin/ls", "-l", NULL};

    // Using execl
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl");
        exit(1);
    } else {
        wait(&status);
    }

    // Using execlp
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    } else {
        wait(&status);
    }

    // Using execv
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        execv("/bin/ls", argv);
        perror("execv");
        exit(1);
    } else {
        wait(&status);
    }

    // Using execvp
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        execvp("ls", argv);
        perror("execvp");
        exit(1);
    } else {
        wait(&status);
    }

    return 0;
}

In this program, we demonstrate four variations of the exec function: execl, execlp, execv, and execvp. Each variation takes different arguments:

execl: Takes the path to the executable and a list of arguments as separate arguments.
execlp: Takes the name of the executable (without the path) and a list of arguments.
execv: Takes the path to the executable and an array of arguments.
execvp: Takes the name of the executable (without the path) and an array of arguments.
In each case, the program attempts to execute the ls -l command to list the files in the current directory. The wait function is used to wait for the child process to finish before continuing.






