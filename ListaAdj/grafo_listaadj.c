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

void insereAresta(Grafo * grafo, int v1, int v2, Peso peso) {
  Apontador novaAresta;

  if (!verticeValido(grafo, v1) && !verticeValido(grafo, v2)) return;
  if (!(novaAresta = (Apontador) calloc(1, sizeof(Apontador)))) {
    fprintf(stderr, "ERRO: Falha na alocacao de memoria na \
      funcao insereAresta\n");
    return;
  }

  novaAresta->vdest = v2;
  novaAresta->peso = peso;
  novaAresta->prox = grafo->listaAdj[v1];
  /*
   * novaAresta entra em PRIMEIRO, e nao na ultima posicao
   * assim a implementacao fica com O(1);
   */
  grafo->listaAdj[v1] = novaAresta;

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

    // inicializaGrafo(grafo, nVertices);

    while(fscanf(arquivoGrafo, "%d %d %d", &v1, &v2, &peso) != EOF) {
        printf("\n v1: %d v2: %d peso: %d", v1, v2, peso);
        // insereAresta(grafo, v1, v2, peso);
    }

    fclose(arquivoGrafo);
    return;
}