/*
 * Source file for the master teensy for LJ STAND
 */

#include <Arduino.h>
#include <t3spi.h>

T3SPI spi;

volatile uint16_t *dataIn;
volatile uint16_t *dataOut;

void setup() {
    Serial.begin(9600);
    Bluetooth::init();

    spi.begin_MASTER(ALT_SCK, MOSI, MISO, CS0, CS_ActiveLOW);
    spi.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV16);
    dataOut[0] = 911;

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void loop() {
    spi.txrx16(dataOut, dataIn, DATA_LENGTH, false, CS0);
    Serial.println(dataIn[0]);
}
