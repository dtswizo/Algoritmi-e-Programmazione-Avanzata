#ifndef EX_01_BST_H
#define EX_01_BST_H
#include "quotazioneGiornaliera.h"

typedef struct binarysearchtree *BST;

BST BSTinit();
void BSTfree(BST bst);
void BSTinsert_leafR(BST bst, entryQuotazione item);
entryQuotazione BSTsearch(BST bst, data key);
void minMaxInorderW(BST bst,char *data1,char *data2);
void minMaxInorderWGlobal(BST bst);








#endif //EX_01_BST_H
