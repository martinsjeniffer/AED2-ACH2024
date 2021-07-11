#include <stdio.h>
#include <stdlib.h>
#include "arvoresB_classica.h"

bool criaArvoreB(ArvB * T) {
  NO * x;

  if (!(x = (NO *) malloc(sizeof(NO)))) {
    printf("ERRO [criaArvoreB]: Falha na alocacao de memoria na funcao.\n");
    return false;
  }

  x->folha = true;
  x->numChaves = 0;
  escreveNoDisco(x);
  T->raiz = x;

  return true;
}

void escreveNoDisco(NO * x) {
  /* codigo especifico para o SO */
  /* Na verdade precisa saber onde escrever.
    Aqui tem que alocar um novo bloco no disco (ex: 350) e
    efetuar um seek(350*4Kb)+ write(x)(assumindo tam do bloco = 4Kb) */
}

void leNoDisco (int x) {
  /* codigo especifico para o SO */
}

NO * busca (NO * x, int k) {
  int i = 0;
  while (i <= x->numChaves && k > x->chave[i]) {
    i++;
  }

  if (i <= x->numChaves && k == x->chave[i]) {
    return x; // par ordenado (x,i)
  }

  if (x->folha) {
    return NULL;
  }
  else {
    leNoDisco(x->filho[i]);
    return busca(x->filho[i], k);
  }
}

void BTreeSplitChild(NO * x, int i, NO * y) {
  // ALOCA E INICIALIZA O z
  NO * z;
  z = (NO *) malloc(sizeof(NO));

  z->folha = y->folha;
  z->numChaves = t - 1;

  // revisar esses for's, já que iniciaremos
  // sempre da posicao 0 e nao da 1, como aqui descrito
  for (int j = 1; j <= t -1; j++) {
    z->filho[j] = y->filho[j+1];
  }

  if (!y->folha) {
    for (int j = 1; j <= t; j++) {
      z->filho[j] = y->filho[j+1];
    }
  }

  // AJUSTE NO y
  y->numChaves = t - 1;

  // AJUSTE NO x
  for (int j = x->numChaves + 1; j > i + 1; j--) {
    x->filho[j+1] = x->filho[j];
  }

  x->filho[i+1] = z;

  for (int j = x->numChaves; j > i; j--) {
    x->chave[j+1] = x->chave[j];
  }

  x->chave[i] = y->chave[t];
  x->numChaves++;

  escreveNoDisco(y);
  escreveNoDisco(z);
  escreveNoDisco(x);
}

// nao sabemos se no esta cheio ou nao
void BTreeInsert(ArvB * T, int k) {
  NO * r = T->raiz;

  if (r->numChaves == 2*t - 1) {
    NO * s;

    s = (NO *) malloc(sizeof(NO));
    T->raiz = s;
    s->folha = false;
    s->filho[0] = r;
    BTreeSplitChild(s, 1, r);
    BTreeInsertNonFull(s,k);
  }
  else {
    BTreeInsertNonFull(r,k);
  }
}

void BTreeInsertNonFull(NO * x, int k) {
  int i = x->numChaves;
  if (x->folha) {
    while(i >= 1 && k < x->chave[i]) {
      x->chave[i+1] = x->chave[i];
      i--;
    }

    x->chave[i+1] = k;
    x->numChaves++;
    escreveNoDisco(x);
  } else {
    while (i >= 1 && k < x->chave[i]) { i--; }
    i++;
    escreveNoDisco(x->filho[i]);

    if (x->filho[i]->numChaves == 2*t - 1) {
      BTreeSplitChild(x, i, x->filho[i]);
      if (k > x->chave[i]) { i++; }
    }
    BTreeInsertNonFull(x->filho[i], k);
  }
}

void BTreeDeleteFromRoot (ArvB * T, int k) {
  NO * r = T->raiz;

  if (r->numChaves == 0) return; // arvore vazia
  else BTreeDelete(r, k);

  if (r->numChaves == 0  && !r->folha) {
    T->raiz = r->filho[0];
    free(r);
  }
}

