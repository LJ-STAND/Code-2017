#ifndef LINE_POSITION_H
#define LINE_POSITION_H

#include <Arduino.h>

enum LinePosition {
    front,
    right,
    back,
    left,
    cornerBigFrontRight,
    cornerBigFrontLeft,
    cornerBigBackRight,
    cornerBigBackLeft,
    cornerSmallFrontRight,
    cornerSmallFrontLeft,
    cornerSmallBackRight,
    cornerSmallBackLeft,
    none
};

#endif // LINE_POSITION_H
