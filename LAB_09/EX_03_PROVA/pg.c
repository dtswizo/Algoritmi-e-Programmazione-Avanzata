#include "pg.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

link newNode(pg_t val, link next){
    link x = malloc(sizeof(*x));
    if(x == NULL)
        return NULL;
    else{
        x->val=val;
        x->next=next;
    }
    return x;
}


link listInsTail(link h, pg_t val,link *tail){
    link x;
    val.equip=(tabEquip_t*)malloc(sizeof(tabEquip_t));
    val.equip->inUso=0;
    for(int i=0;i<S;i++) (val.equip->vettEq)[i]=NULL;
    if (h==NULL)
        return newNode(val, NULL);
    for(x=h; x->next!=NULL; x=x->next);
    x->next= newNode(val,NULL);
    *tail=x->next;
    return h;
}
int listDelExtCodice(link *h,char *codice,link *tail){
    link x,p;
    int found=0;
    for(x=*h, p=NULL;  x!= NULL; p=x, x=x->next){
        if(strcmp(x->val.codice,codice)==0){
            found=1;
            if(x==*h) {
                *h = x->next;
                *tail=NULL;
            }
            else {
                p->next = x->next;
                *tail=p;
            }
            free(x);
            break;
        }
    }
    if(found==1)
        return 1;
    else
        return -1;
}


void caricaPgDaFile(tabPg_t *tabPg,char *filename){
    FILE *fp;
    link tail=NULL;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("errore apertura file\n");
        EXIT_FAILURE;
    }
    pg_t actual;
    while((fscanf(fp,"%s %s %s %d %d %d %d %d %d",actual.codice,actual.nome,actual.classe,&actual.stat.hp,&actual.stat.mp,&actual.stat.atk,&actual.stat.def,&actual.stat.mag,&actual.stat.spr))!=EOF) {
        (*tabPg).headPg = listInsTail((*tabPg).headPg, actual,&tail);
        if(tabPg->nPg==0)
            update_tabPg_t((*tabPg).headPg,tabPg,ADD);
        else{
            if(tail==NULL)
                printf("errore carica Pg Tail");
            update_tabPg_t(tail,tabPg,ADD);
        }
    }
    fclose(fp);
}

void aggiungiPersonaggio(tabPg_t *tabPg){
    pg_t actual;
    tabEquip_t equip;
    equip.inUso=0;
    link tail=NULL;
    printf("Inserisci Codice Nome Tipologia Hp Mp atk def Mag Spr : ");
    scanf("%s %s %s %d %d %d %d %d %d",actual.codice,actual.nome,actual.classe,&actual.stat.hp,&actual.stat.mp,&actual.stat.atk,&actual.stat.def,&actual.stat.mag,&actual.stat.spr);
    actual.equip=&equip;
    tabPg->headPg= listInsTail(tabPg->headPg,actual,&tail);
    if(tabPg->nPg==0)
        update_tabPg_t(tabPg->headPg,tabPg,ADD);
    else{
        if(tail==NULL)
            printf("errore carica Pg Tail");
        update_tabPg_t(tail,tabPg,ADD);
    }
    printf("\n");
}

void eliminaPersonaggio(tabPg_t *tabPg){
    char *codice;
    link tail=NULL;
    printf("Inserisci Codice Personaggio da cancellare: ");
    scanf("%s",codice);
    //C'è un caso non trattato, se si cancella la testa tabPg_t non viene aggiornata corretamente
    listDelExtCodice(&(tabPg->headPg),codice,&tail);
    if(strcmp((tabPg->headPg->val).codice,codice)==0){
        tabPg->nPg--;
        tabPg->headPg=tabPg->headPg;
    }
    else
        update_tabPg_t(tail,tabPg,REMOVE);
}

void initAndLink_tabPg(tabPg_t **tabPg,tabPg_t *tabPgInit){
    (*tabPgInit).headPg=NULL;
    (*tabPgInit).tailPg=NULL;
    (*tabPgInit).nPg=0;
    *tabPg=&(*tabPgInit);
}

void update_tabPg_t(link x,tabPg_t *tabPg,int mode) {
    if (mode == ADD) {
        if (tabPg->nPg == 0) {
            (tabPg->nPg)++;
            tabPg->headPg = x;
        } else {
            (tabPg->nPg)++;
            tabPg->tailPg = x;
        }
    } else {
        if (tabPg->nPg == 1) {
            (tabPg->nPg)--;
            tabPg->headPg = NULL;
            tabPg->tailPg = NULL;
        } else {
            (tabPg->nPg)--;
            tabPg->tailPg = x;
        }
    }
}

void aggiungi_rimuovi_equipPg(tabPg_t *tabPg,tabInv_t *tabInv){
    int select;
    int temp;
    link x;
    inv_t* objPointer;
    char codice[N];
    char oggetto[N];
    printf("\nInserisci Codice personaggio:");
    scanf("%s",codice);
    x=find_Pg_By_Code(tabPg->headPg,codice);
    if(x==NULL){
        printf("Personaggio non trovato");
        return;
    }
    printf("\nInserisci Nome Oggetto:");
    scanf("%s",oggetto);
    objPointer=find_Obj_By_Name(tabInv,oggetto);
    if(objPointer==NULL){
        printf("Oggetto non trovato");
        return;
    }
    printf("\n Aggiungi 0 , Rimuovi 1: ");
    scanf("%d",&select);
    temp=x->val.equip->inUso;
    if(select==0){
        for(int i=0;i<S;i++){
            if((x->val.equip->vettEq)[i]==NULL) {
                (x->val.equip->vettEq)[i] = objPointer;
                break;
            }
        }
        (x->val.equip->inUso)++;
    }
    else{
        for(int i=0; i < S; i++){
            if( (x->val.equip->vettEq)[i]!=NULL && strcmp((x->val.equip->vettEq)[i]->nome,oggetto)==0)
                (x->val.equip->vettEq)[i]=NULL;
        }
        (x->val.equip->inUso)--;
    }
}

void calcola_stats_pg(tabPg_t *tabPg) {
    link x;
    int count = 0;
    char codice[N];
    int t[5];
    printf("\nInserisci codice personaggio: ");
    scanf("%s", codice);
    x = find_Pg_By_Code(tabPg->headPg, codice);
    if (x == NULL) {
        printf("Non trovato");
        return;
    }
}

link find_Pg_By_Code(link h,char *codice){
    link x,p;
    int found=0;
    for(x=h, p=NULL;  x!= NULL; p=x, x=x->next){
        if(strcmp(x->val.codice,codice)==0){
            found=1;
            return x;
        }
    }
    return NULL;
}

void stampaPersonaggi(tabPg_t *tabPg){
    link x;
    printf("Personaggi nel database:\n");
    for(x=tabPg->headPg; x != NULL ; x=x->next) {
        printf("%s %s %s %d %d %d %d %d %d",x->val.codice,x->val.nome,x->val.classe,x->val.stat.hp,x->val.stat.mp,x->val.stat.atk,x->val.stat.def,x->val.stat.mag,x->val.stat.spr);
        printf("\n");
    }
}
void stampaEquipPg(tabPg_t *tabPg,char *codice) {
    link x;
    x = find_Pg_By_Code(tabPg->headPg, codice);
    for (int i = 0; i < S; i++) {
        if ((x->val.equip->vettEq)[i] != NULL) {
            printf("%s %s %d %d %d %d %d %d", (x->val.equip->vettEq)[i]->nome, (x->val.equip->vettEq)[i]->tipologia,
                   (x->val.equip->vettEq)[i]->stat.hp,
                   (x->val.equip->vettEq)[i]->stat.mp, (x->val.equip->vettEq)[i]->stat.atk,
                   (x->val.equip->vettEq)[i]->stat.def, (x->val.equip->vettEq)[i]->stat.mag,
                   (x->val.equip->vettEq)[i]->stat.spr);
            printf("\n");
        }
    }
}
