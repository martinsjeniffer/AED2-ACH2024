#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaadj.h"
#include "fila.h"

bool inicializaGrafo(Grafo * grafo, int numVertices) {
  if (numVertices <= 0) {
    fprintf(stderr, "ERRO [inicializaGrafo linha 08]: Numero de vertices deve ser positivo.\n");
    return false;
  }

  grafo->numVertices = numVertices;

  if (!(grafo->listaAdj = (Apontador*) calloc(numVertices + 1, sizeof(Apontador)))) {
    fprintf(stderr, "ERRO [inicializaGrafo linha 15]: Falha na alocacao de memoria na funcao inicializaGrafo\n");
    return false;
  }

  for (int i = 0; i < grafo->numVertices; i++) grafo->listaAdj[i] = NULL;

  grafo->numArestas = 0;
  return true;
};

bool verticeValido(Grafo * grafo, int vertice) {
  if (vertice > grafo->numVertices) {
    fprintf(stderr, "ERRO [verticeValido linha 27]: Numero do vertice (%d) maior que o numero total de vertices (%d)\n", vertice, grafo->numVertices);
    return false;
  }

  if (vertice < 0) {
    fprintf(stderr, "ERRO [verticeValido linha 32]: Numero do vertice (%d) deve ser positivo\n", vertice);
    return false;
  }

  return true;
}

bool insereAresta(Grafo * grafo, int v1, int v2, Peso peso) {
  Apontador novaAresta;

  if(v1 == v2){
    fprintf(stderr, "ERRO [insereAresta linha 43]: Grafo nao direcionado nao tem self-loop.\n");
    return false;
  } 

  if (!verticeValido(grafo, v1) || !verticeValido(grafo, v2)) {
    fprintf(stderr, "ERRO [insereAresta linha 48]: Vertice invalido.\n");
    return false;
  }

  if (existeAresta(grafo, v1, v2)) {
    fprintf(stderr, "ERRO [insereAresta linha 52]: A aresta (%d,%d) ja existe.\n", v1, v2);
    return false;
  }

  if (!(novaAresta = (Apontador) calloc(1, sizeof(Apontador)))) {
    fprintf(stderr, "ERRO [insereAresta linha 57]: Falha na alocacao de memoria.\n");
    return false;
  }

  novaAresta->vertice = v2;
  novaAresta->peso = peso;
  novaAresta->arestaPrincipal = !existeAresta(grafo, v2, v1);
  novaAresta->prox = grafo->listaAdj[v1];
  grafo->listaAdj[v1] = novaAresta;

  if (!existeAresta(grafo, v2, v1)) grafo->numArestas++;

  return true;
}

bool existeAresta(Grafo * grafo, int v1, int v2) {
  Apontador aresta;

  if (!verticeValido(grafo, v1) && !verticeValido(grafo, v2)) return false;
  aresta = grafo->listaAdj[v1];

  while (aresta != NULL && aresta->vertice != v2)
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

  for (vertice = 0; vertice <= grafo->numVertices; vertice++) {
    while ((aresta = grafo->listaAdj[vertice]) != NULL) {
      grafo->listaAdj[vertice] = aresta->prox;
      aresta->prox = NULL;
      free(aresta);
    }
  }

  grafo->numVertices = 0;
  free(grafo->listaAdj); // pois o vetor tb tem alocacao dinamica
  grafo->listaAdj = NULL;
}

void imprimeGrafo(Grafo* grafo) {
  Apontador atual;
  fprintf(stdout, "%d %d", grafo->numVertices, grafo->numArestas);

  for (int i = 0; i < grafo->numVertices; i++) {
    atual = primeiroListaAdj(grafo, i);

    if (!listaAdjVazia(grafo, i)) {
      while(atual != NULL) {
        if (atual->arestaPrincipal) fprintf (stdout, "\n%d %d %d", i, atual->vertice, atual->peso);
        atual = proxListaAdj(grafo, i, atual);
      }
    }
  }

  return;
}

void visitaBP(int v, Grafo * grafo, int * tempo, int cor[], int tdesc[], int tterm[], int antecessor[], int menorTempoVertRetorno[], int vertArticulacao[]) {
  Apontador atual;
  cor[v] = CINZA; 
  tdesc[v] = menorTempoVertRetorno[v] = ++(*tempo);

  fprintf(stdout, "%d ", v);

  if (!listaAdjVazia(grafo, v)) {
    atual = primeiroListaAdj(grafo, v);

    while(atual != NULL) {
      if (cor[atual->vertice] == BRANCO) {
        antecessor[atual->vertice] = v;
        visitaBP(atual->vertice, grafo, tempo, cor, tdesc, tterm, antecessor, menorTempoVertRetorno, vertArticulacao);

        menorTempoVertRetorno[v] = menorTempoVertRetorno[v] < menorTempoVertRetorno[atual->vertice] ? menorTempoVertRetorno[v] : menorTempoVertRetorno[atual->vertice];

        // iremos considerar a raiz da arvore de descoberta como vert de articulacao?

        // if (parent[u] == NIL && children > 1)
        //   ap[u] = true;
        
        if (antecessor[v] != -1 && menorTempoVertRetorno[atual->vertice] >= tdesc[v])
          vertArticulacao[v] = true;
      } else if (atual->vertice != antecessor[v]) {
        menorTempoVertRetorno[v] = menorTempoVertRetorno[v] < tdesc[atual->vertice] ? menorTempoVertRetorno[v] : tdesc[atual->vertice];
      }

      atual = proxListaAdj(grafo, v, atual);
    }
  }

  tterm[v] = ++(*tempo);
  cor[v] = PRETO;
}


void visitaLargura(int origem, Grafo *grafo, int cor[], int antecessor[], int distancia[]) {
  cor[origem] = CINZA;
  distancia[origem] = 0;
  antecessor[origem] = origem;

  PFILA Fila = inicializarFila();
  PONT elemento;
  Apontador atual;
  inserirElemento(Fila, origem);

  while (Fila->numElementos != 0) {
    elemento = retiraPrimeiroElemento(Fila);
    fprintf(stdout, "%d ", elemento->id);

    if (!listaAdjVazia(grafo, elemento->id)) {
      atual = grafo->listaAdj[elemento->id];
      while(atual != NULL) {
        if(cor[atual->vertice] == BRANCO) {
          cor[atual->vertice] = CINZA;
          antecessor[atual->vertice] = elemento->id;
          distancia[atual->vertice] = distancia[elemento->id] + 1;
          inserirElemento(Fila, atual->vertice);
        }
        atual = atual->prox;
      }
    }

    cor[elemento->id] = PRETO;
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
    if(componenteConexo[atual->vertice] == -1) {
      verificaVerticeComponenteConexo(grafo, componenteConexo, atual->vertice, idComponente);
    }
    atual = atual->prox;
  }
}
