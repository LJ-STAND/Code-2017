#ifndef CALCULATEROBOTPOSITION_H
#define CALCULATEROBOTPOSITION_H

#include "RobotPosition.h"

RobotPosition calculateRobotPosition(LinePosition line, RobotPosition previousPosition) {
    switch (previousPosition) {
        case RobotPosition::field: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::field;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field;
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::smallOnFrontLine: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::smallOnFrontLine;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::bigOnFrontLine: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::bigOnFrontLine;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::overFrontLine: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::overFrontLine;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::smallOnRightLine: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::smallOnRightLine;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::bigOnRightLine: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::bigOnRightLine;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::overRightLine: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::overRightLine;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::smallOnBackLine: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::smallOnBackLine;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::bigOnBackLine: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::bigOnBackLine;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::overBackLine: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::overBackLine;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::smallOnLeftLine: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::smallOnLeftLine;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::bigOnLeftLine: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::bigOnLeftLine;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::overLeftLine: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::overLeftLine;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::smallOnCornerFrontRight: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::smallOnCornerFrontRight;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::bigOnCornerFrontRight: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::bigOnCornerFrontRight;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::overCornerFrontRight: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::overCornerFrontRight;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::smallOnCornerBackRight: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::smallOnCornerBackRight;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::bigOnCornerBackRight: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::bigOnCornerBackRight;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::overCornerBackRight: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::overCornerBackRight;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::smallOnCornerBackLeft: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::smallOnCornerBackLeft;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::bigOnCornerBackLeft: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::bigOnCornerBackLeft;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::overCornerBackLeft: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::overCornerBackLeft;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::smallOnCornerFrontLeft: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::smallOnCornerFrontLeft;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::bigOnCornerFrontLeft: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::bigOnCornerFrontLeft;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
        case RobotPosition::overCornerFrontLeft: {
            switch (line) {
                case LinePosition::unknown: {
                    return RobotPosition::overCornerFrontLeft;
                    break;
                }
                case LinePosition::none: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::front: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::right: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::back: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::left: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::smallCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackRight: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerBackLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::bigCornerFrontLeft: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreVertical: {
                    return RobotPosition::field; // TODO
                    break;
                }
                case LinePosition::centreHorizontal: {
                    return RobotPosition::field; // TODO
                    break;
                }
            }
        }
    }
}

#endif  // CALCULATEROBOTPOSITION_H
