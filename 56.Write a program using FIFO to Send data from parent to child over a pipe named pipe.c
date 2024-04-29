#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 40
#define FIFO_PATH "/tmp/myfifo"

int main() {
    int fd;
    pid_t pid;
    char buffer[BUFFER_SIZE];
    const char *message = "Hello child, this is your parent!";

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

        write(fd, message, BUFFER_SIZE);
        close(fd);
    } else { 

        fd = open(FIFO_PATH, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        read(fd, buffer, BUFFER_SIZE);
        printf("Message from parent: %s\n", buffer);
        close(fd);
    }

    unlink(FIFO_PATH);

    return 0;
}
