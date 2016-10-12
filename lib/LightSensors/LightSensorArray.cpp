#include "LightSensorArray.h"

LightSensorArray::LightSensorArray() {
    ls1 = 
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
