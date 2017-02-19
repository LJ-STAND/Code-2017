#include "LightGate.h"

void LightGate::init() {
    pinMode(LIGHT_GATE, INPUT);
}

bool LightGate::hasBall() {
    return analogRead(LIGHT_GATE) < thresholdValue;
}
