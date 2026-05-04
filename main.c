#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "waveform.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <csv_filename>\n", argv[0]);
        return 1; // Returns 1 if either no files or too many files found in program arguments
    }

    char *filename = argv[1];

    if (!check_file_can_open(filename)) {
        return 1;
    }

    int row_count = count_csv_rows(filename);

    if (row_count <= 0) {
        printf("Error: No CSV data rows found.\n");
        return 1;
    }

    //allocate memory for all waveform samples
    WaveformSample *samples = malloc(row_count * sizeof(WaveformSample));

    if (samples == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    // loads the csv data
    int loaded_rows = load_csv_data(filename, samples, row_count);

    if (loaded_rows <= 0) {
        printf("Error: No CSV data loaded.\n");
        free(samples);
        return 1;
    }

    // Calculate RMS voltage for each phase
    double rms_A = compute_rms(samples, loaded_rows, 'A');
    double rms_B = compute_rms(samples, loaded_rows, 'B');
    double rms_C = compute_rms(samples, loaded_rows, 'C');

    // Calculate peak to peak voltage for each phase
    double peak_to_peak_A = compute_peak_to_peak(samples, loaded_rows, 'A');
    double peak_to_peak_B = compute_peak_to_peak(samples, loaded_rows, 'B');
    double peak_to_peak_C = compute_peak_to_peak(samples, loaded_rows, 'C');

    // Calculate average voltage for each phase
    double dc_offset_A = compute_dc_offset(samples, loaded_rows, 'A');
    double dc_offset_B = compute_dc_offset(samples, loaded_rows, 'B');
    double dc_offset_C = compute_dc_offset(samples, loaded_rows, 'C');

    // Count clipped samples for each phase
    int clipped_A = count_clipped_samples(samples, loaded_rows, 'A');
    int clipped_B = count_clipped_samples(samples, loaded_rows, 'B');
    int clipped_C = count_clipped_samples(samples, loaded_rows, 'C');

    // Check RMS voltage tolerance for each phase
    int compliant_A = check_compliance(rms_A);
    int compliant_B = check_compliance(rms_B);
    int compliant_C = check_compliance(rms_C);

    printf("Power Quality Waveform Analyser\n");
    printf("Input file: %s\n", argv[1]);
    printf("Rows counted: %d\n", row_count);
    printf("Rows loaded: %d\n\n", loaded_rows);

    printf("Phase A RMS: %.2f V\n", rms_A);
    printf("Phase B RMS: %.2f V\n", rms_B);
    printf("Phase C RMS: %.2f V\n\n", rms_C);

    printf("Phase A peak-to-peak: %.2f V\n", peak_to_peak_A);
    printf("Phase B peak-to-peak: %.2f V\n", peak_to_peak_B);
    printf("Phase C peak-to-peak: %.2f V\n\n", peak_to_peak_C);

    printf("Phase A DC offset: %.2f V\n", dc_offset_A);
    printf("Phase B DC offset: %.2f V\n", dc_offset_B);
    printf("Phase C DC offset: %.2f V\n\n", dc_offset_C);

    printf("Phase A clipped samples: %d\n", clipped_A);
    printf("Phase B clipped samples: %d\n", clipped_B);
    printf("Phase C clipped samples: %d\n\n", clipped_C);

    // if compliant is 1 print COMPLIANT otherwise it prints OUT OF TOLERANCE
    printf("Phase A compliance: %s\n", compliant_A ? "COMPLIANT" : "OUT OF TOLERANCE");
    printf("Phase B compliance: %s\n", compliant_B ? "COMPLIANT" : "OUT OF TOLERANCE");
    printf("Phase C compliance: %s\n\n", compliant_C ? "COMPLIANT" : "OUT OF TOLERANCE");

    free(samples); // Releases allocated memory

    return 0;
}