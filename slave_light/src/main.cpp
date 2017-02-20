/*
 * SLAVE_LIGHT
 *
 * Source file for the light slave teensy for LJ STAND 2017
 */

#include <Arduino.h>
#include <t3spi.h>
#include <LightSensorArray.h>
#include <LinePosition.h>
#include <Pins.h>

T3SPI spi;

volatile uint16_t dataIn[DATA_LENGTH_LIGHT];
volatile uint16_t dataOut[DATA_LENGTH_LIGHT];

LightSensorArray lightSensorArray;

void setup() {
    Serial.begin(9600);

    spi.begin_SLAVE(SLAVE_LIGHT_SCK, SLAVE_LIGHT_MOSI, SLAVE_LIGHT_MISO, SLAVE_LIGHT_CS);
    spi.setCTAR_SLAVE(16, SPI_MODE0);

    NVIC_ENABLE_IRQ(IRQ_SPI0);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    lightSensorArray.init();
}

void loop() {
    lightSensorArray.read();
    lightSensorArray.calculatePostion();
    Serial.println(lightSensorArray.data.ls0);
    Serial.println(lightSensorArray.data.ls1);
    Serial.println(lightSensorArray.data.ls2);
    Serial.println(lightSensorArray.data.ls3);
    Serial.println(lightSensorArray.data.ls4);
    Serial.println(lightSensorArray.data.ls5);
    Serial.println(lightSensorArray.data.ls6);
    Serial.println(lightSensorArray.data.ls7);
    Serial.println(lightSensorArray.data.ls8);
    Serial.println(lightSensorArray.data.ls9);
    Serial.println(lightSensorArray.data.ls10);
    Serial.println(lightSensorArray.data.ls11);
    Serial.println(lightSensorArray.data.ls12);
    Serial.println(lightSensorArray.data.ls13);
    Serial.println(lightSensorArray.data.ls14);
    Serial.println(lightSensorArray.data.ls15);
    Serial.println(lightSensorArray.data.ls16);
    Serial.println(lightSensorArray.data.ls17);
    Serial.println(lightSensorArray.data.ls18);
    Serial.println(lightSensorArray.data.ls19);
    Serial.println(lightSensorArray.data.ls20);
    Serial.println(lightSensorArray.data.ls21);
    Serial.println(lightSensorArray.data.ls22);
    Serial.println(lightSensorArray.data.ls23);
    Serial.println();
    delay(2000);

}

void spi0_isr() {
    dataOut[0] = (uint16_t) lightSensorArray.getLinePosition();
    spi.rxtx16(dataIn, dataOut, DATA_LENGTH_LIGHT);
}
