#include <stdbool.h> /* Para utilizarmos o bool como "true" ou "false" */

#define AN -1 /* Aresta nula */
#define VERTICE_INVALIDO -1 /* numero de vertice invalido ou ausente */
#define MAX_VERTICES 100

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define INFINITO 1000

/*
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
 *      arestaPrincipal: indicacao se eh a primeira aresta inserida
 *          entre dois vertices (v1, v2).
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
 *      Vertices vao de 0 a nv.
 */
bool inicializaGrafo(Grafo * grafo, int nv);

/*
 * bool verticeValido(Grafo * grafo, int vertice):
 *      Verifica que o numero do vertice eh valido no grafo.
 */
bool verticeValido(Grafo * grafo, int vertice);

/*
 * bool insereAresta(Grafo * grafo, int v1, int v2, Peso peso):
 *      insere a aresta (v1, v2) com peso "peso" no grafo.
 *      Tambem identifica se a aresta devera ser a aresta principal
 *      caso nao exista uma aresta (v2, v1) no grafo.
 * 
 *      Retorna true se houver sucesso na insercao e false caso contrario
 */
bool insereAresta(Grafo * grafo, int v1, int v2, Peso peso);

/*
 * bool existeAresta(Grafo * grafo, int v1, int v2):
 *      Verifica se a aresta (v1, v2) ja existe no grafo.
 * 
 *      Retorna true caso ja exista e false caso contrario.
 */
bool existeAresta(Grafo * grafo, int v1, int v2);

/*
 * bool listaAdjVazia(Grafo * grafo, int vertice):
 *      Retorna true se a lista de adjacentes de um dado vertice
 *      eh vazia, false caso contrario
 */
bool listaAdjVazia(Grafo * grafo, int vertice);

/*
 * Aresta * primeiroListaAdj(Grafo * grafo, int vertice):
 *      Retorna o endereco do primeiro vertice adjacente
 *      ao parametro 'vertice'.
 */
Apontador primeiroListaAdj(Grafo * grafo, int vertice);

/*
 * Aresta * proxListaAdj(Grafo * grafo, Aresta * atual):
 *      retorna o proximo vertice adjacente de um dado vertice 
 *      (proximo em relacao a um adjacente "atual", passado como parametro)
 *      na primeira chamada retorna o primeiro.
 */
Apontador proxListaAdj(Grafo * grafo, Aresta * atual);

/*
 * void liberaGrafo(Grafo * grafo):
 *      Libera o vetor de apontadores de listas de adjacencias.
 */
void liberaGrafo(Grafo * grafo);

/*
 * void imprimeGrafo(Grafo* grafo):
 *      Imprime o numero de vertices e numero de arestas do grafo na primeira linha
 *      e, apos isso, imprime os vertices, em ordem crescente e os
 *      seus adjacentes.
 *      Essa funcao apenas imprime arestas principais, ou seja
 *      ignora arestas duplicadas que sao geradas por conta do grafo ser nao ordenado.
 */
void imprimeGrafo(Grafo* grafo);
