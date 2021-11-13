#ifndef UTIL_H
#define UTIL_H

#include <at89x52.h>

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;

void sleep(uint N)
{
    while (N--)
        ;
}

void show_column(ushort col)
{
    P0 = ~(col & 0xff);
    P2 = ~(col >> 8);
}

#endif // #ifndef UTIL_H