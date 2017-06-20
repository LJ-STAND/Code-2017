#ifndef LIGHT_SENSOR_CLUSTER_H
#define LIGHT_SENSOR_CLUSTER_H

#include <Arduino.h>
#include <LJSTANDCommon.h>
#include <Config.h>

class LightSensorCluster {
public:
    LightSensorCluster() {}
    LightSensorCluster(double clusterCentre, int clusterLength);

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
};

#endif // LIGHT_SENSOR_CLUSTER_H
