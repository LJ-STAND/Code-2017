#ifndef ROBOT_POSITION_H
#define ROBOT_POSITION_H

#include <Arduino.h>

enum RobotPosition {
    smallOnFrontLine,
    bigOnFrontLine,
    overFrontLine,
    smallOnRightLine,
    bigOnRigtLine,
    overRightLine,
    smallOnBackLine,
    bigOnBackLine,
    overBackLine,
    smallOnLeftLine,
    bigOnLeftLine,
    overLeftLine,
    smallOnCornerFrontRight,
    bigOnCornerFrontRight,
    overCornerFrontRight,
    smallOnCornerBackRight,
    bigOnCornerBackRight,
    overCornerBackRight,
    smallOnCornerBackLeft,
    bigOnCornerBackLeft,
    overCornerBackLeft,
    smallOnCornerFrontLeft,
    bigOnCornerFrontLeft,
    overCornerFrontLeft,
    field
};

#endif // LINE_POSITION_H
