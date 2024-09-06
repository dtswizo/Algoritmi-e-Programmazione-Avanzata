#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "itemList.h"

 typedef struct node *link,node_t;

static link newNode(ITEM val, link next);


struct node{
    ITEM val;
    link next;
};

struct itemList_s{
    link headPg;
    link tailPg;
    int nItems;
};

static link newNode(ITEM  val, link next){
    link x = malloc(sizeof(*x));
    if(x == NULL)
        return NULL;
    else{
        x->val=val;
        x->next=next;
    }
    return x;
}

itemList_t itemList_init(){
    itemList_t itemList=malloc(sizeof(*itemList));
    itemList->headPg=NULL;
    itemList->tailPg=NULL;
    itemList->nItems=0;
    return itemList;
}

void itemList_insert(itemList_t itemList,ITEM it){
    (itemList->nItems)++;
    link actual= newNode(it,NULL);
    if(itemList->headPg==NULL){
        itemList->headPg=actual;
        itemList->tailPg=actual;
    }
    else{
        itemList->tailPg->next=actual;
        itemList->tailPg=actual;
    }
}

ITEM itemList_searchByLabel(itemList_t itemList, char* label){
    link x,p;
    int found=0;
    for(x=itemList->headPg, p=NULL;  x!= NULL; p=x, x=x->next){
        if(strcmp(ITEMgetLabel(x->val),label)==0){
            found=1;
            return x->val;
        }
    }
    return NULL;
}