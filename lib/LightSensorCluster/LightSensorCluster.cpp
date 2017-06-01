#include "LightSensorCluster.h"

LightSensorCluster::LightSensorCluster(double clusterCentre, int clusterLength) {
    centre = clusterCentre;
    length = clusterLength;
}

void LightSensorCluster::addSensorClockwise() {
    centre += 0.5;
    length += 1;
}
