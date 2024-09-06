#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "inv.h"

void stat_print(FILE *fp, stat_t *statp, int soglia){
  printf("%d %d %d %d %d %d %d ",statp->hp,statp->mp,statp->atk,statp->def,statp->mag,statp->spr);
}

void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp," %d %d %d %d %d %d %d ",&statp->hp,&statp->mp,&statp->atk,&statp->def,&statp->mag,&statp->spr);
}

void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp,"%s %s ",invp->nome,invp->tipo);
    stat_read(fp,&(invp->stat));
}

void inv_print(FILE *fp, inv_t *invp){
   printf("%s %s ",invp->nome,invp->tipo);
   stat_print(fp, &invp->stat, 0);
   printf("\n");
}

stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}
