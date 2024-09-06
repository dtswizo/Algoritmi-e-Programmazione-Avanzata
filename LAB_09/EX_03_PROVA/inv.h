#ifndef INV_H_DEFINED
#define INV_H_DEFINED
#include <stdio.h>
#include <stdlib.h>
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

typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct{
    char nome[N];
    char tipologia[N];
    stat_t stat;
}inv_t;



typedef struct{
    inv_t *arrayOggetti;
    int nInv;
}tabInv_t;

void caricaOggettiDaFile(tabInv_t **tabInv, char *filename);
void initAndLink_tabInv_t(tabInv_t **tabInv,tabInv_t *tabInvInit);
void stampaOggetti(tabInv_t *tabInv);
inv_t* find_Obj_By_Name(tabInv_t *tabInv,char *nome);


#endif
