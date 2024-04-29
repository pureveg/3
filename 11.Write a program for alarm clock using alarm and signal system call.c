#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int signum) {
    printf("Alarm triggered!\n");
    exit(0);
}

int main() {
    // Register the alarm signal handler
    if (signal(SIGALRM, alarm_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    // Set the alarm for 5 seconds
    alarm(5);

    printf("Waiting for alarm...\n");

    // Wait indefinitely
    while(1) {
        sleep(1);
    }

    return 0;
}
