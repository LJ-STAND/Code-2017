/*
 * Source file for the light slave teensy for LJ STAND 2017
 */

#include <Arduino.h>
#include <t3spi.h>
#include <LightSensorArray.h>
#include <LinePosition.h>

volatile uint16_t *dataIn;
volatile uint16_t dataOut;

T3SPI spi;

LightSensorArray lightSensorArray;
LinePosition linePosition;

void setup() {
    Serial.begin(9600);

    spi.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    spi.setCTAR_SLAVE(16, SPI_MODE0);

    NVIC_ENABLE_IRQ(IRQ_SPI0);

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    dataOut[0] = 1;
}

void loop() {
    // lightSensorArray.read();
    // lightSensorArray.calculatePostion();
    // linePosition = lightSensorArray.getLinePosition();

    dataOut[0] = dataOut[0] + 1;
    if (dataOut[0] >= 65535) {
        dataOut[0] = 0;
    }
}

void spi0_isr() {
    spi.rxtx16(dataIn, dataOut, DATA_LENGTH);
    Serial.println(dataIn[0]);
}
