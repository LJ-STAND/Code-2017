#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

class LightSensor {
public:
    LightSensor() {}
    LightSensor(int in);
    void calibrate();

    int read();
    bool isOnWhite();

private:
    int inPin;
    int thresholdValue;
};

#endif // LIGHT_SENSOR_H
