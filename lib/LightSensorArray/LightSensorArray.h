#ifndef LIGHT_SENSOR_ARRAY_H
#define LIGHT_SENSOR_ARRAY_H

#include <Arduino.h>

#include <Pins.h>

#include "LightSensorData.h"
#include "LightSensor.h"
#include "LinePosition.h"

typedef struct LightSensorBits {
    unsigned b0:1;
    unsigned b1:1;
    unsigned b2:1;
    unsigned b3:1;
    unsigned b4:1;
    unsigned b5:1;
    unsigned b6:1;
    unsigned b7:1;
    unsigned b8:1;
    unsigned b9:1;
    unsigned b10:1;
    unsigned b11:1;
    unsigned b12:1;
    unsigned b13:1;
    unsigned b14:1;
    unsigned b15:1;
} LightSensorBits;

union LightSensorBitsUnion {
    LightSensorBits bits;
    uint16_t bit16;
};

class LightSensorArray {
public:
    LightSensorArray();

    void init();

    void read();
    void calculatePostion();
    LinePosition getLinePosition();
    uint16_t getFirst16Bit();
    uint16_t getSecond16Bit();

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
};

#endif // LIGHT_SENSOR_ARRAY_H
