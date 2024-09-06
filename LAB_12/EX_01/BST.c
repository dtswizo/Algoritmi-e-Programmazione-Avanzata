#include <stdlib.h>
#include <stdio.h>
#include "quotazioneGiornaliera.h"
#include <float.h>
#include "BST.h"

typedef struct BSTnode* link;
struct BSTnode {entryQuotazione item; link l; link r;int N;};
struct binarysearchtree {link root; link z; int N;};

static link NEW(entryQuotazione item, link l , link r) {
    link x= malloc(sizeof(*x));
    x->item = item; x->l = l ; x->r = r;
    return x;
}

BST BSTinit(){
    BST bst=malloc(sizeof(*bst));
    bst->N=0;
    bst->root->N=0;
    bst->root=(bst->z = NEW(ITEMsetNull(),NULL , NULL ));
    return bst;
}

void BSTfree(BST bst){
    if(bst==NULL)
        return;
    else{
        free(bst);
    }
}

static link insertR(link h, entryQuotazione item, link z){
    if(h==z) {
        item.nTitoli=1;
        return NEW(item, z, z);
    }
    if(confrontaDate(item.d,h->item.d)==-1){
        h->l = insertR(h->l,item, z);
    }
    else if(confrontaDate(item.d,h->item.d)==0){
        h->item.PESO_TOT+=item.PESO_TOT;
        h->item.SOMMA_PESATA+=item.PESO_TOT*item.SOMMA_PESATA;
        h->item.nTitoli+=1;
    }
    else{
        h->r = insertR(h->r,item, z);
    }
    (h->N)++;
    return h;
}

void BSTinsert_leafR(BST bst, entryQuotazione item){
    bst->root= insertR(bst->root, item , bst->z);
}

static entryQuotazione searchR(link h,data key, link z){
  int cmp;
  if(h==z)
      return ITEMsetNull();
  cmp=confrontaDate(key,h->item.d);
  if(cmp==0)
      return h->item;
  if (cmp == -1){
      return searchR(h->l,key,z);
  }
  else{
      return searchR(h->r,key,z);
  }
}

entryQuotazione BSTsearch(BST bst, data key){
    return searchR(bst->root,key,bst->z);
}

static void minMaxInorder(link h,link z,char *data1,char *data2,float *min,float *max){
    float quotazione=0;
    if(h==z)
        return;
    minMaxInorder(h->l,z,data1,data2,min,max);
        if (confrontaDate(h->item.d, createDataItem(data1)) &&
            confrontaDate(h->item.d, createDataItem(data2))) { //questo confronto non considera l'uguaglianza
            quotazione = h->item.SOMMA_PESATA / h->item.PESO_TOT;
            if (quotazione < *min) {
                *min = quotazione;
            }
            if (quotazione > *max)
                *max = quotazione;
        }
    minMaxInorder(h->r,z,data1,data2,min,max);
}

static void minMaxInorderGlobal(link h,link z,float *min,float *max){
    float quotazione=0;
    if(h==z)
        return;
    minMaxInorderGlobal(h->l,z,min,max);
    if(h->item.SOMMA_PESATA!=-1) {
        quotazione = h->item.SOMMA_PESATA / h->item.PESO_TOT;
        if (quotazione < *min) {
            *min = quotazione;
        }
        if (quotazione > *max)
            *max = quotazione;
    }
    minMaxInorderGlobal(h->r,z,min,max);
}

void minMaxInorderW(BST bst,char *data1,char *data2){
    float min=FLT_MAX,max=FLT_MIN;
    minMaxInorder(bst->root,bst->z,data1,data2,&min,&max);
    printf("\nmin=%f max=%f",min,max);
}

void minMaxInorderWGlobal(BST bst){
    float min=FLT_MAX,max=FLT_MIN;
    printf("aa");
    minMaxInorderGlobal(bst->root,bst->z,&min,&max);
    printf("\nmin=%f max=%f",min,max);
}

static link rotL(link h){
    link x=h->r;
    h->r=x->l;
    x->l=h;
    return x;
}

static link rotR(link h){
    link x=h->l;
    h->l=x->r;
    x->r=h;
    return x;
}

static link partR(link h,int r){
   int t= h->l->N;
   if(t>r){
       h->l=partR(h->l,r);
       h=rotR(h);
   }
   else{
       h->r=partR(h->r,r-t-1);
       h=rotL(h);
   }
  return h;
}

void BSTbalance(BST bst){
    int r = (bst->N+1)/2-1;
    bst->root = partR(bst->root,r);
}






