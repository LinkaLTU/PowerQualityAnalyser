#include <stdio.h>
#include "io.h"

int check_file_can_open(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: File not found '%s'.\n", filename);
        return 0;
    }

    fclose(file);
    return 1;
}

int count_csv_rows(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: File not found '%s'.\n", filename);
        return -1;
    }

    char line[256];
    int row_count = 0;

    fgets(line, sizeof(line), file); // Skips the header row

    while (fgets(line, sizeof(line), file) != NULL) { // Counts every row after the header
        row_count++;
    }

    fclose(file);
    return row_count;
}

int load_csv_data(const char *filename, WaveformSample *samples, int max_rows) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: File not found '%s'.\n", filename);
        return -1;
    }

    char line[256];
    int row_number = 0;

    // Skip the header row
    fgets(line, sizeof(line), file);

    // Read each CSV row into the samples array
    while (fgets(line, sizeof(line), file) != NULL && row_number < max_rows) {
        WaveformSample *current_sample = samples + row_number;

        int values_read = sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                                 &current_sample->timestamp,
                                 &current_sample->phase_A_voltage,
                                 &current_sample->phase_B_voltage,
                                 &current_sample->phase_C_voltage,
                                 &current_sample->line_current,
                                 &current_sample->frequency,
                                 &current_sample->power_factor,
                                 &current_sample->thd_percent);

        if (values_read == 8) {
            row_number++;
        }
    }

    fclose(file);
    return row_number;
}