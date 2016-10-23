/*
 * Source file for the light slave teensy for LJ STAND 2017
 */

#include <Arduino.h>
#include <LightSensorArray.h>
#include <LinePosition.h>

LightSensorArray lightSensorArray;
LinePosition linePosition;

void setup() {
    lightSensorArray.init();
}

void loop() {
    lightSensorArray.read();
    lightSensorArray.calculatePostion();
    linePosition = lightSensorArray.getLinePosition();
}
