#ifndef LIGHTGATE_H
#define LIGHTGATE_H

#include <Arduino.h>
#include <Pins.h>

class LightGate {
public:
    void init();
    bool hasBall();

private:
    int thresholdValue;
};

#endif // LIGHTGATE_H
