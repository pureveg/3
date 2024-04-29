#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

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

        ssize_t bytes_read;
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            write(pipefd[1], buffer, bytes_read);
        }

        close(pipefd[1]);

        if (file != stdin) {
            fclose(file);
        }
    } else { 
        close(pipefd[1]); 

        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, BUFFER_SIZE)) > 0) {
            for (int i = 0; i < bytes_read; i++) {
                buffer[i] = tolower(buffer[i]);
            }
            write(STDOUT_FILENO, buffer, bytes_read);
        }

        close(pipefd[0]);
    }

    return 0;
}

