#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];
    FILE *file;
    ssize_t bytes_read;

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

        // Open the file for reading
        file = fopen("input.txt", "r");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        // Read from the file and write to the pipe
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            write(pipefd[1], buffer, bytes_read);
        }

        // Close the write end of the pipe in the parent
        close(pipefd[1]);
        fclose(file);
    } else { // Child process
        close(pipefd[1]); // Close the write end of the pipe in the child

        // Open a new file for writing
        file = fopen("output.txt", "w");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        // Read from the pipe and write to the file
        while ((bytes_read = read(pipefd[0], buffer, BUFFER_SIZE)) > 0) {
            fwrite(buffer, 1, bytes_read, file);
        }

        // Close the read end of the pipe in the child
        close(pipefd[0]);
        fclose(file);
    }

    return 0;
}





//Execution cmd:
//gcc your_program_name.c -o your_program_name
//./your_program_name
