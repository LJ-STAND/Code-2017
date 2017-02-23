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
    int rotation = (imu.heading > 180 ? 360 : 0) - imu.heading;
    if (abs(rotation) < CORRECTION_ROTATION_MAXIMUM){
        return rotation;
    }
    return (rotation > 0 ? CORRECTION_ROTATION_MAXIMUM : -CORRECTION_ROTATION_MAXIMUM);
    // double relativeHeading = 180.0 - (doubleMod((imu.heading + imu.facingDirection) + 180, 360));
    // int rotationCorrection;
    //
	// if (abs(relativeHeading > IMU_THRESHOLD)) {
	// 	rotationCorrection = (int) relativeHeading;
    //
	// 	if (rotationCorrection < 0 && rotationCorrection > -CORRECTION_ROTATION_MINIMUM) {
	// 		rotationCorrection = -CORRECTION_ROTATION_MINIMUM;
	// 	} else if (rotationCorrection > 0 && rotationCorrection < CORRECTION_ROTATION_MINIMUM) {
	// 		rotationCorrection = CORRECTION_ROTATION_MINIMUM;
	// 	} else if (rotationCorrection > 0 && rotationCorrection > CORRECTION_ROTATION_MAXIMUM) {
	// 		rotationCorrection = CORRECTION_ROTATION_MAXIMUM;
	// 	} else if (rotationCorrection < 0 && rotationCorrection < -CORRECTION_ROTATION_MAXIMUM) {
	// 		rotationCorrection = -CORRECTION_ROTATION_MAXIMUM;
	// 	}
	// } else {
	// 	rotationCorrection = 0;
	// }
    //
	// return rotationCorrection;
}

MoveData calculateMovement() {
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

    // Serial.println(slaveData.orbitAngle);

    // motors.move(slaveData.orbitAngle, CORRECTION_ROTATION_MULTIPLIER * calculateRotationCorrection(), (slaveData.orbitAngle != -1 ? 255 : 0));
    motors.move(0, 0, 255);

}
