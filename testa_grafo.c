//
// Created by Vanessa Nascimento on 16/05/21.
//

#include <stdio.h>
#include <stdlib.h>

#include "grafo.c"

int main() {
    Grafo grafo;
    inicializaGrafo(&grafo, 5);
    leGrafo("entrada.txt", &grafo);
    return 0;
}


