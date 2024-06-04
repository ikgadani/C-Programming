/*main.c
*Name: Isha Gadani
*Student Number: 041085940 
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bus.h"
#include "train.h"
#include "train.c"
#include "bus.c"

int main() {
    char line[80];
    int bus_count = 0, train_count = 0;
    double bus_total_duration = 0, train_total_duration = 0;
    double bus_avg_duration, train_avg_duration;
    int ret;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        if (line[0] == 'B') {
            ret = process_bus(line);
            if (ret == 0) {
                bus_count++;
                bus_total_duration += get_bus_duration(line);
            }
        } else if (line[0] == 'T') {
            ret = process_train(line);
            if (ret == 0) {
                train_count++;
                train_total_duration += get_train_duration(line);
            }
        }
    }

    if (bus_count > 0) {
        bus_avg_duration = bus_total_duration / bus_count;
        print_bus_info(bus_count, bus_avg_duration);
        print_worst_bus();
    }

    if (train_count > 0) {
        train_avg_duration = train_total_duration / train_count;
        print_train_info(train_count, train_avg_duration);
        print_worst_train();
    }

    if (bus_count == 0 && train_count == 0) {
        fprintf(stderr, "Error: No valid entries found\n");
        return 1;
    }

    return 0;
}
