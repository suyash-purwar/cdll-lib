#ifndef CDLL_H
#define CDLL_H

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

bool cdll_is_empty(const CDLL*);

void cdll_add(CDLL*, void*);

void cdll_remove(CDLL*, const void*, bool (*matcher)(const void*, const void*, const size_t));

void cdll_iterate(const CDLL*, void (*print)(const void*));

size_t cdll_length(const CDLL*);

long long cdll_get_node_index(const CDLL*, const void*, bool (*matcher)(const void*, const void*, const size_t));

void* cdll_get_node_at_index(const CDLL* ll, const int);

void cdll_purge(CDLL*);

#endif
