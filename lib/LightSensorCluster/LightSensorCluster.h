#ifndef LIGHT_SENSOR_CLUSTER_H
#define LIGHT_SENSOR_CLUSTER_H

#include <Arduino.h>
#include <LJSTANDCommon.h>
#include <Config.h>

class LightSensorCluster {
public:
    LightSensorCluster() {}

    // These constructors are very similar. Be careful when calling!
    LightSensorCluster(double clusterCentre, int clusterLength);
    LightSensorCluster(int leftSensor, int rightSensor);

    void addCluster(LightSensorCluster cluster);

    void addSensorClockwise();

    int getQuadrants();
    Vector2D getCoordinates();

    int getLeftSensor();
    int getRightSensor();

    double getCentre();
    int getLength();

private:
    double centre;
    int length;
    int leftSensor;
    int rightSensor;

    void updateLeftRight() {
        leftSensor = mod(centre - ((length - 1) / 2.0), LS_NUM);
        rightSensor = mod(centre + ((length - 1) / 2.0), LS_NUM);
    }

    void updateLengthCentre() {
        if (leftSensor > rightSensor) {
            centre = doubleMod((-(LS_NUM - leftSensor) + rightSensor) / 2.0, LS_NUM);
            length = (LS_NUM - (leftSensor - rightSensor)) + 1;
        } else {
            centre = (leftSensor + rightSensor) / 2.0;
            length = (rightSensor - leftSensor) + 1;
        }
    }
};

#endif // LIGHT_SENSOR_CLUSTER_H
