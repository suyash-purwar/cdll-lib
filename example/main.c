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
    size_t i = 0;

    while (i < data_size) {
        if (*(char*)a == *(char*)b) return false;
        i++;
    }

    return true;
}

int main() {
    CDLL ll = cdll_create(sizeof(int));

    cdll_add(&ll, &(int){10});
    cdll_add(&ll, &(int){11});
    cdll_add(&ll, &(int){30});
    cdll_add(&ll, &(int){40});
    cdll_add(&ll, &(int){390});

    cdll_iterate(&ll, print_element);
    const size_t len = cdll_length(&ll);
    printf("%zu\n", len);

    const long long index = cdll_get_node_index(&ll, &(int){30}, node_matcher);
    printf("%lld\n", index);

    const void* value_address = cdll_get_node_at_index(&ll, 6);
    print_element(value_address);

    cdll_remove(&ll, &(int){40}, node_matcher);
    cdll_iterate(&ll, print_element);
    cdll_remove(&ll, &(int){10}, node_matcher);
    cdll_iterate(&ll, print_element);
    cdll_remove(&ll, &(int){390}, node_matcher);
    cdll_iterate(&ll, print_element);
    cdll_remove(&ll, &(int){30}, node_matcher);
    cdll_iterate(&ll, print_element);
    cdll_remove(&ll, &(int){11}, node_matcher);

    // Following statements are checking for edge cases
    cdll_iterate(&ll, print_element);

    const long long index2 = cdll_get_node_index(&ll, &(int){11}, node_matcher);
    printf("%lld\n", index2);

    const size_t len2 = cdll_length(&ll);
    printf("%zu\n", len2);

    const void* value2 = cdll_get_node_at_index(&ll, 1);
    print_element(value2);

    cdll_remove(&ll, &(int){40}, node_matcher);

    cdll_purge(&ll);

    CDLL ll2 = cdll_create(sizeof(int));

    cdll_add(&ll2, &(int){47});
    cdll_add(&ll2, &(int){32});
    cdll_add(&ll2, &(int){73});

    cdll_iterate(&ll2, print_element);
    cdll_purge(&ll2);
    cdll_iterate(&ll2, print_element);
}
