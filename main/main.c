#include <stdio.h>
#include <time.h>
#include <string.h>

#include "..\actuator\actuator.h"
#include "..\fixed\fixed.h"
#include "..\text_files\text_files.h"


int main() {
    const char *input_file = "input.txt";
    const char *output_file = "output.txt";

    // Check if the input file exists
    FILE *file0 = fopen(input_file, "r");
    if (file0 == NULL) {
        // If the file doesn't exist, generate it with sample data
        printf("Input file not found. Generating a new one...\n");
        generate_input_file(input_file, 100);
    } else {
        fclose(file0);  // If the file exists, close it
    }

    // Clear the output file by opening it in "w" mode
    FILE *file_out = fopen(output_file, "w");
    if (file_out == NULL) {
        printf("Error opening output file to clear its contents\n");
        return -1;
    }
    fclose(file_out);  // Close immediately after clearing

    Actuator_S act = {0};

    // Open the input file for reading
    FILE *file = fopen(input_file, "r");
    if (file == NULL) {
        printf("Error opening input file\n");
        return -1;
    }

    char line[256];      // Buffer to hold each line
    int line_count = 0;  // Count of processed input sets
    double total_time = 0;  // Total time for all actuator steps

    // Read and parse each line
    while (fgets(line, sizeof(line), file)) {
        double value;

        // Parse based on the current line content
        if (sscanf(line, "in_r=%lf", &value) == 1) {
            act.in_r = FloatToFixed(value);
        } else if (sscanf(line, "in_i=%lf", &value) == 1) {
            act.in_i = FloatToFixed(value);
        } else if (sscanf(line, "a10_r=%lf", &value) == 1) {
            act.a10_r = FloatToFixed(value);
        } else if (sscanf(line, "a10_i=%lf", &value) == 1) {
            act.a10_i = FloatToFixed(value);
        } else if (sscanf(line, "a30_r=%lf", &value) == 1) {
            act.a30_r = FloatToFixed(value);
        } else if (sscanf(line, "a30_i=%lf", &value) == 1) {
            act.a30_i = FloatToFixed(value);
        } else if (sscanf(line, "a50_r=%lf", &value) == 1) {
            act.a50_r = FloatToFixed(value);
        } else if (sscanf(line, "a50_i=%lf", &value) == 1) {
            act.a50_i = FloatToFixed(value);
        } else if (line[0] == '\n' || line[0] == '\0') {
            // Empty line indicates the end of an input set
            clock_t timer = clock();
            
            actuator_step(&act);

            timer = clock() - timer;

            double elapsed_time = ((double)timer) / CLOCKS_PER_SEC;
            total_time += elapsed_time;  // Accumulate total time
            line_count++;  // Increment input set count

            printf("Time taken by function: %lf seconds\n", elapsed_time);

            // Write output to the output file
            write_output_file(output_file, &act);
        }
    }

    fclose(file);

    // Calculate and print the average time
    if (line_count > 0) {
        double average_time = total_time / line_count;
        printf("Average time taken by function: %lf seconds\n", average_time);
    } else {
        printf("No input sets processed.\n");
    }

    printf("Processed %d lines. Output written to %s\n", line_count, output_file);

    return 0;
}
