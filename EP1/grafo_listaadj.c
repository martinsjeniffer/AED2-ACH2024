#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaadj.h"
#include "fila.h"

bool inicializaGrafo(Grafo * grafo, int numVertices){
  if (numVertices <= 0) {
    fprintf(stderr, "ERRO na chamada de inicializaGrafo: \
      Numero de vertices deve ser positivo.\n");
    return false;
  }

  grafo->numVertices = numVertices;

  if (!(grafo->listaAdj = (Apontador*) calloc(numVertices + 1, sizeof(Apontador)))) {
    fprintf(stderr, "ERRO: Falha na alocacao de memoria na \
      funcao inicializaGrafo\n");
    return false;
  }

  for (int i = 0; i < grafo->numVertices; i++) grafo->listaAdj[i] = NULL;

  grafo->numArestas = 0;
  return true;
};

bool verticeValido(Grafo * grafo, int vertice) {
  if (vertice > grafo->numVertices) {
    fprintf(stderr, "ERRO: \
      Numero do vertice (%d) maior que o numero total de vertices (%d)", vertice, grafo->numVertices);
    return false;
  }
  if (vertice < 0) {
    fprintf(stderr, "ERRO: \
      Numero do vertice (%d) deve ser positivo", vertice);
    return false;
  }

  return true;
}

void insereAresta(Grafo * grafo, int v1, int v2, Peso peso) {
  Apontador novaAresta;

  if(v1 == v2){
    fprintf(stderr, "ERRO em insereAresta: Grafo nao direcionado nao tem self-loop.\n");
    return;
  } 

  if (!verticeValido(grafo, v1) && !verticeValido(grafo, v2)) return;

  if (existeAresta(grafo, v1, v2)) {
    fprintf(stderr, "ERRO em insereAresta: A aresta (%d,%d) ja existe.\n", v1, v2);
    return;
  }

  if (!(novaAresta = (Apontador) calloc(1, sizeof(Apontador)))) {
    fprintf(stderr, "ERRO em insereAresta: Falha na alocacao de memoria na \
      funcao insereAresta\n");
    return;
  }

  novaAresta->vdest = v2;
  novaAresta->peso = peso;
  novaAresta->arestaPrincipal = !existeAresta(grafo, v2, v1);
  novaAresta->prox = grafo->listaAdj[v1];
  grafo->listaAdj[v1] = novaAresta;

  if (!existeAresta(grafo, v2, v1)) grafo->numArestas++;
}

bool existeAresta(Grafo * grafo, int v1, int v2) {
  Apontador aresta;

  if (!verticeValido(grafo, v1) && !verticeValido(grafo, v2)) return false;
  aresta = grafo->listaAdj[v1];

  while (aresta != NULL && aresta->vdest != v2)
    aresta = aresta -> prox;

  if (aresta != NULL) return true;
  return false;
}

bool listaAdjVazia(Grafo * grafo, int v) {
  if (!verticeValido(grafo, v)) return false;

  return (grafo->listaAdj[v] == NULL);
}

Apontador primeiroListaAdj(Grafo * grafo, int v) {
  return (grafo->listaAdj[v]);
}

Apontador proxListaAdj(Grafo * grafo, int v, Apontador atual) {
  if (atual == NULL) {
    fprintf(stderr, "ERRO: Aresta atual eh NULL");
    return false;
  }

  return (atual -> prox);
}

void liberaGrafo(Grafo * grafo) {
  int vertice;
  Apontador aresta;

  for (vertice = 0; vertice <= grafo->numVertices; vertice++)
    while ((aresta = grafo->listaAdj[vertice]) != NULL) {
      grafo->listaAdj[vertice] = aresta->prox;
      aresta->prox = NULL;
      free(aresta);
    }

  grafo->numVertices = 0;
  free(grafo->listaAdj); // pois o vetor tb tem alocacao dinamica
  grafo->listaAdj = NULL;

}

void imprimeGrafo(Grafo* grafo) {
  Apontador atual;
  fprintf(stdout, "%d %d", grafo->numVertices, grafo->numArestas);
  
  for (int i = 0; i < grafo->numVertices; i++) {
    atual = grafo->listaAdj[i];

    if (!listaAdjVazia(grafo, i)) {
      while(atual != NULL) {
        if (atual->arestaPrincipal) 
          fprintf (stdout, "\n%d %d %d", i, atual->vdest, atual->peso);
        atual = atual -> prox;
      }
    }
  }

  return;
}

void buscaProfundidade(Grafo* grafo) {
  int numVertices = grafo->numVertices;
  int cor[numVertices], tdesc[numVertices], tterm[numVertices], antecessor[numVertices], vertArticulacao[numVertices], menorTempoVertRetorno[numVertices];
  int tempo = 0;
  int origem;

  for (int v = 0; v < numVertices; v++) {
    cor[v] = BRANCO;
    tdesc[v] = tterm[v] = 0;
    antecessor[v] = -1;
    menorTempoVertRetorno[v] = 0;
    vertArticulacao[v] = false;
  }

  fprintf(stdout, "\n\nBP: \n");
  for (int v = 0; v < numVertices; v++)
    if (cor[v] == BRANCO) visitaBP(v, grafo, &tempo, cor, tdesc, tterm, antecessor, menorTempoVertRetorno, vertArticulacao);
  fprintf(stdout, "\n");

  fprintf(stdout, "\n\nVERTICES DE ARTICULACAO: \n");
  for (int v = 0; v < numVertices; v++) 
    if (vertArticulacao[v]) fprintf(stdout, " %d ", v);
  fprintf(stdout, "\n");

  fprintf(stdout, "\n\nCaminhos BP: \n");
  for (int v = 0; v < numVertices; v++) {
      if(antecessor[v] == -1) origem = v;
      imprimeCaminhoBuscaProf(origem, v, antecessor);
    fprintf(stdout, "\n");
  }
}

void visitaBP(int v, Grafo * grafo, int * tempo, int cor[], int tdesc[], int tterm[], int antecessor[], int menorTempoVertRetorno[], int vertArticulacao[]) {
  Apontador atual;
  cor[v] = CINZA; 
  tdesc[v] = menorTempoVertRetorno[v] = ++(*tempo);

  fprintf(stdout, "%d ", v);

  if (!listaAdjVazia(grafo, v)) {
    atual = grafo->listaAdj[v];

    while(atual != NULL) {
      if (cor[atual->vdest] == BRANCO) {
        antecessor[atual->vdest] = v;
        visitaBP(atual->vdest, grafo, tempo, cor, tdesc, tterm, antecessor, menorTempoVertRetorno, vertArticulacao);

        menorTempoVertRetorno[v] = menorTempoVertRetorno[v] < menorTempoVertRetorno[atual->vdest] ? menorTempoVertRetorno[v] : menorTempoVertRetorno[atual->vdest];

        // iremos considerar a raiz da arvore de descoberta como vert de articulacao?

        // if (parent[u] == NIL && children > 1)
        //   ap[u] = true;
        
        if (antecessor[v] != -1 && menorTempoVertRetorno[atual->vdest] >= tdesc[v])
          vertArticulacao[v] = true;
      } else if (atual->vdest != antecessor[v]) {
        menorTempoVertRetorno[v] = menorTempoVertRetorno[v] < tdesc[atual->vdest] ? menorTempoVertRetorno[v] : tdesc[atual->vdest];
      }

      atual = atual->prox;
    }
  }

  tterm[v] = ++(*tempo);
  cor[v] = PRETO;
}

void buscaEmLargura(Grafo *grafo) {
    /* 
     * Aloca vetores 
     *      cor,
     *      antecessor,
     *      dist,
     *          com tamanho grafo->nrVertices
     */
    int numVertices = grafo->numVertices;
    int cor[numVertices], antecessor[numVertices], distancia[numVertices];
    int origem;

    /*
     * Para cada vertice v 
     *      cor[v] ← branco;
     *      antecessor[v] ← - 1;
     *      distancia[v] ← ∞;
     */
    for (int v = 0; v < numVertices; v++) {
        cor[v] = BRANCO;
        antecessor[v] = -1;
        distancia[v] = INFINITO;
    }
    /*
     * Para cada vertice v 
     *      se cor[v] = branco
     *          visitaLargura(v, grafo, cor, antecessor, distancia);
     */
    fprintf(stdout, "\n\nBL: \n");
    for (int v = 0; v < numVertices; v++) {
        if (cor[v] == BRANCO)
            visitaLargura(v, grafo, cor, antecessor, distancia);
    }

    fprintf(stdout, "\n\nCaminhos BL: \n");
    for (int v = 0; v < numVertices; v++) {
        if(distancia[v] == 0) origem = v;
        imprimeCaminhoLargura(origem, v, antecessor, distancia);
      fprintf(stdout, "\n");
    }
}

void visitaLargura(int origem, Grafo *grafo, int cor[], int antecessor[], int distancia[]) {
  cor[origem] = CINZA;
  distancia[origem] = 0;
  antecessor[origem] = origem;

  PFILA Fila = inicializarFila();
  PONT w;
  Apontador atual;
  inserirElemento(Fila, origem);

  while (Fila->numElementos != 0) {
    w = removePrimeiro(Fila);
    fprintf(stdout, "%d ", w->id);

    if (!listaAdjVazia(grafo, w->id)) {
      atual = grafo->listaAdj[w->id];
      while(atual != NULL) {
        if(cor[atual->vdest] == BRANCO) {
          cor[atual->vdest] = CINZA;
          antecessor[atual->vdest] = w->id;
          distancia[atual->vdest] = distancia[w->id] + 1;
          inserirElemento(Fila, atual->vdest);
        }
        atual = atual->prox;
      }
    }

    cor[w->id] = PRETO;
  }
}

void imprimeCaminhoLargura(int origem, int v, int antecessor[], int distancia[]) {
  if (origem == v) {
    fprintf (stdout, "%d ", origem);
    return;
  } 
  if (distancia[v] == 0) {
    return;
  } else {
    imprimeCaminhoLargura(origem, antecessor[v], antecessor, distancia);
    fprintf (stdout, "%d " , v);
  }
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

void componentesConexos(Grafo * grafo){
  int id = 0;
  int componenteConexo[grafo->numVertices];

  for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
    componenteConexo[vertice] = -1;
  }

  for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
    if (componenteConexo[vertice] == -1) {
      id++;
      fprintf(stdout, "\nC%d: ", id);
      verificaVerticeComponenteConexo(grafo, componenteConexo, vertice, id);
    }
  }
}

void verificaVerticeComponenteConexo(Grafo * grafo, int componenteConexo[], int vertice, int idComponente) {
  componenteConexo[vertice] = idComponente;
  fprintf(stdout, "%d ", vertice);
  Apontador atual = grafo->listaAdj[vertice];

  while (atual != NULL) {
    if(componenteConexo[atual->vdest] == -1) {
      verificaVerticeComponenteConexo(grafo, componenteConexo, atual->vdest, idComponente);
    }
    atual = atual->prox;
  }
}
