#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    void *data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct CDLL {
    Node* head;
    size_t data_size;
} CDLL;

CDLL create_ll(size_t data_size) {
    const struct CDLL ll = { NULL, data_size };
    return ll;
}

void copy_data(void* src, void* dest, size_t byte_length) {
    for (int i = 0; i < byte_length; i++) {
        *((char*)dest + i) = *((char*)src + i);
    }
}

int is_empty(const CDLL* ll) {
    return ll -> head == NULL;
}

void add_node(CDLL* ll, void *data) {
    struct Node* new_node = (Node*)calloc(1, sizeof(Node));
    void *data_address = calloc(1, ll -> data_size);
    copy_data(data, data_address, ll -> data_size);

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

void remove_node(CDLL* ll, const void* data, bool (*matcher)(const void* a, const void *b, const size_t data_size)) {
    if (is_empty(ll)) {
        printf("List is empty\n");
        return;
    }

    Node* node = ll -> head;

    while (matcher(node -> data, data, ll -> data_size)) {
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

void traverse_ll(const CDLL* ll, void (*print_element)(const void* item)) {
    const Node* node = ll -> head;

    if (is_empty(ll)) {
        printf("List is empty\n");
        return;
    }

    do {
        print_element(node -> data);
        node = node -> next;
    } while (ll -> head != node);

    printf("\n");
}

size_t length(const CDLL* ll) {
    if (is_empty(ll)) return 0;

    const Node* node = ll -> head;
    size_t length = 0;

    do {
        node = node -> next;
        length++;
    } while (ll -> head != node);

    return length;
}

long long get_node_index(const CDLL* ll, const void* data, bool (*matcher)(const void* a, const void *b, const size_t data_size)) {
    if (is_empty(ll)) return -1;

    const Node* node = ll -> head;
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

void* get_node_at_index(const CDLL* ll, const int index) {
    if (index < 0 || is_empty(ll)) return NULL;

    long long i = 0;
    const Node* node = ll -> head;

    while (i < index) {
        node = node -> next;
        i++;

        if (node == ll -> head) {
            return NULL;
        }
    }

    return node -> data;
}

void purge_ll(CDLL* ll) {
    if (is_empty(ll)) return;

    Node* last_node = ll -> head -> prev;

    do {
        Node* next_last_node = last_node -> prev;
        free(last_node -> data);
        free(last_node);
        last_node = next_last_node;
    } while (ll -> head != last_node);

    free(ll -> head);
    last_node = NULL;
    ll -> head = NULL;
}

void print_element(const void* data) {
    if (data == NULL) {
        printf("%p\n", data);
        return;
    }

    const int value = *(int*)data;
    printf("%d ", value);
}

bool node_matcher(const void* a, const void* b, const size_t data_size) {
    size_t i = 0;

    while (i < data_size) {
        if (*(char*)a == *(char*)b) return false;
        i++;
    }

    return true;
}

int main() {
    CDLL ll = create_ll(sizeof(int));

    add_node(&ll, &(int){10});
    add_node(&ll, &(int){11});
    add_node(&ll, &(int){30});
    add_node(&ll, &(int){40});
    add_node(&ll, &(int){390});

    traverse_ll(&ll, print_element);
    const size_t len = length(&ll);
    printf("%zu\n", len);

    const long long index = get_node_index(&ll, &(int){30}, node_matcher);
    printf("%lld\n", index);

    const void* value_address = get_node_at_index(&ll, 6);
    print_element(value_address);

    remove_node(&ll, &(int){40}, node_matcher);
    traverse_ll(&ll, print_element);
    remove_node(&ll, &(int){10}, node_matcher);
    traverse_ll(&ll, print_element);
    remove_node(&ll, &(int){390}, node_matcher);
    traverse_ll(&ll, print_element);
    remove_node(&ll, &(int){30}, node_matcher);
    traverse_ll(&ll, print_element);
    remove_node(&ll, &(int){11}, node_matcher);

    // Following statements are checking for edge cases
    traverse_ll(&ll, print_element);

    const long long index2 = get_node_index(&ll, &(int){11}, node_matcher);
    printf("%lld\n", index2);

    const size_t len2 = length(&ll);
    printf("%zu\n", len2);

    const void* value2 = get_node_at_index(&ll, 1);
    print_element(value2);

    remove_node(&ll, &(int){40}, node_matcher);

    CDLL ll2 = create_ll(sizeof(int));

    add_node(&ll2, &(int){47});
    add_node(&ll2, &(int){32});
    add_node(&ll2, &(int){73});

    traverse_ll(&ll2, print_element);
    purge_ll(&ll2);
    traverse_ll(&ll2, print_element);
}
