#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    struct flock lock;

    // Open the file for reading and writing
    fd = open("example.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Initialize the lock structure
    lock.l_type = F_WRLCK;  // Exclusive write lock
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;  // Lock the entire file

    // Attempt to acquire the lock
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }

    printf("File locked successfully.\n");

    // Do some work while the file is locked
    printf("Press Enter to release the lock...\n");
    getchar();

    // Release the lock
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }

    printf("File lock released.\n");

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}







//Execution cmd:
//gcc your_program_name.c -o your_program_name
//./your_program_name





