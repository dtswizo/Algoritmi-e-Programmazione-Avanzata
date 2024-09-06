#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"

data createDataItem(char *string){
    data inputDate;
    sscanf(string,"%d/%d/%d",&inputDate.y,&inputDate.m,&inputDate.g);
    return inputDate;
}


int confrontaDate(data d1,data d2){
    int d,m,a;
    int tempY1,tempY2;
    long res1,res2;
    tempY1=d1.y;
    tempY1-=2017;
    tempY2=d2.y;
    tempY2-=2017;
    res1=tempY1*31536000+2592000*d1.m+86400*d1.g;
    res2=tempY2*31536000+2592000*d2.m+86400*d2.g;
    if(res1>res2)  //data1>data2
        return 1;
    else if (res1==res2){
        return 0;
    }
    else     //data1<data2
        return -1;
}

long dateToLong(char date[S]){
    int d,m,a;
    long res;
    sscanf(date,"%d/%d/%d",&a,&m,&d);
    a-=2017;
    res=a*31536000+2592000*m+86400*d;
    return res;
}

