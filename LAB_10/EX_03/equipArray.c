#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "equipArray.h"
#include "inv.h"
#define N 50

struct equipArray_s{
   int inUso;
   int vettEq[N];
};

equipArray_t equipArray_init(){
    equipArray_t equipArray=malloc(sizeof(*equipArray));
    for(int i=0; i < N ; i++){
        (equipArray->vettEq)[i]=-1;
    }
    return equipArray;
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    int slct;
    char obj[N];
    int index;
    printf("Aggiungere Equip 1 , Rimuovere Equip 0 : ");
    scanf("%d",&slct);
    printf("\n");
    printf("Inserire Nome Oggetto: ");
    scanf("%s",obj);
    printf("\n");
    index=invArray_searchByName(invArray,obj);
    if(index==-1){
        printf("Oggetto non trovato\n");
        return;
    }

    if(slct==1){    //aggiunta
     for(int i=0; i < N ; i++){
         if(equipArray->vettEq[i]==-1){
             equipArray->vettEq[i]=index;
             (equipArray->inUso)++;
             break;
         }
      }
    }
    else{
        for(int i=0; i < N ; i++){
            if(equipArray->vettEq[i]==index){
                equipArray->vettEq[i]=-1;
                (equipArray->inUso)--;
                break;
            }
        }
    }
    //equipArray_print(stdout,equipArray,invArray);
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    for(int i=0 ; i < N ; i++){
        if(equipArray->vettEq[i]!=-1){
            fprintf(fp,"%s ", invArray_getByIndex(invArray,i)->nome);

            printf("\n");
        }
    }

}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}

stat_t calcolaStatsEquip(equipArray_t equipArray,invArray_t invArray){
    int cnt=0;
    stat_t res;
    res.spr=res.mag=res.atk=res.mp=res.hp=res.def=0;
    for(int i=0 ; cnt < equipArray->inUso; i++){
        if(equipArray->vettEq[i]!=-1){
            cnt++;
            res.mp+=inv_getStat(invArray_getByIndex(invArray,i)).mp;
            res.def+=inv_getStat(invArray_getByIndex(invArray,i)).def;
            res.hp+=inv_getStat(invArray_getByIndex(invArray,i)).hp;
            res.atk+=inv_getStat(invArray_getByIndex(invArray,i)).atk;
            res.spr+=inv_getStat(invArray_getByIndex(invArray,i)).spr;
            res.mag+=inv_getStat(invArray_getByIndex(invArray,i)).mag;
        }
    }
    return res;
}

void equipArray_free(equipArray_t equipArray){
   free(equipArray);
}

