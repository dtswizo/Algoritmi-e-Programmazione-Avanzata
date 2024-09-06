#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30
#define S 100

void rotation(int input[],int dir,int P,int dim);
void stampaMatrice(int mat[N][N],int R, int C);

int main() {
    FILE *fp;
    int R,C;
    int mat[N][N];
    int vTemp[N];
    char input[S];
    char selettore[S];
    int indice;
    char direzione[S];
    int dir;
    int P;
    int stop=0;
    fp=fopen("mat.txt","r");
    if(fp==NULL){
        return -1;
    }
    fscanf(fp,"%d %d",&R,&C);
    //salvataggio matrice
    for(int i=0 ; i < R ; i++){
        for(int j=0 ; j < C ; j++){
            fscanf(fp,"%d", &mat[i][j]);
        }
    }
    printf("\n matrice iniziale\n");
    for(int i=0 ; i < R ; i++){
        for(int j=0 ; j < C ; j++)
            printf("%d ",mat[i][j]);
        printf("\n");
    }
    do{
     printf("Inserisci <selettore> <indice> <direzione> <posizioni> : \n");
     gets(input);
     sscanf(input,"%s %d %s %d",selettore,&indice,direzione,&P);
     indice--;
    if(strcmp(selettore,"fine")==0){
        stop=1;
        return 0;
    }
    if(strcmp(selettore,"riga")==0){
        if(strcmp(direzione,"destra")==0)
            dir=-1;
        else
            dir=1;
        for(int j=0 ; j < C ; j++)
            vTemp[j]=mat[indice][j];
        rotation(vTemp,dir,P,C);
        for(int j=0 ; j < C ; j++)
            mat[indice][j]=vTemp[j];
    }
    else{
        if(strcmp(direzione,"giu")==0)
            dir=-1;
        else
            dir=1;
        for(int j=0 ; j < R ; j++)
            vTemp[j]=mat[j][indice];
        rotation(vTemp,dir,P,R);
        for(int j=0 ; j < R ; j++)
            mat[j][indice]=vTemp[j];
    }
    printf("\n matrice con %s spostata %s di %d posizione/i \n",selettore,direzione,indice+1);
        for(int i=0 ; i < R ; i++){
            for(int j=0 ; j < C ; j++)
                printf("%d ",mat[i][j]);
            printf("\n");
        }


    }
    while(stop==0);


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


    return;
}


