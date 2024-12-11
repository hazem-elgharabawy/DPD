#ifndef TEXT_FILES_H

#define TEXT_FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "..\actuator\actuator.h"
#include "..\fixed\fixed.h"

// Function prototypes
double generate_random_double(double min, double max);
void generate_input_file(const char *filename, int num_inputs);
int read_input_file(const char *filename, Actuator_S *act, double value);
void write_output_file(const char *filename, Actuator_S *act);
int clear_file(const char *filename);
#endif // TEXT_FILES_H