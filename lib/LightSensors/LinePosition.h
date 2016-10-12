#ifndef LINE_POSITION_H
#define LINE_POSITION_H

#include <Arduino.h>

enum LinePosition {
    front,
    right,
    back,
    left,
    cornerFrontRight,
    cornerFrontLeft,
    cornerBackRight,
    cornerBackLeft,
    none
};

#endif // LINE_POSITION_H
