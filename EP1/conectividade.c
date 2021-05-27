#include <stdio.h>
#include "grafo_listaadj.h"

void leGrafo(FILE * arquivoGrafo, Grafo* grafo) {
  int nVertices, nArestas;
  int v1, v2;
  Peso peso;

  if(arquivoGrafo == NULL) {
    fprintf(stderr, "O arquivo não existe!");
    return;
  }

  if (!fscanf(arquivoGrafo, "%d %d", &nVertices, &nArestas)) {
    fprintf(stderr, "Problemas ao ler nVertices e nArestas");
    return;
  }

  inicializaGrafo(grafo, nVertices);

  while(fscanf(arquivoGrafo, "%d %d %d", &v1, &v2, &peso) != EOF) {
    insereAresta(grafo, v1, v2, peso);
  }

  fclose(arquivoGrafo);
  return;
}

int main() {
  Grafo grafo;

  if(stdin) leGrafo(stdin, &grafo);
  imprimeGrafo(&grafo);
  liberaGrafo(&grafo);

  return 0;
}