#ifndef LIGHT_SENSOR_ARRAY_H
#define LIGHT_SENSOR_ARRAY_H

#include "LightSensorData.h"
#include "LightSensor.h"
#include "LinePosition.h"

class LightSensorArray {
public:
    LightSensorArray();

    void calculatePostion();
    LinePosition getLinePosition();

private:
    LightSensorData data;

    LinePosition position;
    LinePosition previousPosition;

    int urgency;
};

#endif // LIGHT_SENSOR_ARRAY_H
