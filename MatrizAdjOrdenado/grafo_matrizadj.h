#include <stdbool.h> /* Para utilizarmos o bool como "true" ou "false" */

#define MAXNUMVERTICES 100
#define AN -1 /* Aresta nula */
#define VERTICE_INVALIDO -1 /* numero de vertice invalido ou ausente */

typedef int Peso;
typedef struct {
    Peso mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
    int numVertices;
    int numArestas;
} Grafo;

/*
 * bool inicializaGrafo(Grafo* grafo, int nv): 
 * 
 * Inicializa um grafo com nv vertices.
 * Preenche as celulas com AN (representando a ausencia de arestas).
 * Vertices vao de 1 a nv
 * Retorna true se inicializou com sucesso e false caso contrário
 */
bool inicializaGrafo(Grafo * grafo, int nv);

/*
 * bool verticeValido(Grafo * grafo, int vertice):
 * 
 * Verifica que o numero do vertice eh valido no grafo.
 */
bool verticeValido(Grafo * grafo, int vertice);

/*
 * void insereAresta(Grafo * grafo, int v1, int v2, Peso peso):
 * 
 * Insere a aresta entre o vértice 1 (v1) e o vértice 2 (v2).
 */
void insereAresta(Grafo * grafo, int v1, int v2, Peso peso);

/*
 * bool existeAresta(Grafo * grafo, int v1, int v2):
 * 
 * Retorna true se existe a aresta e false caso contrário
 */
bool existeAresta(Grafo * grafo, int v1, int v2);

/*
 * bool removeAresta(Grafo * grafo, int v1, int v2):
 * 
 * Remove a aresta (v1, v2) do grafo colocando AN em sua celula
 * Se a aresta existia, coloca o peso dessa aresta em "peso" e retorna true
 * caso contrario, retorna false e "peso" é inalterado
 */
bool removeAresta(Grafo * grafo, int v1, int v2, Peso * peso);

/*
 * bool listaAdjVazia(Grafo * grafo, int v):
 * 
 * Retorna true se a lista de adjacentes de um dado vertice eh vazia
 * e false caso contrario
 */
bool listaAdjVazia(Grafo * grafo, int vertice);

/*
 * int proxListaAdj(Grafo * grafo, int vertice, int atual):
 * 
 * Trata-se de um iterador sobre a lista de adjacencia do vertice
 * Retorna o proximo vertice adjacente a v, partindo do vertice "atual"
 * adjacente a v ou -1 se a lista de adjacencia tiver terminado
 * sem um novo proximo
 */
int proxListaAdj(Grafo * grafo, int vertice, int atual);
