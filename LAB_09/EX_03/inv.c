#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "inv.h"

void caricaOggettiDaFile(tabInv_t **tabInv, char *filename){
    int nr;
    inv_t temp;
    FILE *fp;
    fp=fopen(filename,"r");
    fscanf(fp,"%d",&nr);
    (*tabInv)->arrayOggetti=(inv_t*)malloc(nr * sizeof(inv_t));
    for(int i=0; i < nr ; i++) {
        fscanf(fp, "%s %s %d %d %d %d %d %d",temp.nome,temp.tipologia,&temp.stat.hp,&temp.stat.mp,&temp.stat.atk,&temp.stat.def,&temp.stat.mag,&temp.stat.spr);
        ((*tabInv)->arrayOggetti)[i]=temp;
        ((*tabInv)->nInv)++;
    }

    fclose(fp);
}

void initAndLink_tabInv_t(tabInv_t **tabInv,tabInv_t *tabInvInit){
    (*tabInvInit).nInv=0;
    *tabInv=&(*tabInvInit);
}

void stampaOggetto(inv_t* oggetto){
    printf("%s %s %d %d %d %d %d %d\n", oggetto->nome,oggetto->tipologia,
           oggetto->stat.hp,oggetto->stat.mp,oggetto->stat.atk,oggetto->stat.def,
           oggetto->stat.mag,oggetto->stat.spr);
}

void stampaOggetti(tabInv_t *tabInv){
    for(int i=0 ; i < tabInv->nInv ; i++) {
        stampaOggetto(&(tabInv->arrayOggetti)[i]);
    }
}

inv_t* find_Obj_By_Name(tabInv_t *tabInv,char *nome){
    for(int i=0 ; i < tabInv->nInv ; i++){
        if(strcmp((tabInv->arrayOggetti)[i].nome,nome)==0){
            return &((tabInv->arrayOggetti)[i]);
        }
    }
    return NULL;
}

