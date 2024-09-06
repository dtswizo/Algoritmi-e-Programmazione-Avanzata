#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "pgList.h"

typedef struct node *link,node_t;

static link newNode(pg_t val, link next);


struct node{
    pg_t val;
    link next;
};

 struct pgList_s{
    link headPg;
    link tailPg;
    int nPg;
};

pgList_t pgList_init(){
    pgList_t pgList=malloc(sizeof(*pgList));
    pgList->headPg=NULL;
    pgList->tailPg=NULL;
    pgList->nPg=0;
    return pgList;
}

void pgList_insert(pgList_t pgList, pg_t pg){
    (pgList->nPg)++;
    link actual= newNode(pg,NULL);
    actual->val.equip= equipArray_init();
    if(pgList->headPg==NULL){
        pgList->headPg=actual;
        pgList->tailPg=actual;
    }
    else{
        pgList->tailPg->next=actual;
        pgList->tailPg=actual;
    }
}

void pgList_remove(pgList_t pgList, char* cod){
   link x,p;
   for(x=pgList->headPg , p = NULL; x!=NULL ; p=x , x=x->next){
     if((strcmp(x->val.cod,cod))==0){
         (pgList->nPg)--;
         if(x==pgList->headPg && x==pgList->tailPg){
             pgList->headPg=NULL;
             pgList->tailPg=NULL;
         }
         else if(x==pgList->headPg)
            pgList->headPg = x->next;
         else if (x==pgList->tailPg){
             p->next=NULL;
         }
         else
          p->next=x->next;
        }
     }
}


void pgList_read(FILE *fp, pgList_t pgList){
    pg_t actual;
    if(fp==NULL)
        return;
    while(pg_read(fp,&actual)!=0){
        pgList_insert(pgList,actual);
    }

}



void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link x;
    printf("Personaggi nel database:\n");
    for(x=pgList->headPg; x != NULL ; x=x->next) {
    pg_print(fp,&x->val,invArray);
    }
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link x,p;
    int found=0;
    for(x=pgList->headPg, p=NULL;  x!= NULL; p=x, x=x->next){
        if(strcmp(x->val.cod,cod)==0){
            found=1;
            return &x->val;
        }
    }
    return NULL;
}

void pgList_free(pgList_t pgList){
    link x;
    for(x=pgList->headPg ; x!= pgList->tailPg ; x->next){
        free(x);
    }

}

static link newNode(pg_t val, link next){
    link x = malloc(sizeof(*x));
    if(x == NULL)
        return NULL;
    else{
        x->val=val;
        x->next=next;
    }
    return x;
}
