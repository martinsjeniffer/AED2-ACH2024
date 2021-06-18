#include <stdio.h>

void buscaEmProfundidade(Grafo* grafo, int vertArticulacao[]);
void visitaProfundidade(int vertice, Grafo * grafo, int * tempo, int cor[], int tdesc[],
                        int antecessor[], int menorTempoVertRetorno[], int vertArticulacao[]);
void imprimeCaminhoBuscaProf(int origem, int v, int antecessor[]);
void imprimeVerticesDeArticulacao(Grafo* grafo, int vertArticulacao[]);


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

void visitaProfundidade(int vertice, Grafo * grafo, int * tempo, int cor[], int tdesc[],
                        int antecessor[], int menorTempoVertRetorno[], int vertArticulacao[]) {
  Apontador atual;
  int filhos = 0;

  cor[vertice] = CINZA; 
  tdesc[vertice] = menorTempoVertRetorno[vertice] = ++(*tempo);

  fprintf(stdout, "%d ", vertice);

  if (!listaAdjVazia(grafo, vertice)) {
    for (atual = primeiroListaAdj(grafo, vertice); atual != NULL; atual = proxListaAdj(grafo, atual)) {
      if (cor[atual->vertice] == BRANCO) {
        filhos++;
        antecessor[atual->vertice] = vertice;

        visitaProfundidade(atual->vertice, grafo, tempo, cor, tdesc, 
                          antecessor, menorTempoVertRetorno, vertArticulacao);

        menorTempoVertRetorno[vertice] = MIN(menorTempoVertRetorno[vertice], menorTempoVertRetorno[atual->vertice]);

        if (antecessor[vertice] == -1 && filhos > 1) {
          vertArticulacao[vertice] = true;
        }
        
        if (antecessor[vertice] != -1 && menorTempoVertRetorno[atual->vertice] >= tdesc[vertice]) {
          vertArticulacao[vertice] = true;
        }
      } else if (atual->vertice != antecessor[vertice]) {
        menorTempoVertRetorno[vertice] = MIN(menorTempoVertRetorno[vertice], tdesc[atual->vertice]);
      }
    }
  }

  cor[vertice] = PRETO;
}

void imprimeCaminhoBuscaProf(int origem, int v, int antecessor[]) {
  if (origem == v) {
    fprintf (stdout, "%d ", origem);
    return;
  } 
  if (antecessor[v] == -1) {
    return;
  } else {
    imprimeCaminhoBuscaProf(origem, antecessor[v], antecessor);
    fprintf (stdout, "%d " , v);
  }
}

void imprimeVerticesDeArticulacao(Grafo* grafo, int vertArticulacao[]) {
  fprintf(stdout, "\n\nVertices de Articulacao:\n");
  for (int v = 0; v < grafo->numVertices; v++) 
    if (vertArticulacao[v]) fprintf(stdout, "%d ", v);
  fprintf(stdout, "\n");
}