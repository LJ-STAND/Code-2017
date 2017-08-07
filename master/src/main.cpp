/*
* MASTER
*
* Source file for the master teensy for LJ STAND 2017
*/

#include <Arduino.h>
#include <t3spi.h>
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
#include <LineData.h>

T3SPI spi;
MotorArray motors;
IMU imu;

SlaveLightSensor slaveLightSensor;

MoveData moveData(0, 0, 0);
LineData lineData;

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

void updateLine(double angle, double size) {
    bool noLine = angle == NO_LINE_ANGLE || size == 3;

    angle = noLine ? 0 : doubleMod(angle + imu.heading, 360);

    if (lineData.onField) {
        if (!noLine) {
            lineData.angle = angle;
            lineData.size = size;

            lineData.onField = false;
        }
    } else {
        if (lineData.size == 3) {
            if (!noLine) {
                lineData.angle = doubleMod(angle + 180, 360);
                lineData.size = 2 - size;
            }
        } else {
            if (noLine) {
                if (lineData.size <= 1) {
                    lineData.onField = true;
                    lineData.size = 0;
                    lineData.angle = 0;
                } else {
                    lineData.size = 3;
                }
            } else {
                if (smallestAngleBetween(lineData.angle, angle) <= 90) {
                    lineData.angle = angle;
                    lineData.size = size;
                } else {
                    lineData.angle = doubleMod(angle + 180, 360);
                    lineData.size = 2 - size;
                }
            }
        }
    }

    #if DEBUG_LINE
        Serial.print(lineData.onField ? "On" : "Off");
        Serial.println(", Robot: " + String(lineData.angle) + ", " + String(lineData.size) + ", Line: " + String(angle) + ", " + String(size));
    #endif
}

void loop() {
    updateCompass();

    updateLine(slaveLightSensor.getLineAngle(), slaveLightSensor.getLineSize());

    // facingDirection = 0;
    // moveData.speed = 50;
    // if (!lineData.onField) {
    //     moveData.angle = lineData.angle - 90;
    // }
    if (!lineData.onField || lineData.size == 3) {
        facingDirection = mod(lineData.angle - 90, 360);
    }

    int forwardsMovement = ORBIT_SPEED;
    int sidewaysMovement;
    if (lineData.onField) {
        sidewaysMovement = ORBIT_SPEED;
    } else if (lineData.size == 3) {
        sidewaysMovement = -ORBIT_SPEED;
    } else {
        sidewaysMovement = (lineData.size - 1) * -ORBIT_SPEED;
    }
    moveData.angle = mod(radiansToDegrees(atan2(sidewaysMovement, forwardsMovement)), 360);
    moveData.speed = sqrt(forwardsMovement * forwardsMovement + sidewaysMovement * sidewaysMovement);


    calculateRotationCorrection();

    motors.move(moveData);
}
