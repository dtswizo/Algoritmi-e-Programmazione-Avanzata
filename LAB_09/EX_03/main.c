#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define N 30
#define S 8
#define ADD 101
#define REMOVE 102

#include "inv.h"
#include "pg.h"

typedef enum{
    r_caricaPg,r_caricaOggetti,
    r_aggiungiPg,r_cancellaPg,r_ricerca_Pg_Codice,r_stampaPersonaggio,r_aggiungi_rimuovi_equipPg,r_calcolaStats,r_cercaOggetto,r_stampaOggetto,r_stampaPg,r_err
}comando;

int leggiComando();


int main() {
    setbuf(stdout, NULL);
    inv_t* obj;
    link x;
    char input[S];
    tabInv_t *tabInv;
    tabInv_t tabInvInit;
    tabPg_t *tabPg;
    tabPg_t tabPgInit;
    initAndLink_tabPg(&tabPg,&tabPgInit);
    initAndLink_tabInv_t(&tabInv,&tabInvInit);
    int stop=0;
    do{
        switch(leggiComando()){
            case r_caricaPg:
                caricaPgDaFile(tabPg,"pg.txt");
                break;
            case r_caricaOggetti:
                caricaOggettiDaFile(&tabInv,"inventario.txt");
                stampaOggetti(tabInv);
                break;
            case r_aggiungiPg:
                aggiungiPersonaggio(tabPg);
                break;
            case r_ricerca_Pg_Codice:
                printf("\nInserisci Codice Pg Da cercare: ");
                scanf("%s",input);
                if(find_Pg_By_Code(tabPg->headPg,input)==NULL)
                    printf("\npersonaggio non trovato\n");
                else
                    printf("\npersonaggio Trovato\n");
                break;
            case r_stampaPersonaggio:
                printf("\nInserisci Codice Pg Da stampare: ");
                scanf("%s",input);
                x=find_Pg_By_Code(tabPg->headPg,input);
                if(x!=NULL) {
                    stampaPersonaggio(x);
                    stampaEquipPg(tabPg,input);
                }
                else
                    printf("\npersonaggio non trovato\n");
                break;

            case r_cancellaPg:
                eliminaPersonaggio(tabPg);
                printf("\nhead: %s",tabPg->headPg->val.codice);
                printf("\ntail: %s",tabPg->tailPg->val.codice);
                printf("\n%d",tabPg->nPg);
                break;
            case r_aggiungi_rimuovi_equipPg:
                aggiungi_rimuovi_equipPg(tabPg,tabInv);
                printf("%s",(tabPg->headPg->val.equip->vettEq)[0]->nome);
                break;
            case r_calcolaStats:
                //stampaEquipPg(tabPg,"PG0001");
                calcola_stats_pg(tabPg);
                break;
            case r_cercaOggetto:
                printf("\nInserisci Nome Oggetto Da cercare: ");
                scanf("%s",input);
                if(find_Obj_By_Name(tabInv,input)==NULL)
                    printf("\noggetto non trovato\n");
                else
                    printf("\noggetto Trovato\n");
                break;
            case r_stampaOggetto:
                printf("\nInserisci Nome Oggetto Da cercare: ");
                scanf("%s",input);
                obj=find_Obj_By_Name(tabInv,input);
                if(obj==NULL) {
                    printf("\noggetto non trovato\n");
                }
                else
                    stampaOggetto(obj);
                break;
            case r_stampaPg:
                stampaPersonaggi(tabPg);
                break;
            default:
                stop=1;
                break;
        }
    }
    while(stop!=1);

    return 0;
}

int leggiComando(){
    char selezione[r_err+1][N]={"caricaPg","caricaOggettiDaFile",
                                "aggiungiPg","cancellaPg","ricerca_Pg_Codice","stampaPersonaggio","aggiungi_rimuovi_equipPg","calcolaStats","cercaOggetto","stampaOggetto","stampaPg","err"};
    char input[N];
    int index;
    printf("Lista Comandi: \n");
    for(int i = 0 ; i < r_err ; i++) printf("-%s\n",selezione[i]);
    printf("Inserisci Comando: ");
    scanf("%s",input);
    for(int i=0; i < r_err; i++){
        if(strcmp(input,selezione[i])==0){
            index=i;
            break;
        }

    }
    return index;
}
