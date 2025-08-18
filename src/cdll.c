#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../includes/cdll.h"

#include <string.h>

CDLL cdll_create(const size_t data_size) {
    const struct CDLL ll = { NULL, data_size };
    return ll;
}

void copy_data(void* src, void* dest, const size_t byte_length) {
    for (int i = 0; i < byte_length; i++) {
        *((char*)dest + i) = *((char*)src + i);
    }
}

bool cdll_is_empty(const CDLL* ll) {
    return ll -> head == NULL;
}

void cdll_add(CDLL* ll, void* data) {
    struct CDLL_Node* new_node = (CDLL_Node*)calloc(1, sizeof(CDLL_Node));
    void *data_address = calloc(1, ll -> data_size);
    memcpy(data, data_address, ll -> data_size);

    if (!new_node) {
        printf("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }

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
}

void cdll_remove(CDLL* ll, const void* data, bool (*matcher)(const void* a, const void *b, const size_t data_size)) {
    if (cdll_is_empty(ll)) {
        printf("List is empty\n");
        return;
    }

    CDLL_Node* node = ll -> head;

    while (matcher(node -> data, data, ll -> data_size)) {
        node = node -> next;

        if (node == ll -> head) {
            printf("The provided data node is not present in the list");
            exit(EXIT_FAILURE);
        }
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
}

void cdll_iterate(const CDLL* ll, void (*print)(const void* item)) {
    const CDLL_Node* node = ll -> head;

    if (cdll_is_empty(ll)) {
        printf("List is empty\n");
        return;
    }

    do {
        print(node -> data);
        node = node -> next;
    } while (ll -> head != node);

    printf("\n");
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

long long cdll_get_node_index(const CDLL* ll, const void* data, bool (*matcher)(const void* a, const void *b, const size_t data_size)) {
    if (cdll_is_empty(ll)) return -1;

    const CDLL_Node* node = ll -> head;
    long long index = 0;

    while (matcher(node -> data, data,  ll -> data_size)) {
        index++;
        node = node -> next;

        if (node == ll -> head) {
            index = -1;
            break;
        }
    }

    return index;
}

void* cdll_get_node_at_index(const CDLL* ll, const int index) {
    if (index < 0 || cdll_is_empty(ll)) return NULL;

    long long i = 0;
    const CDLL_Node* node = ll -> head;

    while (i < index) {
        node = node -> next;
        i++;

        if (node == ll -> head) {
            return NULL;
        }
    }

    return node -> data;
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
}
