#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define N 50

//strutture dati
typedef enum{
    r_acquisizioneTastiera,r_acquisizioneFile,
    r_ricercaPerCodice,r_cancellazione,r_cancellazioneTraDate,r_stampa,r_err
}comando;

typedef struct{
   char *codice;
   char *nome;
   char *cognome;
   char *dataNascita;
   char *via;
   char *citta;
   int cap;
}Item;

typedef struct node *link,node_t;

struct node{
    Item val;
    link next;
};

//proper functions declaration
link SortListIns(link h , Item val);
link ricercaPerCodice(link h);
Item listDelExtCodice(link *h,char *codice);
void codiciDaEliminare(char ***array,int *size,link h,char *data1,char *data2);
//tools declarations
int leggiComando();
void acquisizione(link *head,int mode);
link newNode(Item val, link next);
Item createItem(char *codice,char *nome,char *cognome,char *dataNascita,char *via,char *citta,int cap);
long dateToLong(char date[N]);
void stampaElemento(link x);
void stampaLista(link h);
Item createVoidItem();

int main() {
    int stop=0;
    char data1[N],data2[N];
    char **array;
    char codice[N];
    int size=0;
    link head=NULL;
    link x;
    Item tmp;
    do{
    switch(leggiComando()){
        case r_acquisizioneTastiera:
            acquisizione(&head,0);
          break;
        case r_acquisizioneFile:
            acquisizione(&head,1);
            break;
        case r_ricercaPerCodice:
            x=ricercaPerCodice(head);
            if(x!=NULL)
                stampaElemento(x);
            break;
        case r_cancellazione:
            printf("\nInserisci il codice dell'elemento da cercare: ");
            scanf("%s",codice);
            tmp=listDelExtCodice(&head,codice);
            if(strcmp(tmp.codice,"EMPTY")==0)
                printf("Oggetto non trovato");
            else{
                link tm;
                tm->val=tmp;
                stampaElemento(tm);
                printf("\nElemento eliminato dalla lista");
            }

            break;
        case r_cancellazioneTraDate:
            printf("\nInserire intervallo di date per la cancellazione dalla lista nel formato gg/mm/aa: ");
            scanf("%s %s",data1,data2);
            codiciDaEliminare(&array,&size,head,data1,data2);
            for(int i=0;i<size;i++){
                tmp=listDelExtCodice(&head,array[i]);
            }

            break;
        case r_stampa:
            stampaLista(head);
            break;
         default:
            stop=1;
            break;
        }
    }
    while(stop!=1);

    return 0;
}


//proper functions

void acquisizione(link *head,int mode){
    Item input;
    char codice[N];
    char nome[N];
    char cognome[N];
    char dataNascita[N];
    char via[N];
    char citta[N];
    int cap;
    char filename[N];
    FILE *fp;
    if(mode==0) {
        printf("\n");
        printf("Inserisci codice: \n");
        scanf("%s", codice);
        printf("Inserisci nome: \n");
        scanf("%s", nome);
        printf("Inserisci cognome: \n");
        scanf("%s", cognome);
        printf("Inserisci data di nascita gg/mm/aaaa: \n");
        scanf("%s", dataNascita);
        printf("Inserisci via: \n");
        scanf("%s", via);
        printf("Inserisci citta: \n");
        scanf("%s", citta);
        printf("Inserisci cap: \n");
        scanf("%d", &cap);
        input = createItem(codice, nome, cognome, dataNascita, via, citta, cap);
        *head = SortListIns(*head, input);
    }
    else{
        printf("Inserisci nome file: \n");
        scanf("%s", filename);
        fp=fopen(filename,"r");
        if(fp==NULL)
            EXIT_FAILURE;
        while(fscanf(fp,"%s %s %s %s %s %s %d",codice,nome,cognome,dataNascita,via,citta,&cap)!=EOF){
            input = createItem(codice, nome, cognome, dataNascita, via, citta, cap);
            *head = SortListIns(*head, input);
        }
    }
}

void stampaLista(link h){
    link x;
    FILE *fp;
    fp=fopen("output.txt","w");
    int cnt=0;
    for(x=h; x!=NULL ; x=x->next){
        fprintf(fp,"Elemento %d",cnt++);
        fprintf(fp,"\n");
        fprintf(fp,"-Codice: %s\n",x->val.codice);
        fprintf(fp,"-Nome: %s\n",x->val.nome);
        fprintf(fp,"-Cognome: %s\n",x->val.cognome);
        fprintf(fp,"-Data di nascita: %s\n",x->val.dataNascita);
        fprintf(fp,"-Via: %s\n",x->val.via);
        fprintf(fp,"-Citta: %s\n",x->val.citta);
        fprintf(fp,"-CAP: %d\n",x->val.cap);
        fprintf(fp,"\n");
    }
    fclose(fp);
}

link ricercaPerCodice(link h){
    char codice[N];
    link x;
    link res;
    int found=0;
    printf("\nInserisci il codice dell'elemento da cercare: ");
    scanf("%s",codice);
    for(x=h; x!= NULL && found==0 ; x=x->next){
        if(strcmp(x->val.codice,codice)==0){
            found=1;
            res=x;
        }
    }
    if(found==1)
    return res;
    else {
        printf("\nElemento non trovato\n");
        return NULL;
    }
}

Item listDelExtCodice(link *h,char *codice){
    link x,p;
    Item res=createVoidItem();
    int found=0;
    for(x=*h, p=NULL;  x!= NULL; p=x, x=x->next){
        if(strcmp(x->val.codice,codice)==0){
            res=x->val;
            found=1;
            if(x==*h)
                *h= x->next;
            else
                p->next = x -> next;
            free(x);
            break;
        }
    }
    return res;
}

//list functions

link newNode(Item val, link next){
    link x = malloc(sizeof(*x));
    if(x == NULL)
        return NULL;
    else{
        x->val=val;
        x->next=next;
    }
    return x;
}

link SortListIns(link h , Item val){
    link x, p;
    if(h==NULL || (dateToLong(h ->val.dataNascita) < dateToLong(val.dataNascita)) )
        return newNode(val,h);
    for (x=h->next, p=h; x!=NULL && (dateToLong(val.dataNascita) < dateToLong(x->val.dataNascita));
    p=x, x=x->next);
    p->next = newNode(val,x);
    return h;
}



//tools
int leggiComando(){
    char selezione[r_err+1][N]={"acquisizione","acquisizioneFile","ricercaPerCodice","cancellazione","cancellazioneTraDate","stampa"};
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

long dateToLong(char date[N]){
    int d,m,a;
    long res;
    sscanf(date,"%d/%d/%d",&d,&m,&a);
    a-=1980;
    res=a*31536000+2592000*m+86400*d;
    return res;
}

Item createItem(char *codice,char *nome,char *cognome,char *dataNascita,char *via,char *citta,int cap){
    Item result;
    int temp;
    temp=strlen(codice);
    result.codice=(char*)malloc(temp*sizeof(char));
    strcpy(result.codice,codice);
    temp=strlen(nome);
    result.nome=(char*)malloc(temp*sizeof(char));
    strcpy(result.nome,nome);
    temp=strlen(cognome);
    result.cognome=(char*)malloc(temp*sizeof(char));
    strcpy(result.cognome,cognome);
    temp=strlen(dataNascita);
    result.dataNascita=(char*)malloc(temp*sizeof(char));
    strcpy(result.dataNascita,dataNascita);
    temp=strlen(via);
    result.via=(char*)malloc(temp*sizeof(char));
    strcpy(result.via,via);
    temp=strlen(citta);
    result.citta=(char*)malloc(temp*sizeof(char));
    strcpy(result.citta,citta);
    result.cap=cap;
    return result;
}

Item createVoidItem(){
    Item res= createItem("EMPTY","","","","","",-1);
    return res;
}

void codiciDaEliminare(char ***array,int *size,link h,char *data1,char *data2) {
    char codice[N];
    long d1 = dateToLong(data1);
    long d2 = dateToLong(data2);
    int cnt = 0;
    link x;
    link res;
    *size = 0;
    for (x = h; x != NULL; x = x->next) {
        if (dateToLong(x->val.dataNascita) >= d1 && dateToLong(x->val.dataNascita) <= d2)
            (*size)=(*size)+1;
    }
    //malloc
    *array =(char**)malloc((*size)*sizeof(char*));
    for(int i=0 ; i < *size ; i++) (*array)[i]=(char*)malloc(5*sizeof(char));
    for (x = h; x != NULL; x = x->next) {
        if (dateToLong(x->val.dataNascita) >= d1 && dateToLong(x->val.dataNascita) <= d2)
            strcpy((*array)[cnt++], x->val.codice);
    }
}

void stampaElemento(link x){
    printf("\n");
    printf("-Codice: %s\n",x->val.codice);
    printf("-Nome: %s\n",x->val.nome);
    printf("-Cognome: %s\n",x->val.cognome);
    printf("-Data di nascita: %s\n",x->val.dataNascita);
    printf("-Via: %s\n",x->val.via);
    printf("-Citta: %s\n",x->val.citta);
    printf("-CAP: %d\n",x->val.cap);
    printf("\n");
}

