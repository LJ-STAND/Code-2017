#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include <Common.h>

class MovingAverage {
public:
    MovingAverage(int number) {
        n = number;
        samples = new int[number];

        for (int i = 0; i < number; i++) {
            samples[i] = 0;
        }
    }

    void update(int value);
    double average();

private:
    int lastIndex = 0;
    int n;
    int *samples;
};

#endif // MOVINGAVERAGE_H
