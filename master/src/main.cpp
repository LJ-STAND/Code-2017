/*
 * Source file for the master teensy for LJ STAND
 */

#include <Arduino.h>
#include <t3spi.h>

T3SPI spi;

#define DATA_LENGTH 1

volatile uint16_t dataIn[DATA_LENGTH];
volatile uint16_t dataOut[DATA_LENGTH];

void setup() {
    pinMode(13, OUTPUT);
}

void loop() {
    //SPI teensy
    // spi.rxtx16(dataIn, dataOut, datalength, false, CS0); //Send data to teensy on CS0

    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}
