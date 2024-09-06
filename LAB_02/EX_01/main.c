#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30
#define S 100

typedef struct{
    int b;
    int h;
    int a;
    int x,y;
}rettangolo;


int calcolaBase(int mat[][N],int R,int C,int i,int j);
int calcolaAltezza(int mat[][N],int R,int C,int i,int j);


int main() {
    rettangolo vettRettangoli[N];
    FILE *fp;
    int R, C;
    int tempBase;
    int tempAltezza;
    int tempArea=0;
    int maxBase=0;
    int maxAltezza=0;
    int maxArea=0;
    int mat[N][N];
    fp = fopen("mappa.txt", "r");
    if (fp == NULL) {
        return -1;
    }
    fscanf(fp, "%d %d", &R, &C);
    //salvataggio matrice
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    //computazione
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (mat[i][j] == 1) {
                tempBase = calcolaBase(mat, R, C,i,j+1);
                tempAltezza = calcolaAltezza(mat, R, C,i+1,j);
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