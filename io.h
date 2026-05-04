#ifndef IO_H
#define IO_H

#include "waveform.h"

int check_file_can_open(const char *filename);
int count_csv_rows(const char *filename);
int load_csv_data(const char *filename, WaveformSample *samples, int max_rows);

#endif