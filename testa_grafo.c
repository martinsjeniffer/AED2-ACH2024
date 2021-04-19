#include <stdio.h>
#include "grafo_matrizadj.h"

int main() {
    Grafo g1;
    int numVertices;

    do {
        printf("Digite o número de vertices do grafo\n");
        scanf("%d", &numVertices);
    } while (!inicializaGrafo(&g1, numVertices));

    // inicializaGrafo(&g1, 10);
    // imprimeGrafo(&g1);

    return 0;
}