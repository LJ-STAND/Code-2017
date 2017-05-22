#ifndef SLAVE_DATA_H
#define SLAVE_DATA_H

#include <LinePosition.h>

typedef struct SlaveData {
    LinePosition linePosition;
    int tsopAngle;
    int tsopStrength;

    SlaveData() {}
    SlaveData(LinePosition position, int ballAngle, int ballStrength) {
        linePosition = position;
        tsopAngle = ballAngle;
        tsopStrength = ballStrength;
    }
} SlaveData;

#endif // SLAVE_DATA_H
