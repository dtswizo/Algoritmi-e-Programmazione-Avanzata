#ifndef EX_01_GRAFO_H
#define EX_01_GRAFO_H
#ifndef S
#define S 30
#endif
#include "ST.h"


typedef enum{false,true}boolean;

//quasi ADT
typedef struct{
    int v;
    int w;
    int wt;
}Edge;

//ADT I Classe Grafo
typedef struct graph *Graph;

//prototipi
void userSelection(Graph G,int mode);
void printMadjMat(Graph G,int V);
void GraphFree(Graph G);
Graph GRAPHload(FILE *fp);
void createAdjList(Graph G);
void GRAPHinsertE(Graph G, int id1, int id2,int wt);
void GRAPHprintLadj(Graph G);
boolean isAdj_Mat(Graph G,int vertexSource,int id2,int id3);
boolean isAdj_List(Graph G,int vertexSource,int id2,int id3);

#endif //EX_01_GRAFO_H



