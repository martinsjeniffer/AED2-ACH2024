// Grafo por lista de adjacencia
// EP1 - Created by Vanessa Alves do Nascimento - 10882848 on 16/05/21
#include <stdbool.h>
#define VERTICE_INVALIDO NULL
#define AN -1

typedef int Peso;

// struct aresta define vertice de destino, o seu peso e um ponteiro para a próxima aresta
typedef struct str_aresta {
    int verticeDestino;
    Peso peso;
    struct srt_aresta * prox;
} Aresta;

typedef Aresta* Apontador;

//listaAdj é um vetor de listas ligadas, onde um vetor que contém o vértice i vai ter um ponteiro para o inicio da lista de adjacencia desse vértice
//em grafos não direcionados, cada aresta é representada duas vezes
typedef struct {
    Apontador* listaAdj;
    int numVertices;
    int numArestas;
} Grafo;



