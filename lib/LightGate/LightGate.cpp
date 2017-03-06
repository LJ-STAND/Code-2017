#include "LightGate.h"

void LightGate::init() {
    pinMode(LIGHT_GATE, INPUT);

    // Auto calibrate
    int defaultValue = 0;

    for (int i = 0; i < LIGHT_GATE_CALIBRATION_COUNT; i++) {
        read();
        defaultValue += value;
    }

    thresholdValue = round((int)((double)defaultValue / LIGHT_GATE_CALIBRATION_COUNT) - LIGHT_GATE_CALIBRATION_BUFFER);
}

void LightGate::read() {
    value = analogRead(LIGHT_GATE);
}

bool LightGate::hasBall() {
    read();
    return value < thresholdValue;
}

int LightGate::getValue() {
    return value;
}
