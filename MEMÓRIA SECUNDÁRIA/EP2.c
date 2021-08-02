#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define t 3
#define MAX_CHAVE 2 * t - 1
#define MAX_FILHOS 2 * t

typedef struct arvbm{
  int numChaves, folha, *chave;
  struct arvbm **filho, *prox;
} NO;

NO * criaNo(){
  NO * novoNo = (NO *) malloc (sizeof(NO));

  novoNo->chave = (int *) malloc (sizeof(int) * MAX_CHAVE);
  novoNo->folha = true;
  novoNo->filho = (NO **) malloc(sizeof(NO *) * MAX_FILHOS);
  novoNo->prox  = NULL;

  novoNo->numChaves = 0;

  for(int i = 0; i < MAX_FILHOS; i++)
    novoNo->filho[i] = NULL;

  return novoNo;
}

NO * inicializa(){
  return NULL;
}

NO * busca(NO * x, int key){
  if (!x) return NULL;

  int i = 0;

  while ((i <= x->numChaves) && (key > x->chave[i])) {
    i++;
  }

  if ((i <= x->numChaves) && (x->folha) && (key == x->chave[i])) {
    return x;
  }

  if (x-> folha) return NULL;

  if (x->chave[i] == key) i++;

  return busca(x->filho[i], key);
}

void imprimeArvore(NO * no, int andar) {
  if (no) {
    int i;
    fprintf(stdout, "(");
    for(i = 0; i <= no->numChaves - 1; i++) {
      imprimeArvore(no->filho[i], andar + 1);

      if (i == no->numChaves - 1 || (i != no->numChaves && i != 0)){
        fprintf(stdout, " ");
      }

      fprintf(stdout, "%d", no->chave[i]);
    }
    imprimeArvore(no->filho[i], andar + 1);
    fprintf(stdout, ")");
  }
}

NO * splitNode(NO * noNaoCheio, int index, NO * noCheio){
  NO * novo = criaNo();
  novo->folha = noCheio->folha;

  if (!noCheio->folha) {
    novo->numChaves = t - 1;

    for(int j = 0; j < t - 1; j++) {
      novo->chave[j] = noCheio->chave[j + t];
    }

    for(int j = 0; j < t; j++){
      novo->filho[j] = noCheio->filho[j+t];
      noCheio->filho[j + t] = NULL;
    }
  } else {
    novo->numChaves = t;

    for(int j = 0; j < t; j++) {
      novo->chave[j] = noCheio->chave[j + t - 1];
    }

    noCheio->prox = novo;
  }

  noCheio->numChaves = t - 1;

  for(int j = noNaoCheio->numChaves; j >= index; j--) {
    noNaoCheio->filho[j + 1] = noNaoCheio->filho[j];
  }

  noNaoCheio->filho[index] = novo;
  for(int j = noNaoCheio->numChaves; j >= index; j--) {
    noNaoCheio->chave[j] = noNaoCheio->chave[j - 1];
  }

  noNaoCheio->chave[index - 1] = noCheio->chave[t - 1];
  noNaoCheio->numChaves++;

  return noNaoCheio;
}

NO * insertNaoCheia(NO * noNaoCheio, int key){
  int i = noNaoCheio->numChaves - 1;

  if(noNaoCheio->folha){
    while(i >= 0 && (key < noNaoCheio->chave[i])){
      noNaoCheio->chave[i + 1] = noNaoCheio->chave[i];
      i--;
    }

    noNaoCheio->chave[i + 1] = key;
    noNaoCheio->numChaves++;

    return noNaoCheio;
  }

  while(i >= 0 && (key < noNaoCheio->chave[i])) { i--; }
  i++;

  if(noNaoCheio->filho[i]->numChaves == MAX_CHAVE){
    noNaoCheio = splitNode(noNaoCheio, i + 1, noNaoCheio->filho[i]);

    if(key > noNaoCheio->chave[i]) i++;
  }

  noNaoCheio->filho[i] = insertNaoCheia(noNaoCheio->filho[i], key);
  return noNaoCheio;
}

NO * insere(NO * node, int key){
  if (busca(node, key)) return node;

  if (!node){
    node = criaNo();
    node->chave[0] = key;
    node->numChaves = 1;
    return node;
  }

  bool raizCheia = node->numChaves == MAX_CHAVE;
  if (raizCheia) {
    NO * novoNo = criaNo();

    novoNo->folha = 0;
    novoNo->filho[0] = node;

    novoNo = splitNode(novoNo, 1, node);
    novoNo = insertNaoCheia(novoNo, key);
    return novoNo;
  }

  node = insertNaoCheia(node, key);
  return node;
}

NO * buscaPai(NO * a, int key){
    if (!a) return NULL;
    int i = 0;
    while ((i < a->numChaves) && (key > a->chave[i])) i++;
    if((a->filho[i]->folha)){
        NO* filho = a->filho[i];
        int j = 0;
        while ((j < filho->numChaves) && (key > filho->chave[j])) j++;
        if ((j < filho->numChaves)  && (key == filho->chave[j])) return a;
    }
    if (a-> folha) return NULL;
    if (a->chave[i] == key) i++;
    return busca(a->filho[i], key);
}

void libera(NO * node){
  if (node){
    if (!node->folha) {
      for(int i = 0; i <= node->numChaves; i++)
        libera(node->filho[i]);
    }

    free(node->chave);
    free(node);
  }
}

bool leArvorePorArquivo(FILE * arquivo, NO * arvore) {
  char comando;
  int chave;

  if (arquivo == NULL) {
    printf("ERRO [leArvorePorArquivo]: O arquivo não existe!\n");
    return false;
  }

  while(fscanf(arquivo, "%c %d", &comando, &chave) != EOF) {
    switch (comando) {
      case 'i':
        arvore = insere(arvore, chave);
      break;
      /* case 'r':
        remove(a, chave, t);
      break; */
      case 'p':
        imprimeArvore(arvore, 0);
        fprintf(stdout, "\n");
      break;
      case 'f':
        libera(arvore);
        fclose(arquivo);
        return true;
    }
  }

  fclose(arquivo);
  return true;
}

int main(int argc, char *argv[]) {
  NO * arvore = inicializa();
  stdin = fopen(argv[1], "r");
  stdout = fopen(argv[2], "w");

  leArvorePorArquivo(stdin, arvore);

  return 0;
}
