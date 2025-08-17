#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct CDLL {
    struct Node* head;
    struct Node* tail;
    struct Node* node;
    size_t size;
} CDLL;

size_t input_length() {
    size_t length;

    printf("Enter the size of the list: ");
    scanf("%zu", &length);

    if (length <= 0) {
        printf("Length must be greater than zero.");
        exit(EXIT_FAILURE);
    }

    return length;
}

CDLL create_ll(const size_t size) {
    Node* node = (struct Node*)calloc(size, sizeof(Node));

    const CDLL ll = { NULL, NULL, node, size };

    return ll;
}

size_t ll_length(CDLL* ll) {
    Node* head = ll -> head;
    Node* tail = ll -> tail;
    Node* curr = head;

    if (head == NULL && tail == NULL) {
        return 0;
    }

    size_t size = 1;

    while (curr != tail) {
        curr += 1;
        size++;
    }

    return size;
}

void add_node(CDLL* ll, int data) {
    size_t ll_len = ll_length(ll);
    size_t allocated_length = ll -> size;

    if (ll_len >= allocated_length) {
        printf("List overflow");
        exit(EXIT_FAILURE);
    }

    Node* new_node;

    if (ll -> head == NULL && ll -> tail == NULL) {
        new_node = ll -> node;

        new_node -> prev = new_node;
        new_node -> next = new_node;

        ll -> head = new_node;
    } else {
        new_node = ll -> tail + 1;

        new_node -> next = ll -> head;
        new_node -> prev = ll -> tail;
    }

    new_node -> data = data;
    ll -> tail = new_node;
}

void traverse_ll(CDLL* ll) {
    Node* head = ll -> head;
    Node* tail = ll -> tail;
    Node* curr = head;

    if (head != NULL && tail != NULL) {
        do {
            printf("%d ", curr -> data);

            if (curr + 1 == tail && head != tail) {
                printf("%d ", (curr + 1) -> data);
            }

            curr += 1;
        } while (curr != ll -> tail && head != tail);
    }

    printf("END\n");
}

void destroy_ll(CDLL* ll) {
    free(ll->node);

    ll -> node = NULL;
    ll -> head = NULL;
    ll -> tail = NULL;
}

int main() {
    const size_t ll_size = input_length();

    const CDLL ll = create_ll(ll_size);

    add_node(&ll, 10);
    add_node(&ll, 38);
    add_node(&ll, 93);
    add_node(&ll, 65);

    size_t len = ll_length(&ll);
    printf("%d\n", len);

    traverse_ll(&ll);

    destroy_ll(&ll);
}