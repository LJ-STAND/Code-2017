#include "IMU.h"

void IMU::init() {
    I2CwriteByte(MPU9250_ADDRESS, 29, 0x06);
    I2CwriteByte(MPU9250_ADDRESS, 26, 0x06);
    I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_500_DPS);
    I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_2_G);
    I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);
    I2CwriteByte(MAG_ADDRESS, 0x0A, 0x16);

    previousTime = micros();
};

Vector3D IMU::readAccelerometer() {
    uint8_t buffer[14];
    I2Cread(MPU9250_ADDRESS, 0x3B, 14, buffer);

    int16_t ax = -(buffer[0] << 8 | buffer[1]);
    int16_t ay = -(buffer[2] << 8 | buffer[5]);
    int16_t az = buffer[4] << 8 | buffer[5];

    Vector3D returnVector = {convertRawAcceleration(ax), convertRawAcceleration(ay), convertRawAcceleration(az)};
    return returnVector;
}

Vector3D IMU::readGyroscope() {
    uint8_t buffer[14];
    I2Cread(MPU9250_ADDRESS, 0x3B, 14, buffer);

    int16_t gx = -(buffer[8] << 8 | buffer[1]);
    int16_t gy = -(buffer[10] << 8 | buffer[11]);
    int16_t gz = buffer[12] << 8 | buffer[13];

    Vector3D returnVector = {convertRawGyro(gx), convertRawGyro(gy), convertRawGyro(gz)};
    return returnVector;
}

Vector3D IMU::readMagnetometer() {
    uint8_t status1;
    do {
        I2Cread(MAG_ADDRESS, 0x02, 1, &status1);
    } while (!(status1 & 0x01));

    uint8_t mag[7];
    I2Cread(MAG_ADDRESS, 0x03, 7, mag);

    int16_t mx = -(mag[3] << 8 | mag[2]);
    int16_t my = -(mag[1] << 8 | mag[0]);
    int16_t mz = -(mag[5] << 8 | mag[4]);

    Vector3D returnVector = {(double) mx, (double) my, (double) mz};
    return returnVector;
}

void IMU::updateGyro() {
    double reading = (double) readGyroscope().z;

	long currentTime = micros();
    heading += (((double)(currentTime - previousTime) / 1000000.0) * (reading - calibration));
	heading = doubleMod(heading, 360.0);

	previousTime = currentTime;
}

double IMU::calibrate() {
    readGyroscope();

    delay(IMU_CALIBRATION_TIME);

    double reading = (double) readGyroscope().z;
    calibration = reading;

    return reading;
}

// TODO: Move to main.cpp
// double IMU::relativeHeading() {
//     return 180.0 - (doubleMod((heading + facingDirection) + 180, 360));
// }
//
// int IMU::correctionRotation() {
//     int correctionRotation;
//
// 	if (abs(relativeHeading()) > IMU_THRESHOLD) {
// 		correctionRotation = (int) relativeHeading();
//
// 		if (correctionRotation < 0 && correctionRotation > -CORRECTION_ROTATION_MINIMUM) {
// 			correctionRotation = -CORRECTION_ROTATION_MINIMUM;
// 		} else if (correctionRotation > 0 && correctionRotation < CORRECTION_ROTATION_MINIMUM) {
// 			correctionRotation = CORRECTION_ROTATION_MINIMUM;
// 		} else if (correctionRotation > 0 && correctionRotation > CORRECTION_ROTATION_MAXIMUM) {
// 			correctionRotation = CORRECTION_ROTATION_MAXIMUM;
// 		} else if (correctionRotation < 0 && correctionRotation < -CORRECTION_ROTATION_MAXIMUM) {
// 			correctionRotation = -CORRECTION_ROTATION_MAXIMUM;
// 		}
// 	} else {
// 		correctionRotation = 0;
// 	}
//
// 	return correctionRotation;
// }
