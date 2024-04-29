Sender Program (sender.c):

c

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t receiver_pid;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]);
        exit(1);
    }

    receiver_pid = atoi(argv[1]);

    // Send SIGUSR1 signal to the specified process
    if (kill(receiver_pid, SIGUSR1) == -1) {
        perror("kill");
        exit(1);
    }

    return 0;
}

Receiver Program (receiver.c):

c

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigusr1_handler(int signum) {
    printf("Received SIGUSR1 signal\n");
}

int main() {
    // Register the signal handler for SIGUSR1
    if (signal(SIGUSR1, sigusr1_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    printf("Waiting for SIGUSR1 signal...\n");

    // Keep the program running to receive the signal
    while(1) {
        sleep(1);
    }

    return 0;
}

Compile both programs separately:

sh

gcc sender.c -o sender
gcc receiver.c -o receiver

Run the receiver program first to get its PID:

sh

./receiver

Then, run the sender program with the PID of the receiver as an argument:

sh

./sender <receiver_pid>

The sender program sends a SIGUSR1 signal to the receiver process using the kill system call. The receiver program registers a signal handler for SIGUSR1 and waits to receive the signal. When the signal is received, the handler function is executed, and a message is printed.