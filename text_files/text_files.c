#include"text_files.h"

// Function to generate random double values within a range
double generate_random_double(double min, double max) {
    return min + (rand() / (RAND_MAX / (max - min)));
}

void generate_input_file(const char *filename, int num_input_sets) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    srand(time(NULL));  // Seed for random number generation

    // Write the inputs to the file
    for (int i = 0; i < num_input_sets; i++) {
        fprintf(file, "in_r=%.6f\n", generate_random_double(0.0, 2.0)); // in_r between 0 and 2
        fprintf(file, "in_i=%.6f\n", generate_random_double(0.0, 2.0)); // in_i between 0 and 2
        fprintf(file, "a10_r=%.6f\n", generate_random_double(0.0, 2.0));  // a10_r between 0 and 2
        fprintf(file, "a10_i=%.6f\n", generate_random_double(0.0, 2.0));  // a10_i between 0 and 2
        fprintf(file, "a30_r=%.6f\n", generate_random_double(0.0, 2.0));  // a30_r between 0 and 2
        fprintf(file, "a30_i=%.6f\n", generate_random_double(0.0, 2.0));  // a30_i between 0 and 2
        fprintf(file, "a50_r=%.6f\n", generate_random_double(0.0, 2.0));  // a50_r between 0 and 2
        fprintf(file, "a50_i=%.6f\n", generate_random_double(0.0, 2.0));  // a50_i between 0 and 2
        fprintf(file, "\n"); // Separate each input set by an empty line
    }

    fclose(file);
    printf("Input file generated successfully: %s\n", filename);
}


// Function to read data from a file and initialize Actuator_S structure
int read_input_file(const char *input_file, Actuator_S *act,double value) {
    
        // Parse based on the current line content
        if (sscanf(line, "in_r=%lf", &value) == 1) {
            act->in_r = FloatToFixed(value);
        } else if (sscanf(line, "in_i=%lf", &value) == 1) {
            act->in_i = FloatToFixed(value);
        } else if (sscanf(line, "a10_r=%lf", &value) == 1) {
            act->a10_r = FloatToFixed(value);
        } else if (sscanf(line, "a10_i=%lf", &value) == 1) {
            act->a10_i = FloatToFixed(value);
        } else if (sscanf(line, "a30_r=%lf", &value) == 1) {
            act->a30_r = FloatToFixed(value);
        } else if (sscanf(line, "a30_i=%lf", &value) == 1) {
            act->a30_i = FloatToFixed(value);
        } else if (sscanf(line, "a50_r=%lf", &value) == 1) {
            act->a50_r = FloatToFixed(value);
        } else if (sscanf(line, "a50_i=%lf", &value) == 1) {
            act->a50_i = FloatToFixed(value);
        } else if (line[0] == '\n' || line[0] == '\0') {
            // Skip empty lines
            
        } else {
            // Handle invalid line format (optional)
            printf("Invalid line format: %s", line);
        }
    
    return 0;  // Successful read
}

// Function to write the actuator output to a file
void write_output_file(const char *filename, Actuator_S *act) {
    FILE *file = fopen(filename, "a");  // Open file in append mode
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    // Write output values to the file
    fprintf(file, "Output R: %.6f\n", FixedToFloat(act->out_r));
    fprintf(file, "Output I: %.6f\n", FixedToFloat(act->out_i));
    fprintf(file, "\n");  // Separate each output by a newline

    fclose(file);
}

int clear_file(const char *filename) {
// Clear the output file by opening it in "w" mode
    FILE *file_out = fopen(filename, "w");
    if (file_out == NULL) {
        printf("Error opening file to clear its contents\n");
        return -1;
    }
    fclose(file_out);  // Close immediately after clearing
}