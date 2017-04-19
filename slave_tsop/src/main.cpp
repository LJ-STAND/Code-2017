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
#include <EEPROM.h>
#include <Timer.h>

T3SPI spi;

volatile uint16_t dataIn[1];
volatile uint16_t dataOut[1];

SPITransactionState transactionState = SPITransactionState::noTransaction;
SPITransactionType currentTransactionType;
SlaveCommand currentCommand;

TSOPArray tsops;
MoveData orbitMovement;

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

void calculateOrbit() {
    int tsopAngle = tsops.getAngle();
    int tsopStrength = tsops.getStrength();

    if (tsopAngle < ORBIT_SMALL_ANGLE || tsopAngle > 360 - ORBIT_SMALL_ANGLE) {
         orbitMovement.angle = (int)round(tsopAngle < 180 ? (tsopAngle * ORBIT_BALL_FORWARD_ANGLE_TIGHTENER) : (180 + tsopAngle * ORBIT_BALL_FORWARD_ANGLE_TIGHTENER));
    } else if (tsopAngle < ORBIT_BIG_ANGLE || tsopAngle > 360 - ORBIT_BIG_ANGLE) {
        if (tsopAngle < 180) {
            double nearFactor = (double)(tsopAngle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            orbitMovement.angle = (int)round(90 * nearFactor + tsopAngle * ORBIT_BALL_FORWARD_ANGLE_TIGHTENER + tsopAngle * (1 - ORBIT_BALL_FORWARD_ANGLE_TIGHTENER) * nearFactor);
        } else {
            double nearFactor = (double)(360 - tsopAngle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            orbitMovement.angle = (int)round(360 - (90 * nearFactor + (360 - tsopAngle) * ORBIT_BALL_FORWARD_ANGLE_TIGHTENER + (360 - tsopAngle) * (1 - ORBIT_BALL_FORWARD_ANGLE_TIGHTENER) * nearFactor));
        }
    } else {
        if (tsopStrength > ORBIT_SHORT_STRENGTH) {
            orbitMovement.angle =  tsopAngle + (tsopAngle < 180 ? 90 : -90);
        } else if (tsopStrength > ORBIT_BIG_STRENGTH) {
            double strengthFactor = (double)(tsopStrength - ORBIT_BIG_STRENGTH) / (double)(ORBIT_SHORT_STRENGTH - ORBIT_BIG_STRENGTH);
            double angleFactor = strengthFactor * 90;
            orbitMovement.angle = tsopAngle + (tsopAngle < 180 ? angleFactor : -angleFactor);
        } else {
            orbitMovement.angle = tsopAngle;
        }
    }

    if (tsopAngle == -1) {
        orbitMovement.angle = -1;
    }

    orbitMovement.speed = MAX_ORBIT_SPEED;
}

void loop() {
    tsops.updateOnce();

    if (tsops.tsopCounter > TSOP_LOOP_COUNT) {
        tsops.finishRead();
        tsops.unlock();

        calculateOrbit();
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
            transactionState = SPITransactionState::command;

            if (currentTransactionType == SPITransactionType::receive) {
                switch (currentCommand) {
                    case SlaveCommand::orbitAngle:
                        dataOut[0] = (uint16_t)(orbitMovement.angle != -1 ? orbitMovement.angle : TSOP_NO_BALL);
                        break;

                    case SlaveCommand::orbitSpeed:
                        dataOut[0] = (uint16_t)orbitMovement.speed;
                        break;

                    case SlaveCommand::hasBallTSOP:
                        dataOut[0] = (uint16_t)tsops.hasBall();
                        break;

                    default:
                        dataOut[0] = 0;
                        break;
                }
            }

            break;

        case SPITransactionState::command:
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
