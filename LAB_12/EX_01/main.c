#include <stdio.h>
#include <stdlib.h>
#include "ListTitoli.h"
#include <string.h>
#include "BST.h"
#include "quotazioneGiornaliera.h"

#define N 30

typedef enum{
    r_acquisizione,r_ricercaTitolo,r_ricercaQuotazione,r_minMax,r_dopo,r_dopo2,r_err
}comandi;

void leggi_E_Alloca(char *nomeFile,titoliList_t *listTitoli);
int leggi_comando();

int main() {
    setbuf(stdout,NULL);
    char input[N];
    char data[N],data1[N];
    int Soglia;
    Titolo t;
    int fine=0;
    titoliList_t listTitoli=titoliList_init();
    leggi_E_Alloca("F1.txt",&listTitoli);
    while(fine==0) {
        switch (leggi_comando()) {
            case 0:
                leggi_E_Alloca("F1.txt", &listTitoli);
                break;
            case 1:
                printf("\nInserire titolo da cercare: ");
                scanf("%s", input);
                t = itemList_search(listTitoli, input);
                if (t != NULL)
                    printf("\nTitolo %s trovato", getName(t));
                break;
            case 2:
                printf("\nInserire titolo e data:");
                scanf("%s %s", input,data);
                t=itemList_search(listTitoli, input);
                if(t!=NULL){
                   if(getQuotazioneGiornaliera(t,data)!=-1){
                       printf("\nMedia pesata %f",getQuotazioneGiornaliera(t,data));
                   }
                }
                break;
            case 3:
                printf("\nInserire titolo e date:");
                scanf("%s %s %s", input,data,data1);
                t=itemList_search(listTitoli, input);
                if(t!=NULL){
                    minMaxQuotazioni(t,data,data1);
                }
            case 4:
                printf("\nInserire titolo:");
                scanf("%s", input);
                t=itemList_search(listTitoli, input);
                if(t!=NULL){
                    minMaxQuotazioniGlobal(t);
                }
                break;
            case 5:
                printf("\nInserire titolo:");
                scanf("%s", input);
                printf("\nInserire Soglia:");
                scanf("%d",Soglia);
                break;
            default:
                fine=1;
                break;
        }
    }



    return 0;
}

void leggi_E_Alloca(char *nomeFile,titoliList_t *listTitoli){
    FILE *fp;
    char tempTitolo[S],tempDate[S],lastDate[S],tempOra[S];
    entryQuotazione tempQuotazione;
    float tempValore;
    int tempQuantita;
    int nTitoli=0;
    int entriesTitolo=0;
    fp=fopen(nomeFile,"r");
    fscanf(fp,"%d",&nTitoli);
    for(int i=0 ; i < nTitoli ; i++){
        fscanf(fp,"%s %d",tempTitolo,&entriesTitolo);
        itemList_insert(*listTitoli, createTitolo(tempTitolo));
        printf("%s %d\n",tempTitolo,entriesTitolo);
        for(int j=0; j < entriesTitolo; j++){
            fscanf(fp, "%s %s %f %d", tempDate, tempOra, &tempValore, &tempQuantita);
            printf("%s %s %.2f %d\n", tempDate, tempOra, tempValore, tempQuantita);
            tempQuotazione.d= createDataItem(tempDate);
            tempQuotazione.SOMMA_PESATA=tempValore;
            tempQuotazione.PESO_TOT=tempQuantita;
            addQuotazioneGiornaliera(itemList_search(*listTitoli,tempTitolo),tempQuotazione);
        }
        printf("\n");
    }
    fclose(fp);
}

int leggi_comando(){
    char tabella[r_err+1][N]={"acquisizione","ricercaTitolo","ricercaQuotazione","ordinaPartenza","ordinaArrivo","ricercaPartenza","fine"};
    char selezione[N];
    printf("\nInserisci comando : acquisizione , ricercaTitolo , ricercaQuotazione, ordinaPartenza , ordinaArrivo, ricercaPartenza,lettura, fine: \n");
    scanf("%s",selezione);
    for(int i=0; i < r_err; i++){
        if(strcmp(tabella[i],selezione)==0)
            return i;
    }
    return r_err;
}

