#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <LinePosition.h>

typedef struct SensorData {
    LinePosition linePosition;
    int tsopAngle;
    int tsopStrength;

    SensorData() {}
    SensorData(LinePosition position, int angle, int strength) {
        linePosition = position;
        tsopAngle = angle;
        tsopStrength = strength;
    }
} SensorData;

#endif // SENSOR_DATA_H
