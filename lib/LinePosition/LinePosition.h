#ifndef LINE_POSITION_H
#define LINE_POSITION_H

#include <Arduino.h>

enum LinePosition {
    front,
    right,
    back,
    left,
    smallCornerFrontRight,
    smallCornerBackRight,
    smallCornerBackLeft,
    smallCornerFrontLeft,
    bigCornerFrontRight,
    bigCornerBackRight,
    bigCornerBackLeft,
    bigCornerFrontLeft,
    centreVertical,
    centreHorizontal,
    none,
    unknown
};

#endif // LINE_POSITION_H
