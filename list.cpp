//#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

#include "list.h"

list_err_t ListInit(list_t *list, int size){

    assert(list != NULL);

    if (list == NULL){
        fprintf(stderr, "Error in ListInit(). List is null.\n");
        return LIST_NULL_PTR;
    }

    // if (size < 64) size = 64;
    list->size = size;

    list->data = (int *) calloc(list->size, sizeof(int));

    list->next = (int *) calloc(list->size, sizeof(int));

    list->prev = (int *) calloc(list->size, sizeof(int));
    ListEmptyIndex(list);

    list->free = 1;

    if (list->data == NULL || list->next == NULL || list->prev == NULL){
        fprintf(stderr, "Error in list ListInit() in allocation.\n");
        return LIST_ALLOCATE_FAILED;
    }

    return LIST_OK;
}

void ListEmptyIndex(list_t *list){
    list->next[0] = 0;
    list->prev[0] = 0;
    int i = 1;
    for (; i < list->size - 1; i++){
        list->next[i] = i + 1;
        list->prev[i] = -1;
    }

    list->next[i] = 0;
    list->prev[i] = -1;
}

bool ListFull(const list_t *list)
{
    int free_cnt = 0;

    for (int i = 1; i < list->size; i++){
        if (list->prev[i] == -1){
            free_cnt++;
        }
    }

    return free_cnt == 0;
}

int ListSizeExtend(list_t *list){

    int *new_data = NULL;
    int *new_next = NULL;
    int *new_prev = NULL;

    size_t new_size = list->size * 2;

    new_data = (int *) realloc(list->data, new_size * sizeof(int));
    new_next = (int *) realloc(list->next, new_size * sizeof(int));
    new_prev = (int *) realloc(list->prev, new_size * sizeof(int));

    if (new_data == NULL || new_next == NULL || new_prev == NULL){
        fprintf(stderr, "Error in ListSizeExtand() in realloc.\n");
        ListDump(list);
        return 0;
    }

    list->data = new_data;
    list->next = new_next;
    list->prev = new_prev;

    size_t i = list->size;
    for (; i < new_size - 1; i++){
        list->next[i] = i + 1;
        list->prev[i] = -1;
    }

    list->next[i] = 0;
    list->prev[i] = -1;

    list->size = new_size;
    return 0;
}

list_err_t ListInsert(list_t *list, int index, int number){

    ListVerify(list, index);

    if (index > list->free){
        fprintf(stderr, "Error in ListInsert(). The number of index is bigger than size of list.\n");
        return LIST_OUT_OF_RANGE;
    }

    if (list->free > list->size){
        fprintf(stderr, "Error in ListInsert(). The index of list->free is bigger than size of list.\n");
        return LIST_OUT_OF_RANGE;
    }

    if (index == 0){
        return ListInsertFirst(list, index, number);
    }

    if (ListFull(list)){
        ListSizeExtend(list);
    }

    int new_free = list->next[list->free];

    list->data[list->free] = number;
    list->next[list->free] = list->next[index];
    list->prev[list->free] = index;

    list->prev[list->next[index]] = list->free;

    list->next[index] = list->free;

    list->free = new_free;

    return LIST_OK;
}

list_err_t ListInsertFirst(list_t *list, int index, int number){

    int new_free = list->next[list->free];

    list->data[list->free] = number;
    list->next[list->free] = 0;
    list->prev[list->free] = index;

    list->next[index] = list->free;
    list->prev[index] = list->free;

    list->free = new_free;

    return LIST_OK;
}

bool ListEmpty(const list_t *list){
    return list->next[0] == 0;
}

list_err_t ListDelete(list_t *list, int index){

    ListVerify(list, index);

    if (ListEmpty(list)){
        fprintf(stderr, "Error in ListDelete(). List is empty. Can not pop the number to stack.\n");
        return LIST_EMPTY;
    }

    int new_free = list->next[index];

    list->next[index] = list->next[new_free];

    list->prev[list->next[new_free]] = index;

    list->next[new_free] = list->free;
    list->prev[new_free] = -1;

    list->free = new_free;

    return LIST_OK;
}

int ListVerify(list_t *list, int index){
    list_err_t err = LIST_OK;

    if (list == NULL){
        err = LIST_NULL_PTR;
    }

    if (list->data == NULL || list->next == NULL || list->prev == NULL){
        err = LIST_ALLOCATE_FAILED;
    }

    if (list->next[0] == 0){
        err = LIST_EMPTY;
    }

    if (list->prev[list->next[index]] != index){
        err = LIST_MIXED;
    }

    if (err != LIST_OK){
        ListDump(list);
        return 0;
    }

    return 0;
}

void ListDump(list_t *list){
    FILE *list_file = fopen("dump.dot", "w+");

    if (list_file == NULL){
        fprintf(stderr, "Error in ListDump(), File is NULL.\n");
    }

    fprintf(list_file, "digraph G {\nrankdir = \"LR\";\n");

// Создание узлов
    for (int i = 0; i < list->size; i++){
        fprintf(list_file, "node_%d [rank = 1; shape=Mrecord; style=filled; fillcolor = \"#FFC0CB\"; color = \"#FC7FC0\"; label = \"index = %d | data = %d | next = %d | prev = %d\"; ]\n", i, i, list->data[i], list->next[i], list->prev[i]);
    }
// Прозрачные ребра для упорядоченного списка
    fprintf(list_file, "edge [color=\"#000000\", fontcolor=\"#000000\"];\n");
    for (int i = 0; i < list->size - 1; i++){
        fprintf(list_file, "node_%d -> node_%d\n", i, i + 1);
    }
// Ребра next
    fprintf(list_file, "edge [color=\"#81D1D0\", fontcolor=\"#000000\"];\n");
    for (int i = 0; i < list->size - 1; i++){
        fprintf(list_file, "node_%d -> node_%d\n", i, list->next[i]);
    }

    fprintf(list_file, "}\n");
}




