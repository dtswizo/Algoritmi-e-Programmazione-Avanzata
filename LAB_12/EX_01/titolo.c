#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "titolo.h"


struct titolo{
char *nome;
BST BSTquotazioni;
};

Titolo createTitolo(char *nome){
   Titolo t=malloc(sizeof(*t));
   t->BSTquotazioni=BSTinit();
   t->nome=(char*)malloc(strlen(nome)*sizeof(char));
   strcpy(t->nome,nome);
   return t;
}

char *getName(Titolo t){
    return t->nome;
}

void addQuotazioneGiornaliera(Titolo t,entryQuotazione entry){
    BSTinsert_leafR(t->BSTquotazioni,entry);
}

float getQuotazioneGiornaliera(Titolo t,char *data){
    entryQuotazione res;
   res=BSTsearch(t->BSTquotazioni, createDataItem(data));
   if(res.SOMMA_PESATA == -1)
       printf("non trovato");
   else{
       return res.SOMMA_PESATA/res.PESO_TOT;
   }
}

void minMaxQuotazioni(Titolo t,char *data1,char *data2){
    minMaxInorderW(t->BSTquotazioni,data1,data2);
}

void minMaxQuotazioniGlobal(Titolo t){
    minMaxInorderWGlobal(t->BSTquotazioni);
}


