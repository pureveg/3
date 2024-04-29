#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 25

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];
    const char *message = "Hello child, this is your parent!";

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {  // Parent process
        close(pipefd[0]); // Close the read end of the pipe in the parent
        write(pipefd[1], message, BUFFER_SIZE); // Write message to the pipe
        close(pipefd[1]); // Close the write end of the pipe in the parent
    } else { // Child process
        close(pipefd[1]); // Close the write end of the pipe in the child
        read(pipefd[0], buffer, BUFFER_SIZE); // Read message from the pipe
        printf("Message from parent: %s\n", buffer);
        close(pipefd[0]); // Close the read end of the pipe in the child
    }

    return 0;
}



//Execution cmd
//gcc your_program_name.c -o your_program_name
//./your_program_name
