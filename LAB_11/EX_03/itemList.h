//
// Created by wizodts on 31/12/2021.
//

#ifndef EX_03_ITEMLIST_H
#define EX_03_ITEMLIST_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ITEM.h"

typedef struct itemList_s *itemList_t;

/* creatore e distruttore */
itemList_t itemList_init();
void itemList_free(itemList_t itemList);
void itemList_insert(itemList_t itemList,ITEM it);
ITEM itemList_searchByLabel(itemList_t itemList, char* label);




#endif //EX_03_ITEMLIST_H
