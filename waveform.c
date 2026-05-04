#include <math.h>
#include "waveform.h"

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