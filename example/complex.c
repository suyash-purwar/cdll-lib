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

    cdll_add(ll, &(p));

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

    Person p1 = add_person(&ll, "suyash", 22);
    add_person(&ll, "shubham", 27);
    add_person(&ll, "rahul", 30);

    printf("%d\n", p1.age);
    printf("%s\n", p1.name);

    print(ll.head -> data);
    print(ll.head -> next -> data);

    cdll_iterate(&ll, print);

    const Person p2 = { "suyash", 22 };
    const size_t p2_index = cdll_get_node_index(&ll, &p2, node_matcher);
    printf("%ld\n", p2_index);

    printf("%d\n", cdll_is_empty(&ll));

    add_person(&ll, "rashi", 20);
    const void* data = cdll_get_node_at_index(&ll, 2);
    print(data);

    printf("\n");

    cdll_remove(&ll, &p1, node_matcher);
    cdll_iterate(&ll, print);

    cdll_purge(&ll);
}