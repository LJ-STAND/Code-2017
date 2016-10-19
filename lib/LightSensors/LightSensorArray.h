#ifndef LIGHT_SENSOR_ARRAY_H
#define LIGHT_SENSOR_ARRAY_H

#include <Arduino.h>
#include "LightSensorData.h"
#include "LightSensor.h"
#include "LinePosition.h"

class LightSensorArray {
public:
    LightSensorArray();

    void read();
    void calculatePostion();
    LinePosition getLinePosition();
    // int getUrgency();

private:
    LightSensorData data;

    LinePosition position;

    // int urgency; // We don't really need this

    LightSensor ls0;
    LightSensor ls1;
    LightSensor ls2;
    LightSensor ls3;
    LightSensor ls4;
    LightSensor ls5;
    LightSensor ls6;
    LightSensor ls7;
    LightSensor ls8;
    LightSensor ls9;
    LightSensor ls10;
    LightSensor ls11;
    LightSensor ls12;
    LightSensor ls13;
    LightSensor ls14;
    LightSensor ls15;
    LightSensor ls16;
    LightSensor ls17;
    LightSensor ls18;
    LightSensor ls19;
    LightSensor ls20;
    LightSensor ls21;
    LightSensor ls22;
    LightSensor ls23;
};

#endif // LIGHT_SENSOR_ARRAY_H
