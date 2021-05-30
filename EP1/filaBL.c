#include "filaBL.h"

PFILA inicializarFila() {
	PFILA res = (PFILA) malloc(sizeof(FILA));
	res->inicio = NULL;
	res->fim = NULL;
	return res;
}

int tamanhoFila(PFILA f) {
	PONT atual = f->inicio;
	int tam = 0;
	while (atual) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->inicio;
	 while (atual) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

bool inserirFila(PFILA f, int id) {
	if(id < 0 || buscarID(f,id) != NULL) return false;

	printf("\n *****inserindo o %d na fila", id);

    PONT newPerson = (PONT)malloc(sizeof(ELEMENTO));
    newPerson->id = id;
    newPerson->prox = NULL;

    if(f->inicio == NULL) {
        f->inicio = newPerson;
        return true;
    }
    if(f->fim != NULL) {
		f->fim->prox = newPerson;
        return true;
	}
    f->fim = newPerson;
    
	printf("\n >>>>>FIM->PROX: %d", f->fim->id);
	return true;
}

PONT removePrimeiroFila(PFILA f/* , int* id */) {
    if (tamanhoFila(f) == 0) return NULL;
    // *id = f->inicio->id;
    PONT apagar = f->inicio;
    f->inicio = f->inicio->prox;
    // free(apagar);

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    return apagar;
}

void exibirLog(PFILA f){
	int numElementos = tamanhoFila(f);
	printf("\nLog fila [elementos: %d] - Inicio:", numElementos);
	PONT atual = f->inicio;
	printf(" [ ");
	while (atual){
		printf(" %i", atual->id);
		atual = atual->prox;
	}
	printf(" ]");
	printf("\n\n");
}
