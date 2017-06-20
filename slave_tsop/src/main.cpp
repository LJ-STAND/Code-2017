/*
 * SLAVE_TSOP
 *
 * Source file for the TSOP slave teensy for LJ STAND 2017
 */

#include <Arduino.h>
#include <t3spi.h>
#include <TSOPArray.h>
#include <Config.h>
#include <MoveData.h>
#include <Slave.h>
#include <Timer.h>
#include <MovingAverage.h>

T3SPI spi;

volatile uint16_t dataIn[1];
volatile uint16_t dataOut[1];

SPITransactionState transactionState = SPITransactionState::noTransaction;
SPITransactionType currentTransactionType;
SlaveCommand currentCommand;

TSOPArray tsops;

MovingAverage tsopStrengthAverage = MovingAverage(20);

Timer ledTimer = Timer(LED_BLINK_TIME_SLAVE_TSOP);
bool ledOn;

void setup() {
    Serial.begin(9600);

    spi.begin_SLAVE(SLAVE_TSOP_SCK, SLAVE_TSOP_MOSI, SLAVE_TSOP_MISO, SLAVE_TSOP_CS);
    spi.setCTAR_SLAVE(16, SPI_MODE0);

    NVIC_ENABLE_IRQ(IRQ_SPI0);

    tsops.init();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    tsops.updateOnce();

    if (tsops.tsopCounter > TSOP_LOOP_COUNT) {
        tsops.finishRead();
        tsops.unlock();

        tsopStrengthAverage.update(tsops.getStrength());
        Serial.println((int)tsopStrengthAverage.average());
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
            if (static_cast<SPITransactionType>(dataIn[0]) == SPITransactionType::start) {
                transactionState = SPITransactionState::beginning;
            }

            break;

        case SPITransactionState::beginning:
            spi.rxtx16(dataIn, dataOut, 1);
            currentTransactionType = static_cast<SPITransactionType>(dataIn[0]);
            transactionState = SPITransactionState::type;

            break;

        case SPITransactionState::type:
            spi.rxtx16(dataIn, dataOut, 1);
            currentCommand = static_cast<SlaveCommand>(dataIn[0]);

            if (currentTransactionType == SPITransactionType::receive) {
                switch (currentCommand) {
                    case SlaveCommand::tsopAngle:
                        dataOut[0] = (uint16_t)tsops.getAngle();
                        break;

                    case SlaveCommand::tsopStrength:
                        dataOut[0] = (uint16_t)tsopStrengthAverage.average();
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
            if (static_cast<SPITransactionType>(dataIn[0]) == SPITransactionType::commandDelay) {
                transactionState = SPITransactionState::cmdDelay;
            }

            break;

        case SPITransactionState::cmdDelay:
            spi.rxtx16(dataIn, dataOut, 1);
            if (static_cast<SPITransactionType>(dataIn[0]) == SPITransactionType::commandDelay2) {
                transactionState = SPITransactionState::cmdDelay2;
            }

            break;

        case SPITransactionState::cmdDelay2:
            spi.rxtx16(dataIn, dataOut, 1);

            transactionState = SPITransactionState::data;

            break;

        case SPITransactionState::data:
            spi.rxtx16(dataIn, dataOut, 1);
            if (static_cast<SPITransactionType>(dataIn[0]) == SPITransactionType::end) {
                transactionState = SPITransactionState::noTransaction;
            }

            break;
    }
}
