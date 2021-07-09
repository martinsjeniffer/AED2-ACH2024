#define MAX_CHAVES 100

typedef int TipoChave;

typedef struct no {
    TipoChave chave[MAX_CHAVES];
    struct no *filho[MAX_CHAVES + 1];
    int numChaves;
    bool folha;
} NO;