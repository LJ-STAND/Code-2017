/*
* MASTER
*
* Source file for the master teensy for LJ STAND 2017
*/

#include <Arduino.h>
#include <t3spi.h>
#include <DebugController.h>
#include <i2c_t3.h>
#include <Config.h>
#include <MotorArray.h>
#include <IMU.h>
#include <MoveData.h>
#include <Pins.h>
#include <Slave.h>
#include <Timer.h>
#include <XBee.h>
#include <Common.h>

T3SPI spi;
MotorArray motors;
IMU imu;

SlaveLightSensor slaveLightSensor;

MoveData moveData(0, 150, 0);

Timer ledTimer = Timer(LED_BLINK_TIME_MASTER);

double compassPreviousAngle = 0;
long compassPreviousTime;
double compassDiff = 0;

double facingDirection = 0;

bool ledOn;

void setup() {
    // Onboard LED
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    // I2C
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 100000);
    Wire.setDefaultTimeout(200000);

    // Serial
    Serial.begin(57600);

    // SPI
    spi.begin_MASTER(MASTER_SCK, MASTER_MOSI, MASTER_MISO, MASTER_CS_TSOP, CS_ActiveLOW);
    spi.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV16);

    slaveLightSensor.init();

    // IMU
    imu.init();
    imu.calibrate();
    compassPreviousTime = micros();
}

void calculateRotationCorrection() {
    double multiplierD = CORRECTION_ROTATION_MULTIPLIER_D;
    double multiplierP = CORRECTION_ROTATION_MULTIPLIER_P;

    int correctionRotation;
    int rotation = ((mod(imu.heading - facingDirection, 360) > 180 ? 360 : 0) - mod(imu.heading - facingDirection, 360)) * multiplierP + compassDiff * multiplierD;

    if (abs(rotation) < CORRECTION_ROTATION_MINIMUM) {
        correctionRotation = 0;
    } else if (abs(rotation) < CORRECTION_ROTATION_MAXIMUM) {
        correctionRotation = rotation;
    } else {
        correctionRotation = (rotation > 0 ? CORRECTION_ROTATION_MAXIMUM : -CORRECTION_ROTATION_MAXIMUM);
    }

    moveData.rotation = correctionRotation;
}

void updateCompass() {
    imu.update();
    long currentTime = micros();
    compassDiff = (imu.heading - compassPreviousAngle) / (currentTime - compassPreviousTime);

    if (compassDiff > 180) {
        compassDiff -= 360;
    } else if (compassDiff < -180) {
        compassDiff += 360;
    }

    compassPreviousAngle = imu.heading;
    compassPreviousTime = currentTime;
}

void loop() {
    updateCompass();

    double lineAngle = slaveLightSensor.getLineAngle();
    double lineSize = slaveLightSensor.getLineSize();

    if (lineSize < 0.5) {
        moveData.angle = lineAngle;
    } else {
        moveData.angle = mod(lineAngle - 90, 360);
    }

    calculateRotationCorrection();

    motors.move(moveData);
}
