#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat fileStat;

    if (stat(argv[1], &fileStat) == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("File Type:                ");
    switch (fileStat.st_mode & S_IFMT) {
        case S_IFBLK:  printf("Block device\n");            break;
        case S_IFCHR:  printf("Character device\n");        break;
        case S_IFDIR:  printf("Directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("Symlink\n");                 break;
        case S_IFREG:  printf("Regular file\n");            break;
        case S_IFSOCK: printf("Socket\n");                  break;
        default:       printf("Unknown?\n");                break;
    }

    printf("File Size:                %lld bytes\n", (long long) fileStat.st_size);
    printf("Blocks Allocated:         %lld\n", (long long) fileStat.st_blocks);
    printf("Last Access Time:         %ld\n", (long) fileStat.st_atime);
    printf("Last Modification Time:   %ld\n", (long) fileStat.st_mtime);
    printf("Last Status Change Time:  %ld\n", (long) fileStat.st_ctime);

    printf("File Access Permissions:  %o\n", fileStat.st_mode & 0777);

    return EXIT_SUCCESS;
}
