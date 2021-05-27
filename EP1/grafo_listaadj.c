#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaadj.h"

bool inicializaGrafo(Grafo * grafo, int numVertices){
  if (numVertices <= 0) {
    fprintf(stderr, "ERRO na chamada de inicializaGrafo: \
      Numero de vertices deve ser positivo.\n");
    return false;
  }

  grafo->numVertices = numVertices;

  if (!(grafo->listaAdj = (Apontador*) calloc(numVertices + 1, sizeof(Apontador)))) {
    fprintf(stderr, "ERRO: Falha na alocacao de memoria na \
      funcao inicializaGrafo\n");
    return false;
  }

  for (int i = 0; i < grafo->numVertices; i++) grafo->listaAdj[i] = NULL;

  grafo->numArestas = 0;
  return true;
};

bool verticeValido(Grafo * grafo, int vertice) {
  if (vertice > grafo->numVertices) {
    fprintf(stderr, "ERRO: \
      Numero do vertice (%d) maior que o numero total de vertices (%d)", vertice, grafo->numVertices);
    return false;
  }
  if (vertice < 0) {
    fprintf(stderr, "ERRO: \
      Numero do vertice (%d) deve ser positivo", vertice);
    return false;
  }

  return true;
}

void insereAresta(Grafo * grafo, int v1, int v2, Peso peso) {
  Apontador novaAresta;

  if(v1 == v2){
    fprintf(stderr, "ERRO em insereAresta: Grafo nao direcionado nao tem self-loop.\n");
    return;
  } 

  if (!verticeValido(grafo, v1) && !verticeValido(grafo, v2)) return;

  if (existeAresta(grafo, v1, v2)) {
    fprintf(stderr, "ERRO em insereAresta: A aresta (%d,%d) ja existe.\n", v1, v2);
    return;
  }

  if (!(novaAresta = (Apontador) calloc(1, sizeof(Apontador)))) {
    fprintf(stderr, "ERRO em insereAresta: Falha na alocacao de memoria na \
      funcao insereAresta\n");
    return;
  }

  novaAresta->vdest = v2;
  novaAresta->peso = peso;
  novaAresta->prox = grafo->listaAdj[v1];
  grafo->listaAdj[v1] = novaAresta;

  // novaAresta->prox = grafo->listaAdj[v2];
  // grafo->listaAdj[v2] = novaAresta;

  grafo->numArestas++;
}

bool existeAresta(Grafo * grafo, int v1, int v2) {
  Apontador aresta;

  if (!verticeValido(grafo, v1) && !verticeValido(grafo, v2)) return false;
  aresta = grafo->listaAdj[v1];

  while (aresta != NULL && aresta->vdest != v2)
    aresta = aresta -> prox;

  if (aresta != NULL) return true;
  return false;
}

bool removeAresta(Grafo * grafo, int v1, int v2, Peso * peso) {
  if (!existeAresta(grafo, v1, v2)) return false;

  Apontador atual, ant;
  atual = grafo->listaAdj[v1];

  while (atual != NULL && atual->vdest != v2) {
    ant = atual;
    atual = atual->prox;
  }

  if (atual != NULL) {
    if (grafo->listaAdj[v1] == atual) grafo->listaAdj[v1] = atual->prox;
    else ant->prox = atual->prox;

    *peso = atual->peso;
    atual->prox = NULL;
    free(atual);
    atual = NULL; // boa pratica
    grafo->numArestas--;
    return true;
  }

  return false;
}

bool listaAdjVazia(Grafo * grafo, int v) {
  if (!verticeValido(grafo, v)) return false;

  return (grafo->listaAdj[v] == NULL);
}

Apontador primeiroListaAdj(Grafo * grafo, int v) {
  return (grafo->listaAdj[v]);
}

Apontador proxListaAdj(Grafo * grafo, int v, Apontador atual) {
  if (atual == NULL) {
    fprintf(stderr, "ERRO: Aresta atual eh NULL");
    return false;
  }

  return (atual -> prox);
}

void liberaGrafo(Grafo * grafo) {
  int vertice;
  Apontador aresta;

  for (vertice = 0; vertice <= grafo->numVertices; vertice++)
    while ((aresta = grafo->listaAdj[vertice]) != NULL) {
      grafo->listaAdj[vertice] = aresta->prox;
      aresta->prox = NULL;
      free(aresta);
    }

  grafo->numVertices = 0;
  free(grafo->listaAdj); // pois o vetor tb tem alocacao dinamica
  grafo->listaAdj = NULL;

}

void imprimeGrafo(Grafo* grafo) {
  Apontador atual;
  printf("\n%d %d", grafo->numVertices, grafo->numArestas);
  
  for (int i = 0; i < grafo->numVertices; i++) {
    atual = grafo->listaAdj[i];

    if (!listaAdjVazia(grafo, i)) {
      // TODO: usar o METODO primeiraListaAdj & proxListaAdj
      while(atual != NULL) {
        printf ("\n%d %d %d", i, atual->vdest, atual->peso);
        atual = atual -> prox;
      }
    }
  }

  return;
}
