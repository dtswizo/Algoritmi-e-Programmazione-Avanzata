#ifndef EX_01_QUOTAZIONEGIORNALIERA_H
#define EX_01_QUOTAZIONEGIORNALIERA_H
#include "data.h"
#include "ora.h"

typedef struct{
    data d;
    float SOMMA_PESATA;
    int PESO_TOT;
    int nTitoli;
}entryQuotazione;


entryQuotazione ITEMsetNull();





#endif //EX_01_QUOTAZIONEGIORNALIERA_H
