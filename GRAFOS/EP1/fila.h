#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
 * Interface e API de filas feitas durante
 * aulas de AED1 com professor Luciano Digiampietri.
 */
typedef struct aux {
  int id;
  struct aux * ant;
  struct aux * prox;
} ELEMENTO, * PONT;

typedef struct {
  PONT inicio;
  int elementosNaFila;
} FILA, * PFILA;

PFILA inicializarFila();

int tamanho(PFILA fila);

PONT buscarElemento(PFILA fila, int id);

bool inserirElemento(PFILA fila, int id);

PONT retiraPrimeiroElemento(PFILA fila);
