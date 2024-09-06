#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"


itemList_t itemList;



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
    itemList=itemList_init();
    return G;

}

Graph GRAPHload(FILE *fp){
    int V=0;
    int wt=0;
    int cnt=0;
    int id1,id2;
    Graph G;
    char label1[S],label2[S];
    char net1[S],net2[S];
    fp=fopen("grafo.txt","r");
    printf("Graph Loaded\n");
    printf("Vertices:\n");
    while(fscanf(fp,"%s %s %s %s %d",label1,net1,label2,net2,&wt)==5)
        V++;
    rewind(fp);
    G= GRAPHInit(2*V);
    for(int i=0; i < V ; i++){
        fscanf(fp,"%s %s %s %s %d",label1,net1,label2,net2,&wt);
        if(STInsert(G->tab,label1,cnt)!=-1) {
            (G->tab.size)++;
            cnt++;
        }
        if(STInsert(G->tab,label2,cnt)!=-1) {
            (G->tab.size)++;
            cnt++;
        }
    }
    printMat(G->tab);
    rewind(fp);
    V= (G->tab.size);
    G->V=V;
    G->madj=MATRIXint(V,V,0);
    while(fscanf(fp,"%s %s %s %s %d",label1,net1,label2,net2,&wt)==5){
        id1= STSearch(G->tab,label1);
        id2= STSearch(G->tab,label2);
        itemList_insert(itemList,ITEMnew(label1,net1));
        itemList_insert(itemList,ITEMnew(label2,net2));
        if(id1>=0 && id2>=0)
            GRAPHinsertE(G,id1,id2,wt);
    }
    printf("Adjacency matrix:\n");
    printMadjMat(G,V);
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

void printV_EAlphabetically(Graph G){
 char **temp;
 char hold[30];
 int i,j;
 ITEM it;
 temp=(char**)malloc((G->tab.size)*sizeof(char*));
 for(i=0; i < G->tab.size; i++)
     temp[i]=(char*)malloc(30*sizeof(char));
 for(int i=0 ; i < (G->tab.size); i++){
     for(j=0 ; j < strlen(G->tab.mat[i]);j++){
         temp[i][j]=G->tab.mat[i][j];
     }
     temp[i][j]='\0';
 }
    for(int i=0; i<G->tab.size; i++){
        for(int j=0; j<(G->tab.size)-1-i; j++){
            if(strcmp(temp[j], temp[j+1]) > 0){
                strcpy(hold, temp[j]);
                strcpy(temp[j], temp[j+1]);
                strcpy(temp[j+1], hold);
            }
        }
    }
    printf("Lista Vertici e archi insistenti su essi: \n");
   for(int i=0 ; i < G->tab.size; i++){
       printf("Vertice %d :",i);
       for(int z=0; z < G->V ; z++){
           for(int x=0 ; x < G->V ; x++){
               if( (G->madj)[z][x]!=0 && (z==i || x==i)){
                   printf("Arco %s <---> %s ", STGetLabelByIndex(G->tab,z),STGetLabelByIndex(G->tab,x));
               }
           }
       }
       printf("\n");
   }
    for(i=0; i < G->tab.size; i++)
        free(temp[i]);
    free(temp);
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

void userSelection(Graph G,int mode){
    if(mode==0){
        printV_EAlphabetically(G);
    }
    else if(mode==1){
        Three_Vertex_SubGraph(G);
    }
    else if (mode==2){
        createAdjList(G);
        GRAPHprintLadj(G);
    }
}

