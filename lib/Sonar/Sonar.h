#ifndef SONAR_H
#define SONAR_H

#include <Arduino.h>
#include <i2c_t3.h>
#include <Config.h>

class Sonar {
public:
    Sonar() {};
    void init(uint16_t address);
    int read();

private:
    void beginRanging();
    int range();

    int lastRange;
    uint16_t i2cAddress;
    unsigned long lastRangeTime;
};

#endif // SONAR_H
