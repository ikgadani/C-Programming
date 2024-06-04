
#include "students.h"
#include <stdio.h>
#include <stdlib.h>



Student* create_student(int number, double mark) {
    Student *new_student = (Student *)malloc(sizeof(Student));
    if (!new_student) {
        fprintf(stderr, "Error allocating memory\n");
        exit(1);
    }
    new_student->number = number;
    new_student->mark = mark;
    new_student->next = NULL;
    return new_student;
}

void add_student(Student **head, int number, double mark) {
    Student *new_student = create_student(number, mark);
    if (*head == NULL) {
        *head = new_student;
    } else {
        Student *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_student;
    }
}

int delete_student(Student **head, int index) {
    Student *temp = *head;
    Student *prev = NULL;
    int i = 0;
    
    if (*head == NULL) return -1;
   

    if (index == 0) {
        *head = temp->next;
        free(temp);
        return 0;
    }

    for (; i < index && temp != NULL; ++i) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return -1;
    prev->next = temp->next;
    free(temp);
    return 0;
}

void swap_students(Student **head, int index, int direction) {
    Student *current = *head;
    Student *prev = NULL;
    int i = 0;
    Student *prevPrev = NULL;
    Student *temp = *head;

    if (*head == NULL || index < 0) return;  
    
    for (; i < index && current->next != NULL; i++) {
        prev = current;
        current = current->next;
    }
    if (current->next == NULL && direction > 0) return;  
    if (prev == NULL && direction < 0) return;          

    if (direction > 0) { 
        Student *next = current->next;
        if (prev) prev->next = next;
        else *head = next; 
        current->next = next->next;
        next->next = current;
    } else if (direction < 0) {
        if (prev == NULL) return;
        
        
        while (temp != prev) {
            prevPrev = temp;
            temp = temp->next;
        }
        if (prevPrev) prevPrev->next = current;
        else *head = current; 
        prev->next = current->next;
        current->next = prev;
    }
}


void print_student(Student *head, int index) {
    Student *temp = head;
    int i = 0;
    for (; i < index && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp != NULL) {
        printf("%d %.2f\n", temp->number, temp->mark);
    } else {
        fprintf(stderr, "Index out of range\n");
        exit(4);
    }
}

void free_list(Student **head) {
    Student *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void read_students_from_file(Student **head, const char *filename) {
    
    Student temp;
    FILE *file = fopen(filename, "rb");
    
    if (!file) {
        fprintf(stderr, "Error opening file\n");
        exit(2);
    }


    while (fread(&temp, sizeof(Student), 1, file)) {
    
    printf("Read student: %d, mark: %.2f\n", temp.number, temp.mark);

        temp.next = NULL;

        add_student(head, temp.number, temp.mark);
    }

    fclose(file);
}

void write_students_to_file(Student *head, const char *filename) {
    Student *temp = head;
    FILE *file = fopen(filename, "wb");
    
    if (!file) {
        fprintf(stderr, "Error opening file\n");
        exit(5);
    }


    while (temp != NULL) {
        fwrite(temp, sizeof(Student), 1, file);
        temp = temp->next;
    }

    fclose(file);
}
