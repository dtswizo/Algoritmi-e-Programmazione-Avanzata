#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#ifndef N
#define N 30
#endif // N
#ifndef S
#define S 8
#endif // S
#ifndef ADD
#define ADD 101
#endif // ADD
#ifndef REMOVE
#define REMOVE 102
#endif

#include "inv.h"
#include "pg.h"

typedef enum{
    r_caricaPg,r_caricaOggetti,
    r_aggiungiPg,r_cancellaPg,r_aggiungi_rimuovi_equipPg,r_calcolaStats,r_stampaPg,r_err
}comando;

int leggiComando();


int main() {
    setbuf(stdout, NULL);
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
                                "aggiungiPg","cancellaPg","aggiungi_rimuovi_equipPg","calcolaStats","stampaPg","err"};
    char input[N];
    int index;
    printf("Lista Comandi: \n");
    for(int i = 0 ; i < r_err ; i++) printf("-%s\n",selezione[i]);
    printf("Inserisci Comando: ");
    scanf("%s",input);
    for(int i=0; i < strlen(input); i++){
        if(strcmp(input,selezione[i])==0){
            index=i;
            break;
        }

    }
    return index;
}
