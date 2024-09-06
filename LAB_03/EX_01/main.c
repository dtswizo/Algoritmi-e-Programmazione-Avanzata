#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50
#define S 100

typedef enum{
    false,true
}boolean;

typedef struct{
    int b;
    int h;
    int a;
    int x,y;
}rettangolo;


int calcolaBase(int mat[][N],int R,int C,int i,int j);
int calcolaAltezza(int mat[][N],int R,int C,int i,int j);
int leggiMatrice(int M[][N],int maxR,int *nr,int *nc);
boolean riconosciRegione(int M[][N],int nr,int nc,int r,int c,int *b,int *h);


int main() {
    rettangolo vettRettangoli[N];
    int R=0, C=0;
    int tempBase;
    int tempAltezza;
    int tempArea=0;
    int maxBase=0;
    int maxAltezza=0;
    int maxArea=0;
    int mat[N][N];
    leggiMatrice(mat,N,&R,&C);
    //computazione
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (mat[i][j] == 1 && riconosciRegione(mat,R,C,i,j,&tempBase,&tempAltezza)) {
                tempArea=tempBase*tempAltezza;
                if(tempBase>maxBase){
                    maxBase=tempBase;
                    vettRettangoli[0].h=tempAltezza;
                    vettRettangoli[0].b=tempBase;
                    vettRettangoli[0].a=tempArea;
                    vettRettangoli[0].x=i;
                    vettRettangoli[0].y=j;
                }
                if(tempAltezza>maxAltezza){
                    maxAltezza=tempAltezza;
                    vettRettangoli[1].h=tempAltezza;
                    vettRettangoli[1].b=tempBase;
                    vettRettangoli[1].a=tempArea;
                    vettRettangoli[1].x=i;
                    vettRettangoli[1].y=j;
                }
                if(tempArea>maxArea){
                    maxArea=tempArea;
                    vettRettangoli[2].h=tempAltezza;
                    vettRettangoli[2].b=tempBase;
                    vettRettangoli[2].a=tempArea;
                    vettRettangoli[2].x=i;
                    vettRettangoli[2].y=j;
                }
                j+=tempBase-1;
            }
        }
    }
    //output
    for(int i = 0 ; i < 3 ; i++){
        switch(i) {
            case 0:
                printf("Rettangolo di base maggiore ha base= %d altezza= %d area= %d coordinate = <%d,%d>",
                       vettRettangoli[0].b, vettRettangoli[0].h, vettRettangoli[0].a, vettRettangoli[0].x,
                       vettRettangoli[0].y);
                break;
            case 1:
                printf("Rettangolo di altezza maggiore ha base= %d altezza= %d area= %d coordinate = <%d,%d>",
                       vettRettangoli[1].b, vettRettangoli[1].h, vettRettangoli[1].a, vettRettangoli[1].x, vettRettangoli[1].y);
                break;
            case 2:
                printf("Rettangolo di area maggiore ha base= %d altezza= %d area= %d coordinate = <%d,%d>",
                       vettRettangoli[2].b, vettRettangoli[2].h, vettRettangoli[2].a, vettRettangoli[2].x, vettRettangoli[2].y);
                break;
        }
        printf("\n");
    }

    return 0;
}

int leggiMatrice(int M[][N],int maxR,int *nr,int *nc){
   FILE *fp;
   int tempR,tempC;
    fp = fopen("mappa.txt", "r");
    if (fp == NULL) {
        return -1;
    }
    fscanf(fp,"%d %d", &tempR,&tempC);
    for (int i = 0; i < tempR; i++) {
        for (int j = 0; j < tempC; j++) {
            fscanf(fp, "%d", &M[i][j]);
        }
    }
    *nr=tempR;
    *nc=tempC;
}

boolean riconosciRegione(int M[][N],int nr,int nc,int r,int c,int *b,int *h){
    int flag=0;
    if( ((r-1>=0 && M[r-1][c]==0) || r-1<0)  &&  ((c-1>=0 && M[r][c-1]==0) || c-1<0)){
       flag=1;
        *b = calcolaBase(M, nr, nc,r,c+1);
        *h = calcolaAltezza(M, nr, nc,r+1,c);
        printf("rettangolo estremo <%d,%d> base %d altezza %d \n",r,c,*b,*h);
    }
    return true;

}

int calcolaBase(int mat[][N],int R,int C,int i,int j){
    int cnt=1;
    int flag=0;
    for(int x=j; x < C && flag==0; x++){
        if(mat[i][x]==1)
            cnt++;
        else
            flag=1;
    }
    return cnt;
}

int calcolaAltezza(int mat[][N],int R,int C,int i,int j){
    int cnt=1;
    int flag=0;
    for(int x=i; x < R && flag==0; x++){
        if(mat[x][j]==1)
            cnt++;
        else
            flag=1;
    }
    return cnt;
}