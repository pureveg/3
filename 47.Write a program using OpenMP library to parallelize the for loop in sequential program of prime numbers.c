#include <stdio.h>
#include <omp.h>

int is_prime(int n) {
    if (n <= 1) return 0; // Not prime
    if (n <= 3) return 1; // 2 and 3 are prime

    // Check if n is divisible by 2 or 3
    if (n % 2 == 0 || n % 3 == 0) return 0;

    // Check for prime numbers starting from 5
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }

    return 1; // Prime
}

int main() {
    int start = 2; // Start of range
    int end = 100; // End of range

    printf("Prime numbers between %d and %d:\n", start, end);

    #pragma omp parallel for
    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            printf("%d\n", i);
        }
    }

    return 0;
}


//Execution Command:
//gcc -fopenmp your_program_name.c -o your_program_name
