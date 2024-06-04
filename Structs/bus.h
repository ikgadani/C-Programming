/*bus.h
*Name: Isha Gadani
*Student Number: 041085940 
*/


#ifndef BUS_H
#define BUS_H

#include <time.h>

/*Function prototypes*/
int process_bus(char *line);
double get_bus_duration(char *line);
void print_bus_info(int count, double avg_duration);
void print_worst_bus();

#endif
