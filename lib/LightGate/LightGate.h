#ifndef LIGHTGATE_H
#define LIGHTGATE_H

#include <Arduino.h>
#include <Pins.h>
#include <Config.h>

class LightGate {
public:
    void init();

    void read();
    bool hasBall();
    int getValue();

private:
    int thresholdValue;
    int value;
};

#endif // LIGHTGATE_H
