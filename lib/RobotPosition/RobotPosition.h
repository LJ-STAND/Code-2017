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

        case smallOnRightLine: {
            return "Small on right line";
        }

        case bigOnRightLine: {
            return "Big on right line";
        }

        case overRightLine: {
            return "Over right line";
        }

        case smallOnBackLine: {
            return "Small on back line";
        }

        case bigOnBackLine: {
            return "Big on back line";
        }

        case overBackLine: {
            return "Over line";
        }

        case smallOnLeftLine: {
            return "Small on left line";
        }

        case bigOnLeftLine: {
            return "Big on left line";
        }

        case overLeftLine: {
            return "Over left line";
        }

        case smallOnCornerFrontRight: {
            return "Small on corner front right";
        }

        case bigOnCornerFrontRight: {
            return "Big on corner front right";
        }

        case overCornerFrontRight: {
            return "Over corner front right";
        }

        case smallOnCornerBackRight: {
            return "Small on corner back right";
        }

        case bigOnCornerBackRight: {
            return "Big on corner back right";
        }

        case overCornerBackRight: {
            return "Over corner back right";
        }

        case smallOnCornerBackLeft: {
            return "Small on corner back left";
        }

        case bigOnCornerBackLeft: {
            return "Big on corner back left";
        }

        case overCornerBackLeft: {
            return "Over corner back left";
        }

        case smallOnCornerFrontLeft: {
            return "Small on corner front left ";
        }

        case bigOnCornerFrontLeft: {
            return "Big on corner front left";
        }

        case overCornerFrontLeft: {
            return "Over corner front left";
        }

        case field: {
            return "Field";
        }

        // TODO
    }
}

#endif // LINE_POSITION_H
