#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

class Timer {
public:
    Timer(unsigned long duration);
    void update();
    bool timeHasPassed();

private:
    unsigned long timerDuration;
    unsigned long lastUpdate;
};

#endif // TIMER_H
