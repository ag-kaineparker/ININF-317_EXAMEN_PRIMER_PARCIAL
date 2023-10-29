#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    char frase[] = "tres tristes tigres trigaban trigo por culpa del bolivar";
    char primera_parte[100] = "";  // Inicializa la primera parte de la frase
    char segunda_parte[100] = "";  // Inicializa la segunda parte de la frase

    char *token;
    int indice = 1;

    // Encuentra la primera palabra de la frase
    token = strtok(frase, " ");
    while (token != NULL) {
        // Utilizamos la directiva omp parallel sections para paralelizar las operaciones
        #pragma omp parallel sections shared(token, indice)
        {
            // Sección para palabras impares
            #pragma omp section
            {
                if (indice % 2 != 0) {
                    // Si el índice es impar, agrega la palabra a la primera parte
                    #pragma omp critical
                    strcat(primera_parte, token);
                    #pragma omp critical
                    strcat(primera_parte, " ");  // Agrega un espacio entre palabras
                }
            }

            // Sección para palabras pares
            #pragma omp section
            {
                if (indice % 2 == 0) {
                    // Si el índice es par, agrega la palabra a la segunda parte
                    #pragma omp critical
                    strcat(segunda_parte, token);
                    #pragma omp critical
                    strcat(segunda_parte, " ");  // Agrega un espacio entre palabras
                }
            }
        }

        token = strtok(NULL, " ");  // Siguiente palabra
        indice++;
    }

    // Imprime las dos partes divididas
    printf("Primera parte: %s\n", primera_parte);
    printf("Segunda parte: %s\n", segunda_parte);

    return 0;
}
