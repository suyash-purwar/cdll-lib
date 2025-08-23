#include <stdio.h>
#include <stdbool.h>

#include "../includes/cdll.h"

void print_element(const void* data) {
    if (data == NULL) {
        printf("%p\n", data);
        return;
    }

    const int value = *(int*)data;
    printf("%d ", value);
}

bool node_matcher(const void* a, const void* b, const size_t data_size) {
    const int* n1 = (int*)a;
    const int* n2 = (int*)b;

    return *n1 == *n2;
}

int main() {
    CDLL ll = cdll_create(sizeof(int));
    const int arr[5] = { 10, 11, 30, 40, 390 };

    for (int i = 0; i < 5; i++) {
        CDLL_Status status;
        if (LL_OK != (status = cdll_add(&ll, &arr[i]))) {
            fprintf(stderr, "%s\n", cdll_strerror(status));
        }
    }

    CDLL_Status s1;
    if (LL_OK != (s1 = cdll_iterate(&ll, print_element))) {
        fprintf(stderr, "%s\n", cdll_strerror(s1));
    }

    const size_t len = cdll_length(&ll);
    printf("\n%zu\n", len);

    long long index1;
    const CDLL_Status s2 = cdll_get_node_index(&ll, &(int){30}, node_matcher, &index1);
    if (LL_OK == s2) {
        printf("%lld\n", index1);
    }

    const void* node_at_index = NULL;
    CDLL_Status s3;
    if (LL_OK == (s3 = cdll_get_node_at_index(&ll, 6, &node_at_index))) {
        print_element(&node_at_index);
    } else {
        fprintf(stderr, "%s\n", cdll_strerror(s3));
    }

    CDLL_Status s4;
    if (LL_OK != (s4 = cdll_remove(&ll, &(int){40}, node_matcher))) {
        fprintf(stderr, "%s\n", cdll_strerror(s4));
    }

    cdll_iterate(&ll, print_element);
    printf("\n");

    cdll_remove(&ll, &(int){10}, node_matcher);
    cdll_iterate(&ll, print_element);
    printf("\n");

    cdll_remove(&ll, &(int){390}, node_matcher);
    cdll_iterate(&ll, print_element);
    printf("\n");

    cdll_remove(&ll, &(int){30}, node_matcher);
    cdll_iterate(&ll, print_element);
    printf("\n");

    cdll_remove(&ll, &(int){11}, node_matcher);

    // Following statements are checking for edge cases
    CDLL_Status s5;
    if (LL_OK != (s5 = cdll_iterate(&ll, print_element))) {
        fprintf(stderr, "%s\n", cdll_strerror(s5));
    }

    long long index2;
    CDLL_Status s6;
    if (LL_OK != (s6 = cdll_get_node_index(&ll, &(int){11}, node_matcher, &index2))) {
        fprintf(stderr, "%s\n", cdll_strerror(s6));
    }

    const size_t len2 = cdll_length(&ll);
    printf("%zu\n", len2);

    const void* value2 = NULL;
    CDLL_Status s7;
    if (LL_OK != (s7 = cdll_get_node_at_index(&ll, 1, value2))) {
        fprintf(stderr, "%s\n", cdll_strerror(s7));
    } else {
        print_element(value2);
    }

    CDLL_Status s8;
    if (LL_OK != (s8 = cdll_remove(&ll, &(int){40}, node_matcher))) {
        fprintf(stderr, "%s\n", cdll_strerror(s8));
    }

    cdll_purge(&ll);

    CDLL ll2 = cdll_create(sizeof(int));

    cdll_add(&ll2, &(int){47});
    cdll_add(&ll2, &(int){32});
    cdll_add(&ll2, &(int){73});

    cdll_iterate(&ll2, print_element);
    cdll_purge(&ll2);
    cdll_iterate(&ll2, print_element);

    printf("\n");
}
