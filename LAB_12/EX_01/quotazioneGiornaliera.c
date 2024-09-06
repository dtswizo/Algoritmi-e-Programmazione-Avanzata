#include <stdlib.h>
#include "quotazioneGiornaliera.h"


entryQuotazione ITEMsetNull(){
    entryQuotazione res;
    res.d.m=0;
    res.d.y=0;
    res.d.g=0;
    res.SOMMA_PESATA=-1;
    return res;
}
