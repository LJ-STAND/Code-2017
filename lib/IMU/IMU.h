#ifndef COMPASS_H
#define COMPASS_H

#include <I2C.h>
#include <Vector3D.h>
#include <LJSTANDCommon.h>
#include <Config.h>

class IMU {
public:
    double heading;
    double facingDirection;

    IMU() {};
    void init();

    Vector3D readAccelerometer();
    Vector3D readGyroscope();
    Vector3D readMagnetometer();

    void updateGyro();
    double calibrate();

private:
    long previousTime;
    double calibration;

    double convertRawAcceleration(int raw) {
        // Since we are using 2G range
        // -2g maps to a raw value of -32768
        // +2g maps to a raw value of 32767

        double a = (raw * 2.0) / 32768.0;
        return a;
    }

    double convertRawGyro(int raw) {
        // Since we are using 500 degrees/seconds range
        // -500 maps to a raw value of -32768
        // +500 maps to a raw value of 32767

        double g = (raw * 500.0) / 32768.0;
        return g;
    }
};

#endif
