#ifndef LIST_H
#define LIST_H

typedef enum {
    LIST_OK                = 0,
    LIST_NULL_PTR          = 1,
    LIST_ALLOCATE_FAILED   = 2,
    LIST_EMPTY_INDEX       = 3,
    LIST_OUT_OF_RANGE      = 4,
    LIST_BREAK             = 5,
    LIST_ERROR             = 6
} list_err_t;

typedef struct list {
    int *data;
    int *next;
    int *prev;
    int free;
    int size;
    int cnt_png;
    int cur_index;
    list_err_t err;
} list_t;

list_err_t ListInit        (list_t *list, int size);
void ListEmptyIndex        (list_t *list);
bool ListAlmostFull        (const list_t *list);
bool ListEmpty             (const list_t *list);
int ListSizeExtend         (list_t *list);
list_err_t ListVerify      (list_t *list);
list_err_t ListInsert      (list_t *list, int index, int number);
list_err_t ListInsertFirst (list_t *list, int index, int number);
list_err_t ListDelete      (list_t *list, int index);
int ListVerifyConnects     (list_t *list);
void ListDump              (list_t *list);
void ListMakePng           (list_t *list);
void ListMakeDumpFile      (FILE **list_file, list_t *list);
void ListMakeNode          (FILE *list_file, list_t *list);
void ListMakeConnects      (FILE *list_file, list_t *list);
void ListMakeConnectsNext  (FILE *list_file, list_t *list);
void ListMakeConnectsPrev  (FILE *list_file, list_t *list);
void ListMakeEnd           (FILE *list_file);
void ListErrOk             (FILE **list_file);
void ListErrNullPtr        (FILE **list_file);
void ListErrAllocFailed    (FILE **list_file);
void ListErrEmptyInd       (FILE **list_file);
void ListErrOutOfRange     (FILE **list_file);
void ListErrBreak          (FILE **list_file);

void (* const OpTable[]) (FILE **list_file) = {
    [LIST_OK]              = ListErrOk,
    [LIST_NULL_PTR]        = ListErrNullPtr,
    [LIST_ALLOCATE_FAILED] = ListErrAllocFailed,
    [LIST_EMPTY_INDEX]     = ListErrEmptyInd,
    [LIST_OUT_OF_RANGE]    = ListErrOutOfRange,
    [LIST_BREAK]           = ListErrBreak
};


#endif
