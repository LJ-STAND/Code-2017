#include "LightSensorCluster.h"

LightSensorCluster::LightSensorCluster(double clusterCentre, int clusterLength) {
    centre = clusterCentre;
    length = clusterLength;

    leftSensor = mod(centre - (length - 1) / 2.0, LS_NUM);
    rightSensor = mod(centre + (length - 1) / 2.0, LS_NUM);
}

LightSensorCluster::LightSensorCluster(int left, int right) {
    if (left > 12 && right < 12) {
        centre = mod((right + mod(left + 12, LS_NUM))/ 2.0 - 6, LS_NUM);
    } else {
        centre = (right + left) / 2.0;
    }
    length = (mod(right - left, LS_NUM)) / 2.0 + 1;

    leftSensor = left;
    rightSensor = right;
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
    LightSensorCluster newCluster = LightSensorCluster((double)mod(getRightSensor() + 1, LS_NUM), 1);
    addCluster(newCluster);
}

void LightSensorCluster::addCluster(LightSensorCluster cluster) {
    int leftOther = cluster.getLeftSensor();
    int rightOther = cluster.getRightSensor();
    int lengthOther = cluster.getLength();

    if (mod(rightSensor + 1, LS_NUM) == leftOther) {
        centre = LightSensorCluster(leftSensor, rightOther).getCentre();
    } else if (mod(rightOther + 1, LS_NUM) == leftSensor) {
        centre = LightSensorCluster(leftOther, rightSensor).getCentre();
    } else {
        // We're adding two non-adjacent clusters so we just do not apply any changes to the cluster.
        return;
    }

    length += lengthOther;
}

int LightSensorCluster::getLeftSensor() {
    // Note: left is the counterclockwise boundary because its easier to write.
    return leftSensor;
}

int LightSensorCluster::getRightSensor() {
    // Note: left is the counterclockwise boundary because its easier to write.
    return rightSensor;
}

double LightSensorCluster::getCentre() {return centre;}

int LightSensorCluster::getLength() {return length;}
