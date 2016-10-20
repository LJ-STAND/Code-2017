#include "LightSensorArray.h"

LightSensorArray::LightSensorArray() {
    ls0 = LightSensor(LS_0);
    ls1 = LightSensor(LS_1);
    ls2 = LightSensor(LS_2);
    ls3 = LightSensor(LS_3);
    ls4 = LightSensor(LS_4);
    ls5 = LightSensor(LS_5);
    ls6 = LightSensor(LS_6);
    ls7 = LightSensor(LS_7);
    ls8 = LightSensor(LS_8);
    ls9 = LightSensor(LS_9);
    ls10 = LightSensor(LS_10);
    ls11 = LightSensor(LS_11);
    ls12 = LightSensor(LS_12);
    ls13 = LightSensor(LS_13);
    ls14 = LightSensor(LS_14);
    ls15 = LightSensor(LS_15);
    ls16 = LightSensor(LS_16);
    ls17 = LightSensor(LS_17);
    ls18 = LightSensor(LS_18);
    ls19 = LightSensor(LS_19);
    ls20 = LightSensor(LS_20);
    ls21 = LightSensor(LS_21);
    ls22 = LightSensor(LS_22);
    ls23 = LightSensor(LS_23);
}

LightSensorArray::init() {
    ls0.init();
    ls1.init();
    ls2.init();
    ls3.init();
    ls4.init();
    ls5.init();
    ls6.init();
    ls7.init();
    ls8.init();
    ls9.init();
    ls10.init();
    ls11.init();
    ls12.init();
    ls13.init();
    ls14.init();
    ls15.init();
    ls16.init();
    ls17.init();
    ls18.init();
    ls19.init();
    ls20.init();
    ls21.init();
    ls22.init();
    ls23.init();
}

void LightSensorArray::read() {
    LightSensorData data = LightSensorData(ls0.isOnWhite(), ls1.isOnWhite(), ls2.isOnWhite(), ls3.isOnWhite(), ls4.isOnWhite(), ls5.isOnWhite(), ls6.isOnWhite(), ls7.isOnWhite(), ls8.isOnWhite(), ls9.isOnWhite(), ls10.isOnWhite(), ls11.isOnWhite(), ls12.isOnWhite(), ls13.isOnWhite(), ls14.isOnWhite(), ls15.isOnWhite(), ls16.isOnWhite(), ls17.isOnWhite(), ls18.isOnWhite(), ls19.isOnWhite(), ls20.isOnWhite(), ls21.isOnWhite(), ls22.isOnWhite(), ls23.isOnWhite());
}

void LightSensorArray::calculatePostion() {
    if (data.lsTotal == 0) {
        // No line
        position = LinePosition::none;
    // One Quadrant
    } else if (data.lsQuadFrontRight + data.lsFront + data.lsRight == data.lsTotal) {
        position = LinePosition::smallCornerFrontRight;
    } else if (data.lsQuadBackRight + data.lsRight + data.lsBack == data.lsTotal) {
        position = LinePosition::smallCornerBackRight;
    } else if (data.lsQuadBackLeft + data.lsBack + data.lsLeft == data.lsTotal) {
        position = LinePosition::smallCornerBackLeft;
    } else if (data.lsQuadFrontLeft + data.lsLeft + data.lsFront == data.lsTotal) {
        position = LinePosition::smallCornerFrontLeft;
    } else {
        // Two Quadrants adjacent
        if (data.lsHalfFront + data.lsLeft + data.lsRight == data.lsTotal) {
            position = LinePosition::front;
        } else if (data.lsHalfRight + data.lsFront + data.lsBack == data.lsTotal) {
            position = LinePosition::right;
        } else if (data.lsHalfBack + data.lsRight + data.lsLeft == data.lsTotal) {
            position = LinePosition::back;
        } else if (data.lsHalfLeft + data.lsBack + data.lsFront == data.lsTotal) {
            position = LinePosition::left;
        } else {
            // Two Quadrants diagonal
            if (data.lsQuadFrontRight + data.lsQuadBackLeft + data.lsFront + data.lsRight + data.lsBack + data.lsLeft == data.lsTotal) {
                if (data.lsLeftFrontRight + data.lsFront + data.RightBackLeft + data.lsBack) {
                    position = LinePosition::centreVertical;
                } else if (data.lsLeftFrontRight + data.lsFront + data.lsCentreFrontRight + data.lsLeftBackLeft + data.lsCentreBackLeft + data.lsLeft == data.lsTotal) {
                    position = LinePosition::bigCornerFrontLeft;
                } else if (data.lsRightFrontRight + data.lsRight + data.lsLeftBackLeft + data.lsLeft == data.lsTotal) {
                    position = LinePosition::centreHorizontal;
                } else if (data.lsRightFrontRight + data.lsCentreFrontRight + data.lsRight + data.lsRightBackLeft + data.lsBack + data.lsCentreBackLeft == data.lsTotal) {
                    position = LinePosition::bigCornerBackRight;
                } else {
                    position = LinePosition::unknown;
                }
            } else if (data.lsQuadBackRight + data.lsQuadFrontLeft + data.lsFront + data.lsRight + data.lsBack + data.lsLeft == data.lsTotal) {
                // TODO
            } else {
                // Three Quadrants
                if (data.lsQuadFrontRight + data.lsQuadBackRight + data.lsQuadBackLeft + data.lsFront + data.lsRight + data.lsBack + data.lsLeft == data.lsTotal) {
                    position = LinePosition::bigCornerBackRight;
                } else if (data.lsQuadBackRight + data.lsQuadBackLeft + data.lsQuadFrontLeft + data.lsFront + data.lsRight + data.lsBack + data.lsLeft == data.lsTotal) {
                    position = LinePosition::bigCornerBackLeft;
                } else if (data.lsQuadBackLeft + data.lsQuadFrontLeft + data.lsQuadBackRight + data.lsFront + data.lsRight + data.lsBack + data.lsLeft == data.lsTotal) {
                    position = LinePosition::bigCornerFrontLeft;
                } else if (ddata.lsQuadFrontLeft + data.lsQuadFrontRight + data.lsQuadBackRight + data.lsFront + data.lsRight + data.lsBack + data.lsLeft == data.lsTotal) {
                    position = LinePosition::bigCornerFrontRight;
                } else {
                    /* We have exhausted all reasonable possibilities.
                     * If the light sensors see white in all four quadrants,
                     * we have no idea where we are.
                     */
                    position = LinePosition::unknown;
                }
            }
        }
    }
}

LinePosition LightSensorArray::getLinePosition() {
    return position;
}

/* int LightSensorArray::getUrgency() {
    return urgency;
} */
