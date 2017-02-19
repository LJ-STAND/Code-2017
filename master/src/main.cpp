/*
 * MASTER
 *
 * Source file for the master teensy for LJ STAND
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

void setup() {
    // I2C
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
    Wire.setDefaultTimeout(200000);

    // Serial
    Serial.begin(9600);
    Bluetooth::init();

    // SPI
    spi.begin_MASTER(MASTER_SCK, MASTER_MOSI, MASTER_MISO, MASTER_CS_TSOP, CS_ActiveLOW);
    spi.setCTAR(CTAR_0, 16, SPI_MODE0, LSB_FIRST, SPI_CLOCK_DIV16);
    spi.enableCS(MASTER_CS_LIGHT, CS_ActiveLOW);

    // Onboard LED
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    // IMU
    imu.init();
    imu.calibrate();

    debug.init();
    debug.toggleAllLEDs(true);
}

int calculateRotationCorrection() {
    double relativeHeading = 180.0 - (doubleMod((imu.heading + imu.facingDirection) + 180, 360));
    int rotationCorrection;

	if (abs(relativeHeading > IMU_THRESHOLD)) {
		rotationCorrection = (int) relativeHeading;

		if (rotationCorrection < 0 && rotationCorrection > -CORRECTION_ROTATION_MINIMUM) {
			rotationCorrection = -CORRECTION_ROTATION_MINIMUM;
		} else if (rotationCorrection > 0 && rotationCorrection < CORRECTION_ROTATION_MINIMUM) {
			rotationCorrection = CORRECTION_ROTATION_MINIMUM;
		} else if (rotationCorrection > 0 && rotationCorrection > CORRECTION_ROTATION_MAXIMUM) {
			rotationCorrection = CORRECTION_ROTATION_MAXIMUM;
		} else if (rotationCorrection < 0 && rotationCorrection < -CORRECTION_ROTATION_MAXIMUM) {
			rotationCorrection = -CORRECTION_ROTATION_MAXIMUM;
		}
	} else {
		rotationCorrection = 0;
	}

	return rotationCorrection;
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
    Serial.println(String(slaveData.orbitAngle) + ", " + String(slaveData.orbitSpeed));
}
