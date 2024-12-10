#include"text_files.h"

// Function to generate random double values within a range
//double generate_random_double(double min, double max) {
   // return min + (rand() / (RAND_MAX / (max - min)));
//}

void generate_input_file(const char* filename, int num_input_sets) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    srand(time(NULL));  // Seed for random number generation

    // Write the inputs to the file
    for (int i = 0; i < num_input_sets; i++) {
        fprintf(file, "in_r=%.6f\n", 0.066591); // in_r between 0 and 2
        fprintf(file, "in_i=%.6f\n", 1.275307); // in_i between 0 and 2
        fprintf(file, "a10_r=%.6f\n", 0.725364);  // a10_r between 0 and 2
        fprintf(file, "a10_i=%.6f\n", 1.840999);  // a10_i between 0 and 2
        fprintf(file, "a30_r=%.6f\n", 1.013825);  // a30_r between 0 and 2
        fprintf(file, "a30_i=%.6f\n", 0.185186);  // a30_i between 0 and 2
        fprintf(file, "a50_r=%.6f\n", 0.854396);  // a50_r between 0 and 2
        fprintf(file, "a50_i=%.6f\n", 0.537675);  // a50_i between 0 and 2
        fprintf(file, "\n"); // Separate each input set by an empty line
    }

    fclose(file);
    printf("Input file generated successfully: %s\n", filename);
}


// Function to read data from a file and initialize Actuator_S structure
int read_input_file(const char* filename, Actuator_S* act) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return -1;
    }

    // Read values from the file
    if (fscanf_s(file, "in_r=%lf\n", &act->in_r) != 1 ||
        fscanf_s(file, "in_i=%lf\n", &act->in_i) != 1 ||
        fscanf_s(file, "a10_r=%lf\n", &act->a10_r) != 1 ||
        fscanf_s(file, "a10_i=%lf\n", &act->a10_i) != 1 ||
        fscanf_s(file, "a30_r=%lf\n", &act->a30_r) != 1 ||
        fscanf_s(file, "a30_i=%lf\n", &act->a30_i) != 1 ||
        fscanf_s(file, "a50_r=%lf\n", &act->a50_r) != 1 ||
        fscanf_s(file, "a50_i=%lf\n", &act->a50_i) != 1) {
        printf("Error reading data from file\n");
        fclose(file);
        return -1;
    }

    // Convert double values to fixed-point values
    act->in_r = FloatToFixed(0.066591);
    act->in_i = FloatToFixed(1.275307);
    act->a10_r = FloatToFixed(0.725364);
    act->a10_i = FloatToFixed(1.840999);
    act->a30_r = FloatToFixed(1.013825);
    act->a30_i = FloatToFixed(0.185186);
    act->a50_r = FloatToFixed(0.854396);
    act->a50_i = FloatToFixed(0.537675);

    fclose(file);
    return 0;  // Successful read
}

// Function to write the actuator output to a file
void write_output_file(const char* filename, Actuator_S* act) {
    FILE* file = fopen(filename, "a");  // Open file in append mode
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
