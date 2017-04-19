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

enum RobotPositionSize {
    small,
    big,
    over
};

String robotPositionString(RobotPosition position) {
    switch (position) {
        case RobotPosition::smallOnFrontLine: {
            return "Small on front line";
            break;
        }

        case RobotPosition::bigOnFrontLine: {
            return "Big on front line";
            break;
        }

        case RobotPosition::overFrontLine: {
            return "Over front line";
            break;
        }

        case RobotPosition::smallOnRightLine: {
            return "Small on right line";
            break;
        }

        case RobotPosition::bigOnRightLine: {
            return "Big on right line";
            break;
        }

        case RobotPosition::overRightLine: {
            return "Over right line";
            break;
        }

        case RobotPosition::smallOnBackLine: {
            return "Small on back line";
            break;
        }

        case RobotPosition::bigOnBackLine: {
            return "Big on back line";
            break;
        }

        case RobotPosition::overBackLine: {
            return "Over back line";
            break;
        }

        case RobotPosition::smallOnLeftLine: {
            return "Small on left line";
            break;
        }

        case RobotPosition::bigOnLeftLine: {
            return "Big on left line";
            break;
        }

        case RobotPosition::overLeftLine: {
            return "Over left line";
            break;
        }

        case RobotPosition::smallOnCornerFrontRight: {
            return "Small on corner front right";
            break;
        }

        case RobotPosition::bigOnCornerFrontRight: {
            return "Big on corner front right";
            break;
        }

        case RobotPosition::overCornerFrontRight: {
            return "Over corner front right";
            break;
        }

        case RobotPosition::smallOnCornerBackRight: {
            return "Small on corner back right";
            break;
        }

        case RobotPosition::bigOnCornerBackRight: {
            return "Big on corner back right";
            break;
        }

        case RobotPosition::overCornerBackRight: {
            return "Over corner back right";
            break;
        }

        case RobotPosition::smallOnCornerBackLeft: {
            return "Small on corner back left";
            break;
        }

        case RobotPosition::bigOnCornerBackLeft: {
            return "Big on corner back left";
            break;
        }

        case RobotPosition::overCornerBackLeft: {
            return "Over corner back left";
            break;
        }

        case RobotPosition::smallOnCornerFrontLeft: {
            return "Small on corner front left ";
            break;
        }

        case RobotPosition::bigOnCornerFrontLeft: {
            return "Big on corner front left";
            break;
        }

        case RobotPosition::overCornerFrontLeft: {
            return "Over corner front left";
            break;
        }

        case RobotPosition::field: {
            return "Field";
            break;
        }
    }
}

#endif // LINE_POSITION_H
