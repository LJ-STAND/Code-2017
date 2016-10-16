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
    data = (LightSensorData) {ls0.isOnWhite(), ls1.isOnWhite(), ls2.isOnWhite(), ls3.isOnWhite(), ls4.isOnWhite(), ls5.isOnWhite(), ls6.isOnWhite(), ls7.isOnWhite(), ls8.isOnWhite(), ls9.isOnWhite(), ls10.isOnWhite(), ls11.isOnWhite(), ls12.isOnWhite(), ls13.isOnWhite(), ls14.isOnWhite(), ls15.isOnWhite(), ls16.isOnWhite(), ls17.isOnWhite, ls18.isOnWhite(), ls19.isOnWhite(), ls20.isOnWhite(), ls21.isOnWhite(), ls22.isOnWhite(), ls23.isOnWhite()};
}

void LightSensorArray::calculatePostion() {

}

LinePosition LightSensorArray::getLinePosition() {
    return position;
}

int LightSensorArray::getUrgency() {
    return urgency;
}
