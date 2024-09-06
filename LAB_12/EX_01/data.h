#ifndef EX_01_DATA_H
#define EX_01_DATA_H

#ifndef S
#define S 30
#endif

typedef struct{
    int y;
    int m;
    int g;
}data;

data createDataItem(char *string);

int confrontaDate(data d1,data d2);

long dateToLong(char date[S]);



#endif //EX_01_DATA_H
