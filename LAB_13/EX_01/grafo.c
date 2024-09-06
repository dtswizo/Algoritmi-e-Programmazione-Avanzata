#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"





typedef struct node *link;

struct node {int v; int wt; link next;};

struct graph{
    int V;
    int E;
    int **madj;
    ST tab;
    //strutture dati necessarie per liste di adiacenza
    link *ladj;
    link z;
};

static link NEW(int v, int wt , link  next){
    link x=malloc(sizeof(*x));
    x->v=v; x->wt=wt; x->next=next;
    return x;
}


static int **MATRIXint(int r,int c, int val){
    int i,j;
    int **t=malloc(r*sizeof(int*));
    for(i=0; i < r ; i++) t[i]=malloc(c*sizeof(int));
    for(i=0 ; i < r ; i++){
        for(j=0; j < c ; j++)
            t[i][j]=val;
    }
    return t;
}

Graph GRAPHInit(int V){
    Graph G=malloc(sizeof(*G));
    G->V=V;
    G->E=0;
    ST_Init(&(G->tab),V);
    return G;

}

Graph GRAPHload(FILE *fp){
    int V;
    char name,name1;
    int wt=0;
    int cnt=0;
    int id1,id2;
    Graph G;
    fp=fopen("grafo1.txt","r");
    if(fp==NULL)
        EXIT_FAILURE;
    printf("Graph Loaded\n");
    printf("Vertices:\n");
    fscanf(fp," %d ",&V);
    G= GRAPHInit(V);
    for(int i=0; i < V ; i++){
        fscanf(fp," %c ",&name);
        STInsert(G->tab,name,i);
        (G->tab.size)++;
    }
    printMat(G->tab);
    G->V=V;
    G->madj=MATRIXint(V,V,0);
    while(fscanf(fp," %c %c %d ",&name,&name1,&wt)==3){
        id1= STSearch(G->tab,name);
        id2= STSearch(G->tab,name1);
        if(id1>=0 && id2>=0)
            GRAPHinsertE(G,id1,id2,wt);
    }
    printf("Adjacency matrix:\n");
    printMadjMat(G,V);
    fclose(fp);
    return G;
}

void createAdjList(Graph G){
    G->ladj=(link*)malloc(G->V*sizeof(link));
    G->z=NEW(-1,0,NULL);
    for (int i=0; i < G->V ; i++)
        G->ladj[i]=G->z;
    for(int i=0 ; i < G->V ; i++){
        for(int j= i+1 ; j < G->V ; j++){
            if(G->madj[i][j]!=0){
                G->ladj[i]= NEW(j,G->madj[i][j],G->ladj[i]);
                G->ladj[j]= NEW(i,G->madj[i][j],G->ladj[i]);
            }
        }
    }
}

static Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v=v; e.w=w; e.wt=wt;
    return e;
}

static void insertE(Graph G, Edge e){
    int v= e.v, w= e.w, wt= e.wt;
    if(G->madj[v][w]==0)
        G->E++;
    G->madj[v][w]=wt;
    G->madj[w][v]=wt;
}

void GRAPHinsertE(Graph G, int id1, int id2,int wt){
    insertE(G, EDGEcreate(id1,id2,wt));
}

void printMadjMat(Graph G,int V){
    for(int i=0 ; i < V ; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", G->madj[i][j]);
        }
        printf("\n");
    }

}



void GRAPHprintLadj(Graph G){
    int i;
    link x;
    for(i = 0; i < G->V; i++){
        printf("%s ", STGetLabelByIndex(G->tab, i));
        for(x = G->ladj[i]; x != G->z; x = x->next){
            printf("-> %s", STGetLabelByIndex(G->tab, x->v));
        }
        printf("\n");
    }
}

void Three_Vertex_SubGraph(Graph G){
    int id1,id2,id3;
    printf("\nInsert the index of the 3 Vertices:");
    scanf("%d %d %d", &id1,&id2,&id3);
    //versione matrice di adiacenze
    if(isAdj_Mat(G,id1,id2,id3) && isAdj_Mat(G,id2,id1,id3) && isAdj_Mat(G,id3,id2,id1))
        printf("I tre vertici formano un sottografo completo");
    else
        printf("I tre vertici non formano un sottografo completo");
    //versione lista adiacenze
    /*
    if(isAdj_List(G,id1,id2,id3) && isAdj_List(G,id2,id1,id3) && isAdj_List(G,id3,id2,id1))
        printf("I tre vertici formano un sottografo completo");
    else
        printf("I tre vertici non formano un sottografo completo");
    */
}

boolean isAdj_Mat(Graph G,int vertexSource,int id2,int id3){
    int count=0;
    if(G->madj[vertexSource][id2]!=0)
        count++;
    if(G->madj[vertexSource][id3]!=0)
        count++;
    if(count==2)
        return true;
    else
        return false;
}

boolean isAdj_List(Graph G,int vertexSource,int id2,int id3){
    int count=0;
    link x;
    for(x = G->ladj[vertexSource]; x != G->z; x = x->next){
        if(x->v==id2) {
            count++;
            break;
        }
    }
    for(x = G->ladj[vertexSource]; x != G->z; x = x->next){
        if(x->v==id3) {
            count++;
            break;
        }
    }
    if(count==2)
        return true;
    else
        return false;
}



