#include "person.h"
#include "person.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    Person *head = NULL;
    int i;

    if (argc < 2 || argc % 3 != 1) {
        printf("Usage: %s [ID NAME AGE]...\n", argv[0]);
        return 1;
    }

    for (i = 1; i < argc; i += 3) {
        int id = atoi(argv[i]);
        char *name = argv[i + 1];
        int age = atoi(argv[i + 2]);
        Person *new_person = create_person(id, name, age);

        if (id < 0 || id > 99999 || strlen(name) > 15 || age < 0 || age > 99) {
            printf("Invalid argument: %s\n", argv[i]);
            free_list(head);
            return 1;
        }

        if (!new_person) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(head);
            return 3;
        }

        if (insert_sorted(head, new_person) == new_person) {
            head = new_person;
        }
    }

    print_list(head);
    free_list(head);
    return 0;
}
