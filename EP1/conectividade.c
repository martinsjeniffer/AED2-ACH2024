#include <stdio.h>
#include "grafo_listaadj.h"

bool leGrafo(FILE * arquivoGrafo, Grafo* grafo) {
  int nVertices, nArestas;
  int v1, v2;
  Peso peso;

  if(arquivoGrafo == NULL) {
    fprintf(stderr, "O arquivo não existe!\n");
    return false;
  }

  if (!fscanf(arquivoGrafo, "%d %d", &nVertices, &nArestas)) {
    fprintf(stderr, "Problemas ao ler nVertices e nArestas\n");
    return false;
  }

  if(!inicializaGrafo(grafo, nVertices)) {
    fprintf(stderr, "Erro ao inicializar o grafo\n");
    return false;
  }

  while(fscanf(arquivoGrafo, "%d %d %d", &v1, &v2, &peso) != EOF) {
    if (insereAresta(grafo, v1, v2, peso)) insereAresta(grafo, v2, v1, peso);
    else fprintf(stderr, "Erro ao inserir aresta.\n");
  }

  fclose(arquivoGrafo);
  return true;
}

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

void buscaEmProfundidade(Grafo* grafo, int vertArticulacao[]) {
  int numVertices = grafo->numVertices;
  int cor[numVertices],
    tempoDescobrimento[numVertices],
    antecessor[numVertices],
    menorTempoVertRetorno[numVertices];

  int tempo = 0;
  int origem;

  for (int v = 0; v < numVertices; v++) {
    cor[v] = BRANCO;
    tempoDescobrimento[v] = 0;
    antecessor[v] = -1;
    menorTempoVertRetorno[v] = 0;
    vertArticulacao[v] = false;
  }

  fprintf(stdout, "\nBP:\n");
  for (int v = 0; v < numVertices; v++) {
    if (cor[v] == BRANCO) {
      visitaProfundidade(v, grafo, &tempo, cor, tempoDescobrimento, antecessor, menorTempoVertRetorno, vertArticulacao);
    }
  }

  fprintf(stdout, "\n\nCaminhos BP:\n");
  for (int v = 0; v < numVertices; v++) {
      if(antecessor[v] == -1) origem = v;
      imprimeCaminhoBuscaProf(origem, v, antecessor);
    fprintf(stdout, "\n");
  }
}

void imprimeVerticesDeArticulacao(Grafo* grafo, int vertArticulacao[]) {
  fprintf(stdout, "\n\nVertices de Articulacao:\n");
  for (int v = 0; v < grafo->numVertices; v++) 
    if (vertArticulacao[v]) fprintf(stdout, "%d ", v);
  fprintf(stdout, "\n");
}

int main() {
  Grafo grafo;
  stdin = fopen("./entrada.txt", "r");
  stdout = fopen("./saida.txt", "w+");
  stderr = fopen("./erro.txt", "w+");

  if (leGrafo(stdin, &grafo)) {
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