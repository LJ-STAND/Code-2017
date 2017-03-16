#ifndef ROBOT_POSITION_H
#define ROBOT_POSITION_H

#include <Arduino.h>

enum RobotPosition {
    smallOnFrontLine, // 0
    bigOnFrontLine, // 1
    overFrontLine, // 2
    smallOnRightLine, // 3
    bigOnRightLine, // 4
    overRightLine, // 5
    smallOnBackLine, // 6
    bigOnBackLine, // 7
    overBackLine, // 8
    smallOnLeftLine, // 9
    bigOnLeftLine, // 10
    overLeftLine, // 11
    smallOnCornerFrontRight, // 12
    bigOnCornerFrontRight, // 13
    overCornerFrontRight, // 14
    smallOnCornerBackRight, // 15
    bigOnCornerBackRight, // 16
    overCornerBackRight, // 17
    smallOnCornerBackLeft, // 18
    bigOnCornerBackLeft, // 19
    overCornerBackLeft, // 20
    smallOnCornerFrontLeft, // 21
    bigOnCornerFrontLeft, // 22
    overCornerFrontLeft, // 23
    field // 24
};

String robotPositionString(RobotPosition position) {
    switch (position) {
        case smallOnFrontLine: {
            return "Small on front line";
        }

        case bigOnFrontLine: {
            return "Big on front line";
        }

        case overFrontLine: {
            return "Over front line";
        }

        // TODO
    }
}

#endif // LINE_POSITION_H
