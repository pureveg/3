#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = vfork();

    if (pid == -1) {
        perror("vfork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        execlp("notepad", "notepad", NULL);  // Use the appropriate command for your platform
        perror("execlp");
        _exit(1); // Ensure child doesn't execute any code after this
    } else {
        // Parent process
        wait(NULL); // Wait for the child to finish
        printf("Child process has finished.\n");
    }

    return 0;
}

Replace "notepad" with the appropriate command for your operating system ("gedit" for Linux, "TextEdit" for macOS, etc.).