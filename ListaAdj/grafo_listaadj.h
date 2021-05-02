#include <stdbool.h> /* Para utilizarmos o bool como "true" ou "false" */

#define AN -1 /* Aresta nula */
#define VERTICE_INVALIDO -1 /* numero de vertice invalido ou ausente */

typedef int Peso;

/*
 * Tipo estruturado Aresta
 *      vdest: vertice destino
 *      peso: peso da aresta
 *      str_aresta: ponteiro para a prox aresta
 */
typedef struct str_aresta {
    int vdest;
    Peso peso;
    struct str_aresta * prox;
} Aresta;

/*
 * Tipo estruturado Grafo
 *      listaAdj: vetor de arestas ligadas (cada posicao i contem o ponteiro
 *                para inicio da lista de adjacencia do vertice i)
 *      numVertices: numero total de vertices
 *      numArestas: numero total de arestas
 */
typedef struct {
    Aresta * listaAdj;
    int numVertices;
    int numArestas;
} Grafo;

/*
 * bool inicializaGrafo(Grafo* grafo): 
 * 
 */
bool inicializaGrafo(Grafo * grafo);

/*
 * bool verticeValido(Grafo * grafo):
 * 
 */
bool verticeValido(Grafo * grafo);

/*
 * void insereAresta(Grafo * grafo):
 * 
 */
void insereAresta(Grafo * grafo);

/*
 * bool existeAresta(Grafo * grafo):
 * 
 */
bool existeAresta(Grafo * grafo);

/*
 * bool removeAresta(Grafo * grafo):
 * 
 */
bool removeAresta(Grafo * grafo);

/*
 * bool listaAdjVazia(Grafo * grafo)
 */
bool listaAdjVazia(Grafo * grafo);

/*
 * int proxListaAdj(Grafo * grafo):
 * 
 */
int proxListaAdj(Grafo * grafo);
