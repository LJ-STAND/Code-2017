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

T3SPI spi;

volatile uint16_t dataIn[DATA_LENGTH_TSOP];
volatile uint16_t dataOut[DATA_LENGTH_TSOP];

TSOPArray tsops;
MoveData orbitMovement;

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
         orbitMovement.angle = (int)round(tsopAngle < 180 ? (tsopAngle * 0.5) : (180 + tsopAngle * 0.5));
    } else if (tsopAngle < ORBIT_BIG_ANGLE || tsopAngle > 360 - ORBIT_BIG_ANGLE) {
        if (tsopAngle < 180) {
            double nearFactor = (double)(tsopAngle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            orbitMovement.angle = (int)round(90 * nearFactor + (1 + nearFactor) * tsopAngle * 0.5);
        } else {
            double nearFactor = (double)(360 - tsopAngle - ORBIT_SMALL_ANGLE) / (double)(ORBIT_BIG_ANGLE - ORBIT_SMALL_ANGLE);
            orbitMovement.angle = (int)round(360 - (90 * nearFactor + (1 + nearFactor) * (360 - tsopAngle) * 0.5));
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

    // double moveSpeedModifier;
    //
    // if (orbitMovement.angle < 90) {
    //     // 0-90 degrees
    //     moveSpeedModifier = (90 - orbitMovement.angle) / 90.0;
    // } else if (orbitMovement.angle < 180) {
    //     // 90-180 degrees
    //     moveSpeedModifier = (orbitMovement.angle - 90) / 90.0;
    // } else if (orbitMovement.angle < 270) {
    //     // 180-270 degrees
    //     moveSpeedModifier = (270 - orbitMovement.angle) / 90.0;
    // } else {
    //     // 270-360 degrees
    //     moveSpeedModifier = (orbitMovement.angle - 270) / 90.0;
    // }
    //
    // orbitMovement.speed = MIN_ORBIT_SPEED + (MAX_ORBIT_SPEED - MIN_ORBIT_SPEED) * moveSpeedModifier;
    orbitMovement.speed = MAX_ORBIT_SPEED;
}

void loop() {
    tsops.updateOnce();

    if (tsops.tsopCounter > TSOP_LOOP_COUNT) {
        tsops.finishRead();
        tsops.unlock();

        calculateOrbit();
    }
}

void spi0_isr() {
    spi.rxtx16(dataIn, dataOut, DATA_LENGTH_TSOP);
    int spiRequest = dataIn[0];

    switch (spiRequest) {
        case SlaveCommands::orbitAngle: {
            dataOut[0] = (uint16_t)(orbitMovement.angle != -1 ? orbitMovement.angle : TSOP_NO_BALL);
            break;
        }

        case SlaveCommands::orbitSpeed: {
            dataOut[0] = (uint16_t)orbitMovement.speed;
            break;
        }

        case SlaveCommands::hasBallTSOP: {
            dataOut[0] = (uint16_t)tsops.hasBall();
            break;
        }

        default: {
            dataOut[0] = 0;
        }
    }
}
