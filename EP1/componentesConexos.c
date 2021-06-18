#include <stdio.h>

void verificaVerticeComponenteConexo(Grafo * grafo, int componenteConexo[], int vertice, int idComponente);
void componentesConexos(Grafo * grafo);

void verificaVerticeComponenteConexo(Grafo * grafo, int componenteConexo[], int vertice, int idComponente) {
  componenteConexo[vertice] = idComponente;

  Apontador atual = primeiroListaAdj(grafo, vertice);
  while (atual != NULL) {
    if (componenteConexo[atual->vertice] == -1) {
      verificaVerticeComponenteConexo(grafo, componenteConexo, atual->vertice, idComponente);
    }
    atual = proxListaAdj(grafo, atual);
  }
}

void componentesConexos(Grafo * grafo) {
  int idComponente = 0;
  int numVertices = grafo->numVertices;
  int componenteConexo[numVertices];

  for (int vertice = 0; vertice < numVertices; ++vertice) {
    componenteConexo[vertice] = -1;
  }

  fprintf(stdout, "\nComponentes Conectados:");
  for (int vertice = 0; vertice < numVertices; ++vertice) {
    if (componenteConexo[vertice] == -1) {
      idComponente++;
      verificaVerticeComponenteConexo(grafo, componenteConexo, vertice, idComponente);
    }
  }

  for (int id = 1; id <= idComponente; id++) {
    fprintf(stdout, "\nC%d: ", id);
    for (int vertice = 0; vertice < numVertices; ++vertice) {
      if (componenteConexo[vertice] == id) fprintf(stdout, "%d ", vertice);
    }
  }
}