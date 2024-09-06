#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define N 30

#define S 8

#define ADD 101
#define REMOVE 102

typedef enum{
    r_caricaPg,r_caricaOggetti,
    r_aggiungiPg,r_cancellaPg,r_aggiungi_rimuovi_equipPg,r_calcolaStats,r_stampaPg,r_err
}comando;

typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct{
    char nome[N];
    char tipologia[N];
    stat_t stat;
}inv_t;

typedef struct{
    int inUso;
    inv_t *vettEq[S];
}tabEquip_t;

typedef struct{
    char codice[N];
    char nome[N];
    char classe[N];
    tabEquip_t *equip;
    stat_t stat;
}pg_t;





typedef struct node *link,node_t;

struct node{
    pg_t val;
    link next;
};

typedef struct{
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

typedef struct{
    inv_t *arrayOggetti;
    int nInv;
}tabInv_t;



void caricaPgDaFile(tabPg_t *tabPg,char *filename);
void caricaOggettiDaFile(tabInv_t **tabInv, char *filename);
void aggiungiPersonaggio(tabPg_t *tabPg);
void eliminaPersonaggio(tabPg_t *tabPg);
void initAndLink_tabPg(tabPg_t **tabPg,tabPg_t *tabPgInit);
void initAndLink_tabInv_t(tabInv_t **tabInv,tabInv_t *tabInvInit);
void update_tabPg_t(link x,tabPg_t *tabPg,int mode);
void aggiungi_rimuovi_equipPg(tabPg_t *tabPg,tabInv_t *tabInv);
void calcola_stats_pg(tabPg_t *tabPg);
//tools
int leggiComando();
link newNode(pg_t val, link next);
link listInsTail(link h, pg_t val,link *tail);
int listDelExtCodice(link *h,char *codice,link *tail);
void stampaPersonaggi(tabPg_t *tabPg);
void stampaOggetti(tabInv_t *tabInv);
void stampaEquipPg(tabPg_t *tabPg,char *codice);
link find_Pg_By_Code(link h,char *codice);
inv_t* find_Obj_By_Name(tabInv_t *tabInv,char *nome);


int main() {
    setbuf(stdout, NULL);
    tabInv_t *tabInv;
    tabInv_t tabInvInit;
    tabPg_t *tabPg;
    tabPg_t tabPgInit;
    initAndLink_tabPg(&tabPg,&tabPgInit);
    initAndLink_tabInv_t(&tabInv,&tabInvInit);
    int stop=0;
    do{
        switch(leggiComando()){
            case r_caricaPg:
                caricaPgDaFile(tabPg,"pg.txt");
                break;
            case r_caricaOggetti:
                caricaOggettiDaFile(&tabInv,"inventario.txt");
                stampaOggetti(tabInv);
                break;
            case r_aggiungiPg:
                aggiungiPersonaggio(tabPg);
                break;
            case r_cancellaPg:
                eliminaPersonaggio(tabPg);
                printf("\nhead: %s",tabPg->headPg->val.codice);
                printf("\ntail: %s",tabPg->tailPg->val.codice);
                printf("\n%d",tabPg->nPg);
                break;
            case r_aggiungi_rimuovi_equipPg:
                aggiungi_rimuovi_equipPg(tabPg,tabInv);
                printf("%s",(tabPg->headPg->val.equip->vettEq)[0]->nome);
                break;
            case r_calcolaStats:
                //stampaEquipPg(tabPg,"PG0001");
                calcola_stats_pg(tabPg);
                break;
            case r_stampaPg:
                stampaPersonaggi(tabPg);
                break;
            default:
                stop=1;
                break;
        }
    }
    while(stop!=1);


    return 0;
}

void caricaPgDaFile(tabPg_t *tabPg,char *filename){
   FILE *fp;
   link tail=NULL;
   fp=fopen(filename,"r");
    pg_t actual;
    while((fscanf(fp,"%s %s %s %d %d %d %d %d %d",actual.codice,actual.nome,actual.classe,&actual.stat.hp,&actual.stat.mp,&actual.stat.atk,&actual.stat.def,&actual.stat.mag,&actual.stat.spr))!=EOF) {
        (*tabPg).headPg = listInsTail((*tabPg).headPg, actual,&tail);
        if(tabPg->nPg==0)
            update_tabPg_t((*tabPg).headPg,tabPg,ADD);
        else{
            if(tail==NULL)
                printf("errore carica Pg Tail");
                update_tabPg_t(tail,tabPg,ADD);
        }
    }
    fclose(fp);
}

 void caricaOggettiDaFile(tabInv_t **tabInv, char *filename){
    int nr;
    inv_t temp;
    FILE *fp;
    fp=fopen(filename,"r");
    fscanf(fp,"%d",&nr);
    (*tabInv)->arrayOggetti=(inv_t*)malloc(nr * sizeof(inv_t));
    for(int i=0; i < nr ; i++) {
        fscanf(fp, "%s %s %d %d %d %d %d %d",temp.nome,temp.tipologia,&temp.stat.hp,&temp.stat.mp,&temp.stat.atk,&temp.stat.def,&temp.stat.mag,&temp.stat.spr);
        ((*tabInv)->arrayOggetti)[i]=temp;
        ((*tabInv)->nInv)++;
    }

    fclose(fp);
}

void aggiungiPersonaggio(tabPg_t *tabPg){
    pg_t actual;
    tabEquip_t equip;
    equip.inUso=0;
    link tail=NULL;
    printf("Inserisci Codice Nome Tipologia Hp Mp atk def Mag Spr : ");
    scanf("%s %s %s %d %d %d %d %d %d",actual.codice,actual.nome,actual.classe,&actual.stat.hp,&actual.stat.mp,&actual.stat.atk,&actual.stat.def,&actual.stat.mag,&actual.stat.spr);
    actual.equip=&equip;
    tabPg->headPg= listInsTail(tabPg->headPg,actual,&tail);
    if(tabPg->nPg==0)
        update_tabPg_t(tabPg->headPg,tabPg,ADD);
    else{
        if(tail==NULL)
            printf("errore carica Pg Tail");
        update_tabPg_t(tail,tabPg,ADD);
    }
    printf("\n");
}

void eliminaPersonaggio(tabPg_t *tabPg){
    char *codice;
    link tail=NULL;
    printf("Inserisci Codice Personaggio da cancellare: ");
    scanf("%s",codice);
    //C'è un caso non trattato, se si cancella la testa tabPg_t non viene aggiornata corretamente
    listDelExtCodice(&(tabPg->headPg),codice,&tail);
    if(strcmp((tabPg->headPg->val).codice,codice)==0){
        tabPg->nPg--;
        tabPg->headPg=tabPg->headPg;
    }
    else
    update_tabPg_t(tail,tabPg,REMOVE);
}

void aggiungi_rimuovi_equipPg(tabPg_t *tabPg,tabInv_t *tabInv){
    int select;
    int temp;
    link x;
    inv_t* objPointer;
    char codice[N];
    char oggetto[N];
    printf("\nInserisci Codice personaggio:");
    scanf("%s",codice);
    x=find_Pg_By_Code(tabPg->headPg,codice);
    if(x==NULL){
        printf("Personaggio non trovato");
        return;
    }
    printf("\nInserisci Nome Oggetto:");
    scanf("%s",oggetto);
    objPointer=find_Obj_By_Name(tabInv,oggetto);
    if(objPointer==NULL){
        printf("Oggetto non trovato");
        return;
    }
    printf("\n Aggiungi 0 , Rimuovi 1: ");
    scanf("%d",&select);
    temp=x->val.equip->inUso;
    if(select==0){
        for(int i=0;i<S;i++){
            if((x->val.equip->vettEq)[i]==NULL) {
                (x->val.equip->vettEq)[i] = objPointer;
                break;
            }
        }
        (x->val.equip->inUso)++;
    }
    else{
            for(int i=0; i < S; i++){
                if( (x->val.equip->vettEq)[i]!=NULL && strcmp((x->val.equip->vettEq)[i]->nome,oggetto)==0)
                    (x->val.equip->vettEq)[i]=NULL;
            }
            (x->val.equip->inUso)--;
        }
}

void calcola_stats_pg(tabPg_t *tabPg) {
    link x;
    int count = 0;
    char codice[N];
    int t[5];
    printf("\nInserisci codice personaggio: ");
    scanf("%s", codice);
    x = find_Pg_By_Code(tabPg->headPg, codice);
    if (x == NULL) {
        printf("Non trovato");
        return;
    }
    printf("Statistiche personaggio %s: \n", x->val.codice);
    t[0] = x->val.stat.hp;
    t[1] = x->val.stat.mp;
    t[2] = x->val.stat.atk;
    t[3] = x->val.stat.def;
    t[4] = x->val.stat.mag;
    t[5] = x->val.stat.spr;
    for (int i = 0; i < S; i++) {
        if ((x->val.equip->vettEq)[i] != NULL) {
            t[0] += (x->val.equip->vettEq)[i]->stat.hp;
            t[1] += (x->val.equip->vettEq)[i]->stat.mp;
            t[2] += (x->val.equip->vettEq)[i]->stat.atk;
            t[3] += (x->val.equip->vettEq)[i]->stat.def;
            t[4] += (x->val.equip->vettEq)[i]->stat.mag;
            t[5] += (x->val.equip->vettEq)[i]->stat.spr;
        }
    }
    printf("Hp: %d , Mp: %d , Atk: %d , Def: %d , Mag: %d , Spr: %d\n",(t[0]>0)? t[0]: 0, (t[1]>0)? t[1]: 0, (t[2]>0)? t[2]: 0 ,
           (t[3]>0)? t[3]: 0, (t[4]>0)? t[4]: 0, (t[5]>0)? t[5]: 0);
}

//tools
link newNode(pg_t val, link next){
    link x = malloc(sizeof(*x));
    if(x == NULL)
        return NULL;
    else{
        x->val=val;
        x->next=next;
    }
    return x;
}

link listInsTail(link h, pg_t val,link *tail){
    link x;
    val.equip=(tabEquip_t*)malloc(sizeof(tabEquip_t));
    val.equip->inUso=0;
    for(int i=0;i<S;i++) (val.equip->vettEq)[i]=NULL;
    if (h==NULL)
        return newNode(val, NULL);
    for(x=h; x->next!=NULL; x=x->next);
    x->next= newNode(val,NULL);
    *tail=x->next;
    return h;
}

link find_Pg_By_Code(link h,char *codice){
    link x,p;
    int found=0;
    for(x=h, p=NULL;  x!= NULL; p=x, x=x->next){
        if(strcmp(x->val.codice,codice)==0){
            found=1;
            return x;
        }
    }
    return NULL;
}

inv_t* find_Obj_By_Name(tabInv_t *tabInv,char *nome){
    for(int i=0 ; i < tabInv->nInv ; i++){
        if(strcmp((tabInv->arrayOggetti)[i].nome,nome)==0){
         return &((tabInv->arrayOggetti)[i]);
        }
    }
   return NULL;
}

void stampaPersonaggi(tabPg_t *tabPg){
    link x;
    printf("Personaggi nel database:\n");
    for(x=tabPg->headPg; x != NULL ; x=x->next) {
        printf("%s %s %s %d %d %d %d %d %d",x->val.codice,x->val.nome,x->val.classe,x->val.stat.hp,x->val.stat.mp,x->val.stat.atk,x->val.stat.def,x->val.stat.mag,x->val.stat.spr);
        printf("\n");
    }
}

void stampaOggetti(tabInv_t *tabInv){
    for(int i=0 ; i < tabInv->nInv ; i++) {
        printf("%s %s %d %d %d %d %d %d", (tabInv->arrayOggetti)[i].nome, (tabInv->arrayOggetti)[i].tipologia, (tabInv->arrayOggetti)[i].stat.hp,
               (tabInv->arrayOggetti)[i].stat.mp, (tabInv->arrayOggetti)[i].stat.atk, (tabInv->arrayOggetti)[i].stat.def, (tabInv->arrayOggetti)[i].stat.mag, (tabInv->arrayOggetti)[i].stat.spr);
        printf("\n");
    }
}

void stampaEquipPg(tabPg_t *tabPg,char *codice) {
    link x;
    x = find_Pg_By_Code(tabPg->headPg, codice);
    for (int i = 0; i < S; i++) {
        if ((x->val.equip->vettEq)[i] != NULL) {
            printf("%s %s %d %d %d %d %d %d", (x->val.equip->vettEq)[i]->nome, (x->val.equip->vettEq)[i]->tipologia,
                   (x->val.equip->vettEq)[i]->stat.hp,
                   (x->val.equip->vettEq)[i]->stat.mp, (x->val.equip->vettEq)[i]->stat.atk,
                   (x->val.equip->vettEq)[i]->stat.def, (x->val.equip->vettEq)[i]->stat.mag,
                   (x->val.equip->vettEq)[i]->stat.spr);
            printf("\n");
        }
    }
}

int leggiComando(){
    char selezione[r_err+1][N]={"caricaPg","caricaOggettiDaFile",
                                "aggiungiPg","cancellaPg","aggiungi_rimuovi_equipPg","calcolaStats","stampaPg","err"};
    char input[N];
    int index;
    printf("Lista Comandi: \n");
    for(int i = 0 ; i < r_err ; i++) printf("-%s\n",selezione[i]);
    printf("Inserisci Comando: ");
    scanf("%s",input);
    for(int i=0; i < strlen(input); i++){
        if(strcmp(input,selezione[i])==0){
            index=i;
            break;
        }

    }
    return index;
}

int listDelExtCodice(link *h,char *codice,link *tail){
    link x,p;
    int found=0;
    for(x=*h, p=NULL;  x!= NULL; p=x, x=x->next){
        if(strcmp(x->val.codice,codice)==0){
            found=1;
            if(x==*h) {
                *h = x->next;
                *tail=NULL;
            }
            else {
                p->next = x->next;
                *tail=p;
            }
            free(x);
            break;
        }
    }
    if(found==1)
        return 1;
    else
        return -1;
}

void initAndLink_tabPg(tabPg_t **tabPg,tabPg_t *tabPgInit){
    (*tabPgInit).headPg=NULL;
    (*tabPgInit).tailPg=NULL;
    (*tabPgInit).nPg=0;
    *tabPg=&(*tabPgInit);
}

void initAndLink_tabInv_t(tabInv_t **tabInv,tabInv_t *tabInvInit){
    (*tabInvInit).nInv=0;
    *tabInv=&(*tabInvInit);
}

void update_tabPg_t(link x,tabPg_t *tabPg,int mode){
    if(mode==ADD) {
        if (tabPg->nPg == 0) {
            (tabPg->nPg)++;
            tabPg->headPg = x;
        } else {
            (tabPg->nPg)++;
            tabPg->tailPg = x;
        }
    }
    else{
     if(tabPg->nPg == 1){
         (tabPg->nPg)--;
         tabPg->headPg=NULL;
         tabPg->tailPg=NULL;
     }
     else{
         (tabPg->nPg)--;
         tabPg->tailPg=x;
     }

    }
}
