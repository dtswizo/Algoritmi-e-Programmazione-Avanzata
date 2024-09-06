#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define S 30
#define N 1000

int dicotomica=0;

typedef enum{
    r_print, r_Ord_Data, r_Ord_CodTratta, r_Ord_Stazione_Partenza, r_Ord_Stazione_Arrivo,r_Ricerca_Stazione_Partenza,r_lettura,r_fine
}comando_e;

typedef struct{
    char cod_tratta[S];
    char partenza[S];
    char destinazione[S];
    char data[S];
    char ora_partenza[S];
    char ora_arrivo[S];
    int ritardo;
}tratte;

typedef struct{
    tratte *ptrData[N];
    tratte *ptrCodTratta[N];
    tratte *ptrPartenza[N];
    tratte *ptrArrivo[N];
}tratteRif;

//tools
comando_e leggiComando();
long dateToLong(char date[S]);
void stampaTratta(tratte vett[],int index);
//proper functions
int confrontaDate(char data1[S],char data2[S]);
void stampaDatabase(tratte vett[],int size);
void ordinaData(tratte *vett[],int size);
void ordinaCodTratta(tratte *vett[],int size);
void ordinaPartenza(tratte *vett[],int size);
void ordinaArrivo(tratte *vett[],int size);
void ricercaStazionePartenza(tratte vett[],int size);
void readFromFile(tratte **arrayTratte,tratteRif *riferimento,int mode,int *size){
    FILE *fp;
    tratte *temp;
    char input[S];
    int nr;
    if(mode==0) {
        fp = fopen("log.txt", "r");
        if (fp == NULL)
            EXIT_FAILURE;
    }
    else{
        printf("\n inserire nome file da aprire : ");
        scanf("%s",input);
        fp=fopen(input,"r");
        if(fp==NULL)
            EXIT_FAILURE;
    }
    fscanf(fp,"%d",&nr);
    *size=nr;
    *arrayTratte=(tratte*)malloc(nr*sizeof(tratte));
    temp=(tratte*)malloc(nr*sizeof(tratte));
    (*arrayTratte)[0].partenza;
    for(int i = 0 ; i < nr ; i++){
        fscanf(fp," %s %s %s %s %s %s %d ", (*arrayTratte)[i].cod_tratta,(*arrayTratte)[i].partenza,
               (*arrayTratte)[i].destinazione,(*arrayTratte)[i].data,(*arrayTratte)[i].ora_partenza,
               (*arrayTratte)[i].ora_arrivo,&(*arrayTratte)[i].ritardo);
    }
    for(int i = 0; i < nr ; i++){
        (*riferimento).ptrData[i]=&(*arrayTratte)[i];
        (*riferimento).ptrArrivo[i]=&(*arrayTratte)[i];
        (*riferimento).ptrCodTratta[i]=&(*arrayTratte)[i];
        (*riferimento).ptrPartenza[i]=&(*arrayTratte)[i];
    }

    fclose(fp);
}

int main() {
    tratte *arrayTratte;
    tratteRif riferimento;
    FILE *fp;
    int nr;
    int exit=0;
    //memorizzazione
    readFromFile(&arrayTratte,&riferimento,0,&nr);


    //aggancio i puntatori

    do{
        switch(leggiComando()){
            case r_print:
                stampaDatabase(arrayTratte,nr);
                break;
            case r_Ord_Data:
                ordinaData(riferimento.ptrData,nr);
                break;
            case r_Ord_CodTratta:
                ordinaCodTratta(riferimento.ptrCodTratta,nr);
                break;
            case r_Ord_Stazione_Partenza:
                ordinaPartenza(riferimento.ptrPartenza,nr);
                break;
            case r_Ord_Stazione_Arrivo:
                ordinaArrivo(riferimento.ptrArrivo,nr);
                break;
            case r_Ricerca_Stazione_Partenza:
                ricercaStazionePartenza(arrayTratte,nr);
                break;
            case r_lettura:
                free(arrayTratte);
                readFromFile(&arrayTratte,&riferimento,1,&nr);
                break;
            case r_fine:
                exit=1;
                break;
        }

    }
    while(!exit);
    return 0;
}

//main functions
void stampaDatabase(tratte vett[],int size){
    FILE *sp;
    int printSelection=0;
    printf("\n Inserire 1 per stampare su video o 2 per stampare su file: \n");
    scanf("%d",&printSelection);
    if(printSelection==1){
        for(int i=0; i < size ; i++)
            stampaTratta(vett,i);
    }
    else {
        sp = fopen("output.txt", "w");
        for (int index = 0; index < size; index++) {
            fprintf(sp, "%s %s %s %s %s %s %d\n", vett[index].cod_tratta, vett[index].partenza,
                    vett[index].destinazione, vett[index].data, vett[index].ora_partenza,
                    vett[index].ora_arrivo, vett[index].ritardo);
        }
    }
}

void ordinaData(tratte *vett[],int size){
    tratte *temp;
    dicotomica=0;
    for(int i = 0; i<size-1; i++) {
        for(int k = 0; k<size-1-i; k++) {
            if(dateToLong(vett[k]->data) >dateToLong(vett[k+1]->data)) {
                temp = vett[k];
                vett[k] = vett[k+1];
                vett[k+1] = temp;
            }
        }
    }
    for(int i = 0 ; i < size ; i++){
        printf(" %s %s %s %s %s %s %d\n", vett[i]->cod_tratta, vett[i]->partenza,
               vett[i]->destinazione, vett[i]->data, vett[i]->ora_partenza,
               vett[i]->ora_arrivo, vett[i]->ritardo);
    }
}

void ordinaCodTratta(tratte *vett[],int size){
    tratte *temp;
    dicotomica=0;
    for(int i = 0; i<size-1; i++) {
        for(int k = 0; k<size-1-i; k++) {
            if(strcmp(vett[k]->cod_tratta,vett[k+1]->cod_tratta)>0) {
                temp = vett[k];
                vett[k] = vett[k+1];
                vett[k+1] = temp;
            }
        }
    }
}

void ordinaPartenza(tratte *vett[],int size){
    tratte *temp;
    dicotomica=1;
    for(int i = 0; i<size-1; i++) {
        for(int k = 0; k<size-1-i; k++) {
            if(strcmp(vett[k]->partenza,vett[k+1]->partenza)>0) {
                temp = vett[k];
                vett[k] = vett[k+1];
                vett[k+1] = temp;
            }
        }
    }
}

void ordinaArrivo(tratte *vett[],int size){
    tratte *temp;
    for(int i = 0; i<size-1; i++) {
        for(int k = 0; k<size-1-i; k++) {
            if(strcmp(vett[k]->destinazione,vett[k+1]->destinazione)>0) {
                temp = vett[k];
                vett[k] = vett[k+1];
                vett[k+1] = temp;
            }
        }
    }
    dicotomica=1;
}

void ricercaStazionePartenza(tratte vett[],int size){
    char input[N];
    int l=0;
    int m=0;
    int r=size;
    char c;
    printf("\nInserire stazione di partenza da cercare: \n");
    scanf("%s",input);
    c=input[0];
    if (dicotomica==0){
        for(int i = 0 ; i < size ; i++){
            if(vett[i].partenza[0]==c){
                printf("\n-%s \n",vett[i].partenza);
            }
        }
    }
    else{
        while(l<=r){
            m = (l+r)/2;
            if(vett[m].partenza[0]==c){
                printf("\n-%s \n",vett[m].partenza);
            }
            if(vett[m].partenza[0]<c)
                l=m+1;
            else
                r=m-1;
        }

    }
}








//tool
comando_e leggiComando(){
    char selezione[S];
    char tabella[r_fine+1][S]={"stampa","ordinaData","ordinaCodtratta","ordinaPartenza","ordinaArrivo","ricercaPartenza","lettura","fine"};
    printf("\nInserisci comando : stampa , ordinaData , ordinaCodtratta, ordinaPartenza , ordinaArrivo, ricercaPartenza,lettura, fine: \n");
    scanf("%s",selezione);
    for(int i=0; i < r_fine; i++){
        if(strcmp(tabella[i],selezione)==0)
            return i;
    }
    return r_fine;
}
int confrontaDate(char data1[S],char data2[S]){
    long data1l,data2l;
    data1l=dateToLong(data1);
    data2l=dateToLong(data2);
    if(data1l>=data2l)
        return 1;
    else
        return 0;
}

long dateToLong(char date[S]){
    int d,m,a;
    long res;
    sscanf(date,"%d/%d/%d",&a,&m,&d);
    a-=2017;
    res=a*31536000+2592000*m+86400*d;
    return res;
}

void stampaTratta(tratte vett[],int index){
    printf(" %s %s %s %s %s %s %d \n", vett[index].cod_tratta, vett[index].partenza,
           vett[index].destinazione, vett[index].data, vett[index].ora_partenza,
           vett[index].ora_arrivo, vett[index].ritardo);
}

