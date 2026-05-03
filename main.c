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

    WaveformSample *samples = malloc(row_count * sizeof(WaveformSample)); //allocate memory for all CSV samples

    if (samples == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    printf("Power Quality Waveform Analyser\n");
    printf("Input file: %s\n", argv[1]);
    printf("Rows counted: %d\n", row_count);

    free(samples); // cleans memory

    return 0;
}