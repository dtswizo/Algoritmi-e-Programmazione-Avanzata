#ifndef EX_01_TITOLO_H
#define EX_01_TITOLO_H
#include "quotazioneGiornaliera.h"
#include "BST.h"

#ifndef S
#define S 20
#endif

typedef struct titolo *Titolo;

Titolo createTitolo(char *nome);
char *getName(Titolo t);
void addQuotazioneGiornaliera(Titolo t,entryQuotazione entry);
float getQuotazioneGiornaliera(Titolo t,char *data);
void minMaxQuotazioni(Titolo t,char *data1,char *data2);
void minMaxQuotazioniGlobal(Titolo t);







#endif //EX_01_TITOLO_H
