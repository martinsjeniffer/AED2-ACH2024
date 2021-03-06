#include <stdio.h>
#include "grafoListaAdj.h"
#include "buscaEmLargura.c"
#include "buscaEmProfundidade.c"
#include "componentesConexos.c"

bool leGrafoPorArquivo(FILE * arquivoGrafo, Grafo * grafo) {
  int nVertices, nArestas;
  int v1, v2;
  Peso peso;

  if (arquivoGrafo == NULL) {
    fprintf(stderr, "ERRO [leGrafoPorArquivo linha 13]: O arquivo não existe!\n");
    return false;
  }

  if (!fscanf(arquivoGrafo, "%d %d", &nVertices, &nArestas)) {
    fprintf(stderr, "ERRO [leGrafoPorArquivo linha 18]: Problemas ao ler nVertices e nArestas\n");
    return false;
  }

  if (!inicializaGrafo(grafo, nVertices)) {
    fprintf(stderr, "ERRO [leGrafoPorArquivo linha 23]: Erro ao inicializar o grafo\n");
    return false;
  }

  while (fscanf(arquivoGrafo, "%d %d %d", &v1, &v2, &peso) != EOF) {
    if (insereAresta(grafo, v1, v2, peso)) insereAresta(grafo, v2, v1, peso);
    else fprintf(stderr, "ERRO [leGrafoPorArquivo linha 29]: Erro ao inserir aresta.\n");
  }

  fclose(arquivoGrafo);
  return true;
}

int main() {
  Grafo grafo;
  stdin = fopen("./entrada.txt", "r");
  stdout = fopen("./saida.txt", "w+");
  stderr = fopen("./erro.txt", "w+");

  if (leGrafoPorArquivo(stdin, &grafo)) {
    imprimeGrafo(&grafo);
    buscaEmLargura(&grafo);

    int numVertices = grafo.numVertices;
    int vertArticulacao[numVertices];
    buscaEmProfundidade(&grafo, vertArticulacao);
    componentesConexos(&grafo);
    imprimeVerticesDeArticulacao(&grafo, vertArticulacao);
    liberaGrafo(&grafo);
  }

  return 0;
}