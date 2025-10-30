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
    ListInsert(&list, 0, 5);
    ListInsert(&list, 1, 20);
    ListInsert(&list, 2, 9);
    ListInsert(&list, 3, 7);
    ListDelete(&list, 1);
    // ListInsert(&list, 4, 14);
    // ListInsert(&list, 5, 31);
    // ListDelete(&list, 3);
    // ListInsert(&list, 1);
    ListDump(&list);

}
