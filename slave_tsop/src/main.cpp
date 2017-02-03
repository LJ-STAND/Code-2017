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
    // TODO

    int tsopAngle = tsops.getAngle();
    int strength = tsops.getStrength();

    if (angle < ORBIT_ORBIT_SMALL_ANGLE || angle > 360 - ORBIT_ORBIT_SMALL_ANGLE) {
         movement.angle = (int) round(angle < 180 ? (angle * 0.5) : (180 + angle * 0.5));
    } else if (angle < ORBIT_BIG_ANGLE || angle > 360 - ORBIT_BIG_ANGLE){
        if (angle < 180) {
            double nearFactor = (double)(angle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            movement.angle = (int) round(90 * nearFactor);
        } else {
            double nearFactor = (double)(360 - angle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            movement.angle =  (int) round(360 - (90 * nearFactor));
        }
    } else {
        if (strength > SHORT_STRENGTH) {
            movement.angle =  angle + (angle < 180 ? 90 : -90);
        } else if (strength > MEDIUM_STRENGTH) {
            double strengthFactor = (double)(strength - MEDIUM_STRENGTH) / (double)(SHORT_STRENGTH - MEDIUM_STRENGTH);
            double angleFactor = strengthFactor * 90;

            movement.angle = mod(angle + (angle < 180 ? angleFactor : -angleFactor), 360);
        } else {
            movement.angle = angle;
        }
    }

    return movement;
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
