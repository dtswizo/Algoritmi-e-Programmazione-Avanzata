
#include "ST.h"

#define S 30


void ST_Init(ST *tab,int size){
    (*tab).mat=(char**)malloc(size*sizeof(char*));
    for(int i=0; i < size ; i++){
        (*tab).mat[i]=malloc(S*sizeof(char));
    }
    (*tab).size=0;
}

void STFree(ST tab){
    for(int i=0; i < tab.size ; i++){
        free(tab.mat[i]);
    }
    free(tab.mat);
}

int STInsert(ST tab,char name,int index){
    if(STSearch(tab,name)!=-1)
        return -1;
    tab.mat[index][0]=name;

    return 0;
}

int STSearch(ST tab,char name){
    for(int i=0; i < tab.size ; i++){
        if(tab.mat[i][0]==name) {
            return i;
        }
    }
    return -1;
}

char *STGetLabelByIndex(ST tab,int index){
    return tab.mat[index];
}

void printMat(ST tab){
    for(int i=0; i < tab.size ; i++){
            printf("%c",tab.mat[i][0]);
            printf("    index %d",i);
            printf("\n");
        }
}