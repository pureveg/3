#include <stdio.h>
#include <omp.h>

int main() {
    int total_threads;

    #pragma omp parallel
    {
        #pragma omp master
        {
            total_threads = omp_get_num_threads();
            printf("Total threads created: %d\n", total_threads);
        }

        // All threads print their thread numbers
        printf("Thread number: %d\n", omp_get_thread_num());
    }

    return 0;
}


//Exe command
//gcc -fopenmp your_program_name.c -o your_program_name
