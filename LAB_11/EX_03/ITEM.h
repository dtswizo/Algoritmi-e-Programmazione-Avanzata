//
// Created by wizodts on 30/12/2021.
//

#ifndef EX_03_ITEM_H
#define EX_03_ITEM_H

//ADT I Classe
typedef struct item *ITEM;


ITEM ITEMnew(char *label, char *net);
void ITEMfree(ITEM I);
char *ITEMgetLabel(ITEM I);
char *ITEMgetNet(ITEM I);















#endif //EX_03_ITEM_H
