
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "ITEM.h"

struct item{
    char *label;
    char *net;
};

ITEM ITEMnew(char *label, char *net) {
ITEM I= malloc(sizeof(*I));
I->label=malloc(strlen(label)*sizeof(char));
I->net=malloc(strlen(net)*sizeof(char));
strcpy(I->label,label);
strcpy(I->net,net);
return I;
}

void ITEMfree(ITEM I){
    if(I==NULL)
        return;
    free(I->label);
    free(I->net);
    free(I);
}

char *ITEMgetLabel(ITEM I){
    return I->label;
}

char *ITEMgetNet(ITEM I){
    return I->net;
}
