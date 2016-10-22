/*
 * Source file for the master teensy for LJ STAND
 */

#include <Arduino.h>
#include <SPI.h>

#include <LightSensorArray.h>
#include <RobotPosition.h>
#include <CalculateRobotPosition.h>

void setup() {
    pinMode(14, OUTPUT);
}

void loop() {
    for (int i = 0; i <= 255; i++) {
        analogWrite(14, i);
        delay(5);
    }

    for (int i = 255; i >= 0; i--) {
        analogWrite(14, i);
        delay(5);
    }
}
