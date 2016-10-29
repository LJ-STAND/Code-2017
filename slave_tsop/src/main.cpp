/*
* Source file for the TSOP slave teensy for LJ STAND 2017
*/

#include <Arduino.h>
#include <t3spi.h>
#include <TsopArray.h>
#include <Config.h>

T3SPI spi;

volatile uint16_t dataIn[DATA_LENGTH_TSOP];
volatile uint16_t dataOut[DATA_LENGTH_TSOP];

TSOPArray tsopArray;

void setup() {
    Serial.begin(9600);

    spi.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
    spi.setCTAR_SLAVE(16, SPI_MODE0);

    NVIC_ENABLE_IRQ(IRQ_SPI0);

    tsopArray.init();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
    tsopArray.readOnce();

    if (tsopArray.tsopCounter > TSOP_LOOP_COUNT) {
        tsopArray.finishRead();
        tsopArray.unlock();
    }
}

void spi0_isr() {
    dataOut[0] = (uint16_t) tsopArray.angle;
    dataOut[1] = (uint16_t) tsopArray.strength;
    spi.rxtx16(dataIn, dataOut, DATA_LENGTH_TSOP);
}
