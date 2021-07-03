#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int numVertices;
    bool mat[10][10]; 
    } Grafo; 

void serializa_opcao1(Grafo* g){

    FILE *fp;

    fp = fopen( "serializacao.txt" , "w" );
    fwrite(g, sizeof(Grafo), 1, fp);

    fclose(fp);
}

void desserializa_opcao1(Grafo* g){

    FILE *fp;

    fp = fopen( "serializacao.txt" , "r" );
    fread(g, sizeof(Grafo), 1, fp);

    fclose(fp);
}


int main (void){
    /* grafo nao ponderado */ 
    Grafo g;
    g.numVertices = 6;
    g.mat[0][0] = false;g.mat[0][1] = true;g.mat[0][2] = false;g.mat[0][3] = true;g.mat[0][4] = false;g.mat[0][5] = false;
    g.mat[1][0] = false;g.mat[1][1] = false;g.mat[1][2] = true;g.mat[1][3] = true;g.mat[1][4] = false;g.mat[1][5] = false;
    g.mat[2][0] = false;g.mat[2][1] = false;g.mat[2][2] = true;g.mat[2][3] = true;g.mat[2][4] = false;g.mat[2][5] = false;
    g.mat[3][0] = true;g.mat[3][1] = false;g.mat[3][2] = false;g.mat[3][3] = false;g.mat[3][4] = false;g.mat[3][5] = false;
    g.mat[4][0] = false;g.mat[4][1] = false;g.mat[4][2] = false;g.mat[4][3] = false;g.mat[4][4] = false;g.mat[4][5] = false;
    g.mat[5][0] = false;g.mat[5][1] = false;g.mat[5][2] = false;g.mat[5][3] = false;g.mat[5][4] = true;g.mat[5][5] = false;
    for (int i=6; i < 10; i++)
        for (int j=6; j < 10; j++)
            g.mat[i][j] = false;
        

    serializa_opcao1(&g);

    Grafo g2;
    desserializa_opcao1(&g2);
    for (int i = 0; i < g2.numVertices; i++){
        for (int j = 0; j < g2.numVertices; j++)
            printf("%3d", g2.mat[i][j]);
        printf("\n");
    }
  

}