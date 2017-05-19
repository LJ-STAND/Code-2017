#ifndef SLAVE_DATA_H
#define SLAVE_DATA_H

#include <LinePosition.h>

typedef struct SlaveData {
    LinePosition linePosition;
    int orbitAngle;
    int orbitSpeed;
    bool hasBallTSOP;
    int tsopAngle;
    int tsopStrength;

    SlaveData() {}
    SlaveData(LinePosition position, int angle, int speed, bool hasBall, int ballAngle, int ballStrength) {
        linePosition = position;
        orbitAngle = angle;
        orbitSpeed = speed;
        hasBallTSOP = hasBall;
        tsopAngle = ballAngle;
        tsopStrength = ballStrength;
    }
} SlaveData;

#endif // SLAVE_DATA_H
