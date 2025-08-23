#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../includes/cdll.h"

CDLL cdll_create(const size_t data_size) {
    const struct CDLL ll = { NULL, data_size };
    return ll;
}

bool cdll_is_empty(const CDLL* ll) {
    return ll -> head == NULL;
}

char* cdll_strerror(const CDLL_Status errno) {
    switch (errno) {
        case LL_OK: return "Success";
        case LL_ERR_OUT_OF_BOUNDS: return "Index out of bounds";
        case LL_ERR_NOT_FOUND: return "Node not found";
        case LL_ERR_EMPTY: return "List is empty";
        case LL_ERR_OOM: return "Memory allocation failed";
        default: return "Unknown Error";
    }
}

CDLL_Status cdll_add(CDLL* ll, const void* data) {
    struct CDLL_Node* new_node = (CDLL_Node*)calloc(1, sizeof(CDLL_Node));
    void *data_address = calloc(1, ll -> data_size);

    if (!data_address || !new_node) return LL_ERR_OOM;

    memcpy(data_address, data, ll -> data_size);
    new_node -> data = data_address;

    if (ll -> head == NULL) {
        new_node -> prev = new_node;
        new_node -> next = new_node;

        ll -> head = new_node;
    } else {
        new_node -> prev = ll -> head -> prev;
        new_node -> next = ll -> head;

        ll -> head -> prev -> next = new_node;
        ll -> head -> prev = new_node;
    }

    return LL_OK;
}

CDLL_Status cdll_remove(CDLL* ll, const void* data, bool (*matcher)(const void* a, const void *b, const size_t data_size)) {
    if (cdll_is_empty(ll)) return LL_ERR_NOT_FOUND;

    CDLL_Node* node = ll -> head;

    while (!matcher(node -> data, data, ll -> data_size)) {
        node = node -> next;

        if (node == ll -> head) return LL_ERR_NOT_FOUND;
    }

    node -> next -> prev = node -> prev;
    node -> prev -> next = node -> next;

    if (node -> next == node) {
        ll -> head = NULL;
    } else {
        if (node == ll -> head) ll -> head = node -> next;
    }

    free(node -> data);
    free(node);
    node = NULL;

    return LL_OK;
}

CDLL_Status cdll_iterate(const CDLL* ll, void (*print)(const void* item)) {
    const CDLL_Node* node = ll -> head;

    if (cdll_is_empty(ll)) return LL_ERR_EMPTY;

    do {
        print(node -> data);
        node = node -> next;
    } while (ll -> head != node);

    return LL_OK;
}

size_t cdll_length(const CDLL* ll) {
    if (cdll_is_empty(ll)) return 0;

    const CDLL_Node* node = ll -> head;
    size_t length = 0;

    do {
        node = node -> next;
        length++;
    } while (ll -> head != node);

    return length;
}

CDLL_Status cdll_get_node_index(const CDLL* ll, const void* data, bool (*matcher)(const void* a, const void *b, const size_t data_size), long long* index) {
    *index = 0;

    if (cdll_is_empty(ll)) {
        *index = -1;
        return LL_ERR_NOT_FOUND;
    }

    const CDLL_Node* node = ll -> head;

    while (!matcher(node -> data, data,  ll -> data_size)) {
        (*index) += 1;
        node = node -> next;

        if (node == ll -> head) {
            *index = -1;
            return LL_ERR_NOT_FOUND;
        }
    }

    return LL_OK;
}

CDLL_Status cdll_get_node_at_index(const CDLL* ll, const int index, const void** found_node) {
    if (index < 0 || cdll_is_empty(ll)) {
        *found_node = NULL;
        return LL_ERR_OUT_OF_BOUNDS;
    }

    long long i = 0;
    const CDLL_Node* node = ll -> head;

    while (i < index) {
        node = node -> next;
        i++;

        if (node == ll -> head) {
            *found_node = NULL;
            return LL_ERR_OUT_OF_BOUNDS;
        }
    }

    *found_node = node -> data;
    return LL_OK;
}

void cdll_purge(CDLL* ll) {
    if (cdll_is_empty(ll)) return;

    CDLL_Node* last_node = ll -> head -> prev;

    do {
        CDLL_Node* next_last_node = last_node -> prev;
        free(last_node -> data);
        free(last_node);
        last_node = next_last_node;
    } while (ll -> head != last_node);

    free(ll -> head -> data);
    free(ll -> head);
    last_node = NULL;
    ll -> head = NULL;
    ll = NULL;
}
