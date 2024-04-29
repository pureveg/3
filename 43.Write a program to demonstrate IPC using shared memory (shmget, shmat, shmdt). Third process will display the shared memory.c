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
    int *shmaddr;
    int input_num, num_count;

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
    shmaddr = (int *)shmat(shmid, NULL, 0);
    if (shmaddr == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    // First process: Input numbers
    printf("Enter numbers (enter -1 to stop):\n");
    num_count = 0;
    do {
        scanf("%d", &input_num);
        if (input_num != -1) {
            shmaddr[num_count++] = input_num;
        }
    } while (input_num != -1);

    // Second process: Sort numbers
    for (int i = 0; i < num_count - 1; i++) {
        for (int j = i + 1; j < num_count; j++) {
            if (shmaddr[i] > shmaddr[j]) {
                int temp = shmaddr[i];
                shmaddr[i] = shmaddr[j];
                shmaddr[j] = temp;
            }
        }
    }

    // Third process: Display sorted numbers
    printf("Sorted numbers:\n");
    for (int i = 0; i < num_count; i++) {
        printf("%d ", shmaddr[i]);
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

    return 0;
}
