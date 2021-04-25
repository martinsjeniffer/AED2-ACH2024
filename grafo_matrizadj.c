#include <stdio.h>
#include "grafo_matrizadj.h"

/*
 * bool inicializaGrafo(Grafo* grafo, int nv):
 * 
 * Inicializa um grafo com nv vertices.
 * Preenche as celulas com AN (representando a ausencia de arestas).
 * Vertices vao de 1 a nv
 * Retorna true se inicializou com sucesso e false caso contrário
 */
bool inicializaGrafo(Grafo* grafo, int nv){
  int i, j;

  if (nv > MAXNUMVERTICES) {
    fprintf(stderr, "ERRO na chamada de inicializaGrafo: \
      Numero de vertices maior que o maximo permitido de %d.\n", MAXNUMVERTICES);
    return false;
  }

  if (nv <= 0) {
    fprintf(stderr, "ERRO na chamada de inicializaGrafo: \
      Numero de vertices deve ser positivo.\n");
    return false;
  }

  grafo->numVertices = nv;
  grafo->numArestas = 0;

  for (i = 0; i <= grafo->numVertices; i++) {
    for (j = 0; j <= grafo->numVertices; j++) {
      grafo->mat[i][j] = AN;
    }
  }

  return true;
};

/*
 * bool verticeValido(Grafo * grafo, int vertice):
 * 
 * Verifica que o numero do vertice eh valido no grafo.
 */
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
 * void insereAresta(Grafo * grafo, int v1, int v2, Peso peso):
 * 
 * Insere a aresta entre o vértice 1 (v1) e o vértice 2 (v2).
 */
void insereAresta(Grafo * grafo, int v1, int v2, Peso peso) {
  if (!verticeValido(grafo, v1) && !verticeValido(grafo, v2)) return;
  grafo->mat[v1][v2] = peso;
  grafo->numArestas++;
}

/*
 * bool existeAresta(Grafo * grafo, int v1, int v2):
 * 
 * Retorna true se existe a aresta e false caso contrário
 */
bool existeAresta(Grafo * grafo, int v1, int v2) {
  if (!verticeValido(grafo, v1) && !verticeValido(grafo, v2)) return false;
  if (grafo->mat[v1][v2] == AN) return false;

  return true;
}

/*
 * bool removeAresta(Grafo * grafo, int v1, int v2):
 * 
 * Remove a aresta (v1, v2) do grafo colocando AN em sua celula
 * Se a aresta existia, coloca o peso dessa aresta em "peso" e retorna true
 * caso contrario, retorna false e "peso" é inalterado
 */
bool removeAresta(Grafo * grafo, int v1, int v2, Peso * peso) {
  if (!existeAresta(grafo, v1, v2)) return false;

  *peso = grafo->mat[v1][v2];
  grafo->mat[v1][v2] = AN;
  grafo->numArestas--;
  return true;
}

/*
 * bool listaAdjVazia(Grafo * grafo, int v):
 * 
 * Retorna true se a lista de adjacentes de um dado vertice eh vazia
 * e false caso contrario
 */
bool listaAdjVazia(Grafo * grafo, int vertice) {
  if (!verticeValido(grafo, vertice)) return true;

  for (int i = 1; i <= grafo->numVertices; i++)
    if (grafo->mat[vertice][i] != AN) return false;
  return true;
}

/*
 * int proxListaAdj(Grafo * grafo, int vertice, int atual):
 * 
 * Trata-se de um iterador sobre a lista de adjacencia do vertice
 * Retorna o proximo vertice adjacente a v, partindo do vertice "atual"
 * adjacente a v ou -1 se a lista de adjacencia tiver terminado
 * sem um novo proximo
 */
// minha versao
int proxListaAdj(Grafo * grafo, int vertice, int atual) {
  if (listaAdjVazia(grafo, vertice)) return VERTICE_INVALIDO;

  for (i = atual + 1; i <= grafo->numVertices; i++) 
    if (grafo->mat[vertice][i] != AN) return i;

  return VERTICE_INVALIDO;
}

// versao professora
/*
int proxListaAdj(Grafo * grafo, int vertice, int atual) {
  if (verticeValido(grafo, vertice)) return VERTICE_INVALIDO;

  atual++;
  while ((atual <= grafo->numVertices) && (grafo->mat[vertice][atual] == AN))
    atual++;

  if (atual > grafo -> numVertices) return VERTICE_INVALIDO;

  return atual;
} 
*/
