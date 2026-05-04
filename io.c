#include <stdio.h>
#include "io.h"

// Using function to check if input file can be opened
int check_file_can_open(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: File not found '%s'.\n", filename);
        return 0;
    }

    fclose(file);
    return 1;
}

// Using function to count the number of data rows in the csv file
int count_csv_rows(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: File not found '%s'.\n", filename);
        return -1;
    }

    char line[256];
    int row_count = 0;

    // Skips the header row
    fgets(line, sizeof(line), file);

    // Counts every row after the header
    while (fgets(line, sizeof(line), file) != NULL) {
        row_count++;
    }

    fclose(file);
    return row_count;
}

// Using function to load csv data into allocated samples array
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

// Using function to write the calculated results in a text file
int write_results_file(
    const char *filename,
    double rms_A, double rms_B, double rms_C,
    double peak_to_peak_A, double peak_to_peak_B, double peak_to_peak_C,
    double dc_offset_A, double dc_offset_B, double dc_offset_C,
    int clipped_A, int clipped_B, int clipped_C,
    int compliant_A, int compliant_B, int compliant_C
) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error: Could not create results file.\n");
        return 0;
    }

    fprintf(file, "Power Quality Waveform Analyser Results\n\n");

    fprintf(file, "RMS Voltage:\n");
    fprintf(file, "Phase A RMS: %.2f V\n", rms_A);
    fprintf(file, "Phase B RMS: %.2f V\n", rms_B);
    fprintf(file, "Phase C RMS: %.2f V\n\n", rms_C);

    fprintf(file, "Peak-to-Peak Voltage:\n");
    fprintf(file, "Phase A peak-to-peak: %.2f V\n", peak_to_peak_A);
    fprintf(file, "Phase B peak-to-peak: %.2f V\n", peak_to_peak_B);
    fprintf(file, "Phase C peak-to-peak: %.2f V\n\n", peak_to_peak_C);

    fprintf(file, "DC Offset:\n");
    fprintf(file, "Phase A DC offset: %.2f V\n", dc_offset_A);
    fprintf(file, "Phase B DC offset: %.2f V\n", dc_offset_B);
    fprintf(file, "Phase C DC offset: %.2f V\n\n", dc_offset_C);

    fprintf(file, "Clipped Samples:\n");
    fprintf(file, "Phase A clipped samples: %d\n", clipped_A);
    fprintf(file, "Phase B clipped samples: %d\n", clipped_B);
    fprintf(file, "Phase C clipped samples: %d\n\n", clipped_C);

    fprintf(file, "RMS Voltage Compliance:\n");
    fprintf(file, "Phase A: %s\n", compliant_A ? "COMPLIANT" : "OUT OF TOLERANCE");
    fprintf(file, "Phase B: %s\n", compliant_B ? "COMPLIANT" : "OUT OF TOLERANCE");
    fprintf(file, "Phase C: %s\n", compliant_C ? "COMPLIANT" : "OUT OF TOLERANCE");

    fclose(file);
    return 1;
}