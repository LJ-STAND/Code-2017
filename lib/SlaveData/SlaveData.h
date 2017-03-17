#ifndef SLAVE_DATA_H
#define SLAVE_DATA_H

#include <LinePosition.h>

typedef struct SlaveData {
    LinePosition linePosition;
    int orbitAngle;
    int orbitSpeed;
    bool hasBallTsop;

    SlaveData() {}
    SlaveData(LinePosition position, int angle, int speed, bool hasBall) {
        linePosition = position;
        orbitAngle = angle;
        orbitSpeed = speed;
        hasBallTsop = hasBall;
    }
} SlaveData;

#endif // SLAVE_DATA_H
