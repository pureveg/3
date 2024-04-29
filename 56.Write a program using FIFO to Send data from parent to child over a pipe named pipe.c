#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 25
#define FIFO_PATH "/tmp/myfifo"

int main() {
    int fd;
    pid_t pid;
    char buffer[BUFFER_SIZE];
    const char *message = "Hello child, this is your parent!";

    // Create the FIFO (named pipe)
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {  // Parent process
        // Open the FIFO for writing
        fd = open(FIFO_PATH, O_WRONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        // Write message to the FIFO
        write(fd, message, BUFFER_SIZE);
        close(fd);
    } else { // Child process
        // Open the FIFO for reading
        fd = open(FIFO_PATH, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        // Read message from the FIFO
        read(fd, buffer, BUFFER_SIZE);
        printf("Message from parent: %s\n", buffer);
        close(fd);
    }

    // Remove the FIFO
    unlink(FIFO_PATH);

    return 0;
}




//Execution cmd
//gcc your_program_name.c -o your_program_name
//./your_program_name
