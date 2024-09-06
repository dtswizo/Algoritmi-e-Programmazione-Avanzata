#include <stdlib.h>
#include <stdio.h>
#include "ora.h"

ora createOraItem(char *string){
    ora inputOra;
    sscanf(string,"%d:%d",&inputOra.h,&inputOra.m);
    return inputOra;
}


int timeToSeconds(ora o){
    int res=0;
    res+=o.h*60*60;
    res+=o.m*60;
    return res;
}




