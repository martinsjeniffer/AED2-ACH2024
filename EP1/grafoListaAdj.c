#include <stdio.h>
#include <stdlib.h>
#include "grafoListaAdj.h"

bool inicializaGrafo(Grafo * grafo, int numVertices) {
  if (numVertices <= 0) {
    fprintf(stderr, "ERRO [inicializaGrafo linha 7]: Numero de vertices deve ser positivo ou maior que zero.\n");
    return false;
  }

  if (numVertices > MAX_VERTICES) {
    fprintf(stderr, "ERRO [inicializaGrafo linha 12]: Numero de vertices deve ser menor que 100.\n");
    return false;
  }

  grafo->numVertices = numVertices;

  if (!(grafo->listaAdj = (Apontador*) calloc(numVertices + 1, sizeof(Apontador)))) {
    fprintf(stderr, "ERRO [inicializaGrafo linha 19]: Falha na alocacao de memoria na funcao inicializaGrafo\n");
    return false;
  }

  for (int i = 0; i < grafo->numVertices; i++) grafo->listaAdj[i] = NULL;

  grafo->numArestas = 0;
  return true;
};

bool verticeValido(Grafo * grafo, int vertice) {
  if (vertice > grafo->numVertices) {
    fprintf(stderr, "ERRO [verticeValido linha 31]: Numero do vertice (%d) maior que o numero total de vertices (%d)\n", vertice, grafo->numVertices);
    return false;
  }

  if (vertice < 0) {
    fprintf(stderr, "ERRO [verticeValido linha 36]: Numero do vertice (%d) deve ser positivo\n", vertice);
    return false;
  }

  return true;
}

bool insereAresta(Grafo * grafo, int v1, int v2, Peso peso) {
  Apontador novaAresta;

  if (v1 == v2){
    fprintf(stderr, "ERRO [insereAresta linha 47]: Grafo nao direcionado nao tem self-loop.\n");
    return false;
  } 

  if (!verticeValido(grafo, v1) || !verticeValido(grafo, v2)) {
    fprintf(stderr, "ERRO [insereAresta linha 52]: Vertice invalido.\n");
    return false;
  }

  if (existeAresta(grafo, v1, v2)) {
    fprintf(stderr, "ERRO [insereAresta linha 57]: A aresta (%d,%d) ja existe.\n", v1, v2);
    return false;
  }

  if (!(novaAresta = (Apontador) calloc(1, sizeof(Apontador)))) {
    fprintf(stderr, "ERRO [insereAresta linha 62]: Falha na alocacao de memoria.\n");
    return false;
  }

  novaAresta->vertice = v2;
  novaAresta->peso = peso;
  novaAresta->arestaPrincipal = !existeAresta(grafo, v2, v1);
  novaAresta->prox = grafo->listaAdj[v1];
  grafo->listaAdj[v1] = novaAresta;

  if (!existeAresta(grafo, v2, v1)) grafo->numArestas++;

  return true;
}

bool existeAresta(Grafo * grafo, int v1, int v2) {
  Apontador aresta;

  if (!verticeValido(grafo, v1) && !verticeValido(grafo, v2)) return false;
  aresta = grafo->listaAdj[v1];

  while (aresta != NULL && aresta->vertice != v2)
    aresta = aresta -> prox;

  if (aresta != NULL) return true;
  return false;
}

bool listaAdjVazia(Grafo * grafo, int vertice) {
  if (!verticeValido(grafo, vertice)) return false;

  return (grafo->listaAdj[vertice] == NULL);
}

Apontador primeiroListaAdj(Grafo * grafo, int vertice) {
  return (grafo->listaAdj[vertice]);
}

Apontador proxListaAdj(Grafo * grafo, Apontador atual) {
  if (atual == NULL) {
    fprintf(stderr, "ERRO [proxListaAdj linha 102]: Aresta atual eh NULL");
    return false;
  }

  return (atual -> prox);
}

void liberaGrafo(Grafo * grafo) {
  Apontador aresta;

  for (int vertice = 0; vertice < grafo->numVertices; vertice++) {
    while ((aresta = grafo->listaAdj[vertice]) != NULL) {
      grafo->listaAdj[vertice] = aresta->prox;
      aresta->prox = NULL;
      free(aresta);
    }
  }

  grafo->numVertices = 0;
  free(grafo->listaAdj);
  grafo->listaAdj = NULL;
}

void imprimeGrafo(Grafo* grafo) {
  Apontador atual;
  fprintf(stdout, "%d %d", grafo->numVertices, grafo->numArestas);

  for (int vertice = 0; vertice < grafo->numVertices; vertice++) {
    atual = primeiroListaAdj(grafo, vertice);

    if (!listaAdjVazia(grafo, vertice)) {
      while (atual != NULL) {
        if (atual->arestaPrincipal) fprintf (stdout, "\n%d %d %d", vertice, atual->vertice, atual->peso);
        atual = proxListaAdj(grafo, atual);
      }
    }
  }

  return;
}