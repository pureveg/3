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

        // Open the file for reading
        file = fopen("input.txt", "r");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        // Read from the file and write to the FIFO
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            write(fd, buffer, bytes_read);
        }

        // Close the file and FIFO
        fclose(file);
        close(fd);
    } else { // Child process
        // Open the FIFO for reading
        fd = open(FIFO_PATH, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Open a new file for writing
        file = fopen("output.txt", "w");
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        // Read from the FIFO and write to the file
        while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
            fwrite(buffer, 1, bytes_read, file);
        }

        // Close the file and FIFO
        fclose(file);
        close(fd);
    }

    // Remove the FIFO
    unlink(FIFO_PATH);

    return 0;
}






//Execution cmd:
//gcc your_program_name.c -o your_program_name
//./your_program_name
