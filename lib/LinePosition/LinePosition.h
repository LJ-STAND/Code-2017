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

String linePositionString(LinePosition position) {
    case RobotPosition::front: {
        return "Front";
    }

    case RobotPosition::right: {
        return "Right";
    }

    case RobotPosition::back: {
        return "Back";
    }

    case RobotPosition::left: {
        return "Left";
    }

    case RobotPosition::smallCornerFrontRight: {
        return "Small corner front right";
    }

    case RobotPosition::smallCornerBackRight: {
        return "Small corner back right";
    }

    case RobotPosition::smallCornerBackLeft: {
        return "Small corner back left";
    }

    case RobotPosition::smallCornerFrontLeft: {
        return "Small corner front left";
    }

    case RobotPosition::bigCornerFrontRight: {
        return "Big corner front right";
    }

    case RobotPosition::bigCornerBackRight: {
        return "Big corner back right";
    }

    case RobotPosition::bigCornerBackLeft: {
        return "Big corner back left";
    }

    case RobotPosition::bigCornerFrontLeft: {
        return "Big corner front left";
    }

    case RobotPosition::centreVertical: {
        return "Centre vertical";
    }

    case RobotPosition::centreHorizontal: {
        return "Centre horizontal";
    }

    case RobotPosition::none: {
        return "None";
    }

    case RobotPosition::unknown: {
        return "Unknown";
    }
}

#endif // LINE_POSITION_H
