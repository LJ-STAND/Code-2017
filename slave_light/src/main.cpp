/*
 * Source file for the light slave teensy for LJ STAND 2017
 */

#include <Arduino.h>
#include <t3spi.h>
#include <LightSensorArray.h>
#include <LinePosition.h>

T3SPI spi;

volatile uint16_t dataIn[DATA_LENGTH_LIGHT];
volatile uint16_t dataOut[DATA_LENGTH_LIGHT];

LightSensorArray lightSensorArray;

void setup() {
    Serial.begin(9600);

    spi.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    spi.setCTAR_SLAVE(16, SPI_MODE0);

    NVIC_ENABLE_IRQ(IRQ_SPI0);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    lightSensorArray.read();
    lightSensorArray.calculatePostion();
}

void spi0_isr() {
    dataOut[0] = (uint16_t) lightSensorArray.getLinePosition();
    spi.rxtx16(dataIn, dataOut, DATA_LENGTH_LIGHT);
}
