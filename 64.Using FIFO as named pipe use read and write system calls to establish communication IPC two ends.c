prog1.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/my_fifo"

int main() {
    int fifo_fd;

    // Create FIFO
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    printf("FIFO created successfully\n");

    // Open FIFO for writing
    fifo_fd = open(FIFO_NAME, O_WRONLY);
    if (fifo_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("FIFO opened for writing\n");

    // Write data to FIFO
    const char *message = "Hello from Writer";
    if (write(fifo_fd, message, sizeof(message)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    printf("Data written to FIFO\n");

    // Close FIFO
    close(fifo_fd);

    return 0;
}

prog2.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/my_fifo"

int main() {
    int fifo_fd;
    char buf[256];

    // Open FIFO for reading
    fifo_fd = open(FIFO_NAME, O_RDONLY);
    if (fifo_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("FIFO opened for reading\n");

    // Read data from FIFO
    ssize_t num_bytes = read(fifo_fd, buf, sizeof(buf));
    if (num_bytes == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Null-terminate the received data
    buf[num_bytes] = '\0';

    printf("Received message: %s\n", buf);

    // Close FIFO
    close(fifo_fd);

    return 0;
}
