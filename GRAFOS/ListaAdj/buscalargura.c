#include <stdio.h>
#include "grafo_listaadj.h"

#define BRANCO 0
#define CINZA 1
#define PRETO 2

void buscaEmLargura(Grafo *grafo) {
    /* 
     * Aloca vetores 
     *      cor,
     *      antecessor,
     *      dist,
     *          com tamanho grafo->nrVertices
     */
    int numVertices = grafo->numVertices;
    int cor[numVertices], antecessor[numVertices], distancia[numVertices];

    /*
     * Para cada vertice v 
     *      cor[v] ← branco;
     *      antecessor[v] ← - 1;
     *      distancia[v] ← ∞;
     */
    for (int v = 0; v <= numVertices; v++) {
        cor[v] = BRANCO;
        antecessor[v] = -1;
        distancia[v] = INFINITO;
    }
    /*
     * Para cada vertice v 
     *      se cor[v] = branco
     *          visitaLargura(v, grafo, cor, antecessor, distancia);
     */
    for (int v = 0; v <= numVertices; v++) {
        if (cor[v] == BRANCO)
            visitaLargura(v, grafo, cor, antecessor, distancia);
    }
};

void visitaLargura(int origem, Grafo *grafo, int cor[], int antecessor[], int distancia[]) {
    /*
     * cor[s] ← cinza;
     * distancia[s] ← 0;
     * F  ← Ø;
     * insereFila(F, s);
     * enquanto F ≠ Ø
     *      w  ←  removeFila(F)
     *      para cada vertice u da lista de adjacência de w
     *          se cor[u] = branco
     *              cor[u] ← cinza;
     *              antecessor[u] ← w;
     *              distancia[u] ← distancia[w] + 1;
     *              insereFila(F, u);
     *      cor[w] ← preto;
    */
}

// u como origem da visitaLargura
void imprimeCaminho(int u, int v, int antecessor[]) {
    if (distancia[v] == INFINITO) {
        printf ("Nao existe caminho de %d ate %d" , u, v);
        return;
    }
    if (u == v) {
        printf ("%d ", u);
        return;
    } else {
        imprimeCaminho(u, antecessor[v], antecessor);
        printf ( "%d " , v);
    }
}