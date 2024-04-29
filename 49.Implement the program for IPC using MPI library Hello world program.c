#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the rank (ID) of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Print "Hello world" message from each process
    printf("Hello world from process %d of %d\n", rank, size);

    // Finalize MPI
    MPI_Finalize();

    return 0;
}


//Exe cmd
//mpicc your_program_name.c -o your_program_name


//To run this program using MPI, you can use a command like
//mpiexec -n 4 ./your_program_name
