#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    key_t key;
    int shmid;
    char *shmaddr;
    char input_choice;
    int i;

    // Generate a unique key
    key = ftok("shm_ipc", 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory segment
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Enter 'A' to 'Z' or '1' to '100': ");
    scanf(" %c", &input_choice);

    if (input_choice >= 'A' && input_choice <= 'Z') {
        for (i = 0; i < 26; i++) {
            shmaddr[i] = 'A' + i;
        }
    } else if (input_choice >= '1' && input_choice <= '9') {
        for (i = 0; i < 10; i++) {
            shmaddr[i] = '0' + i;
        }
    }

    // Detach shared memory segment
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Child process
    if (fork() == 0) {
        // Attach shared memory segment
        shmaddr = shmat(shmid, NULL, 0);
        if (shmaddr == (char *)-1) {
            perror("shmat");
            exit(1);
        }

        // Print the shared memory content
        printf("Received: ");
        for (i = 0; i < SHM_SIZE; i++) {
            if (shmaddr[i] != '\0') {
                printf("%c", shmaddr[i]);
            }
        }
        printf("\n");

        // Detach shared memory segment
        if (shmdt(shmaddr) == -1) {
            perror("shmdt");
            exit(1);
        }

        // Remove shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }

        exit(0);
    }

    wait(NULL);

    return 0;
}
