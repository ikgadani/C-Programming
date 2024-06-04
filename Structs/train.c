/*train.c
*Name: Isha Gadani
*Student Number: 041085940 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train.h"

#define MAX_TRAIN_ENTRIES 128

typedef struct {
    char line[8];
    time_t time_of_event;
    double duration;
} TrainEntry;

static TrainEntry train_entries[MAX_TRAIN_ENTRIES];
static int train_entry_count = 0;

int process_train(char *line) {
    char *token;
    TrainEntry new_entry;

    token = strtok(line, ",");
    if (token == NULL || token[0] != 'T')
        return -1;

    strcpy(new_entry.line, token);

    token = strtok(NULL, ",");
    if (token == NULL)
        return -1;
    new_entry.time_of_event = (time_t) atoi(token);

    token = strtok(NULL, ",");
    if (token == NULL)
        return -1;
    new_entry.duration = atof(token);

    if (new_entry.duration <= 0)
        return -1;

    if (train_entry_count < MAX_TRAIN_ENTRIES) {
        train_entries[train_entry_count++] = new_entry;
        return 0; /* Success */
    } else {
        return -1; /* Max entries reached */
    }
}

double get_train_duration(char *line) {
    char *token;
    double duration;
    char line_copy[80];
    strcpy(line_copy, line);

    /*Skip train line*/
    token = strtok(line_copy, ",");
    /*Skip time of event*/
    token = strtok(NULL, ",");
    /*Get duration*/
    token = strtok(NULL, ",");
    duration = atof(token);

    return duration;
}

void print_train_info(int count, double avg_duration) {
    printf("T-total: %d\n", count);
    printf("T-avg: %.2f\n", avg_duration);
}

void print_worst_train() {
    double worst_duration = train_entries[0].duration;
    int i;
    int worst_index = 0;
    struct tm *event_time_info = localtime(&train_entries[worst_index].time_of_event);


    if (train_entry_count == 0) {
        printf("No train entries.\n");
        return;
    }

    for (i = 1; i < train_entry_count; ++i) {
        if (train_entries[i].duration > worst_duration) {
            worst_duration = train_entries[i].duration;
            worst_index = i;
        }
    }

    event_time_info = localtime(&train_entries[worst_index].time_of_event);

    printf("T-worst: %04d-%02d-%02d %02d:%02d:%02d %s\n", event_time_info->tm_year + 1900,
        event_time_info->tm_mon + 1, event_time_info->tm_mday, event_time_info->tm_hour,
        event_time_info->tm_min, event_time_info->tm_sec, train_entries[worst_index].line);
}
