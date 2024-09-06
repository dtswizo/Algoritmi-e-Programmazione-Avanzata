#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#ifndef EX_03_ST_H
#define EX_03_ST_H

typedef struct{
  char **mat;
  int size;
}ST;


void ST_Init(ST *tab,int size);

void STFree(ST tab);

int STInsert(ST tab,char *label,int index);

int STSearch(ST tab,char *label);

char *STGetLabelByIndex(ST tab,int index);

void printMat(ST tab);





















#endif //EX_03_ST_H
