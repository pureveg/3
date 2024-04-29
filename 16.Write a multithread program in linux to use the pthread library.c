#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *print_even(void *arg) {
    for (int i = 0; i <= 10; i += 2) {
        printf("Even: %d\n", i);
        sleep(1);
    }
    return NULL;
}

void *print_odd(void *arg) {
    for (int i = 1; i <= 10; i += 2) {
        printf("Odd: %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, print_even, NULL);
    pthread_create(&thread2, NULL, print_odd, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}


gcc -o multithread multithread.c -pthread
./multithread