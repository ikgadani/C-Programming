#ifndef PERSON_H
#define PERSON_H

typedef struct Person {
    int id;
    char name[16]; /*15 characters + null terminator*/
    int age;
    struct Person *next;
} Person;

Person *create_person(int id, const char name[], int age);
Person *insert_sorted(Person *head, Person *new_person);
void free_list(Person *head);
void print_list(const Person *head);

#endif
