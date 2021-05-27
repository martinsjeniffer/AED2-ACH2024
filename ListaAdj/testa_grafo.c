#include <stdio.h>
#include "grafo_listaadj.h"

int main() {
    Grafo grafo;
    printf("$$$$$");
    inicializaGrafo(&grafo, 5);

    leGrafo("entrada.txt", &grafo);
    // insereAresta(&grafo, 0, 2, 1);
    // insereAresta(&grafo, 1, 2, 1);
    // insereAresta(&grafo, 2, 4, 1);
    // imprimeGrafo(&grafo);

    return 0;
}