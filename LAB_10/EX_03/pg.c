//
// Created by wizodts on 15/12/2021.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pg.h"


int pg_read(FILE *fp, pg_t *pgp) {
    if ((fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe) )!= EOF){
        stat_read(fp,&(pgp->b_stat));
        return 1;
    }

    else
        return 0;
}

void pg_print(FILE *fp,pg_t *pg, invArray_t invArray){
    fprintf(fp,"%s %s %s ",pg->cod,pg->nome,pg->classe);
    stat_print(fp,&pg->b_stat,0);
    printf("\n");
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    int cnt=0;
    equipArray_update(pgp->equip,invArray);
    //pgp->eq_stat.hp=pgp->eq_stat.mp=pgp->eq_stat.atk=pgp->eq_stat.def=pgp->eq_stat.mag=pgp->eq_stat.spr=0;
   // pgp->eq_stat= calcolaStatsEquip(pgp->equip,invArray);
    //stat_print(stdout,&pgp->eq_stat,0);
  //ho combinato un pugno di cazzate qui è da sistemare
}


