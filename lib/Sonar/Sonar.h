#ifndef SONAR_H
#define SONAR_H

#include <Arduino.h>
#include <i2c_t3.h>
#include <Config.h>
#include <Timer.h>

class Sonar {
public:
    Sonar() {};
    void init(uint16_t address);
    int read();
    void setRange(double newRange);
    void setAddress(uint16_t newAddress);

private:
    void beginRanging();
    int range();

    int lastRange;
    uint16_t i2cAddress;
    Timer rangeTimer = Timer(SONAR_RANGE_TIME);
};

#endif // SONAR_H
