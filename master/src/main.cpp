/*
 * Source file for the master teensy for LJ STAND
 */

#include <Arduino.h>
#include <SPI.h>

#include <LightSensorArray.h>
#include <RobotPosition.h>
#include <CalculateRobotPosition.h>

void setup() {
    // empty
    Serial.begin(9600);
    pinMode(13, OUTPUT);
}

void loop() {
    // empty
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    Serial.println("test");
}
