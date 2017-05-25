#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include <LJSTANDCommon.h>

class MovingAverage {
public:
    MovingAverage(int number) {
        n = number;
        samples = new int[number];
    }

    void update(int value);
    double average();

private:
    int lastIndex = 0;
    int n;
    int *samples;
};

#endif // MOVINGAVERAGE_H
