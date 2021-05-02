#include <stdio.h>
#include "grafo_listaadj.h"

int main() {
    Grafo g1;
    int numVertices;

    do {
        printf("Digite o número de vertices do grafo\n");
        scanf("%d", &numVertices);
    } while (!inicializaGrafo(&g1, numVertices));

    return 0;
}