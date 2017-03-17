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
        case RobotPosition::smallOnFrontLine: {
            return "Small on front line";
        }

        case RobotPosition::bigOnFrontLine: {
            return "Big on front line";
        }

        case RobotPosition::overFrontLine: {
            return "Over front line";
        }

        case RobotPosition::smallOnRightLine: {
            return "Small on right line";
        }

        case RobotPosition::bigOnRightLine: {
            return "Big on right line";
        }

        case RobotPosition::overRightLine: {
            return "Over right line";
        }

        case RobotPosition::smallOnBackLine: {
            return "Small on back line";
        }

        case RobotPosition::bigOnBackLine: {
            return "Big on back line";
        }

        case RobotPosition::overBackLine: {
            return "Over line";
        }

        case RobotPosition::smallOnLeftLine: {
            return "Small on left line";
        }

        case RobotPosition::bigOnLeftLine: {
            return "Big on left line";
        }

        case RobotPosition::overLeftLine: {
            return "Over left line";
        }

        case RobotPosition::smallOnCornerFrontRight: {
            return "Small on corner front right";
        }

        case RobotPosition::bigOnCornerFrontRight: {
            return "Big on corner front right";
        }

        case RobotPosition::overCornerFrontRight: {
            return "Over corner front right";
        }

        case RobotPosition::smallOnCornerBackRight: {
            return "Small on corner back right";
        }

        case RobotPosition::bigOnCornerBackRight: {
            return "Big on corner back right";
        }

        case RobotPosition::overCornerBackRight: {
            return "Over corner back right";
        }

        case RobotPosition::smallOnCornerBackLeft: {
            return "Small on corner back left";
        }

        case RobotPosition::bigOnCornerBackLeft: {
            return "Big on corner back left";
        }

        case RobotPosition::overCornerBackLeft: {
            return "Over corner back left";
        }

        case RobotPosition::smallOnCornerFrontLeft: {
            return "Small on corner front left ";
        }

        case RobotPosition::bigOnCornerFrontLeft: {
            return "Big on corner front left";
        }

        case RobotPosition::overCornerFrontLeft: {
            return "Over corner front left";
        }

        case RobotPosition::field: {
            return "Field";
        }
    }
}

#endif // LINE_POSITION_H
