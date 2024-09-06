//
// Created by wizodts on 02/01/2022.
//

#ifndef EX_01_ORA_H
#define EX_01_ORA_H

typedef struct{
    int h;
    int m;
}ora;

ora createOraItem(char *string);

int timeToSeconds(ora o);



#endif //EX_01_ORA_H
