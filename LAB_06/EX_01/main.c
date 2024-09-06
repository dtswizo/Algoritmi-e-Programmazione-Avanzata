#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define S 25
#define C 255


typedef struct{
    int id;
    int arraySize;
    char arraySongs[S][S];
}amico;

int princ_molt(int pos, amico* arrayptr,char **sol, int n , int count);

int main() {
    char **sol;
    FILE *fp;
    int N;
    int tmp;
    amico *ptrAmici;
    fp=fopen("brani.txt","r");
    if(fp==NULL)
        return -1;
    fscanf(fp,"%d",&N);
    sol=(char**)malloc(N*sizeof(char*));
    for(int i = 0 ; i < N ; i++)
        sol[i]=(char*)malloc(S*sizeof(char));
    //allocazione struct
    ptrAmici=(amico*)malloc(N*sizeof(amico));
    //store dei dati
    for(int i = 0 ; i < N ; i++){
        fscanf(fp,"%d",&tmp);
        for(int j=0 ; j < tmp; j++){
           if(j==0) {
               ptrAmici[i].id = i;
               ptrAmici[i].arraySize = tmp;
           }
            fscanf(fp,"%s",ptrAmici[i].arraySongs[j]);
        }
    }
    princ_molt(0,ptrAmici,sol,N,0);
    fclose(fp);




    return 0;
}

int princ_molt(int pos, amico* arrayptr,char **sol, int n , int count){
    int i;
    if(pos >= n) {
        printf("playlist \n");
        for (i = 0; i < n; i++) {
            printf("-%s ", sol[i]);
            printf("\n");
        }
        printf("\n");
        return count + 1;
    }
   for(int i = 0 ; i < arrayptr[pos].arraySize; i++){
       strcpy(sol[pos],arrayptr[pos].arraySongs[i]);
       count=princ_molt(pos+1,arrayptr,sol,n,count);
   }
}
