#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "invArray.h"
#ifndef N
#define N 50
#endif

struct invArray_s{
    inv_t *vettInv;
    int nInv;
};

invArray_t invArray_init(){
    invArray_t invArray=malloc(sizeof(*invArray));
    return invArray;
}

void invArray_read(FILE *fp, invArray_t invArray){
   fscanf(fp," %d ",&invArray->nInv);
   invArray->vettInv=malloc(invArray->nInv * sizeof(inv_t));
   for(int i=0; i < invArray->nInv; i++){
       inv_read(fp,&(invArray->vettInv[i]));
   }

}

void invArray_print(FILE *fp, invArray_t invArray){
    for(int i=0; i < invArray->nInv; i++){
        inv_print(fp,&(invArray->vettInv[i]));
    }
}

int invArray_searchByName(invArray_t invArray, char *name){
    for(int i=0 ; i < invArray->nInv; i++){
        if((strcmp(invArray->vettInv[i].nome,name))==0)
            return i;
    }
    return -1;
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &invArray->vettInv[index];
}