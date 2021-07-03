#include "fila.h"

/*
 * Interface e API de filas feitas durante
 * aulas de AED1 com professor Luciano Digiampietri.
 */
PFILA inicializarFila() {
  PFILA fila = (PFILA) malloc(sizeof(FILA));
  PONT cabeca = (PONT) malloc(sizeof(ELEMENTO));
  fila->inicio = cabeca;
  fila->elementosNaFila = 0;

  cabeca->ant = cabeca;
  cabeca->prox = cabeca;
  cabeca->id = -1;

  return fila;
}

int tamanho(PFILA fila) {
  return fila->elementosNaFila;
}

PONT buscarElemento(PFILA fila, int id) {
  PONT atual;

  for (atual = fila->inicio; atual != fila->inicio; atual = atual->prox) {
    if (atual->id == id) return atual;
  }

  return NULL;
}

bool inserirElemento(PFILA fila, int id) {
  if (id < 0) {
    fprintf(stderr, "ERRO [fila linha 37]: Id do elemento deve ser positivo.\n");
    return false;
  }

  if (buscarElemento(fila, id) != NULL) {
    fprintf(stderr, "ERRO [fila linha 41]: O id (%d) já consta na fila.\n", id);
    return false;
  }

  PONT elemento = (PONT)malloc(sizeof(ELEMENTO));
  PONT atual = fila->inicio->prox;

  while (atual->id != -1) atual = atual->prox;

  elemento->id = id;
  elemento->ant = atual->ant;
  elemento->prox = atual;

  atual->ant->prox = elemento;
  atual->ant  = elemento;

  fila->elementosNaFila++;
  return true;
}

PONT retiraPrimeiroElemento(PFILA fila) {
  if (tamanho(fila) == 0) return NULL;

  PONT resposta;
  PONT primeiroElemento = fila->inicio->prox;

  primeiroElemento->ant->prox = primeiroElemento->prox;
  primeiroElemento->prox->ant = primeiroElemento->ant;

  resposta = primeiroElemento;

  fila->elementosNaFila--;
  return resposta;
}
