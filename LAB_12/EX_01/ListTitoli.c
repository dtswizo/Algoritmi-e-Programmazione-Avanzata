#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "ListTitoli.h"


typedef struct node *link,node_t;

static link newNode(Titolo val, link next);


struct node{
    Titolo val;
    link next;
};

struct titoliList_s{
    link headPg;
    link tailPg;
    int nItems;
};

static link newNode(Titolo  val, link next){
    link x = malloc(sizeof(*x));
    if(x == NULL)
        return NULL;
    else{
        x->val=val;
        x->next=next;
    }
    return x;
}

titoliList_t titoliList_init(){
    titoliList_t titoliList=malloc(sizeof(*titoliList));
    titoliList->headPg=NULL;
    titoliList->tailPg=NULL;
    titoliList->nItems=0;
    return titoliList;
}

void itemList_insert(titoliList_t titoliList,Titolo it){
    (titoliList->nItems)++;
    link actual= newNode(it,NULL);
    if(titoliList->headPg==NULL){
        titoliList->headPg=actual;
        titoliList->tailPg=actual;
    }
    else{
        titoliList->tailPg->next=actual;
        titoliList->tailPg=actual;
    }
}

Titolo itemList_search(titoliList_t titoliList,char *nome){
    link x;
    for(x=titoliList->headPg; x!=NULL ; x=x->next){
        if((strcmp(nome,getName(x->val)))==0){
            return x->val;
        }
    }
  return NULL;
}
