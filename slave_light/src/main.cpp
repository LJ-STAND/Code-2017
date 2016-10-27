/*
 * Source file for the light slave teensy for LJ STAND 2017
 */

#include <Arduino.h>
#include <t3spi.h>
#include <LightSensorArray.h>
#include <LinePosition.h>

T3SPI spi;

LightSensorArray lightSensorArray;
LinePosition linePosition;

void setup() {
    Serial.begin(9600);

    spi.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    spi.setCTAR_SLAVE(16, SPI_MODE0);

    NVIC_ENABLE_IRQ(IRQ_SPI0);

    lightSensorArray.init();
}

void loop() {
    lightSensorArray.read();
    lightSensorArray.calculatePostion();
    linePosition = lightSensorArray.getLinePosition();
}
