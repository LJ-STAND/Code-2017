/*
 * MASTER
 *
 * Source file for the master teensy for LJ STAND 2017
 */

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <t3spi.h>
#include <DebugController.h>
#include <i2c_t3.h>
#include <Config.h>
#include <SlaveData.h>
#include <Bluetooth.h>
#include <MotorArray.h>
#include <IMU.h>
#include <LinePosition.h>
#include <RobotPosition.h>
#include <CalculateRobotPosition.h>
#include <MoveData.h>
#include <Pins.h>
#include <LightGate.h>

T3SPI spi;

volatile uint16_t dataInTsop[DATA_LENGTH_TSOP];
volatile uint16_t dataOutTsop[DATA_LENGTH_TSOP];
volatile uint16_t dataInLight[DATA_LENGTH_LIGHT];
volatile uint16_t dataOutLight[DATA_LENGTH_LIGHT];

SlaveData slaveData;
RobotPosition position;
RobotPosition previousPosition = RobotPosition::field;

DebugController debug;
MotorArray motors;
IMU imu;
LightGate lightGate;

void setup() {
    // Onboard LED
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    // Debug
    debug.init();

    // I2C
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
    Wire.setDefaultTimeout(200000);

    debug.toggleOrange(true);

    // Serial
    Serial.begin(9600);
    Bluetooth::init();

    debug.toggleWhite(true);

    // SPI
    spi.begin_MASTER(MASTER_SCK, MASTER_MOSI, MASTER_MISO, MASTER_CS_TSOP, CS_ActiveLOW);
    spi.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV16);
    spi.enableCS(MASTER_CS_LIGHT, CS_ActiveLOW);

    debug.toggleYellow(true);

    // IMU
    imu.init();
    imu.calibrate();

    debug.toggleBlue(true);

    // Light Gate
    lightGate.init();

    debug.toggleAllLEDs(true);
}

int calculateRotationCorrection() {
    int correctionRotation;
    int rotation = (imu.heading > 180 ? 360 : 0) - imu.heading;

    if (abs(rotation) < IMU_THRESHOLD) {
        correctionRotation = 0;
    } else if (abs(rotation) < CORRECTION_ROTATION_MINIMUM) {
        correctionRotation = (rotation > 0 ? CORRECTION_ROTATION_MINIMUM : -CORRECTION_ROTATION_MINIMUM);
    } else if (abs(rotation) < CORRECTION_ROTATION_MAXIMUM) {
        correctionRotation = rotation;
    } else {
        correctionRotation = (rotation > 0 ? CORRECTION_ROTATION_MAXIMUM : -CORRECTION_ROTATION_MAXIMUM);
    }

    return correctionRotation * CORRECTION_ROTATION_MULTIPLIER;
}

MoveData calculateMovement() {
    int angle = slaveData.orbitAngle != TSOP_NO_BALL ? slaveData.orbitAngle : 0;
    int speed = slaveData.orbitAngle != TSOP_NO_BALL ? slaveData.orbitSpeed : 0;
    int rotation = calculateRotationCorrection();
    if (position != RobotPosition::field && slaveData.orbitAngle != TSOP_NO_BALL){
        int orbitAngle = slaveData.orbitAngle;
        if (position == RobotPosition::smallOnFrontLine) {
            if (270 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < 90 + LS_MOVEMENT_ANGLE_BUFFER) {
                angle = orbitAngle;
                speed =  (int) slaveData.orbitSpeed * LS_MOVEMENT_SMALL_MULTIPLIER;
            }
        }
        if (position == RobotPosition::bigOnFrontLine) {
            if (270 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < 90 + LS_MOVEMENT_ANGLE_BUFFER) {
                if (orbitAngle < 180) {
                    angle = 120;
                }
                else {
                    angle = 240;
                }
            }
        }
        if (position == RobotPosition::overFrontLine) {
            if (270 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < 90 + LS_MOVEMENT_ANGLE_BUFFER) {
                angle = 180;
            }
        }
        if (position == RobotPosition::smallOnRightLine) {
            if (mod(0 - LS_MOVEMENT_ANGLE_BUFFER, 360) < orbitAngle && orbitAngle < 180 + LS_MOVEMENT_ANGLE_BUFFER) {
                angle = orbitAngle;
                speed =  (int) slaveData.orbitSpeed * LS_MOVEMENT_SMALL_MULTIPLIER;
            }
        }
        if (position == RobotPosition::bigOnRightLine) {
            if (mod(0 - LS_MOVEMENT_ANGLE_BUFFER, 360) < orbitAngle && orbitAngle < 180 + LS_MOVEMENT_ANGLE_BUFFER) {
                if (orbitAngle > 90) {
                    angle = 210;
                }
                else {
                    angle = 330;
                }
            }
        }
        if (position == RobotPosition::overRightLine) {
            if (mod(0 - LS_MOVEMENT_ANGLE_BUFFER, 360) < orbitAngle && orbitAngle < 180 + LS_MOVEMENT_ANGLE_BUFFER) {
                angle = 270;
            }
        }
        if (position == RobotPosition::smallOnBackLine) {
            if (90 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle && orbitAngle < 270 + LS_MOVEMENT_ANGLE_BUFFER) {
                angle = orbitAngle;
                speed =  (int) slaveData.orbitSpeed * LS_MOVEMENT_SMALL_MULTIPLIER;
            }
        }
        if (position == RobotPosition::bigOnBackLine) {
            if (90 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle && orbitAngle < 270 + LS_MOVEMENT_ANGLE_BUFFER) {
                if (orbitAngle > 180) {
                    angle = 300;
                }
                else {
                    angle = 60;
                }
            }
        }
        if (position == RobotPosition::overFrontLine) {
            if (315 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < 45 + LS_MOVEMENT_ANGLE_BUFFER) {
                angle = 0;
            }
        }
        if (position == RobotPosition::smallOnLeftLine) {
            if (180 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < 0 + LS_MOVEMENT_ANGLE_BUFFER) {
                angle = orbitAngle;
                speed =  (int) slaveData.orbitSpeed * LS_MOVEMENT_SMALL_MULTIPLIER;
            }
        }
        if (position == RobotPosition::bigOnLeftLine) {
            if (180 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < 0 + LS_MOVEMENT_ANGLE_BUFFER) {
                if (orbitAngle > 270) {
                    angle = 30;
                }
                else {
                    angle = 150;
                }
            }
        }
        if (position == RobotPosition::overLeftLine) {
            if (180 - LS_MOVEMENT_ANGLE_BUFFER < orbitAngle || orbitAngle < 0 + LS_MOVEMENT_ANGLE_BUFFER) {
                angle = 90;
            }
        }
    }
    // NEED TO DO CORNERS
    MoveData data = MoveData(angle, speed, rotation);
    return data;
    // TODO
}

void getSlaveData() {
    dataOutTsop[0] = SPI_TSOP_ANGLE;
    spi.txrx16(dataOutTsop, dataInTsop, DATA_LENGTH_TSOP, CTAR_0, MASTER_CS_TSOP);
    int orbitAngle = dataInTsop[0];

    dataOutTsop[0] = SPI_TSOP_SPEED;
    spi.txrx16(dataOutTsop, dataInTsop, DATA_LENGTH_TSOP, CTAR_0, MASTER_CS_TSOP);
    int orbitSpeed = dataInTsop[0];

    spi.txrx16(dataOutLight, dataInLight, DATA_LENGTH_LIGHT, CTAR_0, MASTER_CS_LIGHT);

    slaveData = SlaveData(static_cast<LinePosition>((int) dataInLight[0]), orbitAngle, orbitSpeed);
}


void loop() {
    getSlaveData();
    imu.updateGyro();

    #if DEBUG_APP_IMU
    debug.appSendIMU(imu.heading);
    #endif

    position = calculateRobotPosition(slaveData.linePosition, previousPosition);
    MoveData movement = calculateMovement();
    previousPosition = position;

    // Serial.println(position);
    // Serial.println(slaveData.linePosition);
    // Serial.println(movement.angle);
    // Serial.println();

    motors.move(movement.angle, movement.rotation, movement.speed);
}
