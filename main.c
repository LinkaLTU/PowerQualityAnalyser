#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <csv_filename>\n", argv[0]);
        return 1; // Returns 1 if either no files or too many files found in program arguments
    }

    printf("Power Quality Waveform Analyser\n");
    printf("Input file: %s\n", argv[1]);

    return 0;
}