#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 10000; // Longitud de la serie deseada

    int serie[n];
    int local_size = n / size;
    int local_serie[local_size];

    // Calcular la serie en orden secuencial
    for (int i = rank * local_size; i < (rank + 1) * local_size; i++) {
        if (i % 2 == 0) {
            local_serie[i - rank * local_size] = (i / 2 + 1) * (i / 2 + 1) + 1;
        } else {
            local_serie[i - rank * local_size] = (i / 2 + 1) * 2;
        }
    }

    MPI_Gather(local_serie, local_size, MPI_INT, serie, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            printf("%d, ", serie[i]);
        }
        printf("\n");
    }

    MPI_Finalize();

    return 0;
}
