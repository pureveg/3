#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd;
    struct flock lock;

    fd = open("abc.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    fcntl(fd, F_SETFL, O_WRONLY | O_CREAT | O_TRUNC | O_SYNC);

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        if (errno == EACCES || errno == EAGAIN) {
            printf("Mandatory locks not supported or conditions not met. Advisory locks will be used.\n");
        } else {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("File locked successfully.\n");
    }

    printf("Press Enter to release the lock...\n");
    getchar();

    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    } else {
        printf("File lock released.\n");
    }

    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}






//Execution cmd:
//gcc your_program_name.c -o your_program_name
//./your_program_name





