/*
 * Source file for the master teensy for LJ STAND
 */

#include <Arduino.h>
#include <SPI.h>

void setup() {
    Serial.begin(9600);
    // empty
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
