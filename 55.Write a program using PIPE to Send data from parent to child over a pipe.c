#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 40

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];
    const char *message = "Hello child, this is your parent!";


    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }


    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { 
        close(pipefd[0]); 
        write(pipefd[1], message, BUFFER_SIZE);
        close(pipefd[1]); 
    } else { 
        close(pipefd[1]); 
        read(pipefd[0], buffer, BUFFER_SIZE); // Read message from the pipe
        printf("Message from parent: %s\n", buffer);
        close(pipefd[0]); 
    }

    return 0;
}


