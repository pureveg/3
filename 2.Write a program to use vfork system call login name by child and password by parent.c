#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    char login[50], password[50];

    printf("Enter login name: ");
    fflush(stdout);

    pid = vfork(); // create a child process
    if (pid == 0) {
        // Child process reads login name
        scanf("%s", login);
        printf("Child process: Login name is %s\n", login);
        _exit(0); // terminate the child process
    } else if (pid > 0) {
        // Parent process reads password
        wait(NULL); // wait for the child process to finish
        printf("Enter password: ");
        fflush(stdout);
        scanf("%s", password);
        printf("Parent process: Password is %s\n", password);
    } else {
        perror("vfork");
        exit(EXIT_FAILURE);
    }

    return 0;
}


gcc -o vfork_example vfork_example.c
./vfork_example
