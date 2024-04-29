#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

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

    if (pid > 0) {  // Parent process (reader)
        close(pipefd[0]); // Close the read end of the pipe in the parent

        FILE *file;
        if (argc > 1) {
            file = fopen(argv[1], "r");
            if (file == NULL) {
                perror("fopen");
                exit(EXIT_FAILURE);
            }
        } else {
            file = stdin;
        }

        // Read from the file or standard input and write to the pipe
        ssize_t bytes_read;
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            write(pipefd[1], buffer, bytes_read);
        }

        // Close the write end of the pipe in the parent
        close(pipefd[1]);
        
        if (file != stdin) {
            fclose(file);
        }
    } else { // Child process (converter)
        close(pipefd[1]); // Close the write end of the pipe in the child

        // Read from the pipe, convert uppercase to lowercase, and write to standard output
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, BUFFER_SIZE)) > 0) {
            for (int i = 0; i < bytes_read; i++) {
                buffer[i] = tolower(buffer[i]);
            }
            write(STDOUT_FILENO, buffer, bytes_read);
        }

        // Close the read end of the pipe in the child
        close(pipefd[0]);
    }

    return 0;
}







//Execution cmd:
//gcc your_program_name.c -o your_program_name
//./your_program_name input_file.txt
