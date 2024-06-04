/*bus.c
*Name: Isha Gadani
*Student Number: 041085940 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bus.h"

#define MAX_BUS_ENTRIES 128

typedef struct {
    char line[8];
    time_t time_of_event;
    double duration;
    int stops;
} BusEntry;

static BusEntry bus_entries[MAX_BUS_ENTRIES];
static int bus_entry_count = 0;

int process_bus(char *line) {
    char *token;
    BusEntry new_entry;

    token = strtok(line, ",");
    if (token == NULL || token[0] != 'B')
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

    token = strtok(NULL, ",");
    if (token == NULL)
        return -1;
    new_entry.stops = atoi(token);

    if (new_entry.duration <= 0 || new_entry.stops <= 0)
        return -1;

    if (bus_entry_count < MAX_BUS_ENTRIES) {
        bus_entries[bus_entry_count++] = new_entry;
        return 0; /* Success */
    } else {
        return -1; /* Max entries reached */
    }
}

double get_bus_duration(char *line) {
    char *token;
    double duration;
    
    /*Make a copy of the line*/
    char line_copy[80];
    strcpy(line_copy, line);

    /*Skip bus line*/
    token = strtok(line_copy, ",");
    /*Skip time of event*/
    token = strtok(NULL, ",");
    /*Get duration*/
    token = strtok(NULL, ",");
    duration = atof(token);

    return duration;
}

void print_bus_info(int count, double avg_duration) {
    printf("B-total: %d\n", count);
    printf("B-avg: %.2f\n", avg_duration);
}

void print_worst_bus() {
    double worst_duration = bus_entries[0].duration;
    int worst_index = 0;
    int i;
    struct tm *event_time_info = localtime(&bus_entries[worst_index].time_of_event);

    if (bus_entry_count == 0)
        return;

    
    for (i = 1; i < bus_entry_count; ++i) {
        if (bus_entries[i].duration > worst_duration) {
            worst_duration = bus_entries[i].duration;
            worst_index = i;
        }
    }


    printf("B-worst: %04d-%02d-%02d %02d:%02d:%02d %s\n", event_time_info->tm_year + 1900,
        event_time_info->tm_mon + 1, event_time_info->tm_mday, event_time_info->tm_hour,
        event_time_info->tm_min, event_time_info->tm_sec, bus_entries[worst_index].line);
}
