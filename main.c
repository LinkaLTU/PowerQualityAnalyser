#include <stdio.h>
#include "io.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <csv_filename>\n", argv[0]);
        return 1; // Returns 1 if either no files or too many files found in program arguments
    }

    char *filename = argv[1];

    if (!check_file_can_open(filename)) {
        return 1;
    }

    printf("Power Quality Waveform Analyser\n");
    printf("Input file: %s\n", argv[1]);
}