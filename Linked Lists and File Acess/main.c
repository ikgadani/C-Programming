/* main.c */
#include "students.h"
#include "students.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    Student *head = NULL;
    int i;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [actions]\n", argv[0]);
        exit(3);
    }


    read_students_from_file(&head, argv[1]);

    for (i = 2; i < argc; i += 2) {
        if (strcmp(argv[i], "add") == 0) {
            int num = atoi(argv[i + 1]);
            double default_mark = 0.0;
            double mark = default_mark;
            if (num < 1 || num > 2147483647) {
                fprintf(stderr, "Invalid student number\n");
                exit(4);
            }
            add_student(&head, num, mark);
        } else if (strcmp(argv[i], "del") == 0) {
            int index = atoi(argv[i + 1]);
            if (delete_student(&head, index) == -1) {
                fprintf(stderr, "Invalid index\n");
                exit(4);
            }
        } else if (strcmp(argv[i], "psh") == 0) {
            int index = atoi(argv[i + 1]);
            swap_students(&head, index, 1);
        } else if (strcmp(argv[i], "pul") == 0) {
            int index = atoi(argv[i + 1]);
            swap_students(&head, index, -1);
        } else if (strcmp(argv[i], "prn") == 0) {
            int index = atoi(argv[i + 1]);
            print_student(head, index);
        }
    }

    write_students_to_file(head, "output.dat");
    free_list(&head);

    return 0;
}
