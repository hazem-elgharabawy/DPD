#include <stdio.h>
#include <time.h>

#include "..\actuator\actuator.h"
#include "..\fixed\fixed.h"
#include "..\text_files\text_files.h"


int main() {
    const char *input_file = "input.txt";

    // Check if the input file exists
    FILE *file0 = fopen(input_file, "r");
    if (file0 == NULL) {
        // If the file doesn't exist, generate it with sample data
        printf("Input file not found. Generating a new one...\n");
        generate_input_file(input_file,2);
    } else {
        fclose(file0);  // If the file exists, close it
    }

    Actuator_S act = {0};


    // Read input values from the generated file and process them in a loop
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening input file\n");
        return -1;
    }

    char line[256];  // Buffer to read lines
    while (fgets(line, sizeof(line), file)) {
        // For each input set, read the values and perform the actuator step
        if (read_input_file("input.txt", &act) == 0) {
            
            clock_t timer = clock();

            actuator_step(&act);

            timer = clock() - timer;
            printf("Time taken by function: %f seconds\n", ((double)timer) / CLOCKS_PER_SEC); // Process actuator step

            // Write the output to an output file
            write_output_file("output.txt", &act);
        }
    }

    fclose(file);
    printf("Output written to output.txt\n");
    
    return 0;
}
