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
    Serial.print(lightSensorArray.sensors[0].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[1].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[2].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[3].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[4].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[5].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[6].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[7].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[8].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[9].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[10].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[11].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[12].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[13].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[14].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[15].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[16].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[17].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[18].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[19].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[20].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[21].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[22].isOnWhite());
    Serial.print(", ");
    Serial.print(lightSensorArray.sensors[23].isOnWhite());
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
        case SPITransactionState::noTransaction:
            spi.rxtx16(dataIn, dataOut, 1);
            Serial.println("Start: " + String(dataIn[0]));

            if (static_cast<SPITransactionType>(dataIn[0]) == SPITransactionType::start) {
                transactionState = SPITransactionState::beginning;
            }

            break;

        case SPITransactionState::beginning:
            spi.rxtx16(dataIn, dataOut, 1);
            Serial.println("Type: " + String(dataIn[0]));
            currentTransactionType = static_cast<SPITransactionType>(dataIn[0]);
            transactionState = SPITransactionState::type;

            break;

        case SPITransactionState::type:
            spi.rxtx16(dataIn, dataOut, 1);
            Serial.println("Command: " + String(dataIn[0]));
            currentCommand = static_cast<SlaveCommand>(dataIn[0]);

            if (currentTransactionType == SPITransactionType::receive) {
                switch (currentCommand) {
                    case SlaveCommand::linePosition:
                        dataOut[0] = (uint16_t)lightSensorArray.getLinePosition();
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

            transactionState = SPITransactionState::command;

            break;

        case SPITransactionState::command:
            spi.rxtx16(dataIn, dataOut, 1);
            Serial.println("Data: " + String(dataIn[0]) + ", " + String(dataOut[0]));
            if (currentTransactionType == SPITransactionType::send) {
                switch (currentCommand) {
                    case SlaveCommand::sendCompass:
                        heading = dataIn[0];
                        break;
                }
            }

            transactionState = SPITransactionState::data;

            break;

        case SPITransactionState::data:
            spi.rxtx16(dataIn, dataOut, 1);
            Serial.println("End: " + String(dataIn[0]));
            if (static_cast<SPITransactionType>(dataIn[0]) == SPITransactionType::end) {
                transactionState = SPITransactionState::noTransaction;
            }

            break;
    }
}
