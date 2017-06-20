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
    int leftSensor, rightSensor;
};

#endif // LIGHT_SENSOR_CLUSTER_H
