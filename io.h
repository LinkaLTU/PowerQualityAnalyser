#ifndef IO_H
#define IO_H

#include "waveform.h"

int check_file_can_open(const char *filename);

int count_csv_rows(const char *filename);

int load_csv_data(const char *filename, WaveformSample *samples, int max_rows);

int write_results_file(
    const char *filename,
    double rms_A, double rms_B, double rms_C,
    double peak_to_peak_A, double peak_to_peak_B, double peak_to_peak_C,
    double dc_offset_A, double dc_offset_B, double dc_offset_C,
    int clipped_A, int clipped_B, int clipped_C,
    int compliant_A, int compliant_B, int compliant_C
);

#endif