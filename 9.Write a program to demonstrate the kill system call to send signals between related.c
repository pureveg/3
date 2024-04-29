#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>




void sigusr1_handler(int signum) {
    printf("Child: Received SIGUSR1 signal\n");
}

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        if (signal(SIGUSR1, sigusr1_handler) == SIG_ERR) {
            perror("signal");
            exit(1);
        }

        printf("Child: Waiting for SIGUSR1 signal...\n");

        // Keep the child process running to receive the signal
        while (1) {
            sleep(1);
        }

    } else {
        // Parent process
        printf("Parent: Sending SIGUSR1 signal to child\n");

        // Wait for a moment before sending the signal
        sleep(2);

        // Send SIGUSR1 signal to the child process
        if (kill(pid, SIGUSR1) == -1) {
            perror("kill");
            exit(1);
        }

        // Wait for the child process to terminate
        wait(NULL);

        printf("Parent: Child process terminated\n");
    }

    return 0;
}
