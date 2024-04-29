#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {

        close(pipe_fd[1]); 

        dup2(pipe_fd[0], STDIN_FILENO);

        execlp("cat", "cat", NULL);
        perror("execlp");
        return EXIT_FAILURE;
    } else {

        close(pipe_fd[0]); 

        char buffer[BUFFER_SIZE];
        size_t bytes_read;

        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            write(pipe_fd[1], buffer, bytes_read);
        }

        close(pipe_fd[1]);

        wait(NULL);
    }

    fclose(file);
    return EXIT_SUCCESS;
}

//create a file input.txt add data
//run as ./a.out input.txt
