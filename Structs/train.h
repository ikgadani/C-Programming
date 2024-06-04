/*train.h
*Name: Isha Gadani
*Student Number: 041085940 
*/


#ifndef TRAIN_H
#define TRAIN_H

#include <time.h>

/*Function prototypes*/
int process_train(char *line);
double get_train_duration(char *line);
void print_train_info(int count, double avg_duration);
void print_worst_train();

#endif
