
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

int STInsert(ST tab,char *label,int index){
    if(STSearch(tab,label)!=-1)
        return -1;
    int lastindex;
    for(int i=0; i < strlen(label); i++){
        tab.mat[index][i]=label[i];
        lastindex=i;
    }
    lastindex++;
    tab.mat[index][lastindex]='\0';
    return 0;
}

int STSearch(ST tab,char *label){
    for(int i=0; i < tab.size ; i++){
        if((strcmp(label,tab.mat[i]))==0) {
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
        for(int j=0 ; j < strlen(tab.mat[i]); j++){
            printf("%c",tab.mat[i][j]);
        }
        printf("index %d",i);
        printf("\n");
    }
}