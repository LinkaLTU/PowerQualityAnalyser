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