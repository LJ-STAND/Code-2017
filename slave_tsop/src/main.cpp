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

T3SPI spi;

volatile uint16_t dataIn[1];
volatile uint16_t dataOut[1];

TSOPArray tsops;

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
    }

    if (ledTimer.timeHasPassed()) {
        digitalWrite(LED_BUILTIN, ledOn);
        ledOn = !ledOn;
    }
}

void spi0_isr() {
    spi.rxtx16(dataIn, dataOut, 1);
    int command = dataIn[0];

    switch (command) {
        case SlaveCommand::tsopAngle:
            dataOut[0] = (uint16_t)tsops.getAngle();
            break;

        case SlaveCommand::tsopStrength:
            dataOut[0] = (uint16_t)tsops.getStrength();
            break;

        default:
            dataOut[0] = 0;
            break;
    }
}
