#include "titolo.h"


#ifndef LAB_12_LISTTITOLI_H
#define LAB_12_LISTTITOLI_H

typedef struct titoliList_s *titoliList_t;


titoliList_t titoliList_init();
void itemList_insert(titoliList_t titoliList,Titolo it);
Titolo itemList_search(titoliList_t titoliList,char *nome);













#endif //LAB_12_LISTTITOLI_H
