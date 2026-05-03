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