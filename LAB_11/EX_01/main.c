#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define N 30
#define D 5
int solSize;
int indice;

typedef struct{
 char nome[N];
 int tipologia;
 int dirIn;
 int dirOut;
 int precedenza;
 int finale;
 float valore;
 int difficolta;
}elementi;

typedef struct{
    elementi array[D];
    int size;
}diagonale;

typedef struct{
    diagonale *arrayDiagonali;
    float punteggio;
}programma;

typedef enum {
    false, true
}boolean;


int leggiEAlloca(elementi **arrayElementi,char *filename);
void generaProgrammaWrapper(elementi *arrayElementi,diagonale **arrayDiagonali,int lines);
int generaDiagonali(int pos,elementi *val,elementi *sol,diagonale **res,int n,int k,int count,int DP); //disp_rip
int generaProgramma(int pos, diagonale **arrayDiagonali, int *mark, programma sol, int n, int k, int count, int DD,int DP, int nDiagonali); //disp semplici
boolean pruningDiag(elementi *sol,elementi val,int pos,int DD);
boolean finalCheck(elementi *sol,int k);
boolean checkProgramma(programma sol,int DD,int DP);
void stampaDiagonali(diagonale **arrayDiagonali,int nDiagonali);


int main() {
    setbuf(stdout,NULL);
    int lines;
    elementi *arrayElementi;
    diagonale *arrayDiagonali;
    lines=leggiEAlloca(&arrayElementi,"elementi.txt");
    arrayDiagonali=(diagonale*)malloc(sizeof(diagonale));
    generaProgrammaWrapper(arrayElementi,&arrayDiagonali,lines);

    return 0;
}

int leggiEAlloca(elementi **arrayElementi,char *filename){
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("File opening error");
        EXIT_FAILURE;
    }
    int lines;
    fscanf(fp,"%d",&lines);
    *arrayElementi=(elementi*)malloc(lines*sizeof(elementi));
    for(int i=0; i < lines ; i++){
        fscanf(fp,"%s %d %d %d %d %d %f %d",(*arrayElementi)[i].nome,&(*arrayElementi)[i].tipologia,
               &(*arrayElementi)[i].dirIn,&(*arrayElementi)[i].dirOut,&(*arrayElementi)[i].precedenza,
               &(*arrayElementi)[i].finale,&(*arrayElementi)[i].valore,&(*arrayElementi)[i].difficolta);
    }
    return lines;
}

void generaProgrammaWrapper(elementi *arrayElementi,diagonale **arrayDiagonali,int lines){
    int DD=10;
    int DP=20;
    elementi *sol;
    programma sol2;
    int *mark;
    sol=(elementi*)malloc(D*sizeof(elementi));
    mark=calloc(D, sizeof(int));
    solSize=1;
    indice=0;
    int cnt=0;
    for(int i=0; i < D ; i++){
        cnt+=generaDiagonali(0,arrayElementi,sol,arrayDiagonali,lines,i,0,DD);
    }
    sol2.arrayDiagonali=(diagonale*)malloc(cnt*sizeof(diagonale));
    //stampaDiagonali(arrayDiagonali,cnt);
    printf("Numero diagonali : %d\n",cnt);
    /*sol2.arrayDiagonali[0].array[0]=(*arrayDiagonali)[0].array[0];
    sol2.arrayDiagonali[0].size=(*arrayDiagonali)[0].size;
    sol2.arrayDiagonali[1].array[0]=(*arrayDiagonali)[29].array[0];
    sol2.arrayDiagonali[1].array[1]=(*arrayDiagonali)[29].array[1];  //debug con programma ottimale
    sol2.arrayDiagonali[1].size=(*arrayDiagonali)[29].size;
    sol2.arrayDiagonali[2].array[0]=(*arrayDiagonali)[17].array[0];
    sol2.arrayDiagonali[2].array[1]=(*arrayDiagonali)[17].array[1];
    sol2.arrayDiagonali[2].size=(*arrayDiagonali)[17].size;
    printf("%s",sol2.arrayDiagonali[2].array[1].nome);
    if(checkProgramma(sol2,DD,DP)==true)
       printf("true");*/
   generaProgramma(0,arrayDiagonali,mark,sol2,lines,3,0,DD,DP,cnt);
}

int generaDiagonali(int pos,elementi *val,elementi *sol,diagonale **res,int n,int k,int count,int DD){
    int i;
   if(pos>=k){
       if(finalCheck(sol,k)==true) {
           *res = (diagonale *) realloc(*res, ++solSize * sizeof(diagonale));
           (*res)[indice].size=k;
           for (int j = 0; j < k; j++) {
               (*res)[indice].array[j] = sol[j];
           }
           indice++;
           solSize++;
           return count + 1;
       }
       else
           return count;
   }

   for(i=0; i < n ; i++){
       if(pruningDiag(sol,val[i],pos,DD)==true) {
           sol[pos] = val[i];
           count = generaDiagonali(pos + 1, val, sol, res, n, k, count,DD);
       }
   }
  return count;
}

int generaProgramma(int pos, diagonale **arrayDiagonali, int *mark, programma sol, int n, int k, int count, int DD,int DP,int nDiagonali){
    int i;
    if(pos>=k){
        if(checkProgramma(sol,DD,DP)==true) {
            printf("Programma trovato");
            return count+1;
        }
         return count;
    }
    for(i=0; i < nDiagonali ; i++){
        if(mark[i] == 0){
            mark[i]=1;
            for(int j=0; j < (*arrayDiagonali)[i].size; j++){
                sol.arrayDiagonali[i].array[j]=(*arrayDiagonali)[i].array[j];
            }
            sol.arrayDiagonali[i].size=(*arrayDiagonali)[i].size;
            count=generaProgramma(pos+1, arrayDiagonali, mark, sol, n, k, count, DD, DP, nDiagonali);
            mark[i]=0;
        }
    }
    return count;
}

boolean pruningDiag(elementi *sol,elementi val,int pos,int DD){
    float actualValue=0;
    if(pos==0){
        if(val.dirIn!=1)
            return false;
        if(val.precedenza!=0)
            return false;
    }
    else{
     for(int i=0; i < pos ;i++){
         actualValue+=sol[i].valore;
     }
     if(actualValue+val.valore>DD)
         return false;
     if(sol[pos-1].dirOut!=val.dirIn)
         return false;
     if(sol[pos-1].finale==1)
         return false;
    }
    return true;
}

boolean finalCheck(elementi *sol,int k){
    for(int i=0; i < k ; i++){
        if(sol[i].tipologia==2 || sol[i].tipologia==1)
            return true;
    }
    return false;
}

boolean checkProgramma(programma sol,int DD,int DP){
    //debug print
    /*printf("\n Inspecting : \n");
    for(int x=0; x < 3 ; x++ ){
        printf("Diag %d \n",x);
        for(int z=0; z < sol.arrayDiagonali[x].size ; z++){
            printf("- %s \n",sol.arrayDiagonali[x].array[z]);
        }
    }*/
    //real function
    int i,j;
    sol.punteggio=0;
    float diagTempPoints=0;
    int flagElementiAcrobaticoAvanti=0;
    int flagElementiAcrobaticoIndietro=0;
    int flagAcrobaticiSequenza=0;
    for(i=0; i < 3 ; i++){
        sol.punteggio+=diagTempPoints;
        diagTempPoints=0;
            for(j=0 ; j < sol.arrayDiagonali[i].size ; j++){
             diagTempPoints+=sol.arrayDiagonali[i].array[j].valore;
            if(sol.arrayDiagonali[i].array[j].tipologia==2)
             flagElementiAcrobaticoAvanti=1;
            if(sol.arrayDiagonali[i].array[j].tipologia==1)
                flagElementiAcrobaticoIndietro=1;
            if(j <= sol.arrayDiagonali[i].size-1 &&
            sol.arrayDiagonali[i].array[j].tipologia>=1 && sol.arrayDiagonali[i].array[j+1].tipologia>=1)
             flagAcrobaticiSequenza=1;
        }
            if(diagTempPoints> DD)
                return false;
            if(i==2){
                if( sol.arrayDiagonali[2].array[sol.arrayDiagonali[2].size-1].difficolta>=8) {
                    diagTempPoints *= 1.5;
                    sol.punteggio += diagTempPoints;
                }
                else
                    sol.punteggio += diagTempPoints;

            }
    }


    if(sol.punteggio> DP )
        return false;
    if(flagElementiAcrobaticoIndietro!=1 || flagElementiAcrobaticoAvanti!=1 ||  flagAcrobaticiSequenza!=1)
        return false;
    printf("punteggio programma %f\n",sol.punteggio);
    return true;
}

void stampaDiagonali(diagonale **arrayDiagonali,int nDiagonali){
    int i,j;
    for(i=0 ; i < nDiagonali; i++) {
        printf(" diagonale %d: \n", i);
        for (j = 0; j < (*arrayDiagonali)[i].size; j++) {
            printf(" %s\n", (*arrayDiagonali)[i].array[j].nome);
        }
    }
}
