#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct aux {
  int id;
  struct aux* prox;
} ELEMENTO, * PONT;

typedef struct {
  PONT inicio;
  PONT fim;
} FILA, * PFILA;

PFILA inicializarFila();

int tamanhoFila(PFILA f);

PONT buscarID(PFILA f, int id);

bool inserirFila(PFILA f, int id);

PONT removePrimeiroFila(PFILA f);

void exibirLog(PFILA f);