#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process running\n");
        sleep(2); // Simulating some work
        printf("Child process done\n");
        exit(0);
    } else {
        // Parent process
        printf("Parent process waiting for child\n");
        wait(&status); // Wait for the child to terminate
        printf("Parent process done\n");
    }

    return 0;
}



In this program, the parent process creates a child process using fork. The child process prints a message, simulates some work with sleep, and then exits. Meanwhile, the parent process waits for the child to terminate using wait. When the child process finishes, the parent process resumes execution and prints a message.