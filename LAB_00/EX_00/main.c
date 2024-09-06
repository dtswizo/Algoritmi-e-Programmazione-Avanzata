#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 6
void rotation(int input[],int dir,int P,int dim);

int main() {
    int array[N]={1,2,3,4,5,6};
    int P=-1;
    int dir;
    int n = sizeof(array)/sizeof(int);
    for(int i=0; i < n ; i++){
        printf("%d  ",array[i]);
    }
    printf("\n");
    do{
        fflush(stdin);
        printf("Inserisci il numero di posizioni da ruotare o zero per terminare : ");
     scanf(" %d",&P);
        if(P==0)
            return 0;
     printf("Inserisci la direzione, 1 SX , -1 DX: ");
     scanf(" %d",&dir);

     rotation(array, dir, P,N);

    }
    while(P != 0);
    printf("exit");
    return 0;
}

void rotation(int input[],int dir,int P,int dim){
    int vettCopy[dim];
    int index;
    for(int i =0 ; i < dim ; i++){
        vettCopy[i]=input[i];
    }
    //considero che input sia esatto
    if(dir==1){    //spostamento a SX
     for(int i=0 ; i < dim ; i++){
          if(i-P<0){
           index=dim-P+i;
           input[index]=vettCopy[i];
          }
         else{

             input[i-P]=vettCopy[i];
         }
       }
    }
    else{
        for(int i=0 ; i < dim ; i++){
            if(i+P>=dim){
                index=abs(dim-i-P);
                input[index]=vettCopy[i];
            }
            else{
                input[i+P]=vettCopy[i];
            }
        }
    }
    printf("\n");
    for(int i=0; i < dim ; i++){
        printf("%d  ",input[i]);
    }
    printf("\n");

    return;
}