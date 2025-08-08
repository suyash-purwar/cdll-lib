#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct CDLL {
    Node* head;
} CDLL;

CDLL create_ll() {
    const struct CDLL ll = { NULL };
    return ll;
}

int is_empty(const CDLL* ll) {
    return ll -> head == NULL;
}

void add_node(CDLL* ll, const int data) {
    struct Node* new_node = (Node*)calloc(1, sizeof(Node));

    if (!new_node) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }

    new_node -> data = data;

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

void remove_node(CDLL* ll, const int data) {
    if (is_empty(ll)) {
        printf("List is empty");
        exit(EXIT_FAILURE);
    }

    Node* node = ll -> head;

    while (node -> data != data) {
        node = node -> next;

        if (node == ll -> head) {
            printf("The provided data node is not present in the list");
            exit(EXIT_FAILURE);
        }
    }

    node -> next -> prev = node -> prev;
    node -> prev -> next = node -> next;

    if (node->next == node) {
        ll->head = NULL;
    } else {
        if (node == ll->head) ll->head = node->next;
    }

    free(node);
    node = NULL;
}

void traverse_ll(const CDLL* ll) {
    const Node* node = ll -> head;

    if (is_empty(ll)) {
        printf("List is empty");
        exit(EXIT_FAILURE);
    }

    do {
        printf("%d ", node -> data);
        node = node -> next;
    } while (ll -> head != node);

    printf("\n");
}

size_t length(const CDLL* ll) {
    if (is_empty(ll)) {
        printf("List is empty");
        exit(EXIT_FAILURE);
    }

    const Node* node = ll -> head;
    size_t length = 0;

    do {
        node = node -> next;
        length++;
    } while (ll -> head != node);

    return length;
}

long long get_node_index(const CDLL* ll, const int data) {
    if (is_empty(ll)) {
        printf("List is empty");
        exit(EXIT_FAILURE);
    }

    const Node* node = ll -> head;
    long long index = 0;

    while (node -> data != data) {
        index++;
        node = node -> next;

        if (node == ll -> head) {
            index = -1;
            break;
        }
    }

    return index;
}

int get_node_at_index(const CDLL* ll, const int index) {
    if (index < 0) {
        printf("Index value must be greater than or equal to zero");
        exit(EXIT_FAILURE);
    }

    if (is_empty(ll)) {
        printf("List is empty");
        exit(EXIT_FAILURE);
    }

    long long i = 0;
    const Node* node = ll -> head;

    while (i < index) {
        node = node -> next;
        i++;

        if (node == ll -> head) return -1;
    }

    return node -> data;
}

void purge_ll(CDLL* ll) {
    if (is_empty(ll)) return;

    Node* last_node = ll -> head -> prev;

    do {
        Node* next_last_node = last_node -> prev;
        free(last_node);
        last_node = next_last_node;
    } while (ll -> head != last_node);

    free(ll -> head);
    last_node = NULL;
    ll -> head = NULL;
}

int main() {
    CDLL ll = create_ll();

    add_node(&ll, 10);
    add_node(&ll, 11);
    add_node(&ll, 30);
    add_node(&ll, 40);
    add_node(&ll, 390);

    traverse_ll(&ll);
    const size_t len = length(&ll);
    printf("%zu\n", len);

    const long long index = get_node_index(&ll, 11);
    printf("%ld\n", index);

    const int value = get_node_at_index(&ll, 1);
    printf("%d\n", value);

    remove_node(&ll, 40);
    traverse_ll(&ll);
    remove_node(&ll, 10);
    traverse_ll(&ll);
    remove_node(&ll, 390);
    traverse_ll(&ll);
    remove_node(&ll, 30);
    traverse_ll(&ll);
    remove_node(&ll, 11);

    // Following statements are checking for edge cases
    // traverse_ll(&ll);
    //
    // const long long index2 = get_node_index(&ll, 11);
    // printf("%ld\n", index2);
    //
    // const size_t len2 = length(&ll);
    // printf("%zu\n", len2);
    //
    // const int value2 = get_node_at_index(&ll, 1);
    // printf("%d\n", value2);

    // remove_node(&ll, 40);

    CDLL ll2 = create_ll();

    add_node(&ll2, 47);
    add_node(&ll2, 32);
    add_node(&ll2, 73);

    traverse_ll(&ll2);
    purge_ll(&ll2);
    traverse_ll(&ll2);
}
