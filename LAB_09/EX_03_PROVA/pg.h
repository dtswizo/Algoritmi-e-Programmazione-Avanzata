#ifndef PG_H_DEFINED
#define PG_H_DEFINED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inv.h"
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

typedef struct{
    int inUso;
    inv_t *vettEq[S];
}tabEquip_t;

typedef struct{
    char codice[N];
    char nome[N];
    char classe[N];
    tabEquip_t *equip;
    stat_t stat;
}pg_t;

typedef struct node *link,node_t;

struct node{
    pg_t val;
    link next;
};


typedef struct{
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

void caricaPgDaFile(tabPg_t *tabPg,char *filename);
void aggiungiPersonaggio(tabPg_t *tabPg);
void eliminaPersonaggio(tabPg_t *tabPg);
void initAndLink_tabPg(tabPg_t **tabPg,tabPg_t *tabPgInit);
void update_tabPg_t(link x,tabPg_t *tabPg,int mode);
void aggiungi_rimuovi_equipPg(tabPg_t *tabPg,tabInv_t *tabInv);
void calcola_stats_pg(tabPg_t *tabPg);
link newNode(pg_t val, link next);
link listInsTail(link h, pg_t val,link *tail);
int listDelExtCodice(link *h,char *codice,link *tail);
void stampaPersonaggi(tabPg_t *tabPg);
void stampaEquipPg(tabPg_t *tabPg,char *codice);
link find_Pg_By_Code(link h,char *codice);


#endif
