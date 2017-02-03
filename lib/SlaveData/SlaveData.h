#ifndef SLAVE_DATA_H
#define SLAVE_DATA_H

#include <LinePosition.h>

typedef struct SlaveData {
    LinePosition linePosition;
    int orbitAngle;
    int orbitSpeed;

    SlaveData() {}
    SlaveData(LinePosition position, int angle, int speed) {
        linePosition = position;
        orbitAngle = angle;
        orbitSpeed = speed;
    }
} SlaveData;

#endif // SLAVE_DATA_H
