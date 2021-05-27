//
// EP1 - Created by Vanessa Alves do Nascimento - 10882848 on 16/05/21.
//
#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

bool verificaVertice(int vertice, Grafo* grafo) {
    if(vertice < 0) {
        fprintf(stderr, "ERRO: O número de vértices deve ser positivo.\n");
        return false;
    }
    return true;
}

bool inicializaGrafo(Grafo *grafo, int numVertices) {
    int i;

    if(!verificaVertice(numVertices, grafo)) return false;
    
    grafo->numVertices = numVertices;

    if(!(grafo->listaAdj = (Apontador*) calloc(numVertices + 1, sizeof(Apontador)))) {
        fprintf(stderr, "ERRO: Falha na alocação de memória na função inicializaGrafo.\n");
        return false;
    }

    for(i = 0; i < grafo->numVertices; i++) {
        grafo->listaAdj[i] = NULL;
    }

    grafo->numArestas = 0;
    return true;
}

bool existeAresta(int vAtual, int vDestino, Grafo* grafo) {
    Apontador atual;
    atual = grafo->listaAdj[vAtual];
    if(!(verificaVertice(vAtual, grafo) && verificaVertice(vDestino, grafo))) return false;
    
    while(atual != NULL) {
        if(atual->verticeDestino == vDestino) return true; 
        atual = atual->prox;
    }

    return false;
}

void insereAresta(Grafo* grafo, int vAtual, int vDestino, Peso peso) {
    Apontador novaAresta;

    if(!(novaAresta = (Apontador) calloc(1, sizeof(Aresta)))) {
        fprintf(stderr, "ERRO: Falha na alocação de memória na função insereAresta.\n");
        return;
    }
    if(existeAresta(vAtual, vDestino, grafo)){
        fprintf(stderr, "ERRO: Já existe essa aresta.\n");
        return;
    } 
    if(vAtual == vDestino){
        fprintf(stderr, "ERRO: Não pode ter self-loops.\n");
        return;
    } 

    novaAresta->verticeDestino = vDestino;
    novaAresta->peso = peso;
    novaAresta->prox = grafo->listaAdj[vAtual];
    grafo->listaAdj[vAtual] = novaAresta;
    grafo->numArestas++;
    return;
}

Apontador proxListaAdj(int v, Grafo* grafo, Apontador atual) {
    if(atual == NULL) {
        fprintf(stderr, "atual == NULL\n");
        return VERTICE_INVALIDO;
    }
    return(atual->prox);
}

 void leGrafo(char* nomearq, Grafo* grafo) {
    FILE * arquivoGrafo;
    int nVertices, nArestas;
    int v1, v2;
    Peso peso;

    arquivoGrafo = fopen(nomearq, "r");
    if(arquivoGrafo == NULL) {
        fprintf(stderr, "O arquivo não existe!");
        return;
    }

    if (!fscanf(arquivoGrafo, "%d %d", &nVertices, &nArestas)) {
        fprintf(stderr, "Problemas ao ler nVertices e nArestas");
        return;
    }

    printf("\n nVertices nArestas: %d %d\n", nVertices, nArestas);

    // inicializaGrafo(grafo, nVertices);

    while(fscanf(arquivoGrafo, "%d %d %d", &v1, &v2, &peso) != EOF) {
        printf("\n v1: %d v2: %d peso: %d", v1, v2, peso);
        // insereAresta(grafo, v1, v2, peso);
    }

    fclose(arquivoGrafo);
    return;
}

void imprimeGrafo(Grafo* grafo) {
    int i;
    
    printf("%d %d \n", grafo->numVertices, grafo->numArestas);
    
    for (i = 0; i < grafo->numVertices; i++) {
        if(!grafo->listaAdj[i]) {
            printf ("%d %s", i, grafo->listaAdj[i]);
        }
        else {
            printf ("%d %d %d", i, grafo->listaAdj[i]->verticeDestino, grafo->listaAdj[i]->peso);
        }
        printf("\n");
    }

    return;
}
