#include "Timer.h"

Timer::Timer(unsigned long duration) {
    timerDuration = duration;
}

bool Timer::timeHasPassed() {
    if (micros() - lastUpdate > timerDuration) {
        lastUpdate = micros();
        return true;
    }

    return false;
}
