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
#include <Timer.h>
#include <LJSTANDCommon.h>

T3SPI spi;

volatile uint16_t dataIn[1];
volatile uint16_t dataOut[1];

SPITransactionState transactionState = SPITransactionState::noTransaction;
SPITransactionType currentTransactionType;
SlaveCommand currentCommand;

LightSensorArray lightSensorArray;

LinePosition previousPosition = LinePosition::none;

Timer ledTimer = Timer(LED_BLINK_TIME_SLAVE_LIGHT);
bool ledOn;

int heading;

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
    Serial.print(lightSensorArray.ls0.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls1.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls2.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls3.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls4.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls5.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls6.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls7.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls8.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls9.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls10.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls11.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls12.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls13.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls14.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls15.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls16.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls17.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls18.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls19.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls20.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls21.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls22.isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.ls23.isOnWhite());
    Serial.print(", ");
    Serial.print(linePositionString(lightSensorArray.getLinePosition()));
    Serial.println();
}

void loop() {
    lightSensorArray.read();
    lightSensorArray.calculatePostion();
    LinePosition position = lightSensorArray.getLinePosition();

    // debug();

    if (position != previousPosition) {
        previousPosition = position;
    }

    if (ledTimer.timeHasPassed()) {
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }
}

void spi0_isr() {
    switch (transactionState) {
        case SPITransactionState::noTransaction: {
            spi.rxtx16(dataIn, dataOut, 1);
            Serial.println("Start: " + String(dataIn[0]));

            if (static_cast<SPITransactionType>(dataIn[0]) == SPITransactionType::start) {
                transactionState = SPITransactionState::beginning;
            }

            break;
        }

        case SPITransactionState::beginning: {
            spi.rxtx16(dataIn, dataOut, 1);
            Serial.println("Type: " + String(dataIn[0]));
            currentTransactionType = static_cast<SPITransactionType>(dataIn[0]);
            transactionState = SPITransactionState::type;

            break;
        }

        case SPITransactionState::type: {
            spi.rxtx16(dataIn, dataOut, 1);
            Serial.println("Command: " + String(dataIn[0]));
            currentCommand = static_cast<SlaveCommand>(dataIn[0]);

            if (currentTransactionType == SPITransactionType::receive) {
                switch (currentCommand) {
                    case SlaveCommand::linePosition: {
                        dataOut[0] = (uint16_t)lightSensorArray.getLinePosition();
                        break;
                    }

                    case SlaveCommand::lightSensorsFirst16Bit: {
                        dataOut[0] = lightSensorArray.getFirst16Bit();
                        break;
                    }

                    case SlaveCommand::lightSensorsSecond16Bit: {
                        dataOut[0] = lightSensorArray.getSecond16Bit();
                        break;
                    }

                    default: {
                        dataOut[0] = 0;
                        break;
                    }
                }
            }

            transactionState = SPITransactionState::command;

            break;
        }

        case SPITransactionState::command: {
            spi.rxtx16(dataIn, dataOut, 1);
            Serial.println("Data: " + String(dataIn[0]) + ", " + String(dataOut[0]));
            if (currentTransactionType == SPITransactionType::send) {
                switch (currentCommand) {
                    case SlaveCommand::sendCompass: {
                        heading = dataIn[0];
                        break;
                    }
                }
            }

            transactionState = SPITransactionState::data;

            break;
        }

        case SPITransactionState::data: {
            spi.rxtx16(dataIn, dataOut, 1);
            Serial.println("End: " + String(dataIn[0]));
            if (static_cast<SPITransactionType>(dataIn[0]) == SPITransactionType::end) {
                transactionState = SPITransactionState::noTransaction;
            }

            break;
        }
    }
}
