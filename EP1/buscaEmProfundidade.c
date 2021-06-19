#include <stdio.h>

/*
 * void buscaEmProfundidade(Grafo* grafo, int vertArticulacao[]):
 *    grafo: grafo em que sera feita a busca em profundidade
 *    vertArticulacao[]: vetor que ira armazenar um booleano categorizando
 *          se o vertice correspondente ao indice do vetor eh um vertice de articulacao.
 * 
 *    Recebe por parametro um grafo para o qual ira executar
 *    um algoritmo de busca em profundidade e, tambem ira
 *    imprimir o caminho da busca em profundidade.
 */
void buscaEmProfundidade(Grafo* grafo, int vertArticulacao[]);

/*
 * void visitaProfundidade(int vertice, Grafo * grafo, int * tempo, int cor[], int tempoDescobrimento[],
 *                         int antecessor[], int exploracaoBP[], int vertArticulacao[]):
 * 
 *      Funcao recursiva que executa o algoritmo de busca em profundidade marcando, 
 *      tambem, se aquele vertice eh um vertice de articulacao.
 */
void visitaProfundidade(int vertice, Grafo * grafo, int * tempo, int cor[], int tempoDescobrimento[],
                        int antecessor[], int exploracaoBP[], int vertArticulacao[]);

/*
 * void imprimeCaminhoBuscaProf(int origem, int v, int antecessor[]):
 *    Funcao recursiva que imprime o caminho feito pela busca em profundidade.
 */
void imprimeCaminhoBuscaProf(int origem, int v, int antecessor[]);

/*
 * void imprimeVerticesDeArticulacao(Grafo* grafo, int vertArticulacao[]);
 *    Funcao que imprime os vertices marcados como vertice de articulacao.
 */
void imprimeVerticesDeArticulacao(Grafo* grafo, int vertArticulacao[]);


void buscaEmProfundidade(Grafo* grafo, int vertArticulacao[]) {
  int numVertices = grafo->numVertices;
  int cor[numVertices],
    tempoDescobrimento[numVertices],
    antecessor[numVertices],
    exploracaoBP[numVertices];

  int tempo = 0;
  int origem;

  for (int v = 0; v < numVertices; v++) {
    cor[v] = BRANCO;
    tempoDescobrimento[v] = 0;
    antecessor[v] = -1;
    exploracaoBP[v] = v;
    vertArticulacao[v] = false;
  }

  fprintf(stdout, "\nBP:\n");
  for (int v = 0; v < numVertices; v++) {
    if (cor[v] == BRANCO) {
      visitaProfundidade(v, grafo, &tempo, cor, tempoDescobrimento, antecessor, exploracaoBP, vertArticulacao);
    }
  }

  fprintf(stdout, "\n\nCaminhos BP:\n");
  for (int v = 0; v < numVertices; v++) {
      if(antecessor[v] == -1) origem = v;
      imprimeCaminhoBuscaProf(origem, v, antecessor);
    fprintf(stdout, "\n");
  }
}

void visitaProfundidade(int vertice, Grafo * grafo, int * tempo, int cor[], int tempoDescobrimento[],
                        int antecessor[], int exploracaoBP[], int vertArticulacao[]) {
  Apontador atual;
  int filhos = 0;

  cor[vertice] = CINZA; 
  tempoDescobrimento[vertice] = ++(*tempo);

  fprintf(stdout, "%d ", vertice);

  if (!listaAdjVazia(grafo, vertice)) {
    for (atual = primeiroListaAdj(grafo, vertice); atual != NULL; atual = proxListaAdj(grafo, atual)) {
      if (cor[atual->vertice] == BRANCO) {
        filhos++;
        antecessor[atual->vertice] = vertice;

        visitaProfundidade(atual->vertice, grafo, tempo, cor, tempoDescobrimento,
                          antecessor, exploracaoBP, vertArticulacao);

        // Verifica se a subarvore com raiz em atual->vertice tem alguma
        // conexão com um dos antecessores do vertice
        exploracaoBP[vertice] = MIN(exploracaoBP[vertice], exploracaoBP[atual->vertice]);

        // 1. `u` é a raiz da árvore BP e tem pelo menos dois filhos.
        if (antecessor[vertice] == -1 && filhos > 1) {
          vertArticulacao[vertice] = true;
        }

        // 2. `u` não é a raiz da árvore BP e tem um adjacente `v` que 
        // nenhum vértice no subgrafo com raiz em `v` tem uma aresta de retorno para um dos antecessores de `u`
        if (antecessor[vertice] != -1 && exploracaoBP[atual->vertice] >= tempoDescobrimento[vertice]) {
          vertArticulacao[vertice] = true;
        }

      } else if (atual->vertice != antecessor[vertice]) {
        // Atualiza exploracaoBP quando existe uma aresta de retorno
        exploracaoBP[vertice] = MIN(exploracaoBP[vertice], tempoDescobrimento[atual->vertice]);
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