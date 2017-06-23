#include "LightSensorCluster.h"

LightSensorCluster::LightSensorCluster(double clusterCentre, int clusterLength) {
    centre = clusterCentre;
    length = clusterLength;

    updateLeftRight();
}

LightSensorCluster::LightSensorCluster(int left, int right) {
    leftSensor = left;
    rightSensor = right;

    updateLengthCentre();
}

int LightSensorCluster::getQuadrants() {
    /* 1 digit:
     * 1 = front right
     * 2 = back right
     * 3 = back left
     * 4 = front left
     * 2 digits:
     * same as 1 digit for each separate digit
     * e.g. 23 = back right and back left
     * centre 0 length 1 is considered 41 etc. */

     int leftSensor = getLeftSensor();
     int rightSensor = getRightSensor();

     if (0 < leftSensor && rightSensor < 6) {
         return 1;
     } else if (6 < leftSensor && rightSensor < 12) {
         return 2;
     } else if (12 < leftSensor && rightSensor < 18) {
         return 3;
     } else if (18 < leftSensor && 18 < rightSensor) {
         return 4;
     } else {
         if (0 < leftSensor && rightSensor < 12) {
             return 12;
         } else if (6 < leftSensor && rightSensor < 18) {
             return 23;
         } else if (12 < leftSensor && 18 <= rightSensor) {
             return 34;
         } else if ((18 < leftSensor || leftSensor == 0) && rightSensor < 6) {
             return 41;
         } else {
             if (0 < leftSensor && rightSensor < 18) {
                 return 123;
             } else if (6 < leftSensor && 18 <= rightSensor) {
                 return 234;
             } else if (12 < leftSensor && rightSensor < 6) {
                 return 341;
             } else if ((18 < leftSensor || leftSensor == 0) && rightSensor < 12) {
                 return 412;
             }
         }
     }

}

void LightSensorCluster::addSensorClockwise() {
    rightSensor = mod(rightSensor + 1, LS_NUM);

    updateLengthCentre();
}

void LightSensorCluster::addCluster(LightSensorCluster cluster) {
    int leftOther = cluster.getLeftSensor();
    int rightOther = cluster.getRightSensor();

    if (mod(rightSensor + 1, LS_NUM) == leftOther) {
        rightSensor = rightOther;
    } else if (mod(rightOther + 1, LS_NUM) == leftSensor) {
        leftSensor = leftOther;
    } else {
        // We're adding two non-adjacent clusters so we just do not apply any changes to the cluster.
        return;
    }

    updateLengthCentre();
}

int LightSensorCluster::getLeftSensor() {
    // Note: left is the counterclockwise boundary because its easier to write.
    return leftSensor;
}

int LightSensorCluster::getRightSensor() {
    // Note: right is the clockwise boundary because its easier to write.
    return rightSensor;
}

double LightSensorCluster::getCentre() {
    return centre;
}

int LightSensorCluster::getLength() {
    return length;
}

double LightSensorCluster::getAngle() {
    return centre / 24.0 * 360;
}

double LightSensorCluster::getLeftAngle() {
    return leftSensor / 24.0 * 360;
}

double LightSensorCluster::getRightAngle() {
    return rightSensor / 24.0 * 360;
}
