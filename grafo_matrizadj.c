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
    for (j = 0; j <= grafo->numArestas; j++) {
      grafo->mat[i][j] = AN;
    }
  }

  return true;
};
