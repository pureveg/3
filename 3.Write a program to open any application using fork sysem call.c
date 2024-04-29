#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        execlp("notepad", "notepad", NULL);  // Use the appropriate command for your platform
        perror("execlp");
        exit(1);
    } else {
        // Parent process
        wait(NULL); // Wait for the child to finish
        printf("Child process has finished.\n");
    }

    return 0;
}


Replace "notepad" with the appropriate command for your operating system ("gedit" for Linux, "TextEdit" for macOS, etc.). This program creates a child process that opens the specified application, and the parent process waits for the child to finish executing.