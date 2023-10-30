#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int procesador, nprocesadores;
    MPI_Comm_rank(MPI_COMM_WORLD, &procesador);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocesadores);

    char frase[] = "tres tristes tigres trigaban trigo por culpa del bolivar";
    char *token;
    int indice = 1;
    char parte[100] = "";

    // Calcula el tamaño de cada parte
    int tamano_frase = strlen(frase);
    int tamano_parte = tamano_frase / nprocesadores;
    int inicio = procesador * tamano_parte;
    int fin = inicio + tamano_parte - 1;

    // Encuentra la primera palabra de la parte asignada a este procesador
    token = strtok(frase + inicio, " ");
    // Si este procesador no comienza con una palabra, salta al comienzo de la próxima palabra
    if (indice != 1) {
        token = strtok(NULL, " ");
    }
    while (token != NULL && indice <= fin - inicio) {
        strcat(parte, token);
        strcat(parte, " ");  // Agrega un espacio entre palabras
        token = strtok(NULL, " ");  // Siguiente palabra
        indice++;
    }

    char parte_anterior[200]; // Almacena la parte del proceso anterior
    if (procesador != 0) {
        MPI_Recv(parte_anterior, 200, MPI_CHAR, procesador - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Concatena la parte generada por este proceso con la parte del proceso anterior
    strcat(parte_anterior, parte);

    // Envia la parte desde todos los procesadores excepto el último al siguiente proceso
    if (procesador != nprocesadores - 1) {
        MPI_Send(parte_anterior, strlen(parte_anterior) + 1, MPI_CHAR, (procesador + 1) % nprocesadores, 0, MPI_COMM_WORLD);
    }

    // Imprime la parte recolectada para procesadores pares e impares
    if (procesador % 2 == 0) {
        printf("Procesador impar %d: %s\n", procesador, parte_anterior);
    } else {
        printf("Procesador par %d: %s\n", procesador, parte_anterior);
    }

    MPI_Finalize();
    retu
