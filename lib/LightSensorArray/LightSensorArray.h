#ifndef LIGHT_SENSOR_ARRAY_H
#define LIGHT_SENSOR_ARRAY_H

#include <Arduino.h>
#include <Pins.h>
#include <LightSensorData.h>
#include <LightSensor.h>
#include <LinePosition.h>
#include <Bits.h>

class LightSensorArray {
public:
    LightSensorArray();

    void init();

    void read();
    void calculatePostion();
    LinePosition getLinePosition();
    uint16_t getFirst16Bit();
    uint16_t getSecond16Bit();

    void updateHeading(int heading);

    LightSensorData data;

    LinePosition position;

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

private:
    LightSensor sensors[24];
    int arrayOffset = 0;
};

#endif // LIGHT_SENSOR_ARRAY_H
