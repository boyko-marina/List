//#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

#include "list.h"

int main( )
{
    list_t list = {};
    ListInit(&list, 7);
    fprintf(stderr, "first dump in\n");
    ListDump(&list);
    fprintf(stderr, "first dump out\n");
    ListInsert(&list, 0, 21);
    fprintf(stderr, "second dump in\n");
    ListDump(&list);
    fprintf(stderr, "second dump out\n");
    ListInsert(&list, 1, 22);
    ListDump(&list);
    ListInsert(&list, 2, 23);
    ListDump(&list);
    ListInsert(&list, 3, 24);
    ListDump(&list);
    ListDelete(&list, 1);
    ListDump(&list);
    ListInsert(&list, 1, 32);
    ListDump(&list);
    ListInsert(&list, 4, 25);
    ListDump(&list);
    ListDelete(&list, 3);
    ListDump(&list);
    ListInsert(&list, 3, 34);
    ListDump(&list);
    ListInsert(&list, 5, 26);
    ListDump(&list);
    ListInsert(&list, 6, 27);
    ListDump(&list);
    ListInsert(&list, 7, 28);
    ListDump(&list);
}
