#include "LightSensorArray.h"

LightSensorArray::LightSensorArray() {
    sensors[0] = LightSensor(LS_0);
    sensors[1] = LightSensor(LS_1);
    sensors[2] = LightSensor(LS_2);
    sensors[3] = LightSensor(LS_3);
    sensors[4] = LightSensor(LS_4);
    sensors[5] = LightSensor(LS_5);
    sensors[6] = LightSensor(LS_6);
    sensors[7] = LightSensor(LS_7);
    sensors[8] = LightSensor(LS_8);
    sensors[9] = LightSensor(LS_9);
    sensors[10] = LightSensor(LS_10);
    sensors[11] = LightSensor(LS_11);
    sensors[12] = LightSensor(LS_12);
    sensors[13] = LightSensor(LS_13);
    sensors[14] = LightSensor(LS_14);
    sensors[15] = LightSensor(LS_15);
    sensors[16] = LightSensor(LS_16);
    sensors[17] = LightSensor(LS_17);
    sensors[18] = LightSensor(LS_18);
    sensors[19] = LightSensor(LS_19);
    sensors[20] = LightSensor(LS_20);
    sensors[21] = LightSensor(LS_21);
    sensors[22] = LightSensor(LS_22);
    sensors[23] = LightSensor(LS_23);
}

void LightSensorArray::init() {
    for (int i = 0; i < 24; i++) {
        sensors[i].init();
    }
}

void LightSensorArray::read() {
    bool sensor0isOnWhite = sensors[mod(0 - arrayOffset, 24)].isOnWhite();
    bool sensor1isOnWhite = sensors[mod(1 - arrayOffset, 24)].isOnWhite();
    bool sensor2isOnWhite = sensors[mod(2 - arrayOffset, 24)].isOnWhite();
    bool sensor3isOnWhite = sensors[mod(3 - arrayOffset, 24)].isOnWhite();
    bool sensor4isOnWhite = sensors[mod(4 - arrayOffset, 24)].isOnWhite();
    bool sensor5isOnWhite = sensors[mod(5 - arrayOffset, 24)].isOnWhite();
    bool sensor6isOnWhite = sensors[mod(6 - arrayOffset, 24)].isOnWhite();
    bool sensor7isOnWhite = sensors[mod(7 - arrayOffset, 24)].isOnWhite();
    bool sensor8isOnWhite = sensors[mod(8 - arrayOffset, 24)].isOnWhite();
    bool sensor9isOnWhite = sensors[mod(9 - arrayOffset, 24)].isOnWhite();
    bool sensor10isOnWhite = sensors[mod(10 - arrayOffset, 24)].isOnWhite();
    bool sensor11isOnWhite = sensors[mod(11 - arrayOffset, 24)].isOnWhite();
    bool sensor12isOnWhite = sensors[mod(12 - arrayOffset, 24)].isOnWhite();
    bool sensor13isOnWhite = sensors[mod(13 - arrayOffset, 24)].isOnWhite();
    bool sensor14isOnWhite = sensors[mod(14 - arrayOffset, 24)].isOnWhite();
    bool sensor15isOnWhite = sensors[mod(15 - arrayOffset, 24)].isOnWhite();
    bool sensor16isOnWhite = sensors[mod(16 - arrayOffset, 24)].isOnWhite();
    bool sensor17isOnWhite = sensors[mod(17 - arrayOffset, 24)].isOnWhite();
    bool sensor18isOnWhite = sensors[mod(18 - arrayOffset, 24)].isOnWhite();
    bool sensor19isOnWhite = sensors[mod(19 - arrayOffset, 24)].isOnWhite();
    bool sensor20isOnWhite = sensors[mod(20 - arrayOffset, 24)].isOnWhite();
    bool sensor21isOnWhite = sensors[mod(21 - arrayOffset, 24)].isOnWhite();
    bool sensor22isOnWhite = sensors[mod(22 - arrayOffset, 24)].isOnWhite();
    bool sensor23isOnWhite = sensors[mod(23 - arrayOffset, 24)].isOnWhite();

    data = LightSensorData(sensor0isOnWhite, sensor1isOnWhite, sensor2isOnWhite, sensor3isOnWhite, sensor4isOnWhite, sensor5isOnWhite, sensor6isOnWhite, sensor7isOnWhite, sensor8isOnWhite, sensor9isOnWhite, sensor10isOnWhite, sensor11isOnWhite, sensor12isOnWhite, sensor13isOnWhite, sensor14isOnWhite, sensor15isOnWhite, sensor16isOnWhite, sensor17isOnWhite, sensor18isOnWhite, sensor19isOnWhite, sensor20isOnWhite, sensor21isOnWhite, sensor22isOnWhite, sensor23isOnWhite);
}



void LightSensorArray::getClusters(LightSensorData lightData, bool doneClusters2 = false) {
    bool cluster1Done, cluster2Done, cluster3Done = false;
    for (int i = 0; i < LS_NUM; i++) {
        if (cluster1Done) {
            if (cluster2Done) {
                if (cluster3Done) {
                    if (!doneClusters2) {
                        getClusters2();
                    } else {
                        cluster1 = LightSensorCluster(0.0, 0);
                    }
                } else {
                    if (lightData.getSensor(i)) {
                        if (cluster3.getLength() == 0) {
                            cluster3 = LightSensorCluster((double)i, 1);
                        } else {
                            if (i == 23){
                                cluster1.addCluster(cluster3);
                                cluster3 = LightSensorCluster(0.0, 0);
                            } else {
                                cluster3.addSensorClockwise();
                            }
                        }
                    } else {
                        if (cluster3.getLength() == 0) {
                            break;
                        } else {
                            cluster3Done = true;
                        }
                    }
                }
            } else {
                if (lightData.getSensor(i)) {
                    if (cluster2.getLength() == 0) {
                        cluster2 = LightSensorCluster((double)i, 1);
                    } else {
                        if (i == 23){
                            cluster1.addCluster(cluster2);
                            cluster2 = LightSensorCluster(0.0, 0);
                        } else {
                            cluster2.addSensorClockwise();
                        }
                    }
                } else {
                    if (cluster2.getLength() == 0) {
                        break;
                    } else {
                        cluster2Done = true;
                    }
                }
            }
        } else {
            if (lightData.getSensor(i)) {
                if (cluster1.getLength() == 0) {
                    cluster1 = LightSensorCluster((double)i, 1);
                } else {
                    cluster1.addSensorClockwise();
                }
            } else {
                if (cluster1.getLength() == 0) {
                    break;
                } else {
                    cluster1Done = true;
                }
            }
        }
    }
}

void LightSensorArray::getClusters2() {
    LightSensorData newLightData = data; // I feel like this will break things
    for (int i = 0; i < LS_NUM; i++) {
        if (!data.getSensor(i) && data.getSensor(mod(i - 1, LS_NUM)) && data.getSensor(mod(i + 1, LS_NUM))) {
            newLightData.setSensor(i, true);
        }
    }
    getClusters(newLightData, true);
}

void LightSensorArray::calculatePositionClusters() {
    // TODO
}

void LightSensorArray::calculatePostion() {
    if (data.lsTotal == 0) {
        // No line
        position = LinePosition::none;
    // One side section
    } else if (data.lsRightFrontLeft + data.lsFront + data.lsLeftFrontRight == data.lsTotal) {
        position = LinePosition::front;
    } else if (data.lsRightFrontRight + data.lsRight + data.lsRightBackRight == data.lsTotal) {
        position = LinePosition::right;
    } else if (data.lsLeftBackRight + data.lsBack + data.lsRightBackLeft == data.lsTotal) {
        position = LinePosition::back;
    } else if (data.lsLeftBackLeft + data.lsLeft + data.lsLeftFrontLeft == data.lsTotal) {
        position = LinePosition::left;
    } else {
        // One Quadrant
        if (data.lsQuadFrontRight + data.lsFront + data.lsRight == data.lsTotal) {
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
                    if (data.lsLeftFrontRight + data.lsFront + data.lsRightBackLeft + data.lsBack == data.lsTotal) {
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
                    if (data.lsLeftBackRight + data.lsBack + data.lsRightFrontLeft + data.lsFront == data.lsTotal) {
                        position = LinePosition::centreVertical;
                    } else if (data.lsLeftBackRight + data.lsBack + data.lsCentreBackRight + data.lsLeftFrontLeft + data.lsLeft + data.lsCentreFrontLeft) {
                        position = LinePosition::bigCornerBackLeft;
                    } else if (data.lsRightBackRight + data.lsRight + data.lsLeftFrontLeft + data.lsLeft == data.lsTotal) {
                        position = LinePosition::centreHorizontal;
                    } else if (data.lsRightBackRight + data.lsRight + data.lsCentreBackRight + data.lsRightFrontLeft + data.lsCentreFrontLeft + data.lsFront == data.lsTotal) {
                        position = LinePosition::bigCornerFrontRight;
                    } else {
                        position = LinePosition::unknown;
                    }
                } else {
                    // Three Quadrants
                    if (data.lsQuadFrontRight + data.lsQuadBackRight + data.lsQuadBackLeft + data.lsFront + data.lsRight + data.lsBack + data.lsLeft == data.lsTotal) {
                        position = LinePosition::bigCornerBackRight;
                    } else if (data.lsQuadBackRight + data.lsQuadBackLeft + data.lsQuadFrontLeft + data.lsFront + data.lsRight + data.lsBack + data.lsLeft == data.lsTotal) {
                        position = LinePosition::bigCornerBackLeft;
                    } else if (data.lsQuadBackLeft + data.lsQuadFrontLeft + data.lsQuadFrontRight + data.lsFront + data.lsRight + data.lsBack + data.lsLeft == data.lsTotal) {
                        position = LinePosition::bigCornerFrontLeft;
                    } else if (data.lsQuadFrontLeft + data.lsQuadFrontRight + data.lsQuadBackRight + data.lsFront + data.lsRight + data.lsBack + data.lsLeft == data.lsTotal) {
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
}

LinePosition LightSensorArray::getLinePosition() {
    return position;
}

uint16_t LightSensorArray::getFirst16Bit() {
    BitsUnion bitsUnion;
    bitsUnion.bits.b0 = data.ls0;
    bitsUnion.bits.b1 = data.ls1;
    bitsUnion.bits.b2 = data.ls2;
    bitsUnion.bits.b3 = data.ls3;
    bitsUnion.bits.b4 = data.ls4;
    bitsUnion.bits.b5 = data.ls5;
    bitsUnion.bits.b6 = data.ls6;
    bitsUnion.bits.b7 = data.ls7;
    bitsUnion.bits.b8 = data.ls8;
    bitsUnion.bits.b9 = data.ls9;
    bitsUnion.bits.b10 = data.ls10;
    bitsUnion.bits.b11 = data.ls11;
    bitsUnion.bits.b12 = data.ls12;
    bitsUnion.bits.b13 = data.ls13;
    bitsUnion.bits.b14 = data.ls14;
    bitsUnion.bits.b15 = data.ls15;

    return bitsUnion.bit16;
}

uint16_t LightSensorArray::getSecond16Bit() {
    BitsUnion bitsUnion;
    bitsUnion.bits.b0 = data.ls16;
    bitsUnion.bits.b1 = data.ls17;
    bitsUnion.bits.b2 = data.ls18;
    bitsUnion.bits.b3 = data.ls19;
    bitsUnion.bits.b4 = data.ls20;
    bitsUnion.bits.b5 = data.ls21;
    bitsUnion.bits.b6 = data.ls22;
    bitsUnion.bits.b7 = data.ls23;

    return bitsUnion.bit16;
}

void LightSensorArray::updateHeading(int heading) {
    arrayOffset = (int)round((double)heading / 15.0);
}
