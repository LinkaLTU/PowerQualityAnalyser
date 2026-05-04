#include <math.h>
#include "waveform.h"

// Using function here to calculate the RMS voltage for selected phase
double compute_rms(WaveformSample *samples, int row_count, char phase) {
    double sum_squared = 0.0;

    // Loops through every loaded sample
    for (int i = 0; i < row_count; i++) {
        double voltage = 0.0;

        if (phase == 'A') {
            voltage = samples[i].phase_A_voltage;
        } else if (phase == 'B') {
            voltage = samples[i].phase_B_voltage;
        } else if (phase == 'C') {
            voltage = samples[i].phase_C_voltage;
        }

        sum_squared += voltage * voltage;
    }

    return sqrt(sum_squared / row_count);
}

// Using function here to calculate the peak to peak voltage for selected phase
double compute_peak_to_peak(WaveformSample *samples, int row_count, char phase) {
    double min_voltage = 0.0;
    double max_voltage = 0.0;

    // Loops through every loaded sample
    for (int i = 0; i < row_count; i++) {
        double voltage = 0.0;

        if (phase == 'A') {
            voltage = samples[i].phase_A_voltage;
        } else if (phase == 'B') {
            voltage = samples[i].phase_B_voltage;
        } else if (phase == 'C') {
            voltage = samples[i].phase_C_voltage;
        }

        if (i == 0) {
            min_voltage = voltage;
            max_voltage = voltage;
        }

        if (voltage < min_voltage) {
            min_voltage = voltage;
        }

        if (voltage > max_voltage) {
            max_voltage = voltage;
        }
    }

    return max_voltage - min_voltage;
}

// Using function here to calculate the average voltage for a selected phase
double compute_dc_offset(WaveformSample *samples, int row_count, char phase) {
    double sum = 0.0;

    // Loops through every loaded sample
    for (int i = 0; i < row_count; i++) {
        double voltage = 0.0;

        if (phase == 'A') {
            voltage = samples[i].phase_A_voltage;
        } else if (phase == 'B') {
            voltage = samples[i].phase_B_voltage;
        } else if (phase == 'C') {
            voltage = samples[i].phase_C_voltage;
        }

        sum += voltage;
    }

    return sum / row_count;
}