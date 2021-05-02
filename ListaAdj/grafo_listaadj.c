#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaadj.h"

bool inicializaGrafo(Grafo* grafo, int nv){
  if (nv <= 0) {
    fprintf(stderr, "ERRO na chamada de inicializaGrafo: \
      Numero de vertices deve ser positivo.\n");
    return false;
  }

  grafo->numVertices = nv;

  if (!(grafo->listaAdj = (Apontador*) calloc(nv + 1, sizeof(Apontador)))) {
    fprintf(stderr, "ERRO: Falha na alocacao de memoria na \
      funcao inicializaGrafo\n");
    return false;
  }

  grafo->numArestas = 0;

  return true;
};

bool verticeValido(Grafo * grafo, int vertice) {
  if (vertice > grafo->numVertices) {
    fprintf(stderr, "ERRO: \
      Numero do vertice (%d) maior que o numero total de vertices (%d)", vertice, grafo->numVertices);
    return false;
  }
  if (vertice <= 0) {
    fprintf(stderr, "ERRO: \
      Numero do vertice (%d) deve ser positivo", vertice);
    return false;
  }

  return true;
}

/*
 * void insereAresta(Grafo * grafo):
 * 
 */
void insereAresta(Grafo * grafo) {
}

/*
 * bool existeAresta(Grafo * grafo):
 * 
 */
bool existeAresta(Grafo * grafo) {
  return true;
}

/*
 * bool removeAresta(Grafo * grafo
 * 
 */
bool removeAresta(Grafo * grafo) {
  return true;
}

bool listaAdjVazia(Grafo * grafo, int v) {
  if (!verticeValido(grafo, v)) return false;

  return (grafo->listaAdj[v] == NULL);
}

Apontador primeiroListaAdj(Grafo * grafo, int v) {
  return (grafo->listaAdj[v]);
}

Apontador proxListaAdj(Grafo * grafo, int v, Apontador atual) {
  if (listaAdjVazia(grafo, v)) return VERTICE_INVALIDO;
  if (atual == NULL) {
    fprintf(stderr, "ERRO: Aresta atual eh NULL");
    return false;
  }

  return (atual -> prox);
}
