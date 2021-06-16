#include <stdbool.h> /* Para utilizarmos o bool como "true" ou "false" */

#define AN -1 /* Aresta nula */
#define VERTICE_INVALIDO -1 /* numero de vertice invalido ou ausente */
#define MAX_VERTICES 100

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define INFINITO 1000

/**
 * Macro que utiliza do operador ternario
 * para retornar o valor minimo entre dois valores a e b.
 */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef int Peso;

/*
 * Tipo estruturado Aresta
 *      vertice: vertice destino
 *      peso: peso da aresta
 *      str_aresta: ponteiro para a prox aresta
 */
typedef struct str_aresta {
    int vertice;
    Peso peso;
    struct str_aresta * prox;
    bool arestaPrincipal;
} Aresta;

typedef Aresta * Apontador;

/*
 * Tipo estruturado Grafo
 *      listaAdj: vetor de arestas ligadas (cada posicao i contem o ponteiro
 *                para inicio da lista de adjacencia do vertice i)
 *      numVertices: numero total de vertices
 *      numArestas: numero total de arestas
 */
typedef struct {
    Apontador * listaAdj;
    int numVertices;
    int numArestas;
} Grafo;

/*
 * bool inicializaGrafo(Grafo* grafo, int nv):
 *      Cria um grafo com nv vcrtices
 *      Aloca espaco para o vetor de apontadores de listas de adjacencias
 *      e, para cada vertice, inicializa o apontador de sua lista de adjacencia
 * 
 *      Retorna true se houver sucesso e false caso contrario
 *      Vertices vao de 1 a nv.
 */
bool inicializaGrafo(Grafo * grafo, int nv);

/*
 * bool verticeValido(Grafo * grafo, int vertice):
 * 
 * Verifica que o numero do vertice eh valido no grafo.
 */
bool verticeValido(Grafo * grafo, int v);

/*
 * bool insereAresta(Grafo * grafo, int v1, int v2, Peso peso):
 *    insere a aresta (v1, v2) com peso "peso" no grafo.
 *    nao verifica se a aresta ja existia (isso deve ser feito pelo
 *    usuario antes, se necessario)
 */
bool insereAresta(Grafo * grafo, int v1, int v2, Peso peso);

/*
 * bool existeAresta(Grafo * grafo, int v1, int v2):
 */
bool existeAresta(Grafo * grafo, int v1, int v2);

/*
 * bool removeAresta(Grafo * grafo, int v1, int v2)
 *    retorna false se a aresta ja nao existia
 */
bool removeAresta(Grafo * grafo, int v1, int v2, Peso * peso);

/*
 * bool listaAdjVazia(Grafo * grafo, int v):
 *      true se a lista de adjacentes de um dado vertice
 *      eh vazia, false caso contrario
 */
bool listaAdjVazia(Grafo * grafo, int v);

/*
 * Aresta * primeiroListaAdj(Grafo * grafo, int v):
 *      returna o endereco do primeiro vertice adjacente a v
 */
Apontador primeiroListaAdj(Grafo * grafo, int v);

/*
 * Aresta * proxListaAdj(Grafo * grafo, int v, Aresta * atual):
 *      retorna o proximo vertice adjacente de um dado vertice 
 *      (proximo em relacao a um adjacente "atual", passado como parametro)
 *      na primeira chamada retorna o primeiro.
 */
Apontador proxListaAdj(Grafo * grafo, int v, Aresta * atual);

void liberaGrafo(Grafo * grafo);

void imprimeGrafo(Grafo* grafo);

void visitaProfundidade(int vertice, Grafo * grafo, int * tempo, int cor[], int tdesc[], int antecessor[], int menorTempoVertRetorno[], int vertArticulacao[]);

void visitaLargura(int origem, Grafo *grafo, int cor[], int antecessor[], int distancia[]);

void imprimeCaminhoLargura(int u, int v, int antecessor[], int distancia[]);

void imprimeCaminhoBuscaProf(int origem, int v, int antecessor[]);

void componentesConexos(Grafo * grafo);

void verificaVerticeComponenteConexo(Grafo * grafo, int componenteConexo[], int vertice, int idComponente);