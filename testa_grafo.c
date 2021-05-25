//
// Created by Vanessa Nascimento on 16/05/21.
//

#include <stdio.h>
#include <stdlib.h>

#include "grafo.c"

int main() {
    Grafo grafo;
    inicializaGrafo(&grafo, 5);
    insereAresta(&grafo, 0, 2, 1);
    insereAresta(&grafo, 1, 2, 1);
    insereAresta(&grafo, 2, 4, 1);
    imprimeGrafo(&grafo);

    return 0;
}


