#include <stdio.h>

/*
 * void componentesConexos(Grafo * grafo):
 *    Recebe por parametro um grafo para o qual ira executar
 *    um algoritmo de busca de componentes conexos.
 */
void componentesConexos(Grafo * grafo);

/*
 * void verificaVerticeComponenteConexo(Grafo * grafo, int componenteConexo[], int vertice, int idComponente):
 *    Funcao recursiva que marca o parametro idComponente em no vetor componenteConexo
 *    por meio da lista de adjacencias.
 */
void verificaVerticeComponenteConexo(Grafo * grafo, int componenteConexo[], int vertice, int idComponente);

void componentesConexos(Grafo * grafo) {
  int idComponente = 0;
  int numVertices = grafo->numVertices;
  int componenteConexo[numVertices];

  for (int vertice = 0; vertice < numVertices; ++vertice) {
    componenteConexo[vertice] = -1;
  }

  for (int vertice = 0; vertice < numVertices; ++vertice) {
    if (componenteConexo[vertice] == -1) {
      idComponente++;
      verificaVerticeComponenteConexo(grafo, componenteConexo, vertice, idComponente);
    }
  }

  fprintf(stdout, "\nComponentes Conectados:");
  for (int id = 1; id <= idComponente; id++) {
    fprintf(stdout, "\nC%d: ", id);
    for (int vertice = 0; vertice < numVertices; ++vertice) {
      if (componenteConexo[vertice] == id) fprintf(stdout, "%d ", vertice);
    }
  }
}

void verificaVerticeComponenteConexo(Grafo * grafo, int componenteConexo[], int vertice, int idComponente) {
  componenteConexo[vertice] = idComponente;
  Apontador atual;

  for (atual = primeiroListaAdj(grafo, vertice); atual != NULL; atual = proxListaAdj(grafo, atual)) {
    if (componenteConexo[atual->vertice] == -1) {
      verificaVerticeComponenteConexo(grafo, componenteConexo, atual->vertice, idComponente);
    }
  }
}