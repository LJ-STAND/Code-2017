/*
 * SLAVE_LIGHT
 *
 * Source file for the light slave teensy for LJ STAND 2017
 */

#include <Arduino.h>
#include <t3spi.h>
#include <LightSensorArray.h>
#include <Pins.h>
#include <Slave.h>
#include <Timer.h>
#include <Common.h>

T3SPI spi;

volatile uint16_t dataIn[1];
volatile uint16_t dataOut[1];

LightSensorArray lightSensorArray;

Timer ledTimer = Timer(LED_BLINK_TIME_SLAVE_LIGHT);
bool ledOn;

void setup() {
    Serial.begin(57600);

    spi.begin_SLAVE(SLAVE_LIGHT_SCK, SLAVE_LIGHT_MOSI, SLAVE_LIGHT_MISO, SLAVE_LIGHT_CS);
    spi.setCTAR_SLAVE(16, SPI_MODE0);

    NVIC_ENABLE_IRQ(IRQ_SPI0);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    lightSensorArray.init();
}

void debug() {
    for (int i = 0; i < 24; i++) {
        Serial.print(lightSensorArray.data[i]);
        Serial.print(", ");
    }

    Serial.println(String(lightSensorArray.getLineAngle()) + ", " + String(lightSensorArray.getLineSize()));
}

void loop() {
    lightSensorArray.read();
    lightSensorArray.calculateClusters();
    lightSensorArray.calculateLine();

    if (ledTimer.timeHasPassed()) {
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }
}

void spi0_isr() {
    spi.rxtx16(dataIn, dataOut, 1);
    int command = dataIn[0];

    switch (command) {
        case SlaveCommand::lineAngle:
            dataOut[0] = (uint16_t)round(lightSensorArray.getLineAngle() * 100);
            break;

        case SlaveCommand::lineSize:
            dataOut[0] = (uint16_t)round(lightSensorArray.getLineSize() * 100);
            break;

        case SlaveCommand::lightSensorsFirst16Bit:
            dataOut[0] = lightSensorArray.getFirst16Bit();
            break;

        case SlaveCommand::lightSensorsSecond16Bit:
            dataOut[0] = lightSensorArray.getSecond16Bit();
            break;

        default:
            dataOut[0] = 0;
            break;
    }
}
