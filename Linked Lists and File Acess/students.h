/* student_list.h */
#ifndef STUDENT_LIST_H
#define STUDENT_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Student {
    int number;
    double mark;
    struct Student *next;
} Student;

Student* create_student(int number, double mark);
void add_student(Student **head, int number, double mark);
int delete_student(Student **head, int index);
void swap_students(Student **head, int index, int direction);
void print_student(Student *head, int index);
void free_list(Student **head);
void read_students_from_file(Student **head, const char *filename);
void write_students_to_file(Student *head, const char *filename);

#endif
