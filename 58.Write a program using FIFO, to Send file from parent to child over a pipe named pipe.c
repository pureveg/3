#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024
#define FIFO_PATH "/tmp/myfifo"

int main() {
    int fd;
    pid_t pid;
    char buffer[BUFFER_SIZE];
    FILE *file;
    ssize_t bytes_read;

    if (mkfifo(FIFO_PATH, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {  

        fd = open(FIFO_PATH, O_WRONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        file = fopen("input.txt", "r");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            write(fd, buffer, bytes_read);
        }

        fclose(file);
        close(fd);
    } else { 

        fd = open(FIFO_PATH, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        file = fopen("output.txt", "w");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
            fwrite(buffer, 1, bytes_read, file);
        }

        fclose(file);
        close(fd);
    }

    unlink(FIFO_PATH);

    return 0;
}

