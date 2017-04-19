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

RobotPositionSize robotPositionGetSize(RobotPosition posiiton) {
    switch (position) {
        case RobotPosition::smallOnFrontLine:
        case RobotPosition::smallOnLeftLine:
        case RobotPosition::smallOnBackLine:
        case RobotPosition::smallOnCornerFrontLeft:
        case RobotPosition::smallOnCornerBackLeft:
        case RobotPosition::smallOnCornerBackRight:
        case RobotPosition::smallOnCornerFrontRight:
            return RobotPositionSize::small;
            break;

        case RobotPosition::bigOnFrontLine:
        case RobotPosition::bigOnLeftLine:
        case RobotPosition::bigOnBackLine:
        case RobotPosition::bigOnCornerFrontLeft:
        case RobotPosition::bigOnCornerBackLeft:
        case RobotPosition::bigOnCornerBackRight:
        case RobotPosition::bigOnCornerFrontRight:
            return RobotPositionSize::big;
            break;

        case RobotPosition::overFrontLine:
        case RobotPosition::overLeftLine:
        case RobotPosition::overBackLine:
        case RobotPosition::overCornerFrontLeft:
        case RobotPosition::overCornerBackLeft:
        case RobotPosition::overCornerBackRight:
        case RobotPosition::overCornerFrontRight:
            return RobotPositionSize::over;
            break;

        default:
            return RobotPositionSize::small;
            break;
    }
}

int robotPositionGetDirection(RobotPosition posiiton) {
    switch (position) {
        case RobotPosition::smallOnFrontLine:
        case RobotPosition::bigOnFrontLine:
        case RobotPosition::overFrontLine:
            return 0;
            break;

        case RobotPosition::smallOnLeftLine:
        case RobotPosition::bigOnLeftLine:
        case RobotPosition::overLeftLine:
            return 270;
            break;

        case RobotPosition::smallOnBackLine:
        case RobotPosition::bigOnBackLine:
        case RobotPosition::overBackLine:
            return 180;
            break;

        case RobotPosition::smallOnRightLine:
        case RobotPosition::bigOnRightLine:
        case RobotPosition::overRightLine:
            return 90;
            break;

        case RobotPosition::smallOnCornerFrontLeft:
        case RobotPosition::bigOnCornerFrontLeft:
        case RobotPosition::overCornerFrontLeft:
            return 315;
            break;

        case RobotPosition::smallOnCornerBackLeft:
        case RobotPosition::bigOnCornerBackLeft:
        case RobotPosition::overCornerBackLeft:
            return 225;
            break;

        case RobotPosition::smallOnCornerFrontRight:
        case RobotPosition::bigOnCornerFrontRight:
        case RobotPosition::overCornerFrontRight:
            return 45;
            break;

        case RobotPosition::smallOnCornerBackRight:
        case RobotPosition::bigOnCornerBackRight:
        case RobotPosition::overCornerBackRight:
            return 135;
            break;

        default:
            return 0;
            break;
    }
}

bool robotPositionIsCorner(RobotPosition position) {
    switch (position) {
        case RobotPosition::smallOnFrontLine:
        case RobotPosition::bigOnFrontLine:
        case RobotPosition::overFrontLine:
        case RobotPosition::smallOnLeftLine:
        case RobotPosition::bigOnLeftLine:
        case RobotPosition::overLeftLine:
        case RobotPosition::smallOnBackLine:
        case RobotPosition::bigOnBackLine:
        case RobotPosition::overBackLine:
        case RobotPosition::smallOnRightLine:
        case RobotPosition::bigOnRightLine:
        case RobotPosition::overRightLine:
            return false;
            break;

        case RobotPosition::smallOnCornerFrontLeft:
        case RobotPosition::bigOnCornerFrontLeft:
        case RobotPosition::overCornerFrontLeft:
        case RobotPosition::smallOnCornerBackLeft:
        case RobotPosition::bigOnCornerBackLeft:
        case RobotPosition::overCornerBackLeft:
        case RobotPosition::smallOnCornerFrontRight:
        case RobotPosition::bigOnCornerFrontRight:
        case RobotPosition::overCornerFrontRight:
        case RobotPosition::smallOnCornerBackRight:
        case RobotPosition::bigOnCornerBackRight:
        case RobotPosition::overCornerBackRight:
            return true;
            break;

        default:
            return 0;
            break;
    }
}

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
