#include "Timer.h"

Timer::Timer(unsigned long duration) {
    timerDuration = duration;
}

void Timer::update() {
    lastUpdate = micros();
}

bool Timer::timeHasPassed() {
    if (micros() - lastUpdate > timerDuration) {
        lastUpdate = micros();
        return true;
    }

    return false;
}
