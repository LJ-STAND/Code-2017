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
#include <Slave.h>
#include <EEPROM.h>

T3SPI spi;

volatile uint16_t dataIn[DATA_LENGTH_LIGHT];
volatile uint16_t dataOut[DATA_LENGTH_LIGHT];

LightSensorArray lightSensorArray;

LinePosition previousPosition = LinePosition::none;

void setup() {
    Serial.begin(9600);

    spi.begin_SLAVE(SLAVE_LIGHT_SCK, SLAVE_LIGHT_MOSI, SLAVE_LIGHT_MISO, SLAVE_LIGHT_CS);
    spi.setCTAR_SLAVE(16, SPI_MODE0);

    NVIC_ENABLE_IRQ(IRQ_SPI0);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    lightSensorArray.init();
}

void debug() {
    Serial.print(lightSensorArray.ls0.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls1.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls2.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls3.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls4.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls5.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls6.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls7.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls8.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls9.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls10.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls11.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls12.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls13.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls14.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls15.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls16.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls17.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls18.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls19.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls20.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls21.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls22.getValue());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls23.getValue());
    Serial.println();
    delay(100);
}

void loop() {
    lightSensorArray.read();
    lightSensorArray.calculatePostion();
    LinePosition position = lightSensorArray.getLinePosition();

    debug();

    if (position != previousPosition) {
        previousPosition = position;
    }
}

void spi0_isr() {
    spi.rxtx16(dataIn, dataOut, DATA_LENGTH_LIGHT);
    int spiRequest = dataIn[0];

    switch (spiRequest) {
        case SlaveCommands::linePosition: {
            dataOut[0] = (uint16_t)lightSensorArray.getLinePosition();
            break;
        }

        case SlaveCommands::lightSensorsFirst16Bit: {
            dataOut[0] = lightSensorArray.getFirst16Bit();
            break;
        }

        case SlaveCommands::lightSensorsSecond16Bit: {
            dataOut[0] = lightSensorArray.getSecond16Bit();
            break;
        }

        default: {
            dataOut[0] = 0;
            break;
        }
    }
}
