#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int procesador, nprocesadores;
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocesadores);

    char frase[] = "tres tristes tigres trigaban trigo por culpa del bolivar";
    char *token;
    int indice = 0;

    char parte[200]; // Parte actual para cada procesador
    memset(parte, 0, sizeof(parte)); // Inicializar la parte a una cadena vacía

    token = strtok(frase, " ");
    while (token != NULL) {
        if (indice % 2 == procesador) {
            strcat(parte, token);
            strcat(parte, " ");
        }
        token = strtok(NULL, " ");
        indice++;
    }

    // El proceso 0 imprime su parte dividida
    if (procesador == 0) {
        printf("Palabras pares: %s\n", parte);
    }

    // El proceso 1 imprime su parte dividida
    if (procesador == 1) {
        printf("Palabras impares: %s\n", parte);
    }

    MPI_Finalize();
    return 0;
}
