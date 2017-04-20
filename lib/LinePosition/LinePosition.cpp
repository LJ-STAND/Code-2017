#include "LinePosition.h"

String linePositionString(LinePosition position) {
    switch (position) {
        case LinePosition::front:
            return "Front";
            break;

        case LinePosition::right:
            return "Right";
            break;

        case LinePosition::back:
            return "Back";
            break;

        case LinePosition::left:
            return "Left";
            break;

        case LinePosition::smallCornerFrontRight:
            return "Small corner front right";
            break;

        case LinePosition::smallCornerBackRight:
            return "Small corner back right";
            break;

        case LinePosition::smallCornerBackLeft:
            return "Small corner back left";
            break;

        case LinePosition::smallCornerFrontLeft:
            return "Small corner front left";
            break;

        case LinePosition::bigCornerFrontRight:
            return "Big corner front right";
            break;

        case LinePosition::bigCornerBackRight:
            return "Big corner back right";
            break;

        case LinePosition::bigCornerBackLeft:
            return "Big corner back left";
            break;

        case LinePosition::bigCornerFrontLeft:
            return "Big corner front left";
            break;

        case LinePosition::centreVertical:
            return "Centre vertical";
            break;

        case LinePosition::centreHorizontal:
            return "Centre horizontal";
            break;

        case LinePosition::none:
            return "None";
            break;

        case LinePosition::unknown:
            return "Unknown";
            break;
    }
}
