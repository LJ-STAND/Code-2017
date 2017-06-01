#ifndef LIGHT_SENSOR_CLUSTER_H
#define LIGHT_SENSOR_CLUSTER_H

#include <Arduino.h>

class LightSensorCluster {
public:
    LightSensorCluster() {}
    LightSensorCluster(double centre, int length);

    int getQuadrants();
    Vector2D getCoordinates();
}

#endif // LIGHT_SENSOR_CLUSTER_H
