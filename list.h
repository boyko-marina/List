#ifndef LIST_H
#define LIST_H

typedef struct list {
    int *data;
    int *next;
    int *prev;
    int free;
    int size;
    int cnt_png;
} list_t;

typedef enum {
    LIST_OK              = 0,
    LIST_NULL_PTR        = 1,
    LIST_ALLOCATE_FAILED = 1,
    LIST_EMPTY           = 1,
    LIST_OUT_OF_RANGE    = 1,
    LIST_BREAK           = 1
} list_err_t;

list_err_t ListInit         (list_t *list, int size);
void ListEmptyIndex         (list_t *list);
bool ListAlmostFull         (const list_t *list);
int ListSizeExtend          (list_t *list);
list_err_t ListInsert       (list_t *list, int index, int number);
list_err_t ListInsertFirst  (list_t *list, int index, int number);
bool ListEmpty(const list_t *list);
list_err_t ListDelete(list_t *list, int index);
int ListVerify(list_t *list, int index);
void ListDump(list_t *list);
void ListMakePng(list_t *list);

#endif
