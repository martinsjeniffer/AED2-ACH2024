#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int t = 3;

typedef struct arvbm{
  int nchaves, folha, *chave;
  struct arvbm **filho, *prox;
}TABM;


TABM *cria(int t){
  TABM* novo = (TABM*)malloc(sizeof(TABM));
  novo->nchaves = 0;
  novo->chave =(int*)malloc(sizeof(int)*((t*2)-1));
  novo->folha = 1;
  novo->filho = (TABM**)malloc(sizeof(TABM*)*t*2);
  novo->prox = NULL;
  int i;
  for(i=0; i<(t*2); i++) novo->filho[i] = NULL;
  return novo;
}


TABM *inicializa(void){
  return NULL;
}

void libera(TABM *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) libera(a->filho[i]);
    }
    free(a->chave);
    free(a);
  }
}

TABM *busca(TABM *a, int mat){
  if (!a) return NULL;
  int i = 0;
  while ((i < a->nchaves) && (mat > a->chave[i])) i++;
  if ((i < a->nchaves) && (a->folha) && (mat == a->chave[i])) return a;
  if (a-> folha) return NULL;
  if (a->chave[i] == mat) i++;
  return busca(a->filho[i], mat);
}

void imprime(TABM * no, int andar) {
  if(no) {
    int i, j;
    printf("(");

    for(i = 0; i <= no->nchaves-1; i++) {
      
      imprime(no->filho[i], andar + 1);

      if(i == no->nchaves-1 || (i != 0 && i != no->nchaves)) printf(" ");
      
      printf("%d", no->chave[i]);

      // if(i == no->nchaves-1) printf(" ");
    }
    imprime(no->filho[i], andar + 1);
    printf(")");
  }
}

TABM *divisao(TABM *x, int i, TABM* y, int t){
  TABM *z = cria(t);
  z->folha = y->folha;
  int j;
  if(!y->folha){
    z->nchaves = t-1;
    for(j=0;j<t-1;j++) z->chave[j] = y->chave[j+t];
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  else {
    z->nchaves = t; 
    for(j=0;j < t;j++) z->chave[j] = y->chave[j+t-1];
    y->prox = z;
  }
  y->nchaves = t-1;
  for(j=x->nchaves; j>=i; j--) x->filho[j+1]=x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1];
  x->chave[i-1] = y->chave[t-1];
  x->nchaves++;
  return x;
}


TABM *insere_nao_completo(TABM *x, int mat, int t){
  int i = x->nchaves-1;
  if(x->folha){
    while((i>=0) && (mat < x->chave[i])){
      x->chave[i+1] = x->chave[i];
      i--;
    }
    x->chave[i+1] = mat;
    x->nchaves++;
    return x;
  }
  while((i>=0) && (mat < x->chave[i])) i--;
  i++;
  if(x->filho[i]->nchaves == ((2*t)-1)){
    x = divisao(x, (i+1), x->filho[i], t);
    if(mat > x->chave[i]) i++;
  }
  x->filho[i] = insere_nao_completo(x->filho[i], mat, t);
  return x;
}

TABM *insere(TABM *T, int mat, int t){
  if(busca(T, mat)) return T;
  if(!T){
    T=cria(t);
    T->chave[0] = mat;
    T->nchaves=1;
    return T;
  }
  if(T->nchaves == (2*t)-1){
    TABM *S = cria(t);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = divisao(S,1,T,t);
    S = insere_nao_completo(S, mat, t);
    return S;
  }
  T = insere_nao_completo(T, mat, t);
  return T;
}   

// void remove(TABM* arvore, int mat, int t){
// /*     TABM *a = buscaPai(arvore,mat);
//     int i = 0;
//     while ((i < a->nchaves) && (mat > a->chave[i])) i++;
//     if(a->filho[i + 1]->folha){//caso 1
//         a->filho[i+1] = removeCaso1(a->filho[i+1],mat);
//         return;
//     } */
//     return;
// }

TABM* buscaPai(TABM* a, int mat){
    if (!a) return NULL;
    int i = 0;
    while ((i < a->nchaves) && (mat > a->chave[i])) i++;
    if((a->filho[i]->folha)){
        TABM* filho = a->filho[i];
        int j = 0;
        while ((j < filho->nchaves) && (mat > filho->chave[j])) j++;
        if ((j < filho->nchaves)  && (mat == filho->chave[j])) return a;
    }
    if (a-> folha) return NULL;
    if (a->chave[i] == mat) i++;
    return busca(a->filho[i], mat);
}

/* TABM* removeCaso1(TABM* a, int mat){
    int i = 0;
    while (i<a->nchaves){
        a->chave[i] = a->chave[i+1];
    }
    a->nchaves -= 1;
}
 */
bool leArvorePorArquivo(FILE * arquivo, TABM * a) {
  char opcao;
  int valor;

  if (arquivo == NULL) {
    printf("ERRO [leGrafoPorArquivo linha 13]: O arquivo não existe!\n");
    return false;
  }

  while(fscanf(arquivo, "%c %d", &opcao, &valor) != EOF) {
    switch (opcao) {
      case 'i':
        a = insere(a, valor, t);
      break;

      /* case 'r':
        remove(a, valor, t);
      break; */

      case 'p':
        imprime(a, 0);
        printf("\n");
      break;

      case 'f':
        libera(a);
    }
  }

  fclose(arquivo);
  return true;
}

int main(int argc, char *argv[]) {
  TABM * arvore = inicializa();
  stdin = fopen(argv[1], "r");

  leArvorePorArquivo(stdin, arvore);

  imprime(arvore, 0);
  return 0;
}
