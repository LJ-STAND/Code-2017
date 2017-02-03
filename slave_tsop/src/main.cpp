/*
* SLAVE_TSOP
*
* Source file for the TSOP slave teensy for LJ STAND 2017
*/

#include <Arduino.h>
#include <t3spi.h>
#include <tsops.h>
#include <Config.h>

T3SPI spi;

volatile uint16_t dataIn[DATA_LENGTH_TSOP];
volatile uint16_t dataOut[DATA_LENGTH_TSOP];

TSOPArray tsops;
MoveData movement;

void setup() {
    Serial.begin(9600);

    spi.begin_SLAVE(ALT_SCK, MOSI, MISO, CS0);
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
         movement.angle = (int) round(tsopAngle < 180 ? (tsopAngle * 0.5) : (180 + tsopAngle * 0.5));
    } else if (tsopAngle < ORBIT_BIG_ANGLE || tsopAngle > 360 - ORBIT_BIG_ANGLE){
        if (tsopAngle < 180) {
            double nearFactor = (double)(tsopAngle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            movement.angle = (int) round(90 * nearFactor + (1 + nearFactor) * tsopAngle * 0.5);
        } else {
            double nearFactor = (double)(360 - tsopAngle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            movement.angle =  (int) round(360 - (90 * nearFactor + (1 + nearFactor) * (360 - tsopAngle) * 0.5));
        }
    } else {
        if (strength > ORBIT_SHORT_STRENGTH) {
            movement.angle =  tsopAngle + (tsopAngle < 180 ? 90 : -90);
        } else if (strength > ORBIT_BIG_STRENGTH) {
            double strengthFactor = (double)(strength - ORBIT_BIG_STRENGTH) / (double)(ORBIT_SHORT_STRENGTH - ORBIT_BIG_STRENGTH);
            double angleFactor = strengthFactor * 90;

            movement.angle = mod(angle + (angle < 180 ? angleFactor : -angleFactor), 360);
        } else {
            movement.angle = angle;
        }
    }
}

void loop() {
    tsops.readOnce();

    if (tsops.tsopCounter > TSOP_LOOP_COUNT) {
        tsops.finishRead();
        tsops.unlock();

        calculateOrbit();
    }
}

void spi0_isr() {
    dataOut[0] = (uint16_t) movement.angle;
    dataOut[1] = (uint16_t) movement.speed;
    spi.rxtx16(dataIn, dataOut, DATA_LENGTH_TSOP);
}
