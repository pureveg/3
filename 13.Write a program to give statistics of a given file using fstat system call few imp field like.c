#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    struct stat file_stat;

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (fstat(fd, &file_stat) == -1) {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("File statistics for: %s\n", filename);
    printf("File size: %ld bytes\n", file_stat.st_size);
    printf("File type: ");
    switch (file_stat.st_mode & S_IFMT) {
        case S_IFREG:
            printf("Regular file\n");
            break;
        case S_IFDIR:
            printf("Directory\n");
            break;
        case S_IFCHR:
            printf("Character device\n");
            break;
        case S_IFBLK:
            printf("Block device\n");
            break;
        case S_IFIFO:
            printf("FIFO/pipe\n");
            break;
        case S_IFLNK:
            printf("Symbolic link\n");
            break;
        case S_IFSOCK:
            printf("Socket\n");
            break;
        default:
            printf("Unknown file type\n");
            break;
    }

    printf("File access permissions: ");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    close(fd);
    return 0;
}



gcc -o file_stats file_stats.c
./file_stats <filename>

Eg: ./file_stats example.txt


