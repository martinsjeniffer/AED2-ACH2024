#include <stdbool.h> /* Para utilizarmos o bool como "true" ou "false" */

#define MAXNUMVERTICES 100
#define AN -1 /* Aresta nula */

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
bool inicializaGrafo(Grafo* grafo, int nv);
