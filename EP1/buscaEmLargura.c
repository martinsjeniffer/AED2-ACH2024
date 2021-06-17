#include <stdio.h>
#include "fila.h"

void buscaEmLargura(Grafo *grafo);
void visitaLargura(int origem, Grafo *grafo, int cor[], int antecessor[], int distancia[]);
void imprimeCaminhoLargura(int origem, int v, int antecessor[], int distancia[]);

void buscaEmLargura(Grafo *grafo) {
  int numVertices = grafo->numVertices;
  int cor[numVertices], antecessor[numVertices], distancia[numVertices];
  int origem;

  for (int v = 0; v < numVertices; v++) {
    cor[v] = BRANCO;
    antecessor[v] = -1;
    distancia[v] = INFINITO;
  }

  fprintf(stdout, "\n\nBL:\n");
  for (int v = 0; v < numVertices; v++) {
    if (cor[v] == BRANCO) {
      visitaLargura(v, grafo, cor, antecessor, distancia);
    }
  }

  fprintf(stdout, "\n\nCaminhos BL:\n");
  for (int v = 0; v < numVertices; v++) {
      if (distancia[v] == 0) origem = v;
      imprimeCaminhoLargura(origem, v, antecessor, distancia);
    fprintf(stdout, "\n");
  }
}

void visitaLargura(int origem, Grafo *grafo, int cor[], int antecessor[], int distancia[]) {
  PFILA Fila = inicializarFila();
  PONT elemento;
  Apontador atual;

  cor[origem] = CINZA;
  distancia[origem] = 0;
  antecessor[origem] = origem;

  inserirElemento(Fila, origem);

  while (tamanho(Fila) != 0) {
    elemento = retiraPrimeiroElemento(Fila);
    fprintf(stdout, "%d ", elemento->id);

    if (!listaAdjVazia(grafo, elemento->id)) {
      atual = primeiroListaAdj(grafo, elemento->id);

      while (atual != NULL) {
        if (cor[atual->vertice] == BRANCO) {
          cor[atual->vertice] = CINZA;
          antecessor[atual->vertice] = elemento->id;
          distancia[atual->vertice]++;
          inserirElemento(Fila, atual->vertice);
        }
        atual = proxListaAdj(grafo, atual);
      }
    }

    cor[elemento->id] = PRETO;
  }
}

void imprimeCaminhoLargura(int origem, int v, int antecessor[], int distancia[]) {
  if (origem == v) {
    fprintf (stdout, "%d ", origem);
    return;
  } 
  if (distancia[v] == 0) {
    return;
  } else {
    imprimeCaminhoLargura(origem, antecessor[v], antecessor, distancia);
    fprintf (stdout, "%d " , v);
  }
}