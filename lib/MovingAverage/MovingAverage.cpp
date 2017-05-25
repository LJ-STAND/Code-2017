#include "MovingAverage.h"

void MovingAverage::update(int value) {
    samples[lastIndex] = value;

    lastIndex = mod(lastIndex + 1, n);
}

double MovingAverage::average() {
    double sum = 0;

    for (int i = 0; i < n; i++) {
        sum += samples[i];
    }

    return sum / (double)n;
}
