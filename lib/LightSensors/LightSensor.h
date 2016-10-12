#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <Arduino.h>

class LightSensor {
public:
    LightSensor() {}
    LightSensor(int in);
    void calibrate();

    void read();
    bool isOnWhite();

private:
    int value;
    int inPin;
    int thresholdValue;
};

#endif // LIGHT_SENSOR_H
