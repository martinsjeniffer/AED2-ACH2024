#include <stdio.h>
#include "fila.h"

/*
 * void buscaEmLargura(Grafo * grafo):
 *    Recebe por parametro um grafo para o qual ira executar
 *    um algoritmo de busca em largura e, tambem ira
 *    imprimir o caminho da busca em largura
 */
void buscaEmLargura(Grafo * grafo);

/*
 * void visitaLargura(int origem, Grafo * grafo, int cor[], int antecessor[], int distancia[]):
 *    origem: vertice de inicio da busca em largura.
 *    grafo: grafo que sera feita a busca em largura
 *    cor: vetor que registrara o esquema de cor BRANCO, CINZA ou PRETO, para
 *         verificar se o vertice ja foi visitado anteriormente.
 *    antecessor: vetor que armazena o vertice pai pelo qual o vertice atual
 *         foi acessado.
 *    distancia: vetor que armazena a distancia que o vertice atual
 *         esta da origem da busca em largura.
 * 
 *    Funcao executa a busca em largura por meio de uma fila.
 */
void visitaLargura(int origem, Grafo * grafo, int cor[], int antecessor[], int distancia[]);

/*
 * void imprimeCaminhoLargura(int origem, int destino, int antecessor[], int distancia[]):
 *    Funcao recursiva que imprime o caminho feito pela busca em largura.
 */
void imprimeCaminhoLargura(int origem, int destino, int antecessor[], int distancia[]);

void buscaEmLargura(Grafo * grafo) {
  int origemArvoreBuscaLargura;
  int numVertices = grafo->numVertices;
  int cor[numVertices],
      antecessor[numVertices],
      distancia[numVertices];

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
    if (distancia[v] == 0) origemArvoreBuscaLargura = v;

    imprimeCaminhoLargura(origemArvoreBuscaLargura, v, antecessor, distancia);
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

void imprimeCaminhoLargura(int origem, int destino, int antecessor[], int distancia[]) {
  if (origem == destino) {
    fprintf (stdout, "%d ", origem);
    return;
  } 
  if (distancia[destino] == 0) {
    return;
  } else {
    imprimeCaminhoLargura(origem, antecessor[destino], antecessor, distancia);
    fprintf (stdout, "%d " , destino);
  }
}