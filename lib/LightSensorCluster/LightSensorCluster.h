#ifndef LIGHT_SENSOR_CLUSTER_H
#define LIGHT_SENSOR_CLUSTER_H

#include <Arduino.h>
#include <LjstandCommon.h>

class LightSensorCluster {
public:
    LightSensorCluster() {}
    LightSensorCluster(double clusterCentre, int clusterLength);

    void addSensorClockwise();

    int getQuadrants();
    Vector2D getCoordinates();

private:
    double centre;
    int length;
};

#endif // LIGHT_SENSOR_CLUSTER_H
