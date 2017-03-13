#ifndef COMPASS_H
#define COMPASS_H

#include <I2C.h>
#include <Vector3D.h>
#include <Vector2D.h>
#include <LJSTANDCommon.h>
#include <Config.h>

class IMU {
public:
    double heading;
    Vector2D velocity;
    Vector2D position;

    IMU() {};
    void init();

    Vector3D readAccelerometer();
    Vector3D readGyroscope();
    Vector3D readMagnetometer();

    void updateGyro();
    void updateAccelerometer();
    void update();
    void calibrate();

private:
    long previousTimeGyro;
    long previousTimeAccel;
    double calibrationGyro;
    double calibrationAccelX;
    double calibrationAccelY;

    double convertRawAcceleration(int raw) {
        // Since we are using 2G range
        // -2g maps to a raw value of -32768
        // +2g maps to a raw value of 32767

        double a = (raw * 2.0) / 32768.0;
        return a;
    }

    double convertRawGyro(int raw) {
        // Since we are using 1000 degrees/seconds range
        // -1000 maps to a raw value of -32768
        // +1000 maps to a raw value of 32767

        double g = (raw * 1000.0) / 32768.0;
        return g;
    }
};

#endif
