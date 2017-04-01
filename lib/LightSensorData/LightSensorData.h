#ifndef LIGHT_SENSOR_DATA_H
#define LIGHT_SENSOR_DATA_H

typedef struct LightSensorData {
    // Front sensor
    bool ls0;

    // First quadrant (front right)
    bool ls1, ls2, ls3, ls4, ls5;

    // Right sensor
    bool ls6;

    // Second quadrant (back right)
    bool ls7, ls8, ls9, ls10, ls11;

    // Back sensor
    bool ls12;

    // Third quadrant (back left)
    bool ls13, ls14, ls15, ls16, ls17;

    // Left sensor
    bool ls18;

    // Fourth quadrant (front left)
    bool ls19, ls20, ls21, ls22, ls23;

    int lsQuadFrontRight;
    int lsQuadBackRight;
    int lsQuadBackLeft;
    int lsQuadFrontLeft;

    int lsHalfFront;
    int lsHalfRight;
    int lsHalfBack;
    int lsHalfLeft;

    int lsFront;
    int lsLeftFrontRight;
    int lsCentreFrontRight;
    int lsRightFrontRight;
    int lsRight;
    int lsRightBackRight;
    int lsCentreBackRight;
    int lsLeftBackRight;
    int lsBack;
    int lsRightBackLeft;
    int lsCentreBackLeft;
    int lsLeftBackLeft;
    int lsLeft;
    int lsLeftFrontLeft;
    int lsCentreFrontLeft;
    int lsRightFrontLeft;

    int lsTotal;


    LightSensorData() {}
    LightSensorData(bool on0, bool on1, bool on2, bool on3, bool on4, bool on5, bool on6, bool on7, bool on8, bool on9, bool on10, bool on11, bool on12, bool on13, bool on14, bool on15, bool on16, bool on17, bool on18, bool on19, bool on20, bool on21, bool on22, bool on23) {
        ls0 = on0;
        ls1 = on1;
        ls2 = on2;
        ls3 = on3;
        ls4 = on4;
        ls5 = on5;
        ls6 = on6;
        ls7 = on7;
        ls8 = on8;
        ls9 = on9;
        ls10 = on10;
        ls11 = on11;
        ls12 = on12;
        ls13 = on13;
        ls14 = on14;
        ls15 = on15;
        ls16 = on16;
        ls17 = on17;
        ls18 = on18;
        ls19 = on19;
        ls20 = on20;
        ls21 = on21;
        ls22 = on22;
        ls23 = on23;

        calculateQuadrants();
    }

    void calculateQuadrants() {
        lsFront = (int) ls0;
        lsRight = (int) ls6;
        lsBack = (int) ls12;
        lsLeft = (int) ls18;

        lsLeftFrontRight = (int) ls1 + (int) ls2;
        lsCentreFrontRight = (int) ls3;
        lsRightFrontRight = (int) ls4 + (int) ls5;

        lsRightBackRight = (int) ls7 + (int) ls8;
        lsCentreBackRight = (int) ls9;
        lsLeftBackRight = (int) ls10 + (int) ls11;

        lsRightBackLeft = (int) ls13 + (int) ls14;
        lsCentreBackLeft = (int) ls15;
        lsLeftBackLeft = (int) ls16 + (int) ls17;

        lsLeftFrontLeft = (int) ls19 + (int) ls20;
        lsCentreFrontLeft = (int) ls21;
        lsRightFrontLeft = (int) ls22 + (int) ls23;

        lsQuadFrontRight = lsLeftFrontRight + lsCentreFrontRight + lsRightFrontRight;
        lsQuadBackRight = lsRightBackRight + lsCentreBackRight + lsLeftBackRight;
        lsQuadBackLeft = lsRightBackLeft + lsCentreBackLeft + lsLeftBackLeft;
        lsQuadFrontLeft = lsLeftFrontLeft + lsCentreFrontLeft + lsRightFrontLeft;

        lsHalfFront = lsQuadFrontLeft + lsFront + lsQuadFrontRight;
        lsHalfRight = lsQuadFrontRight + lsRight + lsQuadBackRight;
        lsHalfBack = lsQuadBackRight + lsBack + lsQuadBackLeft;
        lsHalfLeft = lsQuadBackLeft + lsLeft + lsQuadFrontLeft;

        lsTotal = lsHalfFront + lsHalfBack + lsRight + lsLeft;
    }
} LightSensorData;

#endif // LIGHT_SENSOR_DATA_H
