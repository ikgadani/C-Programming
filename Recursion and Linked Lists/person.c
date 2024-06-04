#include "person.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Person *create_person(int id, const char name[], int age) {
    Person *new_person = (Person *)malloc(sizeof(Person));
    if (!new_person) return NULL;
    new_person->id = id;
    strncpy(new_person->name, name, 15);
    new_person->name[15] = '\0';
    new_person->age = age;
    new_person->next = NULL;
    return new_person;
}

Person *insert_sorted(Person *head, Person *new_person) {
    if (!head || new_person->id < head->id) {
        new_person->next = head;
        return new_person;
    }
    head->next = insert_sorted(head->next, new_person);
    return head;
}

void free_list(Person *head) {
    while (head) {
        Person *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print_list(const Person *head) {
    while (head) {
        printf("%d %s %d\n", head->id, head->name, head->age);
        head = head->next;
    }
}
