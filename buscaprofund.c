#include <stdio.h>
#include "grafo_listaadj.h"

#define BRANCO 0
#define CINZA 1
#define PRETO 2

void buscaProfundidade(Grafo* grafo) {
    /* 
     * Aloca vetores 
     *      cor,
     *      tdesc,
     *      tterm,
     *      antecessor,
     *          com tamanho grafo->nrVertices
     *      tempo = 0;
     */
   int numVertices = grafo->numVertices;
   int cor[numVertices], tdesc[numVertices], tterm[numVertices], antecessor[numVertices];
   int tempo = 0;

    /*
     * Para cada vertice v 
     *      cor[v] ← branco;
     *      tdesc[v] = tterm[v] = 0;
     *      antecessor[v] = - 1;
     */
   for (int v = 0; v <= numVertices; v++) {
       cor[v] = BRANCO;
       tdesc[v] = tterm[v] = 0;
       antecessor[v] = -1;
   }

    /*
     * Para cada vertice v 
     *      Se cor[v] = branco 
     *          visitaBP(v, grafo, &tempo, cor, tdesc, tterm, antecessor);
     */
   for (int v = 0; v <= numVertices; v++)
       if (cor[v] == BRANCO) visitaBP(v, grafo, &tempo, cor, tdesc, tterm, antecessor);
}

void visitaBP(int v, Grafo * grafo, int * tempo, int * cor[], int * tdesc[], int * tterm[], int * antecessor[]) {
    cor[v] = CINZA;
    tdesc[v] = ++(*tempo);

    if (!listaAdjVazia(grafo, v)) {
        // Para cada vertice u da lista de adjacencia de v {
            if (cor[u] == BRANCO) {
                antecessor[u] = v;
                visitaBP(u, grafo, &tempo, cor, tdesc, tterm, antecessor);
            }

            /*
                Se u é cinza
                    marca que é uma aresta de retorno
            */
        // }
    }

    tterm[v] = ++(*tempo);
    cor[v] = PRETO;
}