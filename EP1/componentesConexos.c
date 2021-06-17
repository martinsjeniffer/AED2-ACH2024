#include <stdio.h>

void verificaVerticeComponenteConexo(Grafo * grafo, int componenteConexo[], int vertice, int idComponente);
void componentesConexos(Grafo * grafo);


void verificaVerticeComponenteConexo(Grafo * grafo, int componenteConexo[], int vertice, int idComponente) {
  Apontador atual = primeiroListaAdj(grafo, vertice);

  componenteConexo[vertice] = idComponente;
  fprintf(stdout, "%d ", vertice);

  while (atual != NULL) {
    if(componenteConexo[atual->vertice] == -1) {
      verificaVerticeComponenteConexo(grafo, componenteConexo, atual->vertice, idComponente);
    }
    atual = proxListaAdj(grafo, atual);
  }
}

void componentesConexos(Grafo * grafo){
  int id = 0;
  int componenteConexo[grafo->numVertices];

  for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
    componenteConexo[vertice] = -1;
  }

  fprintf(stdout, "\nComponentes Conectados:");
  for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
    if (componenteConexo[vertice] == -1) {
      id++;
      fprintf(stdout, "\nC%d: ", id);
      verificaVerticeComponenteConexo(grafo, componenteConexo, vertice, id);
    }
  }
}