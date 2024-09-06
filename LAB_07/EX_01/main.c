#include <stdio.h>
#include <malloc.h>

typedef enum{
    false,true
}boolean;

typedef struct{
   int u;
   int v;
}arco;

void leggi_e_alloca(arco **entriesVertici, int *N, int *E,int **val,int **sol);
int powerset(int pos, int *val,int *sol,int k, int start,int count,arco *entriesArchi,int E);
boolean checkVertexCover(arco *entriesArchi,int *sol,int N,int sizeSol,int E);
boolean distinctVertex(arco *entriesArchi,int size,int u,int v);

int main() {
    arco *entriesArchi;
    int *val;
    int *sol;
    int N;
    int E;
    leggi_e_alloca(&entriesArchi, &N, &E,&val,&sol);
    powerset(0,val,sol,N,0,0,entriesArchi,E);
    return 0;
}

void leggi_e_alloca(arco **entriesVertici, int *N, int *E,int **val,int **sol){
    FILE *fp;
    fp=fopen("grafo.txt","r");
    if(fp==NULL)
      EXIT_FAILURE;
    fscanf(fp,"%d %d",&(*N),&(*E));
    //vettore soluzione
    *sol=(int*)malloc((*N) * sizeof(int));
    //vertici
    *val=(int*)malloc((*N) * sizeof(int));
    for(int i=0; i < *N ; i++)
        (*val)[i]=i;
    //archi
    *entriesVertici=(arco*)malloc((*E) * sizeof(arco));
    for(int i = 0 ; i < *E ; i++)
        fscanf(fp,"%d %d",&(*entriesVertici)[i].u,&(*entriesVertici)[i].v);
    fclose(fp);
}

int powerset(int pos, int *val,int *sol,int k, int start,int count,arco *entriesArchi,int E){
    int i;
    if(start>=k){
        if(checkVertexCover(entriesArchi,sol,k,pos,E)) {
            printf("Vertex cover %d\n",count);
            printf("(");
            for (int i = 0; i < pos; i++){
                if(i!=pos-1)
                printf("%d,", sol[i]);
                else
                    printf("%d", sol[i]);
            }

            printf(")");
            printf("\n");
            return count + 1;
        }
      else
          return count;
    }
    for(i = start ; i < k ; i++){
        sol[pos]=val[i];
        count= powerset(pos+1,val,sol,k,i+1,count,entriesArchi,E);
    }
    count=powerset(pos,val,sol,k,k,count,entriesArchi,E);
    return count;
}

boolean checkVertexCover(arco *entriesArchi,int *sol,int N,int sizeSol,int E){
    int actualVertex;
    arco *distVal;
    int distValCount=0;
    int flag=0;
    distVal=(arco*)malloc(E*sizeof(arco));
    printf("\n");
    //init distVal
    for(int i=0;i<E;i++){
        distVal[i].u=-1;
        distVal[i].v=-1;
    }
    //check
    for(int i=0 ; i < sizeSol; i++){
        for(int j=0 ; j < E ; j++){
          if(sol[i]==entriesArchi[j].u || sol[i]==entriesArchi[j].v){
              if(distinctVertex(distVal,E,entriesArchi[j].u,entriesArchi[j].v)){
                  distVal[distValCount].u=entriesArchi[j].u;
                  distVal[distValCount].v=entriesArchi[j].v;
                  distValCount++;
              }
          }
        }
    }
    if(distValCount==N)
        return true;
    else
        return false;
}

boolean distinctVertex(arco *entriesArchi,int size,int u,int v){
    int flag=0;
    for(int i = 0 ; i< size ; i++){
        if((entriesArchi[i].u==u && entriesArchi[i].v==v) || (entriesArchi[i].u==v && entriesArchi[i].v==u))
            flag=1;
    }
    if(flag==1)   //non distinti
       return false;
    else         //distinti
       return  true;
}