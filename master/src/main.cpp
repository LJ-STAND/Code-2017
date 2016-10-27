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
    Serial.begin(9600);

    spi.begin_MASTER(ALT_SCK, MOSI, MISO, CS0, CS_ActiveLOW);
    spi.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV8);
    dataOut[0] = 911;

    delay(500);
}

void loop() {
    //SPI teensy
    spi.txrx16(dataOut, dataIn, DATA_LENGTH, false, CS0); //Send data to teensy on CS0
    Serial.println(dataIn[0]);
    delay(100);
}
