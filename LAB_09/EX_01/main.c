#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define file_name "att.txt"

typedef enum{
    false,true
}boolean;

typedef struct{
    int si;
    int fi;
}att;

void attSel(int N, att *v);  //funzione wrapper
int leggiEAlloca(att **arrayAtt, char *filename);
int powerset(int pos,att *val,att *sol,int k, int start,int count,int *bestDurata,att **bestSol,int *sizeBestSol);
boolean checkCompatibility(att prev,att actual);
int calcolaDurata(att *array,int size);

int main() {
    setbuf(stdout, NULL);
    att *arrayAtt;
    int N=leggiEAlloca(&arrayAtt,file_name);
    attSel(N,arrayAtt);
    return 0;
}

int leggiEAlloca(att **arrayAtt, char *filename){
   FILE *fp;
   int N;
   fp=fopen(filename,"r");
   if(fp==NULL){
       printf("file opening error");
       return -1;
   }
   fscanf(fp,"%d",&N);
   *arrayAtt=(att*)malloc(N*sizeof(att));
   for(int i=0; i < N ; i++)
       fscanf(fp,"%d %d",&(*arrayAtt)[i].si,&(*arrayAtt)[i].fi);

    return N;
}

void attSel(int N, att *v){   //wrapper
    att *sol;
    att *bestSol;
    int bestDurata=0;
    int sizeBestSol;
    sol=(att*)malloc(N*sizeof(att));
    bestSol=(att*)malloc(N*sizeof(att));
    powerset(0,v,sol,N,0,0,&bestDurata,&(bestSol),&sizeBestSol);
    printf("no dei sottoinsiemi di S di attivita compatibili che massimizza la somma delle durate: ");
    for(int i=0; i < sizeBestSol; i++) printf("(%d,%d) ",bestSol[i].si,bestSol[i].fi);
    printf("\nTempo massimo attivita : %d",bestDurata);
    free(sol);
    free(bestSol);
}

int powerset(int pos,att *val,att *sol,int k, int start,int count,int *bestDurata,att **bestSol,int *sizeBestSol){
    int i;
    if(start>=k){
        if(calcolaDurata(sol,pos) > calcolaDurata(*bestSol,*bestDurata)){
            *bestDurata=calcolaDurata(sol,pos);
            *sizeBestSol=pos;
            for(i=0 ; i < pos ; i++) (*bestSol)[i]=sol[i];
        }
      //  for(int i=0; i < pos ; i++)
       //     printf("%d -inizio: %d , -fine: %d     ",i,sol[i].si,sol[i].fi);
        //printf("\n");
        return count + 1;
    }
    for(i = start ; i < k ; i++){
        if(pos==0 || checkCompatibility(sol[pos-1],val[i])) {
            sol[pos] = val[i];
            count = powerset(pos + 1, val, sol, k, i + 1, count, bestDurata, bestSol,sizeBestSol);
        }
    }
    count=powerset(pos,val,sol,k,k,count,bestDurata,bestSol,sizeBestSol);
    return count;
}

boolean checkCompatibility(att prev,att actual){
    if(prev.si<actual.fi && actual.si<prev.fi)
        return false;
    return true;
}

int calcolaDurata(att *array,int size){
    int sum=0;
    if(size==0)  //initial case, always true
        return 0;
    for(int i=0; i < size ; i++)
        sum+=array[i].fi-array[i].si;
    return sum;
}

