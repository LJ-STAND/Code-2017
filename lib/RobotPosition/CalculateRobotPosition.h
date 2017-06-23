#ifndef CALCULATEROBOTPOSITION_H
#define CALCULATEROBOTPOSITION_H

#include "RobotPosition.h"
#include <LinePosition.h>

RobotPosition calculateRobotPosition(LinePosition line, RobotPosition previousPosition) {
    if (line == LinePosition::unknown) {
        return previousPosition;
    }

    switch (previousPosition) {
        case RobotPosition::field: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::field;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::smallOnFrontLine: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::field;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::bigOnFrontLine: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overFrontLine;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::overFrontLine: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overFrontLine;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::smallOnRightLine: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::field;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::bigOnRightLine: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overRightLine;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::overRightLine: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overRightLine;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::smallOnBackLine: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::field;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
            }
        }
        case RobotPosition::bigOnBackLine: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overBackLine;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
            }
        }
        case RobotPosition::overBackLine: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overBackLine;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
            }
        }
        case RobotPosition::smallOnLeftLine: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::field;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::bigOnLeftLine: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overLeftLine;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::overLeftLine: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overLeftLine;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::smallOnCornerFrontRight: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::field;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::bigOnCornerFrontRight: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overCornerFrontRight;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::overCornerFrontRight: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overCornerFrontRight;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::smallOnCornerBackRight: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::field;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
            }
        }
        case RobotPosition::bigOnCornerBackRight: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overCornerBackRight;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
            }
        }
        case RobotPosition::overCornerBackRight: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overCornerBackRight;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
            }
        }
        case RobotPosition::smallOnCornerBackLeft: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::field;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
            }
        }
        case RobotPosition::bigOnCornerBackLeft: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overCornerBackLeft;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
            }
        }
        case RobotPosition::overCornerBackLeft: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overCornerBackLeft;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
            }
        }
        case RobotPosition::smallOnCornerFrontLeft: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::field;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::bigOnCornerFrontLeft: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overCornerFrontLeft;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
        case RobotPosition::overCornerFrontLeft: {
            switch (line) {
                case LinePosition::none: {
                    return RobotPosition::overCornerFrontLeft;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
            }
        }
    }
}

#endif  // CALCULATEROBOTPOSITION_H
