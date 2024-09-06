#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define file_input_tiles "tiles.txt"
#define file_input_board "board.txt"

typedef enum{
    false,true
}boolean;

typedef struct{
    int tid;
    int t1Value;
    char t1Color;
    int t2Value;
    char t2Color;
    int vuota;
}tiles;

void disp(tiles ***mat,int R,int C,int pos,int **mark,int *bestVal,tiles ***sol,tiles *tessere,int T,int emptySpots);
void leggiEAlloca(tiles ***mat, tiles **inputTiles, char *file1, char *file2,int *R,int *C,int *T);
void ruotaTessera(tiles *tessera);
void riempiScacchieraWrapper(tiles ***mat,tiles *inputTiles,int R,int C,int T);
int calcolaValore(tiles **mat,int R,int C);
void primoSpazioVuoto(tiles **mat,int R,int C,int *index1,int *index2);
void stampaMatrice(tiles **mat,int R,int C);
void copiaMatrice(tiles ***mat,tiles ***sol,int R,int C);

int main() {
    setbuf(stdout, NULL);
    int R,C,T;
    tiles **mat;
    tiles *inputTiles;
    leggiEAlloca(&mat,&inputTiles,file_input_board,file_input_tiles,&R,&C,&T);
    /*for(int i=0; i < T ; i++){
        printf("%c %d %c %d %d %d",inputTiles[i].t1Color,inputTiles[i].t1Value,
               inputTiles[i].t2Color,inputTiles[i].t2Value,inputTiles[i].tid,inputTiles[i].usata);
        printf("\n");
    }*/
    printf("Scacchiera iniziale\n");
    for(int i=0; i < R ; i++){
        for(int j=0 ; j < C; j++){
            if(mat[i][j].vuota==1)
                printf(" void ");
            else
                printf("%c %d %c %d",mat[i][j].t1Color,mat[i][j].t1Value,mat[i][j].t2Color,mat[i][j].t2Value);
        }
        printf ("\n");
    }
    riempiScacchieraWrapper(&mat,inputTiles,R,C,T);
    return 0;
}


void leggiEAlloca(tiles ***mat, tiles **inputTiles, char *file1, char *file2,int *R,int *C,int *T){
   FILE *fp;
   int nt;
   int nr,nc;
   int t1,t2;
   char c1,c2;
   int t,r;
   int tTemp,rTemp;
   tiles temp;
   fp=fopen(file2,"r");
   if(fp==NULL){
       printf("file opening error");
       return;
   }
   //loading tiles
   fscanf(fp,"%d",&nt);
   *T=nt;
   *inputTiles=(tiles*)malloc(nt * sizeof(tiles));
    for(int i=0; i < nt ; i++) {
       fscanf(fp, " %c %d %c %d", &c1, &t1, &c2, &t2);
        (*inputTiles)[i].t1Value=t1;
        (*inputTiles)[i].t1Color=c1;
        (*inputTiles)[i].t2Value=t2;
        (*inputTiles)[i].t2Color=c2;
       (*inputTiles)[i].tid=i;
   }
    printf("stampo tessere\n");
    for(int i=0; i < nt ; i++) {
        printf(" %c %d %c %d", (*inputTiles)[i].t1Color, (*inputTiles)[i].t1Value, (*inputTiles)[i].t2Color, (*inputTiles)[i].t2Value);
        printf("\n");
    }
    fclose(fp);

   //loading Board
   fp= fopen(file1,"r");
   fscanf(fp,"%d %d",&nr,&nc);
   *R=nr;
   *C=nc;
   *mat=(tiles**)malloc(nr*sizeof(tiles*));
   for(int i=0; i < nr ; i++) (*mat)[i]=(tiles*)malloc(nc*sizeof(tiles));
   for(int i=0; i < nr ; i++){
       for(int j=0 ; j < nc ; j++){
           fscanf(fp,"%d%*c%d",&t,&r);
           tTemp=t;
           rTemp=r;
           if(t=-1 && r==-1){
               (*mat)[i][j].vuota=1;
           }
           else {
               (*mat)[i][j]=(*inputTiles)[tTemp];
               if (rTemp == 1)
                   ruotaTessera(&((*mat)[i][j]));
               (*mat)[i][j].vuota=0;
           }
       }
   }
   fclose(fp);
}

void riempiScacchieraWrapper(tiles ***mat,tiles *inputTiles,int R,int C,int T){
    tiles **sol;
    int *mark;
    int bestVal=0;
    int emptySpots=0;
    mark=calloc(T,sizeof(int));
    for(int i=0; i < R ; i++) {
        for (int j = 0; j < C; j++) {
            if ((*mat)[i][j].vuota != 1)
                mark[(*mat)[i][j].tid] = 1;
        }
    }
    for(int i = 0 ; i < T ; i++){
        if(mark[i]==0)
            emptySpots++;
    }
    sol=(tiles**)malloc(R*sizeof(tiles*));
    for(int i=0; i < R ; i++) sol[i]=(tiles*)malloc(C*sizeof(tiles));
    disp(mat,R,C,0,&mark,&bestVal,&sol,inputTiles,T,emptySpots);
    printf("Soluzione Ottima:\n");
    stampaMatrice(sol,R,C);
   printf("\nPunteggio massimo %d",bestVal);
}

void disp(tiles ***mat,int R,int C,int pos,int **mark,int *bestVal,tiles ***sol,tiles *tessere,int T,int emptySpots){
    int i,j;
    int tmp1,tmp2;
    int tmp;
     if(pos>=emptySpots){
             tmp = calcolaValore(*mat, R, C);
             if (tmp >= *bestVal) {
                 *bestVal = tmp;
                 copiaMatrice(mat,sol,R,C);
             }

         return;
     }

    for(i = 0 ; i < T ; i++ ){
        if((*mark)[i]==0) {
            primoSpazioVuoto(*mat, R, C, &tmp1, &tmp2); //prendo il primo spazio vuoto della matrice per inserire una tessera
            (*mat)[tmp1][tmp2] = tessere[i];
            (*mark)[i] = 1;         //prendo la tessera
            disp(mat, R, C, pos + 1, mark, bestVal, sol, tessere, T,emptySpots);
            ruotaTessera(&((*mat)[tmp1][tmp2]));    //ruoto la tessera
            disp(mat, R, C, pos + 1, mark, bestVal, sol, tessere, T,emptySpots);
            (*mark)[i] = 0;  //backtracking
        }

    }

}

void copiaMatrice(tiles ***mat,tiles ***sol,int R,int C){
    for(int i=0 ; i < R ; i++){
        for(int j=0 ; j < C ; j++){
            (*sol)[i][j]=(*mat)[i][j];
        }
    }
}

void stampaMatrice(tiles **mat,int R,int C){
    for(int i=0; i < R ; i++){
        for(int j=0 ; j < C; j++){
            if(mat[i][j].vuota==1)
                printf(" void ");
            else
                printf("%c %d %c %d ",mat[i][j].t1Color,mat[i][j].t1Value,mat[i][j].t2Color,mat[i][j].t2Value);
        }
        printf ("\n");
    }
}

void ruotaTessera(tiles *tessera){
    int t1;
    int c1;
    t1=(*tessera).t1Value;
    (*tessera).t1Value=(*tessera).t2Value;
    (*tessera).t2Value=t1;
    c1=(*tessera).t1Color;
    (*tessera).t1Color=(*tessera).t2Color;
    (*tessera).t2Color=c1;
    return;
}

int calcolaValore(tiles **mat,int R,int C){
    int res=0;
    int i,j;
    int flag=0;
    char color;
    int contributoRighe=0;
    int contributoColonne=0;
    for(i=0; i < R ; i++){
        res+=contributoRighe;
        contributoRighe=0;
        flag=0;
        for(j=0; j < C && flag==0; j++){
            if(j==0) {
                color = mat[i][j].t1Color;
                contributoRighe+=mat[i][j].t1Value;
            }
            else{
                if(mat[i][j].t1Color!=color){
                    flag=1;
                    contributoRighe=0;
                }
                else{
                    contributoRighe+=mat[i][j].t1Value;
                }

            }
        }
    }
    res+=contributoRighe;
    for(i=0; i < C ; i++){
        res+=contributoColonne;
        contributoColonne=0;
        flag=0;
        for(j=0; j < R && flag==0; j++){
            if(j==0) {
                color = mat[j][i].t2Color;
                contributoColonne+=mat[j][i].t2Value;
            }
            else{
                if(mat[j][i].t2Color!=color ){
                    flag=1;
                    contributoColonne=0;
                }
                else{
                    contributoColonne+=mat[j][i].t2Value;
                }

            }
        }
    }
    res+=contributoColonne;
    return res;
}

void primoSpazioVuoto(tiles **mat,int R,int C,int *index1,int *index2){
    for(int i=0; i < R ; i++){
        for(int j=0; j < C ; j++){
            if(mat[i][j].vuota==1){
                *index1=i;
                *index2=j;
                return;
            }

        }
    }
}

