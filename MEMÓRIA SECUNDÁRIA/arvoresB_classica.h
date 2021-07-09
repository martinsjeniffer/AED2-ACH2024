#include <stdbool.h>

#define MAX_CHAVES 100
#define t 2 /* grau minimo da arvore*/

typedef int TipoChave;

typedef struct str_no {
  TipoChave chave[2 * t - 1];
  struct str_no * filho[2 * t];
  int numChaves;
  bool folha;
} NO;

typedef struct {
  NO * raiz; 
} ArvB;