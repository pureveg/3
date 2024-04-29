#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define FIFO_PATH "myfifo"

int main() {
    int fd;
    char message[] = "Hello, this is a message from the writer process!";
    char buffer[256];

    // Create the FIFO (named pipe)
    mkfifo(FIFO_PATH, 0666);

    // Open the FIFO for writing
    fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Write the message to the FIFO
    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Close the FIFO
    close(fd);

    printf("Writer process has written the message to the FIFO.\n");

    // Open the FIFO for reading
    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read the message from the FIFO
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Null-terminate the string
    buffer[bytes_read] = '\0';

    // Close the FIFO
    close(fd);

    printf("Reader process has read the message from the FIFO:\n%s\n", buffer);

    // Remove the FIFO (named pipe)
    unlink(FIFO_PATH);

    return 0;
}




//Execution cmd:
//gcc program_name.c -o program_name
//./program_name






