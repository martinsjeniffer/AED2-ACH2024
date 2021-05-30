#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaadj.h"
#include "filaBL.h"

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
  novaAresta->prox = grafo->listaAdj[v1];
  grafo->listaAdj[v1] = novaAresta;

  // novaAresta->prox = grafo->listaAdj[v2];
  // grafo->listaAdj[v2] = novaAresta;

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

bool removeAresta(Grafo * grafo, int v1, int v2, Peso * peso) {
  if (!existeAresta(grafo, v1, v2)) return false;

  Apontador atual, ant;
  atual = grafo->listaAdj[v1];

  while (atual != NULL && atual->vdest != v2) {
    ant = atual;
    atual = atual->prox;
  }

  if (atual != NULL) {
    if (grafo->listaAdj[v1] == atual) grafo->listaAdj[v1] = atual->prox;
    else ant->prox = atual->prox;

    *peso = atual->peso;
    atual->prox = NULL;
    free(atual);
    atual = NULL; // boa pratica
    grafo->numArestas--;
    return true;
  }

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
  printf("%d %d", grafo->numVertices, grafo->numArestas);
  
  for (int i = 0; i < grafo->numVertices; i++) {
    atual = grafo->listaAdj[i];

    if (!listaAdjVazia(grafo, i)) {
      // TODO: usar o METODO primeiraListaAdj & proxListaAdj
      while(atual != NULL) {
        printf ("\n%d %d %d", i, atual->vdest, atual->peso);
        atual = atual -> prox;
      }
    }
  }

  return;
}

void buscaProfundidade(Grafo* grafo) {
  /* 
  * Aloca vetores 
  *      cor,
  *      tdesc,
  *      tterm,
  *      antecessor,
  *          com tamanho grafo->nrVertices
  *      tempo = 0;
  */
  int numVertices = grafo->numVertices;
  int cor[numVertices], tdesc[numVertices], tterm[numVertices], antecessor[numVertices];
  int tempo = 0;
  /*
  * Para cada vertice v 
  *      cor[v] ← branco;
  *      tdesc[v] = tterm[v] = 0;
  *      antecessor[v] = - 1;
  */
  for (int v = 0; v < numVertices; v++) {
    cor[v] = BRANCO;
    tdesc[v] = tterm[v] = 0;
    antecessor[v] = -1;
  }
  printf("\nBP: \n");

  /*
  * Para cada vertice v 
  *      Se cor[v] = branco 
  *          visitaBP(v, grafo, &tempo, cor, tdesc, tterm, antecessor);
  */
  for (int v = 0; v < numVertices; v++)
    if (cor[v] == BRANCO) visitaBP(v, grafo, &tempo, cor, tdesc, tterm, antecessor);

  printf("\n");
}

void visitaBP(int v, Grafo * grafo, int * tempo, int cor[], int tdesc[], int tterm[], int antecessor[]) {
  Apontador atual;
  cor[v] = CINZA; 
  tdesc[v] = ++(*tempo);
  printf("%d ", v);
  // printf("\nv ficou CINZA: %d \ntdesc[%d]: %d", v, v, tdesc[v]); //Printamos o vértice que foi descoberto

  if (!listaAdjVazia(grafo, v)) {
    atual = grafo->listaAdj[v]; //Primeiro da lista de adjacencia é o 1

    while(atual != NULL) { // Se 1 é diferente de null, ele passa por aqui

      // printf("\nADJ do %d: %d", v, atual->vdest);
      if (cor[atual->vdest] == BRANCO) { // lembrando que o atencessor do 1 é o 0
        antecessor[atual->vdest] = v;

        //aqui temos uma recursão que ira voltar para a linha 44
        visitaBP(atual->vdest, grafo, tempo, cor, tdesc, tterm, antecessor);
      }
      atual = atual->prox;
    }
  }

  tterm[v] = ++(*tempo);
  // printf("\nFICOU PRETO: %d tterm[%d]: %d\n", v, v, tterm[v]);
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

    /*
     * Para cada vertice v 
     *      cor[v] ← branco;
     *      antecessor[v] ← - 1;
     *      distancia[v] ← ∞;
     */
    for (int v = 0; v <= numVertices; v++) {
        cor[v] = BRANCO;
        antecessor[v] = -1;
        distancia[v] = INFINITO;
    }
    /*
     * Para cada vertice v 
     *      se cor[v] = branco
     *          visitaLargura(v, grafo, cor, antecessor, distancia);
     */
    for (int v = 0; v < numVertices; v++) {
        if (cor[v] == BRANCO)
            visitaLargura(v, grafo, cor, antecessor, distancia);
    }
    for (int v = 0; v < numVertices; v++) {
      imprimeCaminhoLargura(0, v, antecessor, distancia);
      printf("\n");
    }
}

void visitaLargura(int origem, Grafo *grafo, int cor[], int antecessor[], int distancia[]) {
  cor[origem] = CINZA;
  distancia[origem] = 0;

  printf("\norigem: %d", origem);
  PFILA Fila = inicializarFila();
  PONT w;
  Apontador atual;
  inserirFila(Fila, origem);

  while (tamanhoFila(Fila) != 0) {
    exibirLog(Fila);
    w = removePrimeiroFila(Fila);

    printf("\nremovePrimeiroFila = w = %d", w->id);

    if (!listaAdjVazia(grafo, w->id)) {
      atual = grafo->listaAdj[w->id];
      while(atual != NULL) {
        printf("\n ADJ DO %d: %d",  w->id, atual->vdest);

        if(cor[atual->vdest] == BRANCO) {
          printf("\n %d FICOU CINZA", atual->vdest);
          cor[atual->vdest] = CINZA;
          antecessor[atual->vdest] = w->id;
          distancia[atual->vdest] = distancia[w->id] + 1;
          inserirFila(Fila, atual->vdest);

          printf("\nACABOU DE INSERIR: ");
          exibirLog(Fila);
        }
        atual = atual->prox;
      }
    }

    cor[w->id] = PRETO;
    printf("\n w->id: %d FICOU Preto ", w->id);
  }

  printf("\nFILA VAZIA!");
}

void imprimeCaminhoLargura(int origem, int v, int antecessor[], int distancia[]) {
    if (distancia[v] == INFINITO) {
        printf ("Nao existe caminho de %d ate %d" , origem, v);
        return;
    }
    if (origem == v) {
        printf ("%d ", origem);
        return;
    } else {
        imprimeCaminhoLargura(origem, antecessor[v], antecessor, distancia);
        printf ( "%d " , v);
    }
}