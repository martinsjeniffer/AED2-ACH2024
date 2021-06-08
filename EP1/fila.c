#include "fila.h"

PFILA inicializarFila() {
  PFILA fila = (PFILA) malloc(sizeof(FILA));
  PONT cabeca = (PONT) malloc(sizeof(ELEMENTO));
  fila->ini = cabeca;
  fila->numElementos = 0;

  cabeca->ant  = cabeca;
  cabeca->prox = cabeca;
  cabeca->id   = -1;

  return fila;
}

int tamanho(PFILA fila) {
  return fila->numElementos;
}

PONT buscarElemento(PFILA f, int id){
  PONT atual = f->ini;
  while (atual != f->ini) {
    if (atual->id == id) return atual;
    atual = atual->prox;
  }

  return NULL;
}

bool inserirElemento(PFILA f, int id) {
  if(id < 0 || buscarElemento(f,id) != NULL) return false;

  PONT elemento = (PONT)malloc(sizeof(ELEMENTO));
  PONT atual = f->ini->prox;

  while (atual->id != -1) atual = atual->prox;

  elemento->id   = id;
  elemento->ant  = atual->ant;
  elemento->prox = atual;

  atual->ant->prox = elemento;
  atual->ant       = elemento;

  f->numElementos++;
  return true;
}

PONT removePrimeiro(PFILA f) {
  if (tamanho(f) == 0) return NULL;
  PONT resposta;
  PONT primeiroElemento = f->ini->prox;

  primeiroElemento->ant->prox = primeiroElemento->prox;
  primeiroElemento->prox->ant = primeiroElemento->ant;

  resposta = primeiroElemento;

  f->numElementos--;
  return resposta;
}

void exibirLog(PFILA f){
  printf("Log [elementos: %i (alem do no cabeca)]\n", tamanho(f));
  PONT atual = f->ini->prox;
  printf(" [ ");
  while (atual != f->ini){
    printf(" %i", atual->id);
    atual = atual->prox;
  }
  printf(" ]\n");
}