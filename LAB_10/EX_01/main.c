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

int leggiEAlloca(att **arrayAtt, char *filename);
void sortActivities(att **arrayAtt,int size);
void attDP(att *val,int N);
void attPrint(att *val, int *P, int i);
boolean checkCompatibility(att prev,att actual);
void debugPrintActivities(att *val,int N);
int calcolaDurata(att *array,int size);

int main() {
    setbuf(stdout, NULL);
    att *arrayAtt;
    int N=leggiEAlloca(&arrayAtt,file_name);
    sortActivities(&arrayAtt,N);
    //debugPrintActivities(arrayAtt,N);
    attDP(arrayAtt,N);
    //attSel(N,arrayAtt);
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


void attDP(att *val,int N){
int *L,*P;
int i,j;
int last=1;
int ris=val[0].fi-val[0].si;
L=(int*)malloc(N*sizeof(int));
P=(int*)malloc(N*sizeof(int));
L[0]=val[0].fi-val[0].si;
P[0]=-1;
for(i=1; i< N ; i++){
    L[i]=val[i].fi-val[i].si;
    P[i]=-1;
    for(j=0 ; j<i ; j++){
        if((val[i].si >= val[j].fi) && (L[i] < val[i].fi-val[i].si + L[j])){ //controllo che l'attività sia compatibile e se miglioro la durata aggiorno
            L[i]= val[i].fi-val[i].si + L[j];
            P[i]=j;
        }
        if(ris < L[i]){
            ris = L[i];
            last=i;
        }
    }
}
    attPrint(val,P,last);
    printf("\nDurata ottima %d",ris);


}

void attPrint(att *val, int *P, int i){
    if(P[i]==-1){
        printf("inizio %d fine %d\n",val[i].si,val[i].fi);
        return;
    }
    attPrint(val,P,P[i]);
    printf("inizio %d fine %d\n",val[i].si,val[i].fi);

}


void sortActivities(att **arrayAtt,int size) {
    int i, j;
    att tmp;
// N.B. n-1 è l'ultima componente dell'array.
    for(i = 0; i < size - 1; i++) //scansiona tutto l'array tranne l'ultima componente: n - 1 escluso. Quindi fino al penultimo elemento.
        for (j = size - 1; j > i; j--) //j settato all'ultima componente e decresce ad ogni iterazione. Esce dal ciclo solo se j <= i
            if ((*arrayAtt)[j].si < (*arrayAtt)[j-1].si){
                tmp=(*arrayAtt)[j];
                (*arrayAtt)[j]=(*arrayAtt)[j-1];
                (*arrayAtt)[j-1]=tmp;
            }  //se la componente corrente è più piccola della precedente, li scambia.
}

void debugPrintActivities(att *val,int N){
    for(int i=0; i< N ; i++){
        printf("attivita no %d : inizio %d fine %d\n",i,val[i].si,val[i].fi);
    }
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

