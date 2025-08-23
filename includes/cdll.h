#ifndef CDLL_H
#define CDLL_H

typedef enum {
    LL_OK = 0,
    LL_ERR_OUT_OF_BOUNDS,
    LL_ERR_NOT_FOUND,
    LL_ERR_EMPTY,
    LL_ERR_OOM,
} CDLL_Status;

typedef struct CDLL_Node {
    void *data;
    struct CDLL_Node* prev;
    struct CDLL_Node* next;
} CDLL_Node;

typedef struct CDLL {
    CDLL_Node* head;
    size_t data_size;
} CDLL;

CDLL cdll_create(const size_t);

char* cdll_strerror(const CDLL_Status);

bool cdll_is_empty(const CDLL*);

CDLL_Status cdll_add(CDLL*, const void*);

CDLL_Status cdll_remove(CDLL*, const void*, bool (*matcher)(const void*, const void*, const size_t));

CDLL_Status cdll_iterate(const CDLL*, void (*print)(const void*));

size_t cdll_length(const CDLL*);

CDLL_Status cdll_get_node_index(const CDLL*, const void*, bool (*matcher)(const void*, const void*, const size_t), long long* index);

CDLL_Status cdll_get_node_at_index(const CDLL* ll, const int, const void* node_data);

void cdll_purge(CDLL*);

#endif
