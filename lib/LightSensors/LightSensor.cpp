#include "LightSensor.h"

LightSensor::LightSensor(int in) {
    inPin = in;
    pinMode(in, INPUT);
}

void LightSensor::calibrate() {
    int defaultValue = 0;

    for (int i = 0; i < LS_CALIBRATION_COUNT; i++) {
        read();
        defaultValue += value;
    }

    thresholdValue = (defaultValue / LS_CALIBRATION_COUNT) + LS_CALIBRATION_BUFFER;
}

void LightSensor::read() {
    value = analogRead(inPin);
}

bool LightSensor::isOnWhite() {
    if (value > thresholdValue) {
        return true;
    } else {
        return false;
    }
}
