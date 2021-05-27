#include <stdio.h>
#include "grafo_listaadj.h"

void leGrafo(char* nomearq, Grafo* grafo) {
    FILE * arquivoGrafo;
    int nVertices, nArestas;
    int v1, v2;
    Peso peso;

    arquivoGrafo = fopen(nomearq, "r");
    if(arquivoGrafo == NULL) {
        fprintf(stderr, "O arquivo não existe!");
        return;
    }

    if (!fscanf(arquivoGrafo, "%d %d", &nVertices, &nArestas)) {
        fprintf(stderr, "Problemas ao ler nVertices e nArestas");
        return;
    }

    printf("\n nVertices nArestas: %d %d\n", nVertices, nArestas);

    inicializaGrafo(grafo, nVertices);

    while(fscanf(arquivoGrafo, "%d %d %d", &v1, &v2, &peso) != EOF) {
        printf("\n v1: %d v2: %d peso: %d", v1, v2, peso);
        insereAresta(grafo, v1, v2, peso);
    }

    fclose(arquivoGrafo);
    return;
}

int main() {
    Grafo grafo;

    leGrafo("entrada.txt", &grafo);
    // insereAresta(&grafo, 0, 2, 1);
    // insereAresta(&grafo, 1, 2, 1);
    // insereAresta(&grafo, 2, 4, 1);
    // imprimeGrafo(&grafo);

    return 0;
}