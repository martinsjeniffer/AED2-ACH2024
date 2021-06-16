#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct aux {
  int id;
  struct aux* ant;
  struct aux* prox;
} ELEMENTO, * PONT;

typedef struct {
  PONT ini;
  int numElementos;
} FILA, * PFILA;

PFILA inicializarFila();

int tamanho(PFILA fila);

PONT buscarElemento(PFILA f, int id);

bool inserirElemento(PFILA f, int id);

PONT retiraPrimeiroElemento(PFILA f);

void exibirLog(PFILA f);