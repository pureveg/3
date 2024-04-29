#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *print_even(void *arg) {
    int i = 0;
    while (1) {
        printf("Even: %d\n", i);
        i += 2;
        sleep(1);
    }
    return NULL;
}

void *print_odd(void *arg) {
    int i = 1;
    while (1) {
        printf("Odd: %d\n", i);
        i += 2;
        sleep(1);
    }
    return NULL;
}

int is_prime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void *print_prime(void *arg) {
    int i = 2;
    while (1) {
        if (is_prime(i)) {
            printf("Prime: %d\n", i);
        }
        i++;
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, print_even, NULL);
    pthread_create(&thread2, NULL, print_odd, NULL);
    pthread_create(&thread3, NULL, print_prime, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}
