#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../includes/cdll.h"

typedef struct {
    char name[20];
    short int age;
} Person;

Person add_person(CDLL* ll, char* name, const short int age) {
    Person p;

    p.age = age;
    memcpy(&(p.name), (void*)name, 20);

    CDLL_Status status;
    if (LL_OK != (status = cdll_add(ll, &p))) {
        fprintf(stderr, "%s\n", cdll_strerror(status));
    }

    return p;
}

void print(const void* person) {
    Person* p = (Person*)person;

    printf("Name: %s\n", p -> name);
    printf("Age: %d\n", p -> age);
}

bool node_matcher(const void* a, const void* b, const size_t data_size) {
    const Person* p1 = (Person*)a;
    const Person* p2 = (Person*)b;

    return strcmp(p1 -> name, p2 -> name) == 0 && p1 -> age == p2 -> age;
}

int main() {
    CDLL ll = cdll_create(sizeof(Person));

    const Person p1 = add_person(&ll, "suyash", 22);
    add_person(&ll, "shubham", 27);
    add_person(&ll, "rahul", 30);

    print(ll.head -> data);
    print(ll.head -> next -> data);

    CDLL_Status s1;
    if ((s1 = cdll_iterate(&ll, print)) != LL_OK) {
        fprintf(stderr, "%s\n", cdll_strerror(s1));
    }

    const Person p2 = { "suyash", 22 };
    long long index1;
    CDLL_Status s2;
    if ((s2 = cdll_get_node_index(&ll, &p2, node_matcher, &index1) != LL_OK)) {
        fprintf(stderr, "%s\n", cdll_strerror(s2));
    } else {
        printf("%lld\n", index1);
    }

    printf("%d\n", cdll_is_empty(&ll));

    add_person(&ll, "rashi", 20);
    const void *node1 = NULL;
    CDLL_Status s5;
    if (LL_OK == (s5 = cdll_get_node_at_index(&ll, 2, &node1))) {
        print(node1);
    } else {
        fprintf(stderr, "%s\n", cdll_strerror(s5));
    }

    cdll_remove(&ll, &p1, node_matcher);
    cdll_iterate(&ll, print);

    const Person p3 = { "bakul", 92 };
    CDLL_Status s6;
    if (LL_OK != (s6 = cdll_remove(&ll, &p3, node_matcher))) {
        fprintf(stderr, "%s\n", cdll_strerror(s6));
    }

    printf("%ld\n", cdll_length(&ll));

    cdll_purge(&ll);
}