#ifndef LINE_POSITION_H
#define LINE_POSITION_H

#include <Arduino.h>

enum LinePosition {
    front, // 0
    right, // 1
    back, // 2
    left, // 3
    smallCornerFrontRight, // 4
    smallCornerBackRight, // 5
    smallCornerBackLeft, // 6
    smallCornerFrontLeft, // 7
    bigCornerFrontRight, // 8
    bigCornerBackRight, // 9
    bigCornerBackLeft, // 10
    bigCornerFrontLeft, // 11
    centreVertical, // 12
    centreHorizontal, // 13
    none, // 14
    unknown // 15
};

String linePositionString(LinePosition position);

#endif // LINE_POSITION_H
